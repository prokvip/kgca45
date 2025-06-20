#pragma once
#include "UWorld.h"
#include "TWindow.h"
#include "TDevice.h"
#include "TSound.h"

class TScene : public UObject
{
public:
	std::shared_ptr<AActor>				m_MapObj = nullptr;
	std::shared_ptr<ATimerEffect>		m_TimerObj = nullptr;
	std::shared_ptr<AActor>				m_EffectObj = nullptr;
	std::vector<TSound*>				m_Soundlist;
	std::shared_ptr<UWorld>				m_World;
	std::shared_ptr<APlayerCharacter>	m_Player = nullptr;
public:
	virtual void InitScene();
	virtual void ReleaseScene();
	virtual void Frame();
	virtual void Render();
	virtual LRESULT MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};