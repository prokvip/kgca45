#pragma once
#include "ACharacter.h"
class APlayerCharacter :   public ACharacter
{
public:
	virtual void Tick() override;
public:
	APlayerCharacter(std::wstring name) : ACharacter(name) {};
	APlayerCharacter() {};
	~APlayerCharacter() {};
};

