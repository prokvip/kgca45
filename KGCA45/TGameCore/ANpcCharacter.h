#pragma once
#include "ACharacter.h"
class ANpcCharacter :  public ACharacter
{
public:
	virtual void  Tick() override;
public:
	ANpcCharacter(std::wstring name) : ACharacter(name) {};
	ANpcCharacter() {};
	~ANpcCharacter() {};
};

