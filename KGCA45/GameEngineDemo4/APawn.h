#pragma once
#include "AActor.h"
/// <summary>
/// 이동 컴포넌트가 붙어 있다.
/// </summary>
class APawn : public AActor
{
public:
	virtual void  Tick() override;
};

