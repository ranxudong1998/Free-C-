#ifndef FC_BUDDYITEM_H
#define FC_BUDDYITEM_H

/**************************************************************

  @brief....:model中的每一个好友项
  @author...: zhouyi
  @date.....:2020-05-23

  ************************************************************/
#include <QObject>

class BuddyItem : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString account READ account WRITE setAccount)
    Q_PROPERTY(QString nickname READ nickname WRITE setNickname)
    Q_PROPERTY(int itemId READ itemId WRITE setItemId)
//    Q_PROPERTY(QString heading READ heading WRITE setHeading NOTIFY headingChanged)
public:
    BuddyItem(QObject* parent=nullptr);
    //getter
    QString account()const;
    QString nickname()const;
    int itemId() const;

    //setter
    void setAccount(const QString& str);
    void setNickname(const QString& str);
    void setItemId(const int& id);
signals:
//    void dataChanged();
private:
    QString m_account;
    QString m_nickname;
    int m_id;
};

#endif // FC_BUDDYITEM_H
