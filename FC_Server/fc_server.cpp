#include "fc_server.h"
#include "fc_acceptor.h"
#include "fc_thread_pool.h"
#include "fc_connection.h"
#include "fc_message.h"

//==============================================
//  public function
//==============================================

FC_Server::FC_Server(int thread_num,int port){

    this->_thread_pool = new FC_Thread_Pool(thread_num);
    this->_accrptor = new FC_Acceptor(this,port);
    this->_thread_pool->init_thread_pool();
}
FC_Server::~FC_Server(){
    delete this->_thread_pool;
    delete this->_accrptor;
}

//thread_pool about
io_service* FC_Server::get_logic_service(){
    return this->_thread_pool->get_logic_service();
}
io_service* FC_Server::get_acceptor_service(){
    return this->_thread_pool->get_acceptor_service();
}

//connection about
FC_Connection* FC_Server::get_connection(){
    io_service* service = this->get_logic_service();
    return new FC_Connection(this,service);
}
void FC_Server::handle_connected(FC_Connection* connection)
{
    //handle connected socket
    connection->read();
    this->_connected.push_back(connection);
}
void FC_Server::erase_connection(FC_Connection* connection){
    for(size_t i=0;i<_connected.size();++i){
        if(_connected[i]==connection){
            std::swap(_connected[i],_connected[_connected.size()-1]);
            _connected.erase(_connected.end()-1);
        }
    }
    delete connection;
}
void FC_Server::forward_message(FC_Message* msg){
    for (auto i=_connected.begin();i!=_connected.end();++i) {
        FC_Message* tmp_msg = new FC_Message(*msg);
       (*i)->write(tmp_msg);
    }
    delete msg;
}
void FC_Server::forward_message(QString id,FC_Message* msg){
    for (auto i=_identified.begin();i!=_identified.end();++i) {
        if(i->first!=id)
            i->second->write(msg);
    }
}

//profile about
void FC_Server::add_identified(QString s,FC_Connection* c){
    this->_identified[s] = c;
}


//==============================================
//  private function
//==============================================
