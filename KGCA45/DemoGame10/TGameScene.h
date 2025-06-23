#pragma once
#include "TScene.h"
class TGameScene :   public TScene
{
public:
	TSound* m_pBGSound = nullptr;
	void	TestFMOD();
public:
	virtual void Process(UPawn* pPlayer);
	virtual void InitScene() override;
	virtual void ReleaseScene()override;
	virtual void Frame()override;
	virtual void Render()override;
	TGameScene(TSceneManager* pOwnder) : TScene(pOwnder)
	{
		m_pOwner = pOwnder;
	}
};

