#pragma once
#include "AActor.h"
/// <summary>
/// �̵� ������Ʈ�� �پ� �ִ�.
/// </summary>
class APawn : public AActor
{
public:
	virtual void  Tick() override;
	APawn(std::wstring name) : AActor(name) {};
	APawn() {};
	~APawn() {};
};

