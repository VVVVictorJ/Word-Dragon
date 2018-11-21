#pragma once
#include"DataBase.h"
class Rule
{
public:
	Rule();
	~Rule();
	bool judge(std::string);
	bool judge_1(std::string);
	bool insert(std::string);
private:
	void setLast_word(std::string str);
private:
	std::string last_words;
	DataBase	database;//singleton
};

