#include "fc_display.h"
#include "fc_client.h"
#include "fc_message_listmodel.h"
#include "fc_profile_handle.h"
#include "fc_message_handle.h"
#include "fc_profile.h"
#include "FC_BuddyModel.h"
#include "FC_BuddyItem.h"
#include "FC_BuddyTeam.h"
#include "fc_buddy.h"
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml/QtQml>
#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <QDebug>
#include<iostream>
using boost::thread;


FC_Display::FC_Display(FC_Client* client,FC_Profile* profile)
    :_client(client),_profile(profile)
{
    _profilemsg = ProfileMsg::getInstance();
    _model = BuddyModel::getInstance();
    _handle = new FC_Message_Handle (client);
    _profile = new FC_Profile (client);
    _buddy = Buddy::getInstance();

}
FC_Display::~FC_Display(){
    qDebug() << "FC_Display::~Display\n";
    delete this->_engine;
    delete this->_app_ui;
    delete this->_profilemsg;
    delete this->_handle;
    delete this->_profile;
}
void FC_Display::show(){
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    int argc=0;
    this->_app_ui = new QGuiApplication(argc,nullptr);
    this->_engine = new QQmlApplicationEngine;
    
    qmlRegisterType<BuddyItem>("buddy",1,0,"BuddyItem");
    qmlRegisterType<BuddyTeam>("buddy",1,0,"BuddyTeam");
    
    _engine->rootContext()->setContextProperty("message_handle",_handle);
    _engine->rootContext()->setContextProperty("teamModel",_model);
    _engine->rootContext()->setContextProperty("profile_handle",_profile);
    _engine->rootContext()->setContextProperty("profilemsg",_profilemsg);
    _engine->rootContext()->setContextProperty("buddy",_buddy);
    this->_engine->load(QUrl(QStringLiteral("qrc:/qml/Fc_MainWindow.qml")));
//    this->_engine->load(QUrl(QStringLiteral("qrc:/Login.qml")));
    this->_app_ui->exec();
}