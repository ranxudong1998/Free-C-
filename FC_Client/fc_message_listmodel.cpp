#include "fc_message_listmodel.h"
#include "fc_message_instance.h"
#include "fc_client.h"
#include <QDebug>

//==============================================
//  public function
//==============================================


FC_Message_ListModel::FC_Message_ListModel(FC_Client*client, QObject* parent)
    :QAbstractListModel(parent),_client(client){
    _instace = new FC_Message_Instance(_client);
}
FC_Message_ListModel::~FC_Message_ListModel(){
    delete this->_instace;
}

//override function
QVariant FC_Message_ListModel::data(const QModelIndex &index, int role ) const{ //index and role data
    return this->_instace->data(index.row(),role);
}
int FC_Message_ListModel::rowCount(const QModelIndex &) const{//row count
    return this->_instace->rowCount();
}
QHash<int, QByteArray> FC_Message_ListModel::roleNames() const{
    return this->_instace->roleNames();
}

//transfer function
void FC_Message_ListModel::add(QVector<QString> content){// display to socket
    beginInsertRows(QModelIndex(),rowCount(),rowCount());
    this->_instace->add(content);
    endInsertRows();
}
void FC_Message_ListModel::recv(QVector<QString> content){// socket to display
    emit recv_mess();
    beginInsertRows(QModelIndex(),rowCount(),rowCount());
    this->_instace->recv(content);
    endInsertRows();
}
//==============================================
//  private function
//==============================================

