#include "TSound.h"
FMOD::System* TSound::m_pSystem = nullptr;
void   TSound::Update()
{
	if(m_pSystem == nullptr)
	{
		return;
	}
	m_pSystem->update();
}
bool   TSound::Load(TString filename)
{
	if(m_pSystem == nullptr)
	{
		FMOD_RESULT result = FMOD::System_Create(&m_pSystem);
		if (result != FMOD_OK)
		{
			return false;
		}
		result = m_pSystem->init(32, FMOD_INIT_NORMAL, nullptr);
		if (result != FMOD_OK)
		{
			return false;
		}
	}
	std::string path = to_wm(filename);
	FMOD_RESULT result = 
		m_pSystem->createSound(
			path.c_str(),
			FMOD_DEFAULT, nullptr, &m_pSound);
	return true;
}
bool   TSound::Play(bool loop)
{
	if (m_pSound == nullptr)
	{
		return false;
	}
	
	FMOD_RESULT result = m_pSystem->playSound(
		m_pSound, nullptr, 
		false, &m_pChannel);
	if (result != FMOD_OK)
	{
		return false;
	}
	if (loop)
	{
		m_pChannel->setMode(FMOD_LOOP_NORMAL);
	}
	return true;
}
bool   TSound::PlayEffect(bool loop)
{
	return true;
}
void TSound::Release()
{
	if (m_pSound != nullptr)
	{
		m_pSound->release();
		m_pSound = nullptr;
	}
	if (m_pSystem != nullptr)
	{
		m_pSystem->close();
		m_pSystem->release();
		m_pSystem = nullptr;
	}
}
TSound::TSound(TString  path) : UObject(path)
{
}
TSound::TSound()
{
}
TSound::~TSound()
{
	Release();
}