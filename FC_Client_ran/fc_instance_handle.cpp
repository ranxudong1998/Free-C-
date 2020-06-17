#include "fc_instance_handle.h"
#include "fc_client.h"
#include<QDebug>

FC_instance_handle::FC_instance_handle(QObject *parent )
    : QObject(parent)
{

}

FC_instance_handle::~FC_instance_handle()
{
    
}

QString FC_instance_handle::writer() const
{
    return this->_writer;
}

QString FC_instance_handle::sId() const
{
    return this->_sId;
}

QString FC_instance_handle::time() const
{
    return this->_time;
}

QString FC_instance_handle::content() const
{
    return this->_content;
}

void FC_instance_handle::set_writer(const QString &writer)
{
    //assert(_writer.isEmpty());
    _writer='\0';
    this->_writer = writer;
    qDebug()<<"__writer data:"<<_writer;

}

void FC_instance_handle::set_sId(const QString &sId)
{
    //assert(_sId.isEmpty());
    _sId ='\0';
    this->_sId = sId;
}

void FC_instance_handle::set_time(const QString &time)
{
    //assert(_time.isEmpty());
    _time='\0';
    this->_time = time;
}

void FC_instance_handle::set_content(const QString &content)
{
    //assert(_content.isEmpty());
    _content = '\0';
    this->_content = content;
}



void FC_instance_handle::add(QVector<QString> content)
{
    if(content.size()==4){  //account,s_account和body
        std::vector<std::string> msg;
        for(auto i:content)
            msg.push_back(i.toStdString());
       // this->_client->add_msg_to_socket(msg);

        //将消息回显至Qml
        set_writer(content[0]);
        set_sId(content[1]);
        set_time(content[2]);
        set_content(content[3]);
        emit msgChanged();

    }else{
        qDebug() << "error in c++ add\n";
    }
}

void FC_instance_handle::recv(QVector<QString> content)
{
    //将消息发送至Qml
    set_writer(content[0]);
    set_sId(content[1]);
    set_time(content[2]);
    set_content(content[3]);
    emit msgChanged();
}

void FC_instance_handle::handleMsg(QVector<QString> msg)
{
    set_writer(msg[0]);
    set_sId(msg[1]);
    set_time(msg[2]);
    set_content(msg[3]);
}


