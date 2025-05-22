#pragma once
#include "UWorld.h"
#include "UInputComponent.h"
#include "UTimerComponent.h"
#include "USoundComponent.h"
#include "TWindow.h"
class Sample :  public TWindow
{
	using CompPtr = std::shared_ptr<UActorComponent>;
	UWorld world;
	std::list< CompPtr> compList;
	std::shared_ptr<UTimerComponent> timer = nullptr;
	std::shared_ptr<UInputComponent> input = nullptr;
public:
	void InitGame();
	void ReleaseGame();
	bool GameLoop(UInputComponent* input);
public:
	virtual void GameRun() override;
};

