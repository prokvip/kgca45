#pragma once
#include "ACharacter.h"
class UWorld : public UObject
{
public:
	// �迭( ũ�Ⱑ ���� ����(���Ҵ�)�ϴ�.
	// addres = 1000, 10�迭 + �ڿ� �Ҵ� �����ϸ� Ȯ���Ѵ�.
	// new address 11�迭(10�迭 ����)
	std::vector<AActor*>		m_ActorList;
};

