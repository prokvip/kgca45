#pragma once
#include "UWorld.h"
#include "TWindow.h"
#include "TDevice.h"
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

