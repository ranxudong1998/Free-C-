#include "fc_display.h"
#include "fc_client.h"
#include "fc_message_listmodel.h"
#include "fc_profile.h"
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml/QtQml>
#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <QDebug>
using boost::thread;

//==============================================
//  public function
//==============================================

FC_Display::FC_Display(FC_Client* client,FC_Profile* profile)
    :_client(client),_profile(profile)
{
    this->_list_model = new FC_Message_ListModel(_client);
}
FC_Display::~FC_Display(){
    qDebug() << "FC_Display::~Display\n";
    delete this->_list_model;
    delete this->_engine;
    delete this->_app_ui;
}
void FC_Display::show(){
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    int argc=0;
    this->_app_ui = new QGuiApplication(argc,nullptr);
    this->_engine = new QQmlApplicationEngine;
    this->_engine->rootContext()->setContextProperty("message_listModel",this->_list_model);
    this->_engine->rootContext()->setContextProperty("profile",this->_profile);
//    this->_engine->load(QUrl(QStringLiteral("qrc:/Fc_log_up.qml")));
    this->_engine->load(QUrl(QStringLiteral("qrc:/Fc_main.qml")));
    this->_app_ui->exec();
}
void FC_Display::recv(QString s){
    this->_list_model->recv({".",".",".",s});
}
void FC_Display::recv(std::vector<std::string> vs){//display receive message
    this->_list_model->recv({QString::fromStdString("."),
                             QString::fromStdString(vs.at(0)),
                             QString::fromStdString("."),
                             QString::fromStdString(vs.at(1)),});
}
//==============================================
//  private function
//==============================================
