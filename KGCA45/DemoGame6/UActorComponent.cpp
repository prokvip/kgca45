#include "UActorComponent.h"
#include "AActor.h"

AActor* UActorComponent::GetOwner()
{
	return m_pOwner;
}

void	UActorComponent::SetOwner(AActor* pOwner)
{
	m_pOwner = pOwner;
}
void   UActorComponent::TickComponent()
{
}

UActorComponent::UActorComponent(std::wstring name):
	UObject(name)
{
	
}
UActorComponent::UActorComponent()
{
	
}
UActorComponent::~UActorComponent()
{
	
}