#pragma once
#include"Rule.h"
class Judgement
{
private:
	Judgement();
	~Judgement();
private:
	static Judgement* judgement;//singleton
	Rule*  CRule;
public:
	static Judgement* getInstance();
	bool judge(std::string str);
	bool ready();
	bool insert(std::string str);
	bool judge_2(std::string str);
};

