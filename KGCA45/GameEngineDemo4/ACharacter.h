#pragma once
#include "APawn.h"
/// <summary>
/// 캐릭터 전용 컴포턴트가 장착되어 있다.
/// </summary>
class ACharacter :  public APawn
{
public:
	virtual void  Tick() override;
};

