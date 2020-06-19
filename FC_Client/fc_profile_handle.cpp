#include "fc_profile_handle.h"
#include "fc_client.h"
#include <string>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>
#include <json/json.h>
#include "fc_message.h"
#include "fc_header.h"
#include <QDebug>
#include <iostream>
#include <fstream>
#include <filesystem>
namespace fs = std::filesystem;

using namespace boost::property_tree;

FC_Profile::FC_Profile(QObject *parent)
    :QObject(parent)
{

}

FC_Profile::FC_Profile(FC_Client *client, QObject *parent)
    :QObject(parent),_client(client)
{
    _profile = ProfileMsg::getInstance();
}

FC_Profile::~FC_Profile()
{

}

QString FC_Profile::getAccount() const
{
    return this->_account;
}

void FC_Profile::login(const QString &userAcount, const QString &password)
{
    qDebug()<<userAcount<<"  "<<password<<"\n";
    char* account = (char*)malloc(userAcount.size()+1);
    memset(account,'\0',userAcount.size()+1);
    strcpy(account,userAcount.toLocal8Bit().data());

    _client->setUniqueUserName(account);//复制用户名信息,在客户端总类中

    char* pass= (char*)malloc(password.size()+1);
    memset(pass,'\0',password.size()+1);
    strcpy(pass,password.toLocal8Bit().data());

    strcpy(account+FC_ACC_LEN,pass);

    qDebug()<<account;

    FC_Message* message = new FC_Message;
    message->set_message_type(FC_SIGN_IN);
    message->set_body_length(strlen(account));
    message->set_body(account,strlen(account));

    free(account);
    free(pass);
    _client->add_msg_to_socket(message);
}

void FC_Profile::updateNick(const QString &acc)
{
    std::string username = _client->getUniqueUserName();
    char* account = (char*)malloc(username.size()+1);
    memset(account,'\0',username.size()+1);
    strcpy(account,username.c_str());

    char* content= (char*)malloc(acc.size()+1);
    memset(content,'\0',acc.size()+1);
    strcpy(content,acc.toLocal8Bit().data());

    strcpy(account+FC_ACC_LEN,content);

    FC_Message* message = new FC_Message;
    message->set_message_type(FC_UPDATE_NICK);
    message->set_body_length(strlen(account));
    message->set_body(account,strlen(account));

//    qDebug() <<"updateNick:"<< message->body();
    free(account);
    free(content);
    _client->add_msg_to_socket(message);

    //会发送给服务端 暂时没写
}

void FC_Profile::updateGender(const QString &sex)
{
    std::string username = _client->getUniqueUserName();
    char* account = (char*)malloc(username.size()+1);
    memset(account,'\0',username.size()+1);
    strcpy(account,username.c_str());

    char* content= (char*)malloc(sex.size()+1);
    memset(content,'\0',sex.size()+1);
    strcpy(content,sex.toLocal8Bit().data());

    strcpy(account+FC_ACC_LEN,content);

    FC_Message* message = new FC_Message;
    message->set_message_type(FC_UPDATE_SEX);
    message->set_body_length(strlen(account));
    message->set_body(account,strlen(account));

    free(account);
    free(content);
    _client->add_msg_to_socket(message);
}

void FC_Profile::update_nick(const QString &nick)
{
    this->_profile->setNickname(nick);
}

void FC_Profile::update_gender(const QString &sex)
{
    this->_profile->setGender(sex);
}

void FC_Profile::parser_json(const std::string &content)
{

      Json::Value root;
      Json::Reader reader;
      std::string acc;
      std::string nick;
      std::string heading;
      std::string sign;
      std::string sex;
      if(!reader.parse(content, root)){
        std::cout <<"failed" <<std::endl;
      }
      else{
          acc = root["account"].asString();
          nick = root["nickname"].asString();
          sex = root["gender"].asString();
          sign = root["sign"].asString();
          heading = root["heading"].asString();
      }

      //保存在配置文件中
      _client->save_user_head(acc,heading);

      //得到整体当前文件所属的位置

      fs::path p = fs::current_path(); //目的是为了得到相对路径

      string path = "file://"+p.string()+"/assert/"+acc+".jpg";

      QString account = QString::fromLocal8Bit(acc.c_str());
      QString nickname = QString::fromLocal8Bit(nick.c_str());
      QString gender = QString::fromLocal8Bit(sex.c_str());
      QString signv = QString::fromLocal8Bit(sign.c_str());
      QString headpath = QString::fromLocal8Bit(path.c_str());


      _profile->setAccount(account);
      _profile->setNickname(nickname);
      _profile->setGender(gender);
      _profile->setHeading(headpath);
      _profile->setSign(signv);
}

void FC_Profile::sendsignal()
{
    emit selfMessage("account","nickname","gender"); //发送信号
}
