#include "fc_message_handle.h"
#include "fc_message.h"
#include "fc_client.h"
#include "fc_header.h"
#include <cstring>
#include <QDebug>
#include<iostream>

//==============================================
//  public function
//==============================================

FC_Message_Handle::FC_Message_Handle(FC_Client* client)
    :_client(client){

}

void FC_Message_Handle::handle_header(FC_Message *message){
    message->set_header(message->mess_type(),message->body_length(),message->userAccount(),
                        message->pawdOrSuserId());  //设置body长度和为message分配空间
    //delete message->userAccount();
   // delete message->pawdOrSuserId();
}

void FC_Message_Handle::handle_body(FC_Message* message){

    std::cout<<"test handle_body()";
    int type = message->mess_type();
    //according message type handle message
    if(type&FC_PROFILE){
    }else if(type & FC_MESSAGES){
        if(type&FC_TEXT_MEG)
            handle_text_msg(message);
    }else{
        qDebug() << "unknow message type:" << message->mess_type();
    }


    message->reset_message();
}

FC_Message* FC_Message_Handle::generate_message(unsigned type,const char* content,const char* account,const char* s_account){
    //use the copy of the content
    //sizeof (a) = strlen(a)+1;
    FC_Message* message = new FC_Message;//delete in on_write()
    //message->set_message_type(type);
    unsigned msg_size = strlen(content)+1;
    message->set_header(type,msg_size,account,s_account);
    message->set_body(content,msg_size);
    return message;
}
//const char * FC_Message_Handle::generate_message_body(unsigned type,const char* content){
//    const char *ret = nullptr;
//    if(type&FC_PROFILE){
//        if(type&FC_SIGN_IN)
//            ret = sign_up_body(content);
//    }else{

//    }
//    return ret;
//}


//generate different message body
const char* FC_Message_Handle::sign_up_body(const char* content){
    return content;
}

const char* FC_Message_Handle::text_body(const char* content){
    int n = strlen(content)+1;
    char * ret = (char*) malloc(n+1);
    memset(ret,'\0',n);
    memcpy(ret,content,strlen(content));
    return ret;
}
//==============================================
//  private function
//==============================================
void FC_Message_Handle::handle_text_msg(FC_Message* msg){
    char s_account[FC_ACC_LEN];
    memcpy(s_account,msg->header()+sizeof (unsigned)*4,FC_ACC_LEN);
    char *content = msg->body();
//    this->_client->add_msg_to_display(content);
    std::vector<std::string> vs;
    vs.push_back(s_account);
    vs.push_back(content);
    this->_client->add_msg_to_display(vs);
}
