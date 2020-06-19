#include "fc_message_listmodel.h"
#include "fc_message_instance.h"
#include "fc_client.h"
#include "fc_instance_handle.h"
#include <QDebug>

//==============================================
//  public function
//==============================================


FC_Message_ListModel::FC_Message_ListModel(FC_Client*client, QObject* parent)
    :QAbstractListModel(parent),_client(client)
{

     _instace = new FC_Message_Instance(_client);
     QVector<QVector<QString>> tmp11,tmp12,tmp13,tmp14;
//         QVector<QVector<QString>> tmp21,tmp22,tmp23,tmp24;
//         QVector<QVector<QString>> tmp31,tmp32,tmp33,tmp34;
//         QVector<QVector<QString>> tmp41,tmp42,tmp43,tmp44;
     //初始化四个好友
//     _all_mess.insert("1111111111111111",tmp11);
//     _all_mess.insert("1111111111111112",tmp11);
//     _all_mess.insert("1111111111111113",tmp11);
//     _all_mess.insert("1111111111111114",tmp11);
//     _all_mess.insert("1111111211111111",tmp11);
//     _all_mess.insert("1111111211111112",tmp11);
//     _all_mess.insert("1111111211111113",tmp11);
//     _all_mess.insert("1111111211111114",tmp11);
//     _all_mess.insert("1111111311111111",tmp11);
//     _all_mess.insert("1111111311111112",tmp11);
//     _all_mess.insert("1111111311111113",tmp11);
//     _all_mess.insert("1111111311111114",tmp11);
//     _all_mess.insert("1111111411111111",tmp11);
//     _all_mess.insert("1111111411111112",tmp11);
//     _all_mess.insert("1111111411111113",tmp11);
//     _all_mess.insert("1111111311111114",tmp11);
          _all_mess.insert("@12345@13456",tmp11);
          _all_mess.insert("@12345@24567",tmp11);
          _all_mess.insert("@12345@23456",tmp11);
          _all_mess.insert("@12345@12345",tmp11);
          _all_mess.insert("@13456@12345",tmp11);
          _all_mess.insert("@13456@13456",tmp11);
          _all_mess.insert("@13456@24567",tmp11);
          _all_mess.insert("@13456@23456",tmp11);
          _all_mess.insert("@24567@12345",tmp11);
          _all_mess.insert("@24567@13456",tmp11);
          _all_mess.insert("@24567@24567",tmp11);
          _all_mess.insert("@24567@24567",tmp11);
          _all_mess.insert("@23456@23456",tmp11);
          _all_mess.insert("@23456@24567",tmp11);
          _all_mess.insert("@23456@13456",tmp11);
          _all_mess.insert("@23456@12345",tmp11);


}
FC_Message_ListModel::~FC_Message_ListModel(){
    delete this->_instace;
}

MsgVector::iterator FC_Message_ListModel::handle_msg(QVector<QString> content)
{
      qDebug()<<"key date:"<<content.at(0)+content.at(1);
      MsgVector::iterator iter =this->_all_mess.find(content.at(0)+content.at(1));  //检索key
      iter.value().push_back(content);

      return iter;
}


void FC_Message_ListModel::add_msg_to_socket(QVector<QString> content)
{
    this->_instace->add_msg_to_socket(content);
}

//override function
QVariant FC_Message_ListModel::data(const QModelIndex &index, int role ) const{ //index and role data
    return this->_instace->data(index.row(),role);
}
//函数返回模型中的项目总数
int FC_Message_ListModel::rowCount(const QModelIndex &) const{//row count
    return this->_instace->rowCount();
}

QHash<int, QByteArray> FC_Message_ListModel::roleNames() const{
     return this->_instace->roleNames();
}


//transfer function
void FC_Message_ListModel::add(QVector<QString> content){// display to socket
    add_msg_to_socket(content);
    handle_msg(content);
    set_msgOpacity(0);

    MsgVector::iterator iter =this->_all_mess.find(this->currentChatId());

    for(int i = 0; i < iter->length();i++){
       beginInsertRows(QModelIndex(),rowCount(),rowCount());
        //消息直接在UI上打印
       this->_instace->add(iter.value().at(i));
       endInsertRows();
       emit recv_mess();
    }
    iter->clear();
}
void FC_Message_ListModel::recv(QVector<QString> content){// socket to display

    handle_msg(content);
    set_msgOpacity(1);
    //检测是否为当前聊天信息
    if(content.at(0)+content.at(1)!=this->currentChatId()){
        return;
    }
    MsgVector:: iterator iter =this->_all_mess.find(this->currentChatId());
    for(int i = 0; i < iter->length();i++){
       beginInsertRows(QModelIndex(),rowCount(),rowCount());
        //消息直接在UI上打印
       this->_instace->recv(iter.value().at(i));

       endInsertRows();
       emit recv_mess();
    }
    iter->clear();
}

void FC_Message_ListModel::loadMsg(QString key)
{
    qDebug()<<"key data:"<<key;
    this->_instace->clearMsg();  //清空信息

    qDebug()<<"load key data: "<<key;
    MsgVector:: iterator iter =this->_all_mess.find(key);
    for(int i = 0; i < iter->length();i++){
       beginInsertRows(QModelIndex(),rowCount(),rowCount());
        //消息直接在UI上打印
       this->_instace->recv(iter.value().at(i));
       endInsertRows();
       emit recv_mess();
    }
    //iter->clear();
}

QString FC_Message_ListModel::currentChatId() const
{
    return this->_currentChatId;
}

int FC_Message_ListModel::msgOpacity() const
{
    return this->_opacity;
}

int FC_Message_ListModel::set_msgOpacity(int opacity)
{
    this->_opacity=opacity;
}


void FC_Message_ListModel::set_currentChatId(QString id)
{
    this->_currentChatId = id;
    loadMsg(id);

}


