#include "pch.h"
#include "CClient.h"
#include"DataBase.h"
#include"Judgement.h"
#include"Rule.h"
template <typename T>
std::string toString(const T & t)
{
	std::ostringstream s;
	s << t;
	return s.str();
}
CClient::CClient()
{
}

CClient::CClient(SOCKET s, sockaddr_in addr)
{
	Ssocket = s;
	_addr = addr;
	HsendThread = NULL;
	HrecvThread = NULL;
	HbroadcastThread = NULL;
	//HregisterThread = NULL;
	Hnregister = NULL;
	B_Is_connected = true;
	B_Issend = true;
	Hevent = CreateEvent(NULL, true, false, NULL);
	CP_recvData = new char[1024];
	CP_sendData = new char[1024];
	memset(CP_recvData, 0, 1024);
	memset(CP_sendData, 0, 1024);
}


CClient::~CClient()
{
	delete[]CP_recvData;
	delete[]CP_sendData;
}
//思路
	//广播线程
	//注册线程
	//阻塞注册线程
DWORD __stdcall CClient::sendThread(void * param)
{
	CClient *PClient = static_cast<CClient*>(param);
	//WaitForSingleObject(PClient->Hevent, INFINITE);
	while (PClient->B_Is_connected)
	{
		memset(&PClient->mp, 0, sizeof(myprotocl));
		PClient->mp.s.status = 1011;
		char aaa[20] = "输入你的成语";
		strcpy(PClient->mp.parse.parse, aaa);
		int ret = send(PClient->Ssocket, (char*)&PClient->mp, sizeof(myprotocl), 0);
		if (ret == SOCKET_ERROR)
		{
			int r = WSAGetLastError();
			if (r == WSAEWOULDBLOCK)
			{
				continue;
			}
			else
			{
				return 0;
			}
		}
		else
		{

			break;
		}

		Sleep(1000);
	}
	return 0;
}
//可用模板类改进
DWORD __stdcall CClient::recvThread_0(void * param)
{
	Judgement::getInstance()->ready();
	CClient *PClient = static_cast<CClient*>(param);
	bool flag = false;
	static int falg = 0;
	while (PClient->B_Is_connected)
	{
		memset(&(PClient->mp), 0, sizeof(myprotocl));
		int ret = recv(PClient->Ssocket, (char*)&PClient->mp, sizeof(myprotocl), 0);
		if (ret == SOCKET_ERROR)
		{
			int r = WSAGetLastError();
			if (WSAEWOULDBLOCK == r)
			{
				Sleep(20);
				continue;
			}
			else if (WSAENETDOWN == r)
			{
				std::cout << "recvthread error!" << std::endl;
				break;
			}
			else
			{
				std::cout << "recvthread error!!" << std::endl;
				break;
			}
		}
		if (1 == PClient->mp.s.status)
		{
			//注册
			//DataBase db;
			//db.enquiry(toString(PClient->mp.login.username));
			std::cout << "有人来注册" << std::endl;
			//创建表
				//插入数据
			if (0 == Judgement::getInstance()->insert(std::to_string(PClient->mp.reg.username)))
			{
				PClient->mp.s.status = 1001;
				int ret = send(PClient->Ssocket, (char*)&PClient->mp, sizeof(myprotocl), 0);
			}
			else
			{

				std::cout << "error" << std::endl;
				PClient->DisConnect();
			};

		}
		if (2 == PClient->mp.s.status)
		{//登陆			
			std::cout << "有人来登陆" << std::endl;
			if (0 == Judgement::getInstance()->judge_2(std::to_string(PClient->mp.login.username)))
			{
				PClient->mp.s.status = successfullogin;
				int ret = send(PClient->Ssocket, (char*)&PClient->mp, sizeof(myprotocl), 0);
				return 0;
			}
			else
			{
				PClient->mp.s.status = usernamepasfault;
				int ret = send(PClient->Ssocket, (char*)&PClient->mp, sizeof(myprotocl), 0);
			}

		}
#pragma region waste
		//if (3 == PClient->mp.s.status)
		//{
		//	std::cout << "有人来发成语" << std::endl;
		//	std::string str(PClient->mp.parse.parse);
		//	if (0==Judgement::getInstance()->judge(str))
		//	{
		//		std::cout << "111" << std::endl;
		//		char a[20] = { "you 'e right." };
		//		PClient->mp.s.status = 1111;
		//		strcpy(PClient->mp.parse.parse,a);
		//		send(PClient->Ssocket, (char*)&PClient->mp, sizeof(myprotocl), 0);
		//		PClient->DisConnect();
		//	}
		//	else
		//	{
		//		std::cout << "11111" << std::endl;
		//		char b[20] = { "you 'e worry." };
		//		PClient->mp.s.status = 1000;
		//		strcpy_s(PClient->mp.parse.parse, strlen(b) + 1, b);
		//		send(PClient->Ssocket, (char*)&PClient->mp, sizeof(myprotocl), 0);
		//		PClient->version = false;
		//		PClient->DisConnect();
		//		//关闭该线程
		//	}
		//	
		//}	//校验

#pragma endregion
	}
	return 0;
}

DWORD __stdcall CClient::recvThread_1(void * param)
{
	Judgement::getInstance()->ready();
	CClient *PClient = static_cast<CClient*>(param);
	bool flag = false;
	static int falg = 0;
	while (PClient->B_Is_connected)
	{
		memset(&(PClient->mp), 0, sizeof(myprotocl));
		int ret = recv(PClient->Ssocket, (char*)&PClient->mp, sizeof(myprotocl), 0);
		if (ret == SOCKET_ERROR)
		{
			int r = WSAGetLastError();
			if (WSAEWOULDBLOCK == r)
			{
				Sleep(20);
				continue;
			}
			else if (WSAENETDOWN == r)
			{
				std::cout << "recvthread error!" << std::endl;
				break;
			}
			else
			{
				std::cout << "recvthread error!!" << std::endl;
				break;
			}
		}
		if (3 == PClient->mp.s.status)
		{
			std::cout << "有人来发成语" << std::endl;
			std::string str(PClient->mp.parse.parse);
			if (0 == Judgement::getInstance()->judge(str))
			{
				std::cout << "111" << std::endl;
				char a[20] = { "you 'e right." };
				PClient->mp.s.status = 1111;
				strcpy(PClient->mp.parse.parse, a);
				send(PClient->Ssocket, (char*)&PClient->mp, sizeof(myprotocl), 0);
				PClient->DisConnect();
			}
			else
			{
				std::cout << "11111" << std::endl;
				char b[20] = { "you 'e worry." };
				PClient->mp.s.status = 1000;
				strcpy_s(PClient->mp.parse.parse, strlen(b) + 1, b);
				send(PClient->Ssocket, (char*)&PClient->mp, sizeof(myprotocl), 0);
				PClient->version = false;
				WSACleanup();
				PClient->DisConnect();
				//关闭该线程
			}

			//校验
		}
	}
	return 0;
	return 0;
}
//只在60s内启动该线程
DWORD CClient::registerThread(void * param)
{
	CClient *PClient = static_cast<CClient*>(param);
	clock_t start, finished;
	start = clock();
	while (PClient->B_Is_connected)
	{
		finished = clock();
		if (((finished - start) / CLOCKS_PER_SEC) > 60)
		{
			//启动send发送进入观赛模式

			return 0;
		}
		memset(PClient->CP_recvData, 0, 1024);
		int ret = recv(PClient->Ssocket, PClient->CP_recvData, 1024, 0);
		if (ret == SOCKET_ERROR)
		{
			int r = WSAGetLastError();
			if (WSAEWOULDBLOCK == r)
			{
				Sleep(20);
				continue;
			}
			else if (WSAENETDOWN == r)
			{
				std::cout << "recvthread error!" << std::endl;
				break;
			}
			else
			{
				std::cout << "recvthread error!!" << std::endl;
				break;
			}
		}

	}
	return 0;
}

#pragma region waste
//template<typename T>
//DWORD __stdcall CClient::recvThread(T * param)
//{
//	T *PClient = param;
//
//	while (PClient->B_Is_connected)
//	{
//		memset(PClient->CP_recvData, 0, 1024);
//		int ret = recv(PClient->Ssocket, PClient->CP_recvData, 1024, 0);
//		if (ret == SOCKET_ERROR)
//		{
//			int r = WSAGetLastError();
//			if (WSAEWOULDBLOCK == r)
//			{
//				Sleep(20);
//				continue;
//			}
//			else if (WSAENETDOWN == r)
//			{
//				std::cout << "recvthread error!" << std::endl;
//			}
//			else
//			{
//				std::cout << "recvthread error!!" << std::endl;
//			}
//		}
//		else
//		{
//			std::cout << "receive : " << PClient->CP_recvData << std::endl;
//			SetEvent(PClient->Hevent);
//			PClient->B_Issend = true;
//		}
//	}
//	return 0;
//}
//线程间通信
#pragma endregion

DWORD CClient::broadcastThread(void * param)
{
	CClient *PClient = static_cast<CClient*>(param);

	while (PClient->B_Is_connected)
	{


	}
	return 0;
}

bool CClient::Is_connect()
{
	return B_Is_connected;
}

bool CClient::DisConnect()
{
	B_Is_connected = false;
	return false;
}


bool CClient::startRunning()
{
	HrecvThread = CreateThread(NULL, 0, recvThread_0, (void*)this, 0, NULL);
	std::cout << "启动recvThread" << std::endl;
	if (NULL == HrecvThread)
	{
		return false;
	}
	//HsendThread = CreateThread(NULL, 0, sendThread, (void*)this, 0, NULL);
	//std::cout << "启动 send" << std::endl;
	//if (NULL == HsendThread)
	//{
	//	return false;
	//}

	return true;
}

bool CClient::startSending()
{
	HsendThread = CreateThread(NULL, 0, sendThread, (void*)this, 0, NULL);
	std::cout << "startSending" << std::endl;
	if (NULL== HsendThread)
	{
		return false;
	}
	return false;
}

bool CClient::startRunning_1()
{
	HrecvThread_1 = CreateThread(NULL, 0, recvThread_1, (void*)this, 0, NULL);
	std::cout << "startRunning_1" << std::endl;
	if (NULL == HrecvThread_1)
	{
		return false;
	}
	return false;
}
