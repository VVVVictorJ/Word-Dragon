#include "pch.h"
#include "encode.h"


encode::encode()
{
}

void encode::_encode(myprotocl mp,int version)
{
	mp.s.status = version;
	switch (mp.s.status)
	{
	case 1:

	default:
		break;
	}
}


encode::~encode()
{
}
