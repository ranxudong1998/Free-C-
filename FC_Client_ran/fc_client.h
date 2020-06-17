#ifndef FC_CLIENT_H
#define FC_CLIENT_H

#include <boost/thread.hpp>
#include <boost/asio.hpp>
#include <string>

using boost::thread;
using std::string;
using boost::asio::io_service;

class FC_Connection;
class FC_Display;
class FC_Thread_Pool;
class FC_Profile;
class FC_Message;
class FC_Message_Handle;
class FC_instance_handle;

class FC_Client
{
public:
    FC_Client();
    ~FC_Client();

    //thread pool about
    io_service* get_logic_service(); //get io_service from thread_pool;
    //display about
    void add_msg_to_display(char* msg); //socket message to display
    void add_msg_to_display(std::vector<std::string> msg); //socket message to display
    void add_msg_to_socket(std::vector<std::string> msg); //display message to socket
    //profile about
    void set_account(string s);
    char* getAccount();
    char* getSAccount();

    void forward_message(FC_Message* msg);
private:
    FC_Connection* _connections = nullptr;//connect to server
    FC_Display* _display = nullptr;//user interface
    FC_Thread_Pool* _thread_pool = nullptr;
    FC_Profile* _profile = nullptr; //account information
    FC_instance_handle* _instance_handle = nullptr;   //
    FC_Message_Handle* _message_handle; //handle message
    char account[8]={"0000000"};
    char s_account[8]={"0000000"};
};

#endif // FC_CLIENT_H

