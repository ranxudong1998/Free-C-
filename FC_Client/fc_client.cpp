#include "fc_client.h"
#include "fc_display.h"
#include "fc_thread_pool.h"
#include "fc_connection.h"
#include "fc_profile.h"
#include "fc_message_handle.h"
#include "fc_header.h"
#include <QDebug>

//==============================================
//  public function
//==============================================


FC_Client::FC_Client()
{
    this->_thread_pool = new FC_Thread_Pool;
    this->_connections = new FC_Connection(this);
    this->_profile = new FC_Profile(this);
    this->_message_handle = new FC_Message_Handle(this);
    this->_display = new FC_Display(this,_profile);
    this->_display->show(); //show ui
}

FC_Client::~FC_Client(){
//    qDebug() <<"FC_Client::~FC_Client()\n";
    //DO NOT CHANGE THIS SEQUENCE
    delete this->_display;
    delete this->_thread_pool;
    delete this->_connections;
    delete this->_profile;
    delete this->_message_handle;
}

//thread pool about
io_service* FC_Client::get_logic_service(){
    return this->_thread_pool->get_logic_service();
}

//display about
void FC_Client::add_msg_to_socket(std::vector<std::string> msg){
    this->_connections->write(msg);
}
void FC_Client::add_msg_to_display(char* msg){
    QString s = msg;
    this->_display->recv(s);
}
void FC_Client::add_msg_to_display(std::vector<std::string> msg){ //socket message to display
    this->_display->recv(msg);
}

//profile about
void FC_Client::send_account(string s){
    int type = FC_SIGN_IN;
    const char* content = this->_message_handle->sign_up_body(s.c_str());
    FC_Message* msg = FC_Message_Handle::generate_message(type,content);
    this->_connections->write(msg);
}


//==============================================
//  private function
//==============================================
