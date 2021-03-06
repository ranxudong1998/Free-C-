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
    FC_Message* generate_message(unsigned type,const char* content);
    //about json message
    void send_self_msg(const string& username);
    void send_friends_lists(const string& username);
    void send_history(const string& userId);

    //about json operation
    string make_json(string username);
    string make_json_user(const string& username);

    //profile
    void update_nick(const char* s);
    void update_gender(const char* s);
    void update_heading(FC_Message* msg);

    //friends message
    void friends_search_handle(const char* s);//好友查找处理
    void add_friends(FC_Message* msg);
    void add_friends_lists(FC_Message* msg);
    void delete_friend(FC_Message* msg);
    void handle_remark(const char* s);

    //handle offline
    void handle_offlineM(const string& acc);
    void handle_group_text_msg(FC_Message*);

    //历史记录
    void store_history(FC_Message* msg,const string& path);
    string get_file_path(FC_Message*msg);
    bool is_file_exist(const std::string& name);  //判断某个历史
private:
    void handle_ordinary_msg(FC_Message*);
    void handle_sign_in(const char* s);
    void handle_register(FC_Message* msg);
    void handle_text_msg(FC_Message*);
    void handle_file_msg(FC_Message* msg);

    string random_account();


    string handle_user_head(const string& filepath);
    bool save_user_head(const std::string& acc,const string& heading);


private:
    //    DbBroker* _broker = nullptr;
    FC_Server* _server = nullptr;

    FC_Connection *_connection = nullptr;
};

#endif // FC_MESSAGE_HANDLE_H
