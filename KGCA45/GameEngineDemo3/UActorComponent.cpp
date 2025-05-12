#include "UActorComponent.h"

int   UActorComponent::m_iNumInstance = 0;
std::wstring UActorComponent::GetName() const
{
	return m_szName;
}
void UActorComponent::SetName(std::wstring name)
{
	m_szName = name;
}
int			 UActorComponent::GetNumInstance() 
{
	return m_iNumInstance;
}
UActorComponent::UActorComponent(std::wstring name): m_szName(name)
{
	m_iNumInstance++;
}
UActorComponent::UActorComponent()
{
	m_iNumInstance++;
}
UActorComponent::~UActorComponent()
{
	m_iNumInstance--;
}