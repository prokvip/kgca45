#pragma once
#include "TScene.h"
class TLobbyScene :   public TScene
{
public:
	virtual void Process(UPawn* pPlayer);
	virtual void InitScene() override;
	virtual void ReleaseScene()override;
	virtual void Frame()override;
	virtual void Render()override;
	TLobbyScene(TSceneManager* pOwnder) : TScene(pOwnder)
	{
		m_pOwner = pOwnder;
	}
};

