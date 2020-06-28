#ifndef FC_CHAT_LISTMODEL_H
#define FC_CHAT_LISTMODEL_H

/**************************************************************

  @brief....: chatViews.qml最新消息加载
  @author...: ran
  @date.....:2020-06-25

  ************************************************************/
#include <QAbstractListModel>
#include<iostream>

class FC_Message_Instance;
class FC_Client;
class FC_instance_handle;

//<userId,<userName,imagePaht,lastcontent>>
typedef QHash <QString, QVector<QString>> LastMsgVector;

class FC_Chat_ListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    FC_Chat_ListModel(FC_Client*client,QObject* parent=nullptr);
    ~FC_Chat_ListModel();


   //override function
   QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const; //index and role data
   int rowCount(const QModelIndex &parent = QModelIndex()) const; //row count

   QHash<int, QByteArray> roleNames() const;

    Q_INVOKABLE void add(QVector<QString> mess);// 显示在qml
   void recv(QVector<QString> content);// 显示在qml


   void handle_last_msg(QVector<QString> content); //不用

signals:
   void update_mess();
private:
   QHash<int, QByteArray> _roles;//store rolename
   QVector<QVector<QString>> _data; //store message
   FC_Client* _client = nullptr;
   LastMsgVector _all_last_msg;
};

#endif // FC_CHAT_LISTMODEL_H
