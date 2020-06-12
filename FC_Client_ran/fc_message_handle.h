#ifndef FC_MESSAGE_HANDLE_H
#define FC_MESSAGE_HANDLE_H

#include <cstdlib>

class FC_Message;
class FC_Client;

class FC_Message_Handle
{
public:
    FC_Message_Handle(FC_Client* client);
    void handle_header(FC_Message*); //handle message header
    void handle_body(FC_Message*); //handle message body

    static FC_Message* generate_message(unsigned type,const char* content,
                                        const char* account,const char* s_account);//generate a message
//    const char * generate_message_body(unsigned type,const char* contentr);
    const char* sign_up_body(const char* content);
    const char* text_body(const char* content);
private:
    void handle_text_msg(FC_Message* msg);


private:
    FC_Client* _client;
};

#endif // FC_MESSAGE_HANDLE_H
