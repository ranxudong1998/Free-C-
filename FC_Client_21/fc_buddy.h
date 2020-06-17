#ifndef FC_BUDDY_H
#define FC_BUDDY_H

#include <QObject>

class Buddy : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString account READ account WRITE setAccount NOTIFY dataChanged)
    Q_PROPERTY(QString nickname READ nickname WRITE setNickname NOTIFY dataChanged)
    Q_PROPERTY(QString heading READ heading WRITE setHeading NOTIFY dataChanged)
    Q_PROPERTY(QString value READ value WRITE setValue NOTIFY valueChanged)
public:
    static Buddy* getInstance();
    //getter
    QString account()const;
    QString nickname()const;
    QString heading()const;
    QString value()const;

    //setter
    void setAccount(const QString& str);
    void setNickname(const QString& str);
    void setHeading(const QString& str);
    void setValue(const QString& str);
signals:
    void dataChanged();
    void valueChanged();
private:
    static Buddy* instance;
    Buddy(QObject* parent=nullptr);
    QString m_account;
    QString m_nickname;
    QString m_heading;
    QString m_value;
};

#endif // FC_BUDDY_H
