#ifndef FC_MESSAGE_H
#define FC_MESSAGE_H

#include <cstdlib>

#define FC_MESSAGE_HEADER_LENGTH 24
/*
 * 消息包括消息头部和消息body
 * 	消息头部包括消息类型和消息body的大小
 * 	消息body包括消息的具体内容
 *
 * this->_body_length include the last '\0'
 */

class FC_Message
{
public:
    FC_Message();
    FC_Message(const FC_Message& msg);
    ~FC_Message();

    //getter
    unsigned header_length()const;
    unsigned body_length()const;
    char* userAccount()const;
    char* pawdOrSuserId()const;
    unsigned mess_length()const;
    unsigned mess_type()const;
    char* header()const;
    char* body()const;

    //setter
   // void set_body_length(unsigned body_len);
    void set_header(unsigned type, unsigned body_len,char*userId,char* pu);
    void set_message_type(unsigned type);
    void set_body(const char*data,unsigned len);
    void set_userAccount(const char* data,unsigned len);
    void set_pawdOrSuserID(const char*data,unsigned len);

    //reset message
    void reset_message();
private:
    void apply_memory(unsigned len); //apply for new memory
private:
    char* _data;
//    unsigned _header_length; //unsigned 4 byte
//    unsigned _body_length; //the length include the last '\0'
//    unsigned _message_type;
};

#endif // FC_MESSAGE_H
