#pragma once
#include "APawn.h"
/// <summary>
/// ĳ���� ���� ������Ʈ�� �����Ǿ� �ִ�.
/// </summary>
class ACharacter :  public APawn
{
public:
	virtual void  Tick() override;
};

