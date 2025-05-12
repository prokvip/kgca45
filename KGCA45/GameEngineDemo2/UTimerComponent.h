#pragma once
#include "UActorComponent.h"
#include <chrono> // �ð����� ���
using namespace std::chrono;
class UTimerComponent : public UActorComponent
{
	system_clock::time_point  m_Start;
	system_clock::time_point  m_End;
	float	m_fGameTimer = 0.0f;
public:	
	float   GetGameGlobalTimer() const;
public:
	virtual void    TickComponent();
public:
	UTimerComponent(std::wstring name);
	UTimerComponent();
	~UTimerComponent();
};

