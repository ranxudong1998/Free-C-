#ifndef FC_PROFILE_H
#define FC_PROFILE_H

#include <QObject>
#include <QString>

/**************************************************************

  @brief....:界面显示的Profile实体
  @author...: zhouyi
  @date.....:2020-06-09

  ************************************************************/

class ProfileMsg :public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString account READ account)
    Q_PROPERTY(QString nickname READ nickname WRITE setNickname NOTIFY nicknameChanged)
    Q_PROPERTY(QString gender READ gender WRITE setGender NOTIFY genderChanged)
public:
    static ProfileMsg* getInstance();


    //setter
    void setAccount(const QString& acc);
    void setNickname(const QString& nick);
    void setGender(const QString& gender);

    //getter
    QString account() const;
    QString nickname() const;
    QString gender() const;

signals:
//    void accountChanged();
    void nicknameChanged();
    void genderChanged();

private:
    static ProfileMsg* instance;
    ProfileMsg(QObject* parent = nullptr);

    QString m_account;
    QString m_nickname;
//    QString headi
    QString m_gender;
};

#endif // FC_PROFILE_H
