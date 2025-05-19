#include "UObject.h"
int   UObject::m_iNumInstance = 0;
std::wstring UObject::GetName() const
{
	return m_szName;
}
void UObject::SetName(std::wstring name)
{
	m_szName = name;
}
int			 UObject::GetNumInstance()
{
	return m_iNumInstance;
}
void UObject::operator=(const UObject& comp)
{
	SetName(comp.GetName());
	std::wcout << L" = AActor ";
}
UObject::UObject(const UObject& comp)
{
	SetName(comp.GetName());
	std::wcout << L"Copy AActor ";
}
UObject::UObject(std::wstring name) : m_szName(name)
{
	m_iNumInstance++;
}
UObject::UObject()
{
	m_iNumInstance++;
}
UObject::~UObject()
{
	m_iNumInstance--;
}