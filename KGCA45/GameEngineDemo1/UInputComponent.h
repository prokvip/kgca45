#pragma once
#include "UActorComponent.h"
class UInputComponent : public UActorComponent
{
public:
	std::wstring GetName() const;
	void		 SetName(std::wstring name);
	virtual  void Tick() {}
public:
	UInputComponent(std::wstring name);
	UInputComponent();
	~UInputComponent();
};

