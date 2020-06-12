#ifndef FC_MESSAGE_LISTMODEL_H
#define FC_MESSAGE_LISTMODEL_H

#include <QAbstractListModel>

class FC_Message_Instance;
class FC_Client;

class FC_Message_ListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    FC_Message_ListModel(FC_Client*client, QObject* parent=nullptr);
    ~FC_Message_ListModel();

    Q_INVOKABLE void add(QVector<QString> content);// display to socket
    Q_INVOKABLE void recv(QVector<QString> content);// socket to display

    //override function
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const; //index and role data
    int rowCount(const QModelIndex &parent = QModelIndex()) const; //row count
    QHash<int, QByteArray> roleNames() const;

signals:
    void recv_mess();

private:
    //json restore data
    FC_Message_Instance* _instace = nullptr;
    FC_Client* _client = nullptr;
    QVector<QString> mess_user;  //存储接受到的消息的账号
};

#endif // FC_MESSAGE_LISTMODEL_H
