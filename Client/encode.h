#pragma once
#include"pch.h"
typedef struct myprotocolhead
{
	int status;//根据status处理协议体
}head;
typedef struct _register
{
	int username;
	int password;
}R;
typedef struct _login
{
	int username;
	int password;
}L;
typedef struct _parse
{
	char parse[20];
}P;
typedef struct myprotocl
{
	head s;
	union
	{
		R reg;
		L login;
		P parse;
	};
}myprotocol;

class encode
{
public:
	encode();
	void _encode(myprotocl mp,int version);
	~encode();
};

