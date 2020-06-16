#include "fc_buddylist_ctrl.h"
#include "FC_BuddyItem.h"
#include "FC_BuddyModel.h"
#include "FC_BuddyTeam.h"


FC_BuddyItem::FC_BuddyItem()
{
    //string类型会初始化为null，so 不用初始化
    m_nID = 0;
    m_bShowSign = true;

}

FC_BuddyItem::~FC_BuddyItem()
{

}

FC_BuddyTeamItem::FC_BuddyTeamItem()
{
    m_nID = 0;
    m_nCurCnt = -1;
    m_nMaxCnt = 0;
}

FC_BuddyTeamItem::~FC_BuddyTeamItem()
{
    for(int i=0;i< (int)m_arrBuddys.size();i++)
    {
        FC_BuddyItem* lpItem = m_arrBuddys[i];
        if(lpItem != nullptr)
            delete lpItem; //释放内存
    }
    m_arrBuddys.clear(); //清空
}

//FC_BuddyListCtrl::FC_BuddyListCtrl()
//{

//}

FC_BuddyListCtrl::FC_BuddyListCtrl(FC_Client *client)
    :_client(client)
{

}


FC_BuddyListCtrl::~FC_BuddyListCtrl()
{
}

int FC_BuddyListCtrl::AddBuddyTeam(int nID) //添加一个新的分组
{
    FC_BuddyTeamItem* lpItem = new FC_BuddyTeamItem ();
    lpItem->m_nID = nID;
    m_arrBuddyTeamItems.push_back(lpItem);
    return m_arrBuddyTeamItems.size()-1;
}

bool FC_BuddyListCtrl::DelBuddyTeam(int nTeamIndex)
{

}

int FC_BuddyListCtrl::AddBuddyItem(int nTeamIndex, int nID) //在指定分组中 添加新的项
{
    FC_BuddyTeamItem* lpTeamItem = GetBuddyTeamByIndex(nTeamIndex);
    if(lpTeamItem == nullptr)
        return -1;
    FC_BuddyItem* lpItem = new FC_BuddyItem ();
    lpItem->m_nID = nID;
    lpTeamItem->m_arrBuddys.push_back(lpItem);
    return lpTeamItem->m_arrBuddys.size()-1;
}

//删除好友分组中的一个项
bool FC_BuddyListCtrl::DelBuddyItem(int nTeamIndex, int nIndex)
{
    if(nTeamIndex >= 0 && nTeamIndex < (int)m_arrBuddyTeamItems.size())
    {
        FC_BuddyTeamItem* lpTeamItem = m_arrBuddyTeamItems[nTeamIndex];
        if(lpTeamItem != nullptr)
        {
            if(nIndex >= 0 && nIndex < (int)lpTeamItem->m_arrBuddys.size())
            {
                FC_BuddyItem* lpBuddyItem = lpTeamItem->m_arrBuddys[nIndex];
                if(lpBuddyItem != nullptr)
                    delete lpBuddyItem;
                lpTeamItem->m_arrBuddys.erase(lpTeamItem->m_arrBuddys.begin()+nIndex);
                return true;
            }
        }
    }
    return false;
}

int FC_BuddyListCtrl::GetBuddyTeamCount() //得到当前分组个数
{
    return m_arrBuddyTeamItems.size();
}

int FC_BuddyListCtrl::GetBuddyItemCount(int nTeamIndex) //得到每个分组中好友个数
{
    FC_BuddyTeamItem* lpTeamItem = GetBuddyTeamByIndex(nTeamIndex);

    if(lpTeamItem != nullptr)
        return lpTeamItem->m_arrBuddys.size();
    else
        return 0;
}

void FC_BuddyListCtrl::DelAllItems()
{

}

void FC_BuddyListCtrl::SetBuddyTeamID(int nTeamIndex, int nID)
{
    FC_BuddyTeamItem* lpTeamItem = GetBuddyTeamByIndex(nTeamIndex);
    if(lpTeamItem != nullptr)
        lpTeamItem->m_nID = nID;
}

void FC_BuddyListCtrl::SetBuddyTeamName(int nTeamIndex, string lpszText)
{
    FC_BuddyTeamItem* lpTeamItem = GetBuddyTeamByIndex(nTeamIndex);
    if(lpTeamItem != nullptr)
        lpTeamItem->m_strName = lpszText;
}

void FC_BuddyListCtrl::SetBuddyTeamMaxCnt(int nTeamIndex, int nMaxCnt)
{
    FC_BuddyTeamItem* lpTeamItem = GetBuddyTeamByIndex(nTeamIndex);
    if(lpTeamItem != nullptr)
        lpTeamItem->m_nMaxCnt = nMaxCnt;
}

void FC_BuddyListCtrl::SetBuddyTeamCurCnt(int nTeamIndex, int nCurCnt)
{
    FC_BuddyTeamItem* lpTeamItem = GetBuddyTeamByIndex(nTeamIndex);
    if(lpTeamItem != nullptr)
        lpTeamItem->m_nCurCnt = nCurCnt;
}

void FC_BuddyListCtrl::SetBuddyItemID(int nTeamIndex, int nIndex, int nID)
{
    FC_BuddyItem* lpItem = GetBuddyItemByIndex(nTeamIndex,nIndex);
    if(lpItem != nullptr)
        lpItem->m_nID = nID;
}

void FC_BuddyListCtrl::SetBuddyItemAccNum(int nTeamIndex, int nIndex, string str)
{
    FC_BuddyItem* lpItem = GetBuddyItemByIndex(nTeamIndex,nIndex);
    if(lpItem != nullptr)
        lpItem->m_strAccNum = str;
}

void FC_BuddyListCtrl::SetBuddyItemNickName(int nTeamIndex, int nIndex, string str)
{
    FC_BuddyItem* lpItem = GetBuddyItemByIndex(nTeamIndex,nIndex);
    if(lpItem != nullptr)
        lpItem->m_strNickName = str;
}

void FC_BuddyListCtrl::SetBuddyItemMarkName(int nTeamIndex, int nIndex, string str)
{
    FC_BuddyItem* lpItem = GetBuddyItemByIndex(nTeamIndex,nIndex);
    if(lpItem != nullptr)
        lpItem->m_strMarkName = str;
}

void FC_BuddyListCtrl::SetBuddyItemSign(int nTeamIndex, int nIndex, string str)
{
    FC_BuddyItem* lpItem = GetBuddyItemByIndex(nTeamIndex,nIndex);
    if(lpItem != nullptr)
        lpItem->m_strSign = str;
}

void FC_BuddyListCtrl::SetBuddyItemGender(int nTeamIndex, int nIndex, string bGender)
{
    FC_BuddyItem* lpItem = GetBuddyItemByIndex(nTeamIndex,nIndex);
    if(lpItem != nullptr)
        lpItem->m_bGender = bGender;
}

void FC_BuddyListCtrl::SetBuddyItemHeadPic(int nTeamIndex, int nIndex, string pic)
{
    FC_BuddyItem* lpItem = GetBuddyItemByIndex(nTeamIndex,nIndex);
    if(lpItem != nullptr)
        lpItem->m_strHeadImgName = pic;
}

int FC_BuddyListCtrl::GetBuddyTeamID(int nTeamIndex)
{
    FC_BuddyTeamItem* lpTeamItem = GetBuddyTeamByIndex(nTeamIndex);
    if(lpTeamItem != nullptr)
        return lpTeamItem->m_nID;
//    else
//        return -1;
}

string FC_BuddyListCtrl::GetBuddyTeamName(int nTeamIndex)
{
    FC_BuddyTeamItem* lpTeamItem = GetBuddyTeamByIndex(nTeamIndex);
    if(lpTeamItem != nullptr)
        return lpTeamItem->m_strName;
}

int FC_BuddyListCtrl::GetBuddyTeamMaxCnt(int nTeamIndex)
{
    FC_BuddyTeamItem* lpTeamItem = GetBuddyTeamByIndex(nTeamIndex);
    if(lpTeamItem != nullptr)
        return lpTeamItem->m_nMaxCnt;  //当前分组好友数
}

int FC_BuddyListCtrl::GetBuddyTeamCurCnt(int nTeamIndex)
{
    FC_BuddyTeamItem* lpTeamItem = GetBuddyTeamByIndex(nTeamIndex);
    if(lpTeamItem != nullptr)
        return lpTeamItem->m_nCurCnt;  //当前在线好友数
}

string FC_BuddyListCtrl::GetBuddyItemAccNum(int nTeamIndex, int nIndex)
{
    FC_BuddyItem* lpItem = GetBuddyItemByIndex(nTeamIndex,nIndex);
    if(lpItem != nullptr)
        return lpItem->m_strAccNum;
}

string FC_BuddyListCtrl::GetBuddyItemNickName(int nTeamIndex, int nIndex)
{
    FC_BuddyItem* lpItem = GetBuddyItemByIndex(nTeamIndex,nIndex);
    if(lpItem != nullptr)
        return lpItem->m_strNickName;
}

string FC_BuddyListCtrl::GetBuddyItemMarkName(int nTeamIndex, int nIndex)
{
    FC_BuddyItem* lpItem = GetBuddyItemByIndex(nTeamIndex,nIndex);
    if(lpItem != nullptr)
        return lpItem->m_strMarkName;
}

string FC_BuddyListCtrl::GetBuddyItemSignName(int nTeamIndex, int nIndex)
{
    FC_BuddyItem* lpItem = GetBuddyItemByIndex(nTeamIndex,nIndex);
    if(lpItem != nullptr)
        return lpItem->m_strSign;
}

string FC_BuddyListCtrl::GetBuddyItemHeading(int nTeamIndex, int nIndex)
{
    FC_BuddyItem* lpItem = GetBuddyItemByIndex(nTeamIndex,nIndex);
    if(lpItem != nullptr)
        return lpItem->m_strHeadImgName;
}

string FC_BuddyListCtrl::GetBuddyItemGender(int nTeamIndex, int nIndex)
{
    FC_BuddyItem* lpItem = GetBuddyItemByIndex(nTeamIndex,nIndex);
    if(lpItem != nullptr)
        return lpItem->m_bGender;
}

FC_BuddyTeamItem *FC_BuddyListCtrl::GetBuddyTeamByIndex(int nIndex)
{
    if(nIndex >=0 && nIndex < (int)m_arrBuddyTeamItems.size())
        return m_arrBuddyTeamItems[nIndex];
    else
        return nullptr;
}

FC_BuddyItem *FC_BuddyListCtrl::GetBuddyItemByIndex(int nTeamIndex, int nIndex)
{
    FC_BuddyTeamItem* lpTeamItem;
    if(nTeamIndex >=0 && nTeamIndex < (int)m_arrBuddyTeamItems.size())
    {
        lpTeamItem = m_arrBuddyTeamItems[nTeamIndex];
        if(lpTeamItem != nullptr)
        {
            if(nIndex >=0 && nIndex < (int)lpTeamItem->m_arrBuddys.size())
                return lpTeamItem->m_arrBuddys[nIndex];
        }
    }
    return nullptr;
}

void FC_BuddyListCtrl::addBuddyModel()
{

    BuddyModel* model = BuddyModel::getInstance();
    model->clearTeams(); //客服端修改成功
    for(int i=0;i<this->GetBuddyTeamCount();i++)
    {
        BuddyTeam* team = new BuddyTeam ();
        string str = this->GetBuddyTeamName(i);
        team->setTeamname(QString::fromLocal8Bit(str.c_str()));
        team->setTeamId(i);
        for(int j=0;j<this->GetBuddyItemCount(i);j++)
        {
            BuddyItem* item = new BuddyItem();
            string account = this->GetBuddyItemAccNum(i,j);
            string nickName = this->GetBuddyItemMarkName(i,j);
            string heading = this->GetBuddyItemHeading(i,j);
            string gender = this->GetBuddyItemGender(i,j);
            string sign = this->GetBuddyItemSignName(i,j);

            item->setAccount(QString::fromLocal8Bit(account.c_str()));
            item->setNickname(QString::fromLocal8Bit(nickName.c_str()));
            item->setHeading(QString::fromLocal8Bit(heading.c_str()));
            item->setGender(QString::fromLocal8Bit(gender.c_str()));
            item->setSign(QString::fromLocal8Bit(sign.c_str()));
            item->setItemId(j);
            team->appendItem(item);

            cout<<"account: "<<account<<" nickname: "<<nickName<<endl;
        }
         model->appendTeam(team);
    }
    emit model->teamsChanged();
}

