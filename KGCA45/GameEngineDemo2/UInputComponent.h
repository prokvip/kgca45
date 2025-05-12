#pragma once
#include "UActorComponent.h"
/// <summary>
/// 키보드 & 마우스 입력 처리
/// </summary>
enum {KEY_FREE, KEY_PUSH, KEY_HOLD, KEY_UP};
class UInputComponent : public UActorComponent
{
private:
	DWORD			m_dwKeyState[255];
private:
	bool			GetKeyState(int key);
public:	
	DWORD			GetKey(int ikey) const;
	std::wstring	GetName() const;
	void			SetName(std::wstring name);
	virtual  void	TickComponent();	
public:
	UInputComponent(std::wstring name);
	UInputComponent();
	~UInputComponent();
};

