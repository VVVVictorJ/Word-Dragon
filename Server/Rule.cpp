#include "pch.h"
#include "Rule.h"


Rule::Rule():last_words("NULL")
{
	if (database.Init()) { std::cout << "666" << std::endl; };
	if(database.createTable()) { std::cout << "777" << std::endl; };
	if (database.createTable_2())
	{
		std::cout << "888" << std::endl;
	}
}


Rule::~Rule()
{
}

bool Rule::judge(std::string str)
{
	if (-1==database.enquiry(str))
	{
		return -1;
	}
	if (last_words != "NULL")
	{
		if (last_words[3] != str[0] || last_words[4] != str[1])
		{
			return false;
		}
	}
	setLast_word(str);
	return 0;
}

bool Rule::judge_1(std::string str)
{
	if (!database.enquiry_2(str))
	{
		return 0;
	}
	return false;
}

bool Rule::insert(std::string str)
{
	if (!database.insert(str))
	{
		return 0;
	}
	return true;
}

void Rule::setLast_word(std::string str)
{
	last_words = str;
}
