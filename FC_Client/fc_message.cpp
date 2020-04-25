#include "fc_message.h"
#include <cstdlib>
#include <cstring>

//==============================================
//  public function
//==============================================

FC_Message::FC_Message()
{
//    this->_header_length = FC_MESSAGE_HEADER_LENGTH;
//    this->_body_length = 0;
//    this->_message_type = 0;
    this->_data = (char *)malloc(FC_MESSAGE_HEADER_LENGTH+1);
    memset(this->_data,'\0',FC_MESSAGE_HEADER_LENGTH+1);
}
FC_Message::FC_Message(const FC_Message& msg){
    this->_data = (char *)malloc(header_length());
    memcpy(this->_data,msg._data,header_length());
    this->set_body_length(this->body_length());
    memcpy(this->_data,msg._data,mess_length());
}
FC_Message::~FC_Message(){
    free(this->_data);
}

//getter
unsigned FC_Message::header_length()const{
    return FC_MESSAGE_HEADER_LENGTH;
}
unsigned FC_Message::body_length()const{
    unsigned body_length = 0;
    memcpy(&body_length,this->_data+sizeof (unsigned),sizeof (unsigned));
    return body_length;
}
unsigned FC_Message::mess_length()const{
    return this->header_length()+body_length();
}
unsigned FC_Message::mess_type()const{
    unsigned mess_type=0;
    memcpy(&mess_type,this->_data,sizeof (mess_type));
    return mess_type;
}
char* FC_Message::header()const{
    return this->_data;
}
char* FC_Message::body()const{
    return this->_data+FC_MESSAGE_HEADER_LENGTH;
}

//setter
void FC_Message::set_body_length(unsigned body_len){
    memcpy(this->_data+sizeof (unsigned),&body_len,sizeof (unsigned));
    this->apply_memory(this->mess_length());
}
void FC_Message::set_message_type(unsigned type){
    memcpy(this->_data,&type,sizeof (type));
}
void FC_Message::set_body(const char*data,unsigned len){
//    this->apply_memory(this->mess_length()); //lazy fetch
    memcpy(this->_data+sizeof (unsigned)*2,data,len);
}

void FC_Message::reset_message(){ //reset this message
    this -> set_message_type(0);
    this -> set_body_length(0);
}

//==============================================
//  private function
//==============================================

void FC_Message::apply_memory(unsigned len){ //apply for new memory
    //apply new memory for message_body
    char *tmp = (char *)malloc(len);
    memset(tmp,0,len);
    memcpy(tmp,this->_data,FC_MESSAGE_HEADER_LENGTH);
    free(this->_data);
    this->_data = tmp;
}
