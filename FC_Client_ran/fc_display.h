#ifndef FC_DISPLAY_H
#define FC_DISPLAY_H

#include <QVariant>
#include <vector>
class QGuiApplication;
class QQmlApplicationEngine;
class FC_Client;
class FC_Message_ListModel;
class FC_Profile;
class FC_instance_handle;

class FC_Display
{
public:
    FC_Display(FC_Client* client,FC_Profile* profile);
    ~FC_Display();
    void show(); //show ui
    void recv(QString s); //display receive message
    void recv(std::vector<std::string> vs); //display receive message

private:
    FC_Client* _client = nullptr;

    FC_Profile* _profile = nullptr;

    FC_Message_ListModel* _list_model = nullptr;
    QGuiApplication* _app_ui = nullptr;
    QQmlApplicationEngine* _engine = nullptr;
};

#endif // FC_DISPLAY_H
