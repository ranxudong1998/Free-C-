#ifndef FC_SERVER_H
#define FC_SERVER_H

#include <boost/asio.hpp>
#include <vector>
#include <unordered_map>
#include <QVariant>

using boost::asio::io_service;
using std::vector;
using std::unordered_map;

class FC_Thread_Pool;
class FC_Acceptor;
class FC_Connection;
class FC_Message;

class FC_Server
{
public:
    FC_Server(int thread_num,int port);
    ~FC_Server();

    //thread_pool about
    io_service* get_logic_service(); //get socket io_service
    io_service* get_acceptor_service(); // get acceptor io_service

    //connection about
    FC_Connection* get_connection(); //get new connection
    void handle_connected(FC_Connection* connection);//
    void erase_connection(FC_Connection* connection);//remove closed connect
    //
    void forward_message(char* msg);
    void forward_message(FC_Message* msg);
    void forward_message(QString id,FC_Message* msg);
    //profile about
    void add_identified(QString,FC_Connection*);

private:
    FC_Thread_Pool* _thread_pool = nullptr;
    FC_Acceptor* _accrptor = nullptr;
    vector<FC_Connection*> _connected; //connected but not identify
    unordered_map<QString,FC_Connection*> _identified;//connected and identified;
};

#endif // FC_SERVER_H
