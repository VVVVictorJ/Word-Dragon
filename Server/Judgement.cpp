#include "pch.h"
#include "Judgement.h"

Judgement * Judgement::judgement = NULL;//ȫ�ֱ�����ʼ��

Judgement::Judgement()
{

	CRule = NULL;
}


Judgement::~Judgement()
{
	if (CRule)
	{
		delete CRule;
	}
}

Judgement * Judgement::getInstance()
{
	if (NULL==judgement)
	{
		judgement = new Judgement();//��������
	}
	return judgement;
}

bool Judgement::judge(std::string str)
{
	return CRule->judge(str);
}



bool Judgement::ready()
{
	CRule = new Rule();
	return true;
}

bool Judgement::insert(std::string str)
{
	return CRule->insert(str);
}



bool Judgement::judge_2(std::string str)
{
	return CRule->judge_1(str);
}
