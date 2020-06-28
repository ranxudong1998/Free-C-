#include "fc_message_listmodel.h"
#include "fc_message_instance.h"
#include "fc_client.h"
#include "fc_instance_handle.h"
#include "fc_chat_listmodel.h"
#include <QDebug>
#include <fstream>
#include <filesystem>
#include <string>

namespace fs =std::filesystem ;

//==============================================
//  public function
//==============================================


FC_Message_ListModel::FC_Message_ListModel(FC_Client*client, QObject* parent)
    :QAbstractListModel(parent),_client(client)
{

    _instace = new FC_Message_Instance(_client);
    _chat_listModel = new FC_Chat_ListModel(_client);
    QVector<QVector<QString>> tmp;
    _all_mess.insert("@12345",tmp);
    _all_mess.insert("@24567",tmp);
    _all_mess.insert("@23456",tmp);
    _all_mess.insert("@13456",tmp);

    //群ID:
    _all_mess.insert("@56789",tmp);

}
FC_Message_ListModel::~FC_Message_ListModel(){
    delete this->_instace;
}

MsgVector::iterator FC_Message_ListModel::handle_own_msg(QVector<QString> content)
{
    qDebug()<<"key date:"<<content.at(0)+content.at(1);
    MsgVector::iterator iter =this->_all_mess.find(content.at(1));  //检索key
    iter.value().push_back(content);

    return iter;
}


MsgVector::iterator FC_Message_ListModel::handle_recv_msg(QVector<QString> content)
{
    qDebug()<<"key date:"<<content.at(0)+content.at(1);
    MsgVector::iterator iter =this->_all_mess.find(content.at(0));  //检索key
    iter.value().push_back(content);

    return iter;
}


void FC_Message_ListModel::add_msg_to_socket(QVector<QString> content)
{
    this->_instace->add_msg_to_socket(content);
}

QString FC_Message_ListModel::get_head_path(QString id)
{

    fs::path p = fs::current_path(); //目的是为了得到绝对路径
    std::string tmpAccount = id.toStdString();
    std::string path = "file://"+p.string()+"/assert/"+tmpAccount+".jpg";
    QString headpath = QString::fromLocal8Bit(path.c_str());
    return headpath;
}

//override function
QVariant FC_Message_ListModel::data(const QModelIndex &index, int role ) const{ //index and role data
    return this->_instace->data(index.row(),role);
}
//函数返回模型中的项目总数
int FC_Message_ListModel::rowCount(const QModelIndex &) const{//row count
    return this->_instace->rowCount();
}

QHash<int, QByteArray> FC_Message_ListModel::roleNames() const{
    return this->_instace->roleNames();
}


//transfer function
void FC_Message_ListModel::add(QVector<QString> content){// display to socket
    add_msg_to_socket(content); //传送给了服务端
    QString tmpPathLeft= get_head_path(content.at(1));
    QString tmpPathRight = get_head_path(content.at(0));
    content.push_back(tmpPathLeft);         //添加对应头像路径
    content.push_back(tmpPathRight);
    content.push_back("0"); //设置可见还是不可见
    handle_own_msg(content);

    beginInsertRows(QModelIndex(),rowCount(),rowCount());
    //消息直接在UI上打印
    this->_instace->add(content);
    endInsertRows();
    emit recv_mess();
}
void FC_Message_ListModel::recv(QVector<QString> content){// socket to display

    //添加对应头像路径
    //这里也可以直接调用 好友列表的接口，不需要自己重新获取头像路径
    QString tmpPathLeft= get_head_path(content.at(0));
    QString tmpPathRight = get_head_path(content.at(1));
    content.push_back(tmpPathLeft);
    content.push_back(tmpPathRight);
    content.push_back("1");
    handle_recv_msg(content);
    //检测是否为当前聊天信息
    if(content.at(0) !=this->currentChatId()){
        return;
    }
    beginInsertRows(QModelIndex(),rowCount(),rowCount());
    //消息直接在UI上打印
    this->_instace->recv(content);
    endInsertRows();
    emit recv_mess();
}

void FC_Message_ListModel::recv_group(QVector<QString> content)
{
    handle_own_msg(content);
    //this->_chat_listModel->handle_last_msg({content.at(0),content.at(3)});
    //检测是否为当前聊天信息
    if(content.at(1) !=this->currentChatId()){
        return;
    }
//    set_msgOpacity(true);
    beginInsertRows(QModelIndex(),rowCount(),rowCount());
    //消息直接在UI上打印
    this->_instace->recv(content);
    endInsertRows();
    emit recv_mess();
}

void FC_Message_ListModel::loadMsg(QString key)
{
    qDebug()<<"key data:"<<key;
    this->_instace->clearMsg();  //清空信息

    qDebug()<<"load key data: "<<key;
    MsgVector:: iterator iter =this->_all_mess.find(key);
    for(int i = 0; i < iter->length();i++){

        //消息直接在UI上打印
        if(iter.value().at(i).at(0) == key){
            //添加对应头像路径
            beginInsertRows(QModelIndex(),rowCount(),rowCount());
            this->_instace->recv(iter.value().at(i));
            endInsertRows();
            emit recv_mess();
        }else {      
            beginInsertRows(QModelIndex(),rowCount(),rowCount());
            this->_instace->add(iter.value().at(i));
            endInsertRows();
            emit recv_mess();
        }
    }

}

QString FC_Message_ListModel::currentChatId() const
{
    return this->_currentChatId;
}

void FC_Message_ListModel::set_currentChatId(QString id)
{
    this->_currentChatId = id;
    loadMsg(id);
}


//bool FC_Message_ListModel::msgOpacity() const
//{
//    return this->_msgOpacity;
//}

//bool FC_Message_ListModel::set_msgOpacity(bool tmp)
//{
//    return this->_msgOpacity = tmp;
//}





