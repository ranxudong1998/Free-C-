#ifndef FC_PROFILE_H
#define FC_PROFILE_H

#include <QObject>

class FC_Client;

class FC_Profile: public QObject
{
    Q_OBJECT
public:
    FC_Profile(FC_Client* client, QObject *parent = nullptr);
    ~FC_Profile();

    Q_PROPERTY(QString account READ account WRITE set_account )
    QString account()const;
    Q_INVOKABLE void set_account(const QString& account);
signals:
    QString accountChanged();
private:
    QString _account;    //用户账号
    //QString _Saccount;   //接收端账号(个人账号,群号)
    FC_Client* _client;
};

#endif // FC_PROFILE_H
