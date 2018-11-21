#pragma once
#include"pch.h"
#include"DataBase.h"
#include"Judgement.h"
#include"Rule.h"

#pragma region Parameter
/**************************************分割线*****************************************/

#pragma region Protocol

#pragma region head
typedef struct myprotocolhead
{
	int status;//根据status处理协议体
}head;
#pragma endregion

#pragma region register
typedef struct _register
{
	int username;
	int password;
}R;
#pragma endregion

#pragma region login
typedef struct _login
{
	int username;
	int password;
}L;
#pragma endregion

#pragma region parse
typedef struct _parse
{
	char parse[20];
}P;
#pragma endregion

#pragma region protocol
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
#pragma endregion

#pragma endregion

#pragma region parameter
#define successfulregistered 1001
#define someonehasregistered 1010
#define outofrange			 -1	
#define	usernamepasfault	 5
#define	successfullogin		 1002
#define success				 1111
#define urworry				 1000
#pragma endregion

/**************************************分割线*****************************************/
#pragma endregion

#pragma region CClient
class CClient	
{
public:
	CClient();
	explicit CClient(SOCKET s,sockaddr_in addr);
	~CClient();
public:
	static DWORD WINAPI sendThread(void*param);//发送线程入口函数。
	static DWORD WINAPI recvThread_0(void*param);//接收线程入口函数。
	static DWORD WINAPI recvThread_1(void*param);//接收线程入口函数。
	static DWORD WINAPI registerThread(void*param);//注册线程入口函数。
	static DWORD WINAPI broadcastThread(void*param);//广播线程入口函数。
	bool Is_connect();
	bool DisConnect();
	bool startRunning();
	bool startSending();
	bool startRunning_1();

	inline int act(std::string str)
	{
		return Judgement::getInstance()->judge(str);
	}
	bool version = true;
private:
	HANDLE HsendThread;//发送线程的句柄
	HANDLE HrecvThread;//接收线程的句柄
	HANDLE HrecvThread_1;//接收线程的句柄
	HANDLE HbroadcastThread;//广播线程的句柄
	//HANDLE HregisterThread;//注册线程的句柄

	HANDLE Hnregister;//无注册
	myprotocl mp;//接收缓冲区（新）
	HANDLE Hevent;//同步事件对象
	SOCKET Ssocket;//与客户端连接的套接字
	SOCKET Bsocket;//广播连接的套接字
	sockaddr_in _addr;//客户端地址
	sockaddr_in b_addr;//广播地址s
	bool B_Is_connected;//连接状态

	char *CP_recvData;//接收缓冲区
	char *CP_sendData;//发送缓冲区
	bool B_Issend;//控制是否发送变量

};
#pragma endregion

#pragma region 废作


/**************************************分割线*****************************************/
//不需要分这么清
class Teacher :public CClient
{
public:
	Teacher();
	~Teacher();
	Teacher(int i) :index(i) {}
public:
	int act();
private:
	int index;

};

Teacher::Teacher() :index(0)
{
}

Teacher::~Teacher()
{
}

inline int Teacher::act()
{
	std::string str;
	std::cout << "我是老师，" << "我说的成语是：";
	std::cin >> str;
	return Judgement::getInstance()->judge(str);
}
/**************************************分割线*****************************************/

class student :public CClient
{
public:
	student();
	~student();
	explicit student(int i) :index(i) {}
public:
	int act();
private:
	int index;
};

student::student() :index(0)
{
}

student::~student()
{
}

inline int student::act()
{
	std::string str;
	std::cout << "我是学生，" << "我说的成语是：";
	std::cin >> str;
	return Judgement::getInstance()->judge(str);
}
#pragma endregion
