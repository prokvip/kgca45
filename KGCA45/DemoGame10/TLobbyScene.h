#pragma once
#include "TScene.h"
class TLobbyScene :   public TScene
{
public:
	virtual void InitScene() override;
	virtual void ReleaseScene()override;
	virtual void Frame()override;
	virtual void Render()override;
};

