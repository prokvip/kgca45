#pragma once
#include "UWorld.h"
#include "UInputComponent.h"
#include "UTimerComponent.h"
#include "USoundComponent.h"
#include "TWindow.h"
#include "TDevice.h"
class Sample :  public TWindow
{
	TDevice m_dxDevice;
	using CompPtr = std::shared_ptr<UActorComponent>;
	UWorld								m_World;
	std::list< CompPtr>					m_CompList;
	std::shared_ptr<UTimerComponent>	m_Timer = nullptr;
	std::shared_ptr<UInputComponent>	m_Input = nullptr;
	std::shared_ptr< ACharacter>		m_Player = nullptr;
public:
	void InitGame();
	void ReleaseGame();
	bool GameLoop();
public:
	virtual void GameRun() override;
	virtual LRESULT MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;
};

