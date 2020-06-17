#ifndef FC_BUDDYLIST_CTRL_H
#define FC_BUDDYLIST_CTRL_H

/**************************************************************

  @brief....:好友列表接口，是唯一的后期可以使用单例模式，是每次产生都是一样的
  @author...: zhouyi
  @date.....:2020-05-13

  ************************************************************/

#include <iostream>
#include <vector>

using namespace std;
class FC_Client;

class FC_BuddyItem
{
public:
    FC_BuddyItem(void);
    ~FC_BuddyItem(void);

public:
    int			m_nID;					// 项ID
    string		m_strAccNum;			// 号码
    string		m_strNickName;			// 昵称
    string		m_strMarkName;			// 备注
    string		m_strSign;				// 签名
    bool		m_bShowSign;			// 是否显示签名
//    bool		m_bOnline;				// 是否在线标志,保留 后期再说

    string     m_strHeadImgName;       // 头像图片路径
    string		m_bGender;				// 性别
};

class FC_BuddyTeamItem
{
public:
    FC_BuddyTeamItem(void);
    ~FC_BuddyTeamItem(void);

public:
    int m_nID;									// 项ID
    string m_strName;							// 好友分组名称
    int m_nCurCnt;								// 当前在线好友数
    int m_nMaxCnt;								// 该好友分组的好友数							// 是否展开标志
    std::vector<FC_BuddyItem*> m_arrBuddys;		// 该好友分组的好友项
};

class FC_BuddyListCtrl
{
public:
    FC_BuddyListCtrl(FC_Client* client);
    ~FC_BuddyListCtrl();

    int AddBuddyTeam(int nID);
    bool DelBuddyTeam(int nTeamIndex);

    int AddBuddyItem(int nTeamIndex,int nID);
    bool DelBuddyItem(int nTeamIndex,int nIndex);

    //getter Team count or item count
    int GetBuddyTeamCount();
    int GetBuddyItemCount(int nTeamIndex);

    void DelAllItems();
    //setter Team
    void SetBuddyTeamID(int nTeamIndex, int nID);
    void SetBuddyTeamName(int nTeamIndex, string lpszText);
    void SetBuddyTeamMaxCnt(int nTeamIndex, int nMaxCnt);
    void SetBuddyTeamCurCnt(int nTeamIndex, int nCurCnt);

    //setter item
    void SetBuddyItemID(int nTeamIndex, int nIndex, int nID);
    void SetBuddyItemAccNum(int nTeamIndex, int nIndex, string str);
    void SetBuddyItemNickName(int nTeamIndex, int nIndex, string str);
    void SetBuddyItemMarkName(int nTeamIndex, int nIndex, string str);
    void SetBuddyItemSign(int nTeamIndex, int nIndex, string str);
    void SetBuddyItemGender(int nTeamIndex, int nIndex, string bGender);
    void SetBuddyItemHeadPic(int nTeamIndex, int nIndex, string pic);


    //id为1表示默认分组
//    //getter team
    int GetBuddyTeamID(int nTeamIndex);
    string GetBuddyTeamName(int nTeamIndex);
    int GetBuddyTeamMaxCnt(int nTeamIndex);
    int GetBuddyTeamCurCnt(int nTeamIndex);

    //getter

    string GetBuddyItemAccNum(int nTeamIndex, int nIndex);
    string GetBuddyItemNickName(int nTeamIndex, int nIndex);
    string GetBuddyItemMarkName(int nTeamIndex, int nIndex);
    string GetBuddyItemSignName(int nTeamIndex, int nIndex);
    string GetBuddyItemHeading(int nTeamIndex, int nIndex);
    string GetBuddyItemGender(int nTeamIndex, int nIndex);

    //getter
    FC_BuddyTeamItem* GetBuddyTeamByIndex(int nIndex);
    FC_BuddyItem* GetBuddyItemByIndex(int nTeamIndex, int nIndex);


    void addBuddyModel();
private:
    std::vector<FC_BuddyTeamItem*> m_arrBuddyTeamItems;  //好友分组信息,在client端填满
    FC_Client* _client;
};


#endif // FC_BUDDLYLIST_CTRL_H
