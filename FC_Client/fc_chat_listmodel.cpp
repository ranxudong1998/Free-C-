#include "fc_chat_listmodel.h"

#include <QDebug>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include "fc_client.h"
#include "fc_buddyitem.h"

namespace fs =std::filesystem ;



FC_Chat_ListModel::FC_Chat_ListModel(FC_Client *client, QObject *parent)
    :QAbstractListModel(parent),_client(client)
{

}

FC_Chat_ListModel::~FC_Chat_ListModel()
{

}

QVariant FC_Chat_ListModel::data(const QModelIndex &index, int role) const
{
    //return this->_data.at(index.row()).at(role);
    if(index.row() <0 || index.row() >= _data.size())
    {
        return QVariant();
    }
    if(role == 0) //判断当前1所属于的状态
        return this->_data.at(index.row()).at(0);
    else if(role == 1)
        return this->_data.at(index.row()).at(1);
    else if(role == 2)
        return this->_data.at(index.row()).at(2);
}

int FC_Chat_ListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
     return this->_data.size();//函数返回模型中的项目总数
}

QHash<int, QByteArray> FC_Chat_ListModel::roleNames() const
{
    QHash<int,QByteArray> _hash;
    _hash[0] = "userName"; //昵称
    _hash[1] = "imagePath"; //头像
    _hash[2] = "lastContent"; //信息

    return _hash;
}

void FC_Chat_ListModel::add(QVector<QString> content)
{
    //这里需要判断这条记录的用户id是否显示过，需要把服务端中传过来的数据，全部添加进_all_last_msg容器中，设置该容器和model的转换
//    if(_all_last_msg.count(content.at(0)) == 0) //表明最后一条历史记录中没有
//    {
        //0是用户标识，2是消息信息
         BuddyItem* item = _client->get_item()[content.at(0).toStdString()];
         QVector<QString> temp;
          //0 是昵称 1是头像 2是内容
         temp.push_back(item->nickname()); //这里还可以判断下，有无备注，如果有备注则传入备注，没有备注，则传入昵称
         temp.push_back(item->heading());
         temp.push_back(content.at(1));//内容
         beginInsertRows(QModelIndex(),rowCount(),rowCount());
         this->_data.push_back(temp);
         endInsertRows();
         emit update_mess();
//    }else{ //表明有这个用户，则只需要进行修改
//        _all_last_msg[content.at(0)][2] = content.at(1);
//        emit update_mess();
//    }

}

//recv和add代码可以合并 内容相同
void FC_Chat_ListModel::recv(QVector<QString> content)
{
    //为了方面查找 所有用户信息都存在表 _client->get_item()这个hash表中，需要信息可以直接在hash表中查找
    BuddyItem* item = _client->get_item()[content.at(0).toStdString()];
    QVector<QString> temp;
    temp.push_back(item->nickname()); //这里还可以判断下，有无备注，如果有备注则传入备注，没有备注，则传入昵称
    temp.push_back(item->heading());
    temp.push_back(content.at(1));//内容
    beginInsertRows(QModelIndex(),rowCount(),rowCount());
    this->_data.push_back(temp);
    endInsertRows();
    emit update_mess();
}

//存储所有账号对应的最后一条消息
void FC_Chat_ListModel::handle_last_msg(QVector<QString> content)
{

//    if(_all_last_msg.count(content.at(0))) //表明存在这个用户
//    {

//    }else //表明不存在这个用户，则插入一条消息
//    {

//    }
//     LastMsgVector::iterator iter =this->_all_last_msg.find(content.at(0));  //检索key
//     iter.value() =content;

     beginInsertRows(QModelIndex(),rowCount(),rowCount());
//     消息直接在UI上打印
     this->_data.push_back(content);
     std::cout<<"this->_data.size()"<<this->_data.size()<<std::endl;
     endInsertRows();
     emit update_mess();
    // this->_data.clear();
}
