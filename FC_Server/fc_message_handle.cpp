#include "fc_message_handle.h"
#include "fc_message.h"
#include "fc_server.h"
#include "fc_message.h"
#include "fc_header.h"
#include "fc_connection.h"
#include "fc_server.h"
#include <cstring>
#include <QDebug>


//==============================================
//  public function
//==============================================


FC_Message_Handle::FC_Message_Handle(FC_Server* server,FC_Connection *connection )
    :_server(server),_connection(connection){
}

void FC_Message_Handle::handle_header(FC_Message *message){
    message->set_body_length(message->body_length());
}

void FC_Message_Handle::handle_body(FC_Message* message){
    qDebug() << "received "<< message->body();
    int type = message->mess_type();
    //according message type handle message
    if(type&FC_PROFILE){
        if(type & FC_SIGN_IN)
            handle_sign_in(message->body());
    }else if(type & FC_MESSAGES){
        if(type&FC_TEXT_MEG)
            handle_text_msg(message);
    }else{
        qDebug() << "unknow message type:" << message->mess_type();
    }
}

FC_Message* FC_Message_Handle::generate_message(unsigned type,char* content){
    FC_Message* message = new FC_Message;//delete in on_write()
    message->set_message_type(type);
    unsigned msg_size = strlen(content)+1;
    message->set_body_length(msg_size);
    message->set_body(content,msg_size);
    return message;
}

//==============================================
//  private function
//==============================================


void FC_Message_Handle::handle_ordinary_msg(FC_Message* message){

}
void FC_Message_Handle::handle_sign_in(const char* s){
    qDebug() << s << "has singed in";
    this->_server->add_identified(s,this->_connection);
}

void FC_Message_Handle::handle_text_msg(FC_Message* msg){
//    this->_server->forward_message();
    char c[FC_ACC_LEN];
    memcpy(c,msg->body(),FC_ACC_LEN);
    this->_server->forward_message(QString(c),msg);
}
