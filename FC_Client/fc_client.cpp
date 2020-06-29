#include "fc_client.h"
#include "fc_display.h"
#include "fc_thread_pool.h"
#include "fc_connection.h"
#include "fc_profile_handle.h"
#include "fc_message_handle.h"
#include "fc_header.h"
#include <QDebug>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>
#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;
using namespace std;

using namespace boost::property_tree;
//==============================================
//  public function
//==============================================


FC_Client::FC_Client()
{
    this->_thread_pool = new FC_Thread_Pool;
    this->_connections = new FC_Connection(this);

    this->_message_handle = new FC_Message_Handle (this);
    this->_profile = new FC_Profile(this);
    this->_display = new FC_Display(this,_profile);
    this->_display->show(); //show ui
}

FC_Client::~FC_Client(){
    delete this->_display;
    delete this->_thread_pool;
    delete this->_connections;
    delete this->_message_handle;
    delete this->_profile;
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
    //    _message_handle->displaytoQML(msg);
}

//display about
void FC_Client::add_msg_to_socket(std::vector<std::string> msg){

    this->_connections->write(msg);
}

void FC_Client::add_group_msg_to_display(std::vector<std::string> msg)
{
    this->_display->recv_group_msg(msg);
}

void FC_Client::add_history_to_display(FC_Message *msg)
{
    this->_display->recv_history(msg);
}


void FC_Client::setUniqueUserName(string name)
{
    this->uniqueUserName = name;
}

string FC_Client::getUniqueUserName()
{
    return this->uniqueUserName;
}

void FC_Client::add_msg_to_display(char* msg){
    QString s = msg;
    this->_display->recv(s);
}
void FC_Client::add_msg_to_display(std::vector<std::string> msg){ //socket message to display
    this->_display->recv(msg);
}


void FC_Client::forward_message(FC_Message *msg)
{
    this->_connections->write(msg);
    delete msg;

}

bool FC_Client::save_user_head(const string &acc,const string& heading)
{
    //保存在配置文件中

    std::string filepath = "./assert/"+acc+".jpg";

    std::ofstream fout(filepath, std::ios::binary);
    if(!fout)
    {
        std::cout<<"open failed";
        return false;
//        exit(0);
    }
    fout.write(heading.data(), heading.size());
    fout.close();
    return true;
}

std::string FC_Client::handle_user_head(const std::string &filepath)
{
    // 1. 打开图片文件
    ifstream is(filepath, ifstream::in | ios::binary);

    if(!is.is_open())
    {
        cout<<"open failed"<<endl;
        exit(0);
    }
    // 2. 计算图片长度
    is.seekg(0, is.end);
    int length = is.tellg();
    is.seekg(0, is.beg);
    // 3. 创建内存缓存区
    char * buffer = new char[length];
    // 4. 读取图片
    is.read(buffer, length);
    string content(buffer,length);
    is.close();
    delete [] buffer;
    return content;
}

std::unordered_map<std::string, BuddyItem *> &FC_Client::get_item()
{
    return _items;
}

void FC_Client::set_item(std::string &acc, BuddyItem *item)
{
    _items[acc] = item;
}


//==============================================
//  private function
//==============================================
