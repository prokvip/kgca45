#include "UTimerComponent.h"
float   UTimerComponent::GetGameGlobalTimer() const
{
    return m_fGameTimer;
}
void    UTimerComponent::TickComponent()
{    
    m_End = system_clock::now();
    duration<float> sec = m_End - m_Start;
    float fTimer = sec.count();
    m_fGameTimer += fTimer;
    m_Start = m_End;     
}

UTimerComponent::UTimerComponent(std::wstring name)
	: UActorComponent(name)
{
    m_Start = system_clock::now();
}
UTimerComponent::UTimerComponent()
{
    m_Start = system_clock::now();
}

UTimerComponent::~UTimerComponent()
{

}