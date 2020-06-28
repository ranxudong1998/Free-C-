#include "fc_message_handle.h"
#include <QDebug>
#include <QQuickItem>
#include <QQuickView>
#include <memory>
#include <string>
#include <json/json.h>
#include <filesystem>
#include "fc_friends_handle.h"
#include "fc_buddy.h"
#include "fc_profile_handle.h"
#include <iostream>

namespace fs = std::filesystem;
using namespace std;

//控制类 好友模块的




FC_Message_Handle::FC_Message_Handle(FC_Client *client)
    :_client(client)
{
    _friends_handle = new FC_Friends_Handle(client);
    _profile = new FC_Profile (client);
}

FC_Message_Handle::~FC_Message_Handle()
{
    delete _friends_handle;
    delete _profile;
}
void FC_Message_Handle::handle_header(FC_Message *message){
    message->set_body_length(message->body_length());
}

void FC_Message_Handle::handle_body(FC_Message* message){
    unsigned type = message->mess_type();
    //according message type handle message
    if(type&FC_PROFILE){
        switch (type) {
        case FC_SELF_MES:
            //            _client->json_data_parser_self(message->body());
            _profile->parser_json(message->body());
            break;
        case FC_UPDATE_NICK:
            _profile->update_nick(message->body());
            //            _client->update_nick(message->body());
            break;
        case FC_UPDATE_SEX:
            //            _client->update_gender(message->body());
            _profile->update_gender(message->body());
            break;
        default:
            cout<<"没有这样的类型"<<endl;
            break;
        }
    }else if(type & FC_FRIENDS){
        switch (type) {
        case FC_FRIENDS_SEARCH_R:
            std::cout<<"come on result"<<std::endl;
            _friends_handle->displaytoQML(message);
            //show search result
            break;
        case FC_FRIENDS_ADD:
            //QML中显示
            _friends_handle->displaytoQML(message);
            break;
        case FC_FRIENDS_ADD_R:
        {
            _friends_handle->refresh_friends_list(message->body());
            break;
        }
        case FC_FRIENDS_MESSAGE:
        {
            _friends_handle->parser_friends_json(message->body());
            cout<<"_friends_handle->get_item().size()"<<_friends_handle->get_item().size()<<endl;
            break;
        }
        case FC_FRIENDS_TEST:
            std::cout<<"测试数据"<<std::endl;
            break;
        case FC_FRIENDS_REMARK:
            std::cout<<"修改好友备注"<<std::endl;
            //            _friends_handle->update_remark(message->body());
            break;
        default:
            cout<<"好友没有这样的类型"<<endl;
            break;
        }
    }else if(type & FC_MESSAGES ){
        switch (type) {
        case FC_TEXT_MEG:
            handle_text_msg(message);
            break;
        case FC_GROUP_TEXT_MEG:
            handle_group_text_msg(message);
            break;
        }

    }else{
        qDebug() << "unknow message type:" << message->mess_type();
    }
}


void FC_Message_Handle::handle_text_msg(FC_Message* msg){
    char* w_account = new char[7];
    memset(w_account,'\0',7);
    char* m_account =new char[7];
    memset(m_account,'\0',6);
    memcpy(w_account,msg->header()+sizeof (unsigned)*2,FC_ACC_LEN);
    memcpy(m_account,msg->header()+14,FC_ACC_LEN);
    char *content = msg->body()+12;  //消息内容
    std::vector<std::string> vs(3);
    qDebug()<<"w_account: "<< w_account;
    vs.at(0)=w_account;   //消息发送者id
    vs.at(1)=m_account;   //消息接收者id
    vs.at(2)=content;     //消息内容
    this->_client->add_msg_to_display(vs);
    free(w_account);
    free(m_account);
}

void FC_Message_Handle::handle_group_text_msg(FC_Message *msg)
{
    char* w_account = new char[7];
    memset(w_account,'\0',7);
    char* m_account =new char[7];
    memset(m_account,'\0',7);
    memcpy(w_account,msg->header()+sizeof (unsigned)*2,FC_ACC_LEN);
    memcpy(m_account,msg->header()+14,FC_ACC_LEN);
    char *content = msg->body()+12;  //消息内容
    std::vector<std::string> vs(3);
    qDebug()<<"群消息:"<< content;
    vs.at(0)=w_account;   //消息发送者id
    vs.at(1)=m_account;   //消息接收者id
    vs.at(2)=content;     //消息内容
    this->_client->add_group_msg_to_display(vs);
    free(w_account);
    free(m_account);
}
const char* FC_Message_Handle::text_body(const char* content){
    int n = strlen(content)+1;
    char * ret = (char*) malloc(n+1);
    memset(ret,'\0',n);
    memcpy(ret,content,strlen(content));
    return ret;
}

FC_Message* FC_Message_Handle::generate_message(unsigned type,const char* content){
    //use the copy of the content
    //sizeof (a) = strlen(a)+1;
    FC_Message* message = new FC_Message;//delete in on_write()
    //message->set_message_type(type);
    unsigned msg_size = strlen(content)+1;
    message->set_header(type,msg_size);
    message->set_body(content,msg_size);
    return message;
}

