#include "fc_message.h"
#include <cstdlib>
#include <cstring>

//==============================================
//  public function
//==============================================

FC_Message::FC_Message()
{
    this->_data = (char *)malloc(FC_MESSAGE_HEADER_LENGTH+1);
    memset(this->_data,'\0',FC_MESSAGE_HEADER_LENGTH+1);
}
FC_Message::FC_Message(const FC_Message& msg){
    this->_data = (char *)malloc(header_length());
    memcpy(this->_data,msg._data,header_length());
    //set_header()同时分配message需要的空间
    this->set_header(this->mess_type(),this->body_length(),this->userAccount(),this->pawdOrSuserId());
    memcpy(this->_data,msg._data,mess_length());
    //delete this->userAccount();
    //delete this->pawdOrSuserId();
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

char* FC_Message::userAccount() const
{
    char* userAccount=(char*)malloc(8);
    memcpy(userAccount,this->_data+sizeof(unsigned)*2,sizeof(unsigned)*2);
    return userAccount;
}

char *FC_Message::pawdOrSuserId() const
{
    char*pu =(char*)malloc(8);
    memcpy(pu,this->_data+sizeof(unsigned)*4,sizeof (unsigned)*2);
    return pu;
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
void FC_Message::set_header(unsigned type,unsigned int body_len,const char *userId,const char* pu){
    memcpy(this->_data,&type,sizeof(unsigned));
    memcpy(this->_data+sizeof (unsigned),&body_len,sizeof (unsigned));
    memcpy(this->_data+sizeof(unsigned)*2,userId,sizeof(unsigned)*2);
    memcpy(this->_data+sizeof(unsigned)*4,pu,sizeof(unsigned)*2);
    this->apply_memory(this->mess_length());
}
void FC_Message::set_message_type(unsigned type){
    memcpy(this->_data,&type,sizeof (type));
}
void FC_Message::set_body(const char*data,unsigned len){
//    this->apply_memory(this->mess_length()); //lazy fetch
    memcpy(this->_data+sizeof (unsigned)*6,data,len);
}
//存放用户ID,8字节
void FC_Message::set_userAccount(const char *data)
{
    memcpy(this->_data+sizeof (unsigned)*2,data,sizeof(unsigned)*2);
}

//存放接受消息的用户ID或用户密码
void FC_Message::set_pawdOrSuserId(const char *data)
{
    memcpy(this->_data+sizeof (unsigned)*4,data,sizeof(unsigned)*2);
}
void FC_Message::reset_message(){ //reset this message
    this -> set_message_type(0);
    this -> set_header(0,0,"00000000","00000000");
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
