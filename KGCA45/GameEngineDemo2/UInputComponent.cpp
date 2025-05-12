#include "UInputComponent.h"


bool UInputComponent::GetKeyState(int key)
{
	SHORT sKey = GetAsyncKeyState(key);
	// 00000000 00000000  free
	// 10000000 00000000  push
	// 10000000 00000001  hold
	// 0x8000 -> 1000 0000 0000 0000
	if (sKey & 0x8000)
	{
		if (m_dwKeyState[key] == KEY_FREE || 
			m_dwKeyState[key] == KEY_UP)
		{
			m_dwKeyState[key] = KEY_PUSH;
		}
		else
		{
			m_dwKeyState[key] = KEY_HOLD;
		}
		return true;
	}
	else
	{
		if (m_dwKeyState[key] == KEY_PUSH ||
			m_dwKeyState[key] == KEY_HOLD)
		{
			m_dwKeyState[key] = KEY_UP;
		}
		else
		{
			m_dwKeyState[key] = KEY_FREE;
		}
	}
	return false;
}
DWORD	UInputComponent::GetKey(int ikey) const
{
	return m_dwKeyState[ikey];
}
void UInputComponent::TickComponent()
{
	for (int ikey = 0; ikey < 255; ikey++)
	{
		GetKeyState(ikey);
	}
}
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
	//memset(m_dwKeyState, 0, sizeof(m_dwKeyState));
	ZeroMemory(m_dwKeyState, sizeof(m_dwKeyState));
}
UInputComponent::UInputComponent()
{
	ZeroMemory(m_dwKeyState, sizeof(m_dwKeyState));
}
UInputComponent::~UInputComponent()
{

}