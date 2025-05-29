#include "UTimerComponent.h"
float g_fSPF = 0.0f;
void   UTimerComponent::Reset()
{
    m_Start = m_End = system_clock::now();
}
float   UTimerComponent::GetGameGlobalTimer() const
{
    return m_fGameTimer;
}
void    UTimerComponent::TickComponent()
{    
    m_End = system_clock::now();
    duration<float> sec = m_End - m_Start;
    g_fSPF = m_fSecondPerFrame = sec.count();
    m_fGameTimer += m_fSecondPerFrame;
    m_Start = m_End;     
}
void UTimerComponent::operator=(const UTimerComponent& comp)
{
    SetName(comp.GetName());
    m_Start = comp.m_Start;
    m_End = comp.m_End;
    m_fGameTimer = comp.m_fGameTimer;
}
UTimerComponent::UTimerComponent(const UTimerComponent& comp)
{
    SetName(comp.GetName());
    m_Start = comp.m_Start;
    m_End   = comp.m_End;
    m_fGameTimer = comp.m_fGameTimer;
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