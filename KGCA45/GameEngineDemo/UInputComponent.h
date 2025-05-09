#pragma once
#include "UActorComponent.h"
class UInputComponent : public UActorComponent
{
public:
	std::wstring GetName() const;
	void		 SetName(std::wstring name);
public:
	UInputComponent(std::wstring name);
	UInputComponent();
	~UInputComponent();
};

