#include "fc_profile.h"
#include "fc_client.h"
#include <cassert>

//==============================================
//  public function
//==============================================


FC_Profile::FC_Profile(FC_Client* client, QObject *parent ):QObject(parent),_client(client){
}
FC_Profile::~FC_Profile(){
}

QString FC_Profile::account()const{
    return this->_account;
}
void FC_Profile::set_account(const QString& account){
    if(_account != account){

    assert(_account.isEmpty());
    this->_account = account;
    this->_client->set_account(account.toStdString());
    emit accountChanged();
    }
}

//==============================================
//  private function
//==============================================
