#ifndef FC_MESSAGE_LISTMODEL_H
#define FC_MESSAGE_LISTMODEL_H

#include <QAbstractListModel>
#include<iostream>

class FC_Message_Instance;
class FC_Client;
class FC_instance_handle;


typedef QHash<QString, QVector<QVector<QString>>> MsgVector;

class FC_Message_ListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    FC_Message_ListModel(FC_Client*client, QObject* parent=nullptr);
    ~FC_Message_ListModel();

     MsgVector::iterator handle_msg(QVector<QString> content);
     void add_msg_to_socket(QVector<QString> content);

    //override function
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const; //index and role data
    int rowCount(const QModelIndex &parent = QModelIndex()) const; //row count

    QHash<int, QByteArray> roleNames() const;

    Q_PROPERTY(QString currentChatId READ currentChatId WRITE set_currentChatId)
    Q_PROPERTY(int msgOpacity READ msgOpacity WRITE set_msgOpacity)

    QString currentChatId() const;
    int msgOpacity() const;
    int set_msgOpacity(int opacity);

    Q_INVOKABLE void add(QVector<QString> mess);// display to socket
    Q_INVOKABLE void recv(QVector<QString> content);// socket to display

    Q_INVOKABLE void loadMsg(QString key);// 当打开一个chatPage时,刷新消息


    Q_INVOKABLE void set_currentChatId(QString id);


signals:
    void recv_mess();
private:

    FC_Client* _client = nullptr;
    FC_Message_Instance* _instace = nullptr;
    MsgVector _all_mess;   //存储所有的消息 <消息发送者id,对行id的所有消息>
    QString _currentChatId;  //当前聊天对象Id
    int _opacity=0;           //设置消息的左右显示,0表示右边显示,1表示左边显示


};

#endif // FC_MESSAGE_LISTMODEL_H
