#ifndef FC_HEADER_H
#define FC_HEADER_H

//==============================================
//  profile about
//==============================================
/*
    const unsigned FC_PROFILE = 1<<29;
    const unsigned FC_SIGN_IN = FC_PROFILE | 1<<3;
 */
#define FC_HEADER_TYPE_BYTE 4
#define FC_HEADER_BODY_BYTE 8

//part one -- message about
#define FC_MESSAGES unsigned(1<<31)
#define FC_TEXT_MEG unsigned(FC_MESSAGES | 1<<1)

//part two -- friend about
#define FC_FRIENDS unsigned(1<<30)

//part three -- profile about
#define FC_PROFILE unsigned(1<<29)
#define FC_SIGN_IN unsigned(FC_PROFILE | 1<<3)

//part four -- dynamic about
#define FC_DYNAMICS unsigned(1<<28)

//part five -- undifined
#define FC_UNDIFINED unsigned(1<<27)


#define FC_ACC_LEN 8 //account length


#endif // HEADER_H


//==============================================
//  private function
//==============================================
