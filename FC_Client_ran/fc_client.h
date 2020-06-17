#ifndef FC_CLIENT_H
#define FC_CLIENT_H

#include <boost/thread.hpp>
#include <boost/asio.hpp>
#include <string>
#include <json/json.h>

using boost::thread;
using std::string;
using boost::asio::io_service;

class FC_Connection;
class FC_Display;
class FC_Thread_Pool;
class FC_Profile;
class FC_Message;
class FC_Message_Handle;
class FC_BuddyListCtrl;

class FC_Client
{
public:
    FC_Client();
    ~FC_Client();

    //thread pool about
    io_service* get_logic_service(); //get io_service from thread_pool;

    //display about
    void add_msg_to_socket(FC_Message* msg);
    void add_msg_to_qml(FC_Message* msg);
    void add_msg_to_display(char* msg); //socket message to display
    void add_msg_to_display(std::vector<std::string> msg); //socket message to display
    void add_msg_to_socket(std::vector<std::string> msg); //display message to socket

    //friends about
    void json_data_parser_self(const std::string& content);
    void json_data_parser(); //这是使用boost json来存数据 但是不可以解析二进制数据，所以目前采用cppjson来存储
    void parser_friends_json(const std::string& content);
    void test_data();

    void update_nick(const std::string& nick);
    void update_gender(const std::string& sex);

    //profile about
    //set funcation
    void setUniqueUserName(std::string name);
    //get funcation
    std::string getUniqueUserName();

    FC_BuddyListCtrl* get_buddy_list();
    void forward_message(FC_Message* msg);
    void save_user_head(const std::string& acc,const string& heading);
private:
    FC_Connection* _connections = nullptr;//connect to server
    FC_Display* _display = nullptr;//user interface
    FC_Thread_Pool* _thread_pool = nullptr;
    FC_Profile* _profile = nullptr; //account information
    FC_Message_Handle* _message_handle; //handle message
    FC_BuddyListCtrl* _buddy_list = nullptr; //存放好友列表的结果

    std::string uniqueUserName; //现在用户模块单出来了 可以单独使用;
};

#endif // FC_CLIENT_H

