#pragma once
#include "TScene.h"

class TGameScene :   public TScene
{
public:
	TNpcManager    m_NpcManager;
	TSound* m_pBGSound = nullptr;
	void	TestFMOD();
	
public:
	virtual void Process(APawn* pPlayer);
	virtual void InitScene() override;
	virtual void ReleaseScene()override;
	virtual void Frame()override;
	virtual void Render()override;
	TGameScene(TSceneManager* pOwnder) : TScene(pOwnder)
	{
		m_pOwner = pOwnder;
	}
};

