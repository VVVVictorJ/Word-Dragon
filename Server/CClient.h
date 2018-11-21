#pragma once
#include"pch.h"
#include"DataBase.h"
#include"Judgement.h"
#include"Rule.h"

#pragma region Parameter
/**************************************�ָ���*****************************************/

#pragma region Protocol

#pragma region head
typedef struct myprotocolhead
{
	int status;//����status����Э����
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

/**************************************�ָ���*****************************************/
#pragma endregion

#pragma region CClient
class CClient	
{
public:
	CClient();
	explicit CClient(SOCKET s,sockaddr_in addr);
	~CClient();
public:
	static DWORD WINAPI sendThread(void*param);//�����߳���ں�����
	static DWORD WINAPI recvThread_0(void*param);//�����߳���ں�����
	static DWORD WINAPI recvThread_1(void*param);//�����߳���ں�����
	static DWORD WINAPI registerThread(void*param);//ע���߳���ں�����
	static DWORD WINAPI broadcastThread(void*param);//�㲥�߳���ں�����
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
	HANDLE HsendThread;//�����̵߳ľ��
	HANDLE HrecvThread;//�����̵߳ľ��
	HANDLE HrecvThread_1;//�����̵߳ľ��
	HANDLE HbroadcastThread;//�㲥�̵߳ľ��
	//HANDLE HregisterThread;//ע���̵߳ľ��

	HANDLE Hnregister;//��ע��
	myprotocl mp;//���ջ��������£�
	HANDLE Hevent;//ͬ���¼�����
	SOCKET Ssocket;//��ͻ������ӵ��׽���
	SOCKET Bsocket;//�㲥���ӵ��׽���
	sockaddr_in _addr;//�ͻ��˵�ַ
	sockaddr_in b_addr;//�㲥��ַs
	bool B_Is_connected;//����״̬

	char *CP_recvData;//���ջ�����
	char *CP_sendData;//���ͻ�����
	bool B_Issend;//�����Ƿ��ͱ���

};
#pragma endregion

#pragma region ����


/**************************************�ָ���*****************************************/
//����Ҫ����ô��
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
	std::cout << "������ʦ��" << "��˵�ĳ����ǣ�";
	std::cin >> str;
	return Judgement::getInstance()->judge(str);
}
/**************************************�ָ���*****************************************/

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
	std::cout << "����ѧ����" << "��˵�ĳ����ǣ�";
	std::cin >> str;
	return Judgement::getInstance()->judge(str);
}
#pragma endregion
