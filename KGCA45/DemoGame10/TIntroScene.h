#pragma once
#include "TScene.h"
class TIntroScene :  public TScene
{
public:
	virtual void Process(UPawn* pPlayer);
	virtual void InitScene() override;
	virtual void ReleaseScene()override;
	virtual void Tick()override;
	virtual void Render()override;
	TIntroScene(TSceneManager* pOwnder) : TScene(pOwnder)
	{
		m_pOwner = pOwnder;
	}
};

