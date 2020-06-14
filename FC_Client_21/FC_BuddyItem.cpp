#include "FC_BuddyItem.h"

BuddyItem::BuddyItem(QObject *parent)
    :QObject(parent)
{

}

QString BuddyItem::account() const
{
    return m_account;
}

QString BuddyItem::nickname() const
{
    return m_nickname;
}

int BuddyItem::itemId() const
{
    return m_id;
}

void BuddyItem::setAccount(const QString &str)
{
    m_account = str;
//    emit dataChanged();
}

void BuddyItem::setNickname(const QString &str)
{
    m_nickname = str;
//    emit dataChanged();
}

void BuddyItem::setItemId(const int &id)
{
    m_id = id;
}
