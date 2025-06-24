#pragma once
#include "TScene.h"


class Sample :  public TWindow
{
	TDevice		m_dxDevice;
	TEngine		m_Engine;
	TSceneManager  m_SceneManager;
public:
	void InitGame();
	void ReleaseGame();
	virtual void GameRun() override;
	virtual LRESULT MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;
};

