#include "UInputComponent.h"
std::wstring UInputComponent::GetName() const
{
	return UActorComponent::GetName();
}
void UInputComponent::SetName(std::wstring name)
{
	std::wstring inputname = L"UInputComponent\\";
	inputname += name;
	UActorComponent::SetName(inputname);
}
UInputComponent::UInputComponent(std::wstring name) 
	: UActorComponent(name)
{	
	int k = 0;
}
UInputComponent::UInputComponent()
{

}
UInputComponent::~UInputComponent()
{

}