#ifndef FC_INSTANCE_HANDLE_H
#define FC_INSTANCE_HANDLE_H


#include <QObject>

class FC_Client;
class FC_instance_handle : public QObject
{
     Q_OBJECT
public:
    FC_instance_handle(QObject *parent = nullptr);
    ~FC_instance_handle();


    Q_PROPERTY(QString writer READ writer WRITE set_writer)
    Q_PROPERTY(QString sId READ sId WRITE set_sId)
    Q_PROPERTY(QString time READ time WRITE set_time)
    Q_PROPERTY(QString content READ content WRITE set_content)

    //getter
    QString writer()const;
    QString sId()const;
    QString time()const;
    QString content()const;

    //setter
    Q_INVOKABLE void set_writer(const QString& writer);
    Q_INVOKABLE void set_sId(const QString& sId);
    Q_INVOKABLE void set_time(const QString& time);
    Q_INVOKABLE void set_content(const QString& content);

    void messagechanged(const QString& writer,const QString& sId,const QString& time,const QString& content);
    //transfer function
    void add(QVector<QString> content);//display to socket
    void recv(QVector<QString> content);//socket to display
    void handleMsg(QVector<QString> msg);
signals:
    QString msgChanged();

private:
    QString _writer;    //消息发送者
    QString _sId;       //消息接收者
    QString _time;      //时间
    QString _content;   //消息内容

    FC_Client* _client;
};

#endif // FC_INSTANCE_HANDLE_H
