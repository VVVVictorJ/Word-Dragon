#pragma once
#include<winsock.h>
#include<iostream>
#include<mysql.h>
class DataBase
{
public:
	DataBase();
	~DataBase();
	int Init();//初始化
	int close();//关闭
	int createTable();//创建表
	int createTable_2();
	bool insert(std::string str);//插入
	bool enquiry(std::string str);//查询
	bool enquiry_2(std::string str);
	bool r_register(std::string str, std::string str_1);//注册用户
private:
	MYSQL mydata;
	std::string tablename;
};

