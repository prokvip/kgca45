#pragma once
#include "TIntroScene.h"
#include "TLobbyScene.h"
#include "TGameScene.h"
#include "TResultScene.h"

class Sample :  public TWindow
{
	TDevice		m_dxDevice;
	TEngine		m_Engine;
	TScene*		m_pCurrentScene = nullptr;
	std::shared_ptr<TScene> m_pIntroScene = nullptr;
	std::shared_ptr<TScene> m_pLobbyScene = nullptr;
	std::shared_ptr<TScene> m_pInGameScene = nullptr;
	std::shared_ptr<TScene> m_pResultScene = nullptr;	
public:
	void InitGame();
	void ReleaseGame();
	virtual void GameRun() override;
	virtual LRESULT MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;
};

