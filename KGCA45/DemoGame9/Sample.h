#pragma once
#include "UWorld.h"
#include "TWindow.h"
#include "TDevice.h"
#include "TSound.h"
//1)DirectXTK �ٿ�ε� �� ������
//2)bin->������� DirectXTK.lib
//3)inc-> ��ü�� �����ؼ� 
//4)����������Ʈ�� ../../DirectXTK ���� ����, ���ο� lib���� ���� �� �����Ѵ�.
//5)���� ���丮�� inc���� ���� �� �����ؼ� �ִ´�.
//6)�ش� ������Ʈ�� �Ӽ�->C++->�߰����Ե��丮(../../DirectXTK/Inc;)
//7)�ش� ������Ʈ�� �Ӽ�->��Ŀ>�߰����̺귯�����丮(../../DirectXTK/lib;)

// TGameCore lib
// ������ �̺�Ʈ (������ ���� ���Ŀ� �۵���.)
// copy "A" "B"  // A������ B�� �����Ѵ�.
// copy "*.h" "..\\..\\TGameCore\\inc"
// copy "..\\..\\output\\TGameCore.lib" "..\\..\\TGameCore\\lib\\TGameCore.lib"

// ������Ʈ���� �����߰�(�ش���̺귯���� �߰��Ѵ�.);
// �׷��� ���̺귯���� ������ ���� �������ϰ� ������Ʈ�� �����ϵȴ�.

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

