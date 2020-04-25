#include "fc_message_instance.h"
#include "fc_client.h"
#include <QDebug>
#include <vector>
#include <string>

//==============================================
//  public function
//==============================================

FC_Message_Instance::FC_Message_Instance(FC_Client* client):_client(client)
{
    int i = Qt::DisplayRole;
    this->_roles.insert(i++,"time");
    this->_roles.insert(i++,"writer");
    this->_roles.insert(i++,"headimg");
    this->_roles.insert(i++,"content");

    //for test
    _data.push_back({"1","11111111111","1","1"});
    _data.push_back({"2","2","2","2"});
    _data.push_back({"3","3","3","3"});
}


//override function
QVariant FC_Message_Instance::data(const int &index, int role ) const{ //index and role data
    return this->_data.at(index).at(role);
}
int FC_Message_Instance::rowCount() const{ //row count
    return this->_data.size();
}
QHash<int, QByteArray> FC_Message_Instance::roleNames() const{
    return this->_roles;
}

//transfer function
void  FC_Message_Instance::add(QVector<QString> content){//display to socket
    if(content.size()==4){
        std::vector<std::string> msg;
        for(auto i:content)
            msg.push_back(i.toStdString());
        this->_client->add_msg_to_socket(msg);
        _data.push_back(content);
    }else{
        qDebug() << "error in c++ add\n";
    }
}
void FC_Message_Instance::recv(QVector<QString> content){//socket to display
    _data.push_back(content);
}

//==============================================
//  private function
//==============================================
