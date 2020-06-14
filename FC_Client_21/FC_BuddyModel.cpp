#include "FC_BuddyModel.h"
#include "FC_BuddyItem.h"
#include "fc_buddylist_ctrl.h"
#include <QString>

BuddyModel* BuddyModel::instance = nullptr;

BuddyModel::BuddyModel(QObject *parent)
    :QObject(parent)
{
}

//BuddyModel::BuddyModel(FC_Client *client, QObject *parent)
//    :QObject(parent),_client(client)
//{
////    addBuddyModel();
//    BuddyTeam* team1 = new BuddyTeam ();
//    team1->setTeamname("family");
//    BuddyItem* item1 = new BuddyItem ();
//    item1->setAccount("@12345");
//    item1->setNickname("zhouyi");
//    BuddyItem* item2= new BuddyItem ();
//    item2->setAccount("@24685");
//    item2->setNickname("xiaohu");

//    team1->appendItem(item1);
//    team1->appendItem(item2);



//    BuddyTeam* team2 = new BuddyTeam ();
//    team2->setTeamname("friends");
//    BuddyItem* item3 = new BuddyItem ();
//    item3->setAccount("@78678");
//    item3->setNickname("zhangli");

//    team2->appendItem(item3);


//    m_teams.append(team1);
//    m_teams.append(team2);
//}

BuddyModel *BuddyModel::getInstance()
{
        if(instance == nullptr)
            instance = new BuddyModel ();
        return instance;
}

QQmlListProperty<BuddyTeam> BuddyModel::teams()
{
    return {this,this,
    &BuddyModel::appendTeam,
    &BuddyModel::teamCount,
    &BuddyModel::team,
    BuddyModel::clearTeams};
}

void BuddyModel::appendTeam(BuddyTeam *p)
{
    m_teams.append(p);
}

int BuddyModel::teamCount() const
{
    return m_teams.count();
}

BuddyTeam *BuddyModel::team(int index) const
{
    return m_teams.at(index);
}


void BuddyModel::clearTeams()
{
    m_teams.clear();
}

void BuddyModel::appendTeam(QQmlListProperty<BuddyTeam> *list, BuddyTeam *p)
{
    reinterpret_cast<BuddyModel*>(list->data)->appendTeam(p);
}

int BuddyModel::teamCount(QQmlListProperty<BuddyTeam> *list)
{
    return reinterpret_cast<BuddyModel*>(list->data)->teamCount();
}

BuddyTeam *BuddyModel::team(QQmlListProperty<BuddyTeam> *list, int p)
{
    return reinterpret_cast<BuddyModel*>(list->data)->team(p);
}

void BuddyModel::clearTeams(QQmlListProperty<BuddyTeam> * list)
{
    reinterpret_cast<BuddyModel*>(list->data)->clearTeams();
}

