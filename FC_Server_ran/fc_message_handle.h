#ifndef FC_MESSAGE_HANDLE_H
#define FC_MESSAGE_HANDLE_H

#include <cstdlib>

class FC_Message;
class FC_Server;
class FC_Connection;

class FC_Message_Handle
{
public:
    FC_Message_Handle(FC_Server* server,FC_Connection *connection );
    //handle recv message
    void handle_header(FC_Message*);
    void handle_body(FC_Message*);
    //handle send message
    FC_Message* generate_message(unsigned type,const char* content,char* account,char*s_account);
private:
    void handle_ordinary_msg(FC_Message*);
    void handle_sign_in(const char* s);
    void handle_text_msg(FC_Message*);
private:
    FC_Server* _server = nullptr;
    FC_Connection *_connection = nullptr;
};

#endif // FC_MESSAGE_HANDLE_H
