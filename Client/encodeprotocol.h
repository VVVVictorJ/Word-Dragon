#pragma once
///*
//   |_____|check|_____|
//   |_|_____len_____|_|
//   |__protocol-body__|
//*/
///*
//	Э
//	��
//	ͷ
//*/
//struct Cyprotocol
//{
//	uint8_t version;
//	uint32_t len;
//};
//
///*
//	attribute-ע��
//*/
//typedef	struct _register
//{
//	long username;
//	int password;
//}_reg;
//
///*
//	attribute-��½
//*/
//typedef struct _login
//{
//	long username;
//	int password;
//}_log;
//
///*
//	attribute-���ͳ���
//*/
//typedef struct _send
//{
//	char prase[30];
//}_send;
//
///*
//	Э
//	��
//	��
//*/
//struct Myprotocol
//{
//	Cyprotocol head;
//	union 
//	{
//		_reg r;
//		_log l;
//		_send s;
//	};
//};
//
////------------------------------------------------------//
//
//typedef enum status
//{
//	On_init=0,
//	On_head=1,
//	On_body=2,
//} _status;
//
//enum 
//{
//	headlen = 8
//};
//
////------------------------------------------------------//
//
//class encodeprotocol
//{
//public:
//	uint8_t *encode(Myprotocol *cy, uint32_t &_len,int version);
//	
//protected:
//
//private:
//	void headEncode(uint8_t * p, Myprotocol *_cy, int version);
//
//};
//
//class decodeprotocol
//{
//public:
//
//protected:
//	decodeprotocol();
//	~decodeprotocol();
//private:
//
//};
//
//decodeprotocol::decodeprotocol()
//{
//}
//
//decodeprotocol::~decodeprotocol()
//{
//}
