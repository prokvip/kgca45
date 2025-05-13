#pragma once
#include "ACharacter.h"
class UWorld : public UObject
{
public:
	// 배열( 크기가 조절 가능(재할당)하다.
	// addres = 1000, 10배열 + 뒤에 할당 가능하면 확장한다.
	// new address 11배열(10배열 복사)
	std::vector<AActor*>		m_ActorList;
};

