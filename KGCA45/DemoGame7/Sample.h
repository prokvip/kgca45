#pragma once
#include "UWorld.h"

#include "TWindow.h"
#include "TDevice.h"
#include "ATimerEffect.h"

//1)DirectXTK �ٿ�ε� �� ������
//2)bin->������� DirectXTK.lib
//3)inc-> ��ü�� �����ؼ� 
//4)����������Ʈ�� ../../DirectXTK ���� ����, ���ο� lib���� ���� �� �����Ѵ�.
//5)���� ���丮�� inc���� ���� �� �����ؼ� �ִ´�.
//6)�ش� ������Ʈ�� �Ӽ�->C++->�߰����Ե��丮(../../DirectXTK/Inc;)
//7)�ش� ������Ʈ�� �Ӽ�->��Ŀ>�߰����̺귯�����丮(../../DirectXTK/lib;)
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

