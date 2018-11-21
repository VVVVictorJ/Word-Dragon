#include "pch.h"
//#include"encodeprotocol.h"
//
//uint8_t* encodeprotocol::encode(Myprotocol * cy, uint32_t & _len,int version)
//{
//	cy->head.version = version;
//	uint8_t * p = NULL;
//	switch (cy->head.version)
//	{
//	case 0:
//
//		_len = headlen + (uint32_t)(sizeof(cy->r));
//		cy->head.len = _len;
//		p = new uint8_t[_len];
//		headEncode(p, cy, 0);
//		memcpy(p + headlen, (const void*)cy->r.username, sizeof(cy->r.username));
//		memcpy(p + headlen + sizeof(cy->r.username), (const void*)cy->r.password, sizeof(cy->r.password));
//		return p;
//
//	case 1:
//
//		_len = headlen + (uint32_t)(sizeof(cy->l));
//		cy->head.len = _len;
//		p = new uint8_t[_len];
//		headEncode(p, cy, 0);
//		memcpy(p + headlen, (const void*)cy->l.username, sizeof(cy->r.username));
//		memcpy(p + headlen + sizeof(cy->l.username), (const void*)cy->l.password, sizeof(cy->l.password));
//		return p;
//
//	case 2:
//
//		_len = headlen + (uint32_t)(sizeof(cy->s));
//		cy->head.len = _len;
//		p = new uint8_t[_len];
//		headEncode(p, cy, 0);
//		memcpy(p + headlen, (const void*)cy->s.prase, sizeof(cy->s.prase));
//		return p;
//
//	default:
//		break;
//	}
//	return uint8_t();
//}
//
//void encodeprotocol::headEncode(uint8_t * p, Myprotocol * _cy, int version)
//{
//
//	*p = (uint8_t)version;
//	++p;
//	*(uint32_t*)p = htonl(_cy->head.len);
//
//}
