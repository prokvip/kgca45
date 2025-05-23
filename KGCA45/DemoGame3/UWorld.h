#pragma once
#include "ACharacter.h"

using sharedActor	= std::shared_ptr<AActor>;
using TArray		= std::vector<sharedActor>;
// stl::map<key, value> list;
using TMap			= std::map<std::wstring, sharedActor>;

class UWorld : public UObject
{
public:
	// �迭( ũ�Ⱑ ���� ����(���Ҵ�)�ϴ�.
	// addres = 1000, 10�迭 + �ڿ� �Ҵ� �����ϸ� Ȯ���Ѵ�.
	// new address 11�迭(10�迭 ����)
	//std::vector<std::unique_ptr<AActor>> m_ActorList;
	//TArray		m_ActorList;
	TMap			m_ActorList;
};

