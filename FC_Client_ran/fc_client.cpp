#include "fc_client.h"
#include "fc_display.h"
#include "fc_thread_pool.h"
#include "fc_connection.h"
#include "fc_profile_handle.h"
#include "fc_buddylist_ctrl.h"
#include "fc_message_handle.h"
#include "fc_header.h"
#include <QDebug>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>
#include <filesystem>

namespace fs = std::filesystem;

using namespace boost::property_tree;
//==============================================
//  public function
//==============================================


FC_Client::FC_Client()
{
    this->_thread_pool = new FC_Thread_Pool;
    this->_connections = new FC_Connection(this);
    this->_buddy_list = new FC_BuddyListCtrl (this); //申请新空间,好友列表控制类

    this->_profile = new FC_Profile(this);
    this->_message_handle = new FC_Message_Handle(this);
    this->_display = new FC_Display(this,_profile);
    this->_display->show(); //show ui
}

FC_Client::~FC_Client(){
    delete this->_display;
    delete this->_thread_pool;
    delete this->_connections;
    delete this->_profile;
    delete this->_message_handle;
    delete  this->_buddy_list;
}

//thread pool about
io_service* FC_Client::get_logic_service(){
    return this->_thread_pool->get_logic_service();
}

void FC_Client::add_msg_to_socket(FC_Message *msg)
{
    this->_connections->write(msg);
}

void FC_Client::add_msg_to_qml(FC_Message *msg)
{
    _message_handle->displaytoQML(msg);
}

//display about
void FC_Client::add_msg_to_socket(std::vector<std::string> msg){

    this->_connections->write(msg);
}

void FC_Client::json_data_parser_self(const string &content)
{
    _profile->parser_json(content);
}

//得到服务端的解析信息

//这个做法不采用
void FC_Client::json_data_parser()
{
    const string file_path = "friends_list.json";
    ptree root;
    ptree items;

    try
    {
        read_json<boost::property_tree::ptree>(file_path,root);
    }
    catch (boost::property_tree::ptree_bad_path& e)
    {
        cout <<"boost::property_tree::ptree_bad_path:"<<e.what();
        exit(0);
    }
    catch (boost::property_tree::ptree_bad_data& e)
    {
        cout <<"boost::property_tree::ptree_bad_data:"<<e.what();
    }

    cout<<root.get<string>("username")<<endl;
    items = root.get_child("group");
    cout<<"items: "<<items.size()<<endl;
    for(ptree::iterator it = begin(items);it != end(items);it++)
    {
        //添加一个项,项的ID为之前数组中分组个数
        int n_id = _buddy_list->GetBuddyTeamCount();
        _buddy_list->AddBuddyTeam(n_id);
        //设置团队名字
        _buddy_list->SetBuddyTeamName(n_id,it->second.get<string>("teamname"));
        ptree item;
        item = it->second.get_child("members");
        cout<<"item: "<<item.size()<<endl;
        for(ptree::iterator lit = begin(item);lit != end(item);lit++)
        {
            //计算该分组中member的值
            int m_id = _buddy_list->GetBuddyItemCount(n_id);
            _buddy_list->AddBuddyItem(n_id,m_id);  //这个

            string acc = lit->second.get<string>("account");
//            //添加一个新成员后，会增加一个成员信息
            _buddy_list->SetBuddyTeamMaxCnt(n_id,m_id+1);
            _buddy_list->SetBuddyItemAccNum(n_id,m_id,acc);
            _buddy_list->SetBuddyItemNickName(n_id,m_id,lit->second.get<string>("nickname"));
            _buddy_list->SetBuddyItemMarkName(n_id,m_id,lit->second.get<string>("markname"));
            _buddy_list->SetBuddyItemSign(n_id,m_id,lit->second.get<string>("sign"));

//            save_user_head(acc,lit->second.get<string>("heading"));

//            fs::path p = fs::current_path(); //目的是为了得到相对路径

//            string path = "file://"+p.string()+"/assert/"+acc+".jpg";
//            _buddy_list->SetBuddyItemHeadPic(n_id,m_id,path);
//            _buddy_list->SetBuddyItemHeadPic(n_id,m_id,lit->second.get<string>("heading"));
            _buddy_list->SetBuddyItemGender(n_id,m_id,lit->second.get<string>("gender"));
        }
    }
    _buddy_list->addBuddyModel();
    //移除这个文件，暂时不移动
    //    remove(file_path.c_str());
}

void FC_Client::parser_friends_json(const string &content)
{
    Json::Reader reader;
    Json::Value root;
    // reader将Json字符串解析到root，root将包含Json里所有子元素
    if (reader.parse(content, root))
    {
        cout<<"root asString():"<<root["username"].asString()<<endl;
        Json::Value items  = root["group"];
        for(int i=0;i<items.size();i++)
        {
            int n_id = _buddy_list->GetBuddyTeamCount();
            _buddy_list->AddBuddyTeam(n_id);
            //设置团队名字
            _buddy_list->SetBuddyTeamName(n_id,items[i]["teamname"].asString());
            cout<<items[i]["teamname"].asString()<<endl;
            Json::Value item = items[i]["members"];
            for(int j=0;j<item.size();j++)
            {
                int m_id = _buddy_list->GetBuddyItemCount(n_id);
                _buddy_list->AddBuddyItem(n_id,m_id);  //这个

                string acc = item[j]["account"].asString();
    //            //添加一个新成员后，会增加一个成员信息
                _buddy_list->SetBuddyTeamMaxCnt(n_id,m_id+1);
                _buddy_list->SetBuddyItemAccNum(n_id,m_id,acc);
                _buddy_list->SetBuddyItemNickName(n_id,m_id,item[j]["nickname"].asString());
                _buddy_list->SetBuddyItemMarkName(n_id,m_id,item[j]["markname"].asString());
                _buddy_list->SetBuddyItemSign(n_id,m_id,item[j]["sign"].asString());

                save_user_head(acc,item[j]["heading"].asString());

                fs::path p = fs::current_path(); //目的是为了得到相对路径

                string path = "file://"+p.string()+"/assert/"+acc+".jpg";
                _buddy_list->SetBuddyItemHeadPic(n_id,m_id,path);
                _buddy_list->SetBuddyItemGender(n_id,m_id,item[j]["gender"].asString());
            }
        }
    }
     _buddy_list->addBuddyModel();
}

void FC_Client::test_data()
{
    cout<<"friends team:"<<_buddy_list->GetBuddyTeamCount()<<endl;
    cout<<"one team is friends num:"<<_buddy_list->GetBuddyItemCount(0)<<endl;
}

void FC_Client::update_nick(const string &nick)
{
    _profile->update_nick(QString::fromStdString(nick));
}

void FC_Client::update_gender(const string &sex)
{
    _profile->update_gender(QString::fromStdString(sex));
}

void FC_Client::setUniqueUserName(string name)
{
    this->uniqueUserName = name;
}

string FC_Client::getUniqueUserName()
{
    return this->uniqueUserName;
}

FC_BuddyListCtrl *FC_Client::get_buddy_list()
{
    return this->_buddy_list;
}
void FC_Client::add_msg_to_display(char* msg){
    QString s = msg;
//    this->_display->recv(s);
}
void FC_Client::add_msg_to_display(std::vector<std::string> msg){ //socket message to display
    this->_display->recv(msg);
}


void FC_Client::forward_message(FC_Message *msg)
{
    this->_connections->write(msg);
    delete msg;

}

void FC_Client::save_user_head(const string &acc,const string& heading)
{
    //保存在配置文件中

    std::string filepath = "./assert/"+acc+".jpg";

    std::ofstream fout(filepath, std::ios::binary);
    if(!fout)
    {
        std::cout<<"open failed";
        exit(0);
    }
    fout.write(heading.data(), heading.size());
    fout.close();
}


//==============================================
//  private function
//==============================================
