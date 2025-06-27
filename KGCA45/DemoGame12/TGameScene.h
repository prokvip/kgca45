#pragma once
#include "TScene.h"

class ANpcKillEffect : public ATimerEffect
{
public:
	virtual void   Tick() override {}
public:
	ANpcKillEffect(std::wstring name) : ATimerEffect(name) {}
	ANpcKillEffect() {};
	virtual ~ANpcKillEffect() {};
};
class TGameScene :   public TScene
{
public:
	static    int  g_iNumNpc;
	TNpcManager    m_NpcManager;
	std::shared_ptr<ATimerEffect>		m_NpcKillObj = nullptr;
	TSound* m_pBGSound = nullptr;
	void	TestFMOD();	
public:
	virtual void Process(APawn* pPlayer);
	virtual void InitScene() override;
	virtual void ReleaseScene()override;
	virtual void Tick()override;
	virtual void Render()override;
	TGameScene(TSceneManager* pOwnder) : TScene(pOwnder)
	{
		m_pOwner = pOwnder;
	}
};

