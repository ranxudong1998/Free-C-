#include "fc_profile.h"

ProfileMsg* ProfileMsg::instance = nullptr;

ProfileMsg *ProfileMsg::getInstance()
{
    if(instance == nullptr)
        instance = new ProfileMsg ();
    return instance;
}

void ProfileMsg::setAccount(const QString &acc)
{
    m_account = acc;
//    emit accountChanged();
}

void ProfileMsg::setNickname(const QString &nick)
{
    m_nickname = nick;
    emit nicknameChanged();
}

void ProfileMsg::setGender(const QString &gender)
{
    if( m_gender != gender)
    {
        m_gender = gender;
        emit genderChanged();
    }
}

QString ProfileMsg::account() const
{
    return m_account;
}

QString ProfileMsg::nickname() const
{
    return m_nickname;
}

QString ProfileMsg::gender() const
{
    return m_gender;
}

ProfileMsg::ProfileMsg(QObject *parent)
    :QObject(parent)
{

}
