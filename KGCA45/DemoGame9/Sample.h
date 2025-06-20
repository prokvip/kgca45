#pragma once
#include "UWorld.h"
#include "TWindow.h"
#include "TDevice.h"
#include "TSound.h"
//1)DirectXTK 다운로드 및 컴파일
//2)bin->하위노드 DirectXTK.lib
//3)inc-> 전체를 복사해서 
//4)현재프로젝트의 ../../DirectXTK 폴더 생성, 내부에 lib폴더 생성 및 복사한다.
//5)같은 디렉토리에 inc폴더 생성 및 복사해서 넣는다.
//6)해당 프로젝트의 속성->C++->추가포함디렉토리(../../DirectXTK/Inc;)
//7)해당 프로젝트의 속성->링커>추가라이브러리디렉토리(../../DirectXTK/lib;)

// TGameCore lib
// 빌드후 이벤트 (컴파일 성공 이후에 작동함.)
// copy "A" "B"  // A파일을 B로 복사한다.
// copy "*.h" "..\\..\\TGameCore\\inc"
// copy "..\\..\\output\\TGameCore.lib" "..\\..\\TGameCore\\lib\\TGameCore.lib"

// 프로젝트에서 참조추가(해당라이브러리를 추가한다.);
// 그러면 라이브러리가 수정시 먼저 컴파일하고 프로젝트가 컴파일된다.

class Sample :  public TWindow
{
	TSound*	m_pBGSound = nullptr;
public:
	static TAssetManager<TSound> g_SoundManager;
	bool CreateFMOD();
	TSound* LoadSound(TString filepath);
	void TestFMOD();
public:
	TDevice m_dxDevice;
	std::shared_ptr<AActor>				m_MapObj = nullptr;
	std::shared_ptr<ATimerEffect>		m_TimerObj = nullptr;
	std::shared_ptr<AActor>				m_EffectObj = nullptr;

	TEngine								m_Engine;
	UWorld								m_World;
	
	std::shared_ptr<APlayerCharacter>	m_Player = nullptr;

	ComPtr<ID3D11BlendState> m_AlphaBlendState = nullptr;
	ComPtr<ID3D11BlendState> m_AddBlendState = nullptr;
	ComPtr<ID3D11BlendState> m_SubtrackBlendState = nullptr;
	ComPtr<ID3D11BlendState> m_RevSubtrackBlendState = nullptr;
	ComPtr<ID3D11BlendState> m_MultiplyBlendState = nullptr;
	ComPtr<ID3D11BlendState> m_DualSourceBlendState = nullptr;
	TTexture* m_AlphaTexture = nullptr;
public:
	bool CreateBlendState();

public:
	void InitGame();
	void ReleaseGame();
	bool GameLoop();
public:
	virtual void GameRun() override;
	virtual LRESULT MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;
};

