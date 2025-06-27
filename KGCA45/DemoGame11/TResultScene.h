#pragma once
#include "TScene.h"
class TResultScene :  public TScene
{
public:
	virtual void Process(APawn* pPlayer);
	virtual void InitScene() override;
	virtual void ReleaseScene()override;
	virtual void Tick()override;
	virtual void Render()override;
	TResultScene(TSceneManager* pOwnder) : TScene(pOwnder)
	{
		m_pOwner = pOwnder;
	}
};

