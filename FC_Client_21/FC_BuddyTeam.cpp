#include "FC_BuddyTeam.h"
#include "FC_BuddyItem.h"


BuddyTeam::BuddyTeam(QObject *parent)
    :QObject(parent)
{

}

QQmlListProperty<BuddyItem> BuddyTeam::buddys()
{
    return {this,this,
    &BuddyTeam::appendItem,
    &BuddyTeam::itemCount,
    &BuddyTeam::item,
    &BuddyTeam::clearItems};
}

void BuddyTeam::appendItem(BuddyItem * p)
{
    m_items.append(p);
}

int BuddyTeam::itemCount() const
{
    return m_items.count();
}

BuddyItem *BuddyTeam::item(int index) const
{
    return m_items.at(index);
}

void BuddyTeam::clearItems()
{
    m_items.clear();
}

QString BuddyTeam::teamname() const
{
    return m_teamname;
}

int BuddyTeam::teamId() const
{
    return m_id;
}

void BuddyTeam::setTeamname(const QString &str)
{
    m_teamname = str;
//    emit teamChanged();
}

void BuddyTeam::setTeamId(const int &id)
{
    m_id = id;
}

void BuddyTeam::appendItem(QQmlListProperty<BuddyItem> *list, BuddyItem *p)
{
    reinterpret_cast<BuddyTeam*>(list->data)->appendItem(p);
}

int BuddyTeam::itemCount(QQmlListProperty<BuddyItem> *list)
{
    return reinterpret_cast<BuddyTeam*>(list->data)->itemCount();
}

BuddyItem *BuddyTeam::item(QQmlListProperty<BuddyItem> *list, int index)
{
    return reinterpret_cast<BuddyTeam*>(list->data)->item(index);
}

void BuddyTeam::clearItems(QQmlListProperty<BuddyItem> *list)
{
    reinterpret_cast<BuddyTeam*>(list->data)->clearItems();
}
