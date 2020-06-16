#ifndef FC_MESSAGE_HANDLE_H
#define FC_MESSAGE_HANDLE_H

#include <cstdlib>
#include <iostream>

using namespace std;

class FC_Message;
class FC_Server;
class FC_Connection;
class DbBroker;

class FC_Message_Handle
{
public:
    FC_Message_Handle(FC_Server* server,FC_Connection *connection );
    //handle recv message
    void handle_header(FC_Message*);
    void handle_body(FC_Message*);
    //handle send message
    FC_Message* generate_message(unsigned type,const char* content,char* account,char*s_account);

    //about json message
    void send_self_msg(const string& username);
    void send_friends_lists(const string& username);

    //about json operation
    string make_json(string username);
    string make_json_user(const string& username);

    //profile
    void update_nick(const char* s);
    void update_gender(const char* s);

    //friends message
     void friends_search_handle(const char* s);//好友查找处理
     void add_friends(FC_Message* msg);
     void add_friends_lists(FC_Message* msg);
     void delete_friend(FC_Message* msg);
     void handle_remark(const char* s);

     //handle offline
     void handle_offlineM(const string& acc);

private:
    void handle_ordinary_msg(FC_Message*);
    void handle_sign_in(const char* s);
    void handle_text_msg(FC_Message*);

    string handle_user_head(const string& filepath);
private:
//    DbBroker* _broker = nullptr;
    FC_Server* _server = nullptr;

    FC_Connection *_connection = nullptr;
};

#endif // FC_MESSAGE_HANDLE_H
