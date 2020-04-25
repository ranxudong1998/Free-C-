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

private:
    QString _account;
    FC_Client* _client;
};

#endif // FC_PROFILE_H
