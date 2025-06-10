#pragma once
#include "UWorld.h"

#include "TWindow.h"
#include "TDevice.h"
#include "ATimerEffect.h"

//1)DirectXTK 다운로드 및 컴파일
//2)bin->하위노드 DirectXTK.lib
//3)inc-> 전체를 복사해서 
//4)현재프로젝트의 ../../DirectXTK 폴더 생성, 내부에 lib폴더 생성 및 복사한다.
//5)같은 디렉토리에 inc폴더 생성 및 복사해서 넣는다.
//6)해당 프로젝트의 속성->C++->추가포함디렉토리(../../DirectXTK/Inc;)
//7)해당 프로젝트의 속성->링커>추가라이브러리디렉토리(../../DirectXTK/lib;)
class Sample :  public TWindow
{
	TDevice m_dxDevice;
	std::shared_ptr<AActor>				m_MapObj = nullptr;
	std::shared_ptr<ATimerEffect>		m_TimerObj = nullptr;
	std::shared_ptr<AActor>				m_EffectObj = nullptr;

	TEngine								m_Engine;
	UWorld								m_World;
	
	std::shared_ptr<APlayerCharacter>	m_Player = nullptr;

public:
	void InitGame();
	void ReleaseGame();
	bool GameLoop();
public:
	virtual void GameRun() override;
	virtual LRESULT MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;
};

