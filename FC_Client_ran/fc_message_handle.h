#ifndef FC_MESSAGE_HANDLE_H
#define FC_MESSAGE_HANDLE_H

#include "fc_message.h"
#include "fc_client.h"
#include <QObject>
#include <QString>

class FC_Message_Handle : public QObject
{
    Q_OBJECT
public:
    FC_Message_Handle();
    FC_Message_Handle(FC_Client* client,QObject* parent=nullptr);
    ~FC_Message_Handle();
    //handle recv message
    void handle_header(FC_Message*);
    void handle_body(FC_Message*);
    void handle_text_msg(FC_Message* msg);

    const char* text_body(const char* content);
    static FC_Message* generate_message(unsigned type,const char* content);//generate a message
signals:
    void showToQml(const QString &msg);
    void begin();
public slots:
    void show();

public:
    void registered(); //register
    Q_INVOKABLE void search_friends(const QString& friendsAccount);
    Q_INVOKABLE void add_friends(const QString &msg);
    Q_INVOKABLE void update_remark(const int &team,const int &item,const QString &user);
    Q_INVOKABLE void delete_friend(const int &team,const int &item);
    Q_INVOKABLE void validation_request(const QString& result);

    void update_remark(char* content);
    void displaytoQML(FC_Message* message);
    void refresh_friends_list(const string& msg);


signals:
    void addFriendSignal(const QString& value);
private:
    void search_show(const string& msg);
    void add_friends_show(const string& msg);

    char* text_content(const char* account,const char* pass);
    std::string QStrTostr(QString& qstr);
    char* stringTochar(const std::string &str);
    FC_Client* _client;

};

#endif // FC_MESSAGE_HANDLE_H
