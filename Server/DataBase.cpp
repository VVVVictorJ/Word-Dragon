#include "pch.h"
#include "DataBase.h"

#pragma region parameter
#define srvAddr		"localhost"
#define user		"root"
#define password	"081154"
#define database	"words"
#define tablename	"words"
#define username	"username"
#define port		3306
#pragma endregion

#pragma region construct&deconstruct
DataBase::DataBase()
{
}

DataBase::~DataBase()
{
}
#pragma endregion

#pragma region Init & Close
int DataBase::Init()
{
	// 初始化数据库
	if (0 != mysql_library_init(0, NULL, NULL))
	{
		std::cout << "mysql_library_init() failed" << std::endl;
		return -1;
	}

	// 初始化数据结构
	if (NULL == mysql_init(&mydata))
	{
		std::cout << "mysql_init() failed" << std::endl;
		return -1;
	}

	// 设置字符集，否则无法处理中文
	if (0 != mysql_options(&mydata, MYSQL_SET_CHARSET_NAME, "gbk"))
	{
		std::cout << "mysql_options() failed" << std::endl;
		return -1;
	}

	// 连接数据库
	if (NULL == mysql_real_connect(&mydata, srvAddr, user, password, database, port, NULL, 0))
	{
		std::cout << "mysql_real_connect() failed" << std::endl;
		return -1;
	}

	return 0;
}

int DataBase::close()
{
	mysql_close(&mydata);
	mysql_server_end();
	return 0;
}
#pragma endregion

#pragma region creatable&_2
int DataBase::createTable()
{
	int count = 0;
	MYSQL_RES* result = NULL;

	if (0 == mysql_query(&mydata, "select table_name from information_schema.tables where TABLE_SCHEMA='test' \
	and TABLE_NAME='parse'"))
	{
		result = mysql_store_result(&mydata);
		count = mysql_num_rows(result);
	}
	else
	{
		printf("Error: %s\n\n", mysql_error(&mydata));
	}

	if (count > 0)		// 表已存在
		return 0;
	 

	std::string sqlstr;
	sqlstr = "CREATE TABLE IF NOT EXISTS words";
	sqlstr += "(";
	sqlstr +=
		"id INT UNSIGNED NOT NULL AUTO_INCREMENT PRIMARY KEY COMMENT 'ID',";
	sqlstr +=
		"name VARCHAR(100) CHARACTER SET gb2312 COLLATE gb2312_chinese_ci NULL COMMENT 'name'";
	sqlstr += ");";


	if (0 == mysql_query(&mydata, sqlstr.c_str()))
	{
		//cout << "mysql_query() create table succeed" << endl;
	}
	else
	{
		std::cout << "mysql_query() create table failed" << std::endl;
		mysql_close(&mydata);
		return -1;
	}


	sqlstr = "INSERT INTO words(name) VALUES	\
		('胸有成竹'),('竹报平安'),('安富尊荣'),('荣华富贵'),('贵而贱目'),('目无余子'),('子虚乌有'),	\
		('有目共睹'),('睹物思人'),('人中骐骥'),('骥子龙文'),('文质彬彬'),('彬彬有礼'),('礼贤下士')	\
		;";

	if (0 == mysql_query(&mydata, sqlstr.c_str()))
	{
		//cout << "mysql_query() insert data succeed" << endl;
	}
	else
	{
		std::cout << "mysql_query() insert data failed" << std::endl;
		mysql_close(&mydata);
		return -1;
	}
	return 0;
}

int DataBase::createTable_2()
{
	int count = 0;
	MYSQL_RES* result = NULL;

	if (0 == mysql_query(&mydata, "select table_name from information_schema.tables where TABLE_SCHEMA='test' \
	and TABLE_NAME='username'"))
	{
		result = mysql_store_result(&mydata);
		count = mysql_num_rows(result);
	}
	else
	{
		printf("Error: %s\n\n", mysql_error(&mydata));
	}

	if (count > 0)		// 表已存在
		return true;


	std::string sqlstr;
	sqlstr = "CREATE TABLE IF NOT EXISTS username";
	sqlstr += "(";
	sqlstr +=
		"id INT UNSIGNED NOT NULL AUTO_INCREMENT PRIMARY KEY COMMENT 'ID',";
	sqlstr +=
		"name VARCHAR(100) CHARACTER SET gb2312 COLLATE gb2312_chinese_ci NULL COMMENT 'name'";
	sqlstr += ");";


	if (0 == mysql_query(&mydata, sqlstr.c_str()))
	{
		//cout << "mysql_query() create table succeed" << endl;
	}
	else
	{
		std::cout << "mysql_query() create table failed" << std::endl;
		mysql_close(&mydata);
		return -1;
	}

	if (0 == mysql_query(&mydata, sqlstr.c_str()))
	{
		//cout << "mysql_query() insert data succeed" << endl;
	}
	else
	{
		std::cout << "mysql_query() insert data failed" << std::endl;
		mysql_close(&mydata);
		return -1;
	}
	return 0;
}
#pragma endregion

#pragma region insert
bool DataBase::insert(std::string str)
{
	std::string sqlstr;
	sqlstr = "insert into username(name) values('";
	sqlstr += str;
	sqlstr += "');";

	MYSQL_RES *result = NULL;
	int rowcount = 0;

	if (0 == mysql_query(&mydata, sqlstr.c_str()))
	{

			
	}
	else
	{
		mysql_close(&mydata);
		return false;
	}

	mysql_free_result(result);

	return 0;
}
#pragma endregion

#pragma region enquiry&_2
bool DataBase::enquiry(std::string str)
{
	std::string sqlstr;
	sqlstr = "select * from ";
	sqlstr += tablename;
	sqlstr += " where name = '";
	sqlstr += str;
	sqlstr += "';";

	MYSQL_RES *result = NULL;
	int rowcount = 0;

	if (0 == mysql_query(&mydata, sqlstr.c_str()))
	{
		result = mysql_store_result(&mydata);
		rowcount = mysql_num_rows(result);

		if (rowcount > 0)
		{
			return 0;
		}

		else
			return -1;
	}
	else
	{
		mysql_close(&mydata);
		return false;
	}

	mysql_free_result(result);

	return true;
}

bool DataBase::enquiry_2(std::string str)
{
	std::string sqlstr;
	sqlstr = "select * from ";
	sqlstr += username;
	sqlstr += " where name = '";
	sqlstr += str;
	sqlstr += "';";

	MYSQL_RES *result = NULL;
	int rowcount = 0;

	if (0 == mysql_query(&mydata, sqlstr.c_str()))
	{
		result = mysql_store_result(&mydata);
		rowcount = mysql_num_rows(result);

		if (rowcount > 0)
			return true;
		else
			return false;
	}
	else
	{
		mysql_close(&mydata);
		return false;
	}

	mysql_free_result(result);

	return true;
	return false;
}
#pragma endregion

#pragma region waste
bool DataBase::r_register(std::string str, std::string str_1)
{
	int count = 0;
	MYSQL_RES* result = NULL;

	if (0 == mysql_query(&mydata, "select table_name from information_schema.tables where TABLE_SCHEMA='test' \
	and TABLE_NAME='customer'"))
	{
		result = mysql_store_result(&mydata);
		count = mysql_num_rows(result);
	}
	else
	{
		printf("Error: %s\n\n", mysql_error(&mydata));
	}

	if (count > 0)		// 表已存在
		return 0;


	std::string sqlstr;
	sqlstr = "CREATE TABLE IF NOT EXISTS customer";
	sqlstr += "(";
	sqlstr +=
		"id INT UNSIGNED NOT NULL AUTO_INCREMENT PRIMARY KEY COMMENT 'ID',";
	sqlstr +=
		"name VARCHAR(100) CHARACTER SET gb2312 COLLATE gb2312_chinese_ci NULL COMMENT 'name'";
	sqlstr +=
		"number VARCHAR(100) NULL COMMENT 'number'";
	sqlstr += ");";


	if (0 == mysql_query(&mydata, sqlstr.c_str()))
	{
		//cout << "mysql_query() create table succeed" << endl;
	}
	else
	{
		std::cout << "mysql_query() create table failed" << std::endl;
		mysql_close(&mydata);
		return -1;
	}

	if (str.size() != 13)
	{
		return	0;
	}
	sqlstr = "INSERT INTO customer(name) VALUES";
	sqlstr += str;

	if (0 == mysql_query(&mydata, sqlstr.c_str()))
	{
		//cout << "mysql_query() insert data succeed" << endl;
	}
	else
	{
		std::cout << "mysql_query() insert data failed" << std::endl;
		mysql_close(&mydata);
		return -1;
	}

	sqlstr = "INSERT INTO customer(number) VALUES";
	sqlstr += str_1;

	if (0 == mysql_query(&mydata, sqlstr.c_str()))
	{
		//cout << "mysql_query() insert data succeed" << endl;
	}
	else
	{
		std::cout << "mysql_query() insert data failed" << std::endl;
		mysql_close(&mydata);
		return -1;
	}
	return false;
}

#pragma endregion


