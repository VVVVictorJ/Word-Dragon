#pragma once
#include<winsock.h>
#include<iostream>
#include<mysql.h>
class DataBase
{
public:
	DataBase();
	~DataBase();
	int Init();//��ʼ��
	int close();//�ر�
	int createTable();//������
	int createTable_2();
	bool insert(std::string str);//����
	bool enquiry(std::string str);//��ѯ
	bool enquiry_2(std::string str);
	bool r_register(std::string str, std::string str_1);//ע���û�
private:
	MYSQL mydata;
	std::string tablename;
};

