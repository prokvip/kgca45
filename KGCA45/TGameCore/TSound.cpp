#include "TSound.h"
FMOD::System* TSound::m_pSystem = nullptr;
void   TSound::UpdateSystem()
{
	if(m_pSystem == nullptr)
	{
		return;
	}
	m_pSystem->update();
}
void   TSound::ReleaseSystem()
{
	if (m_pSystem != nullptr)
	{
		m_pSystem->close();
		m_pSystem->release();
		m_pSystem = nullptr;
	}
}
void   TSound::Update()
{
	if (m_pChannel == nullptr)
	{
		return;
	}	
	m_pChannel->getPosition(&m_msPosition, FMOD_TIMEUNIT_MS);
	wchar_t buffer[256];
	swprintf(buffer, 256,
		L" 경과시간[%02d:%02d], 길이[%02d:%02d]",
		m_msPosition / 1000 / 60,
		m_msPosition / 1000 % 60,
		//m_msPosition / 10 % 60,
		m_msSoundLength / 1000 / 60, // 분
		m_msSoundLength / 1000 % 60);// 초
		//,m_msSoundLength / 10 % 60);
	//P(L"\n%s", buffer);
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

	
	m_pSound->getLength(&m_msSoundLength, FMOD_TIMEUNIT_MS);
	P(L"\n%s[% 02d:% 02d]", filename.c_str(),
		m_msSoundLength / 1000 / 60, // 분
		m_msSoundLength / 1000 % 60);
	return true;
}
bool   TSound::Play(bool loop)
{
	if (m_pSound == nullptr || IsPlaying())
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
	SetVolume(0.5f);
	
	return true;
}

bool   TSound::PlayEffect()
{
	if (m_pSystem == nullptr)
	{
		return false;
	}
	m_pSystem->playSound(m_pSound, nullptr, false, &m_pChannel);
	return true;
}
void   TSound::Stop() // 사운드 정지
{
	if(m_pChannel == nullptr)
	{
		return;
	}
	m_pChannel->stop();
	m_pChannel = nullptr;
}
void   TSound::PauseToggle() // 사운드 일시정지
{
	if (m_pChannel == nullptr)
	{
		return;
	}
	bool isPaused = IsPaused();
	//m_pChannel->getPaused(&isPaused);
	m_pChannel->setPaused(!isPaused);
}
void   TSound::Pause() // 사운드 일시정지
{
	if (m_pChannel == nullptr)
	{
		return;
	}
	m_pChannel->setPaused(true);
}
void   TSound::Resume() // 사운드 재개
{
	if (m_pChannel == nullptr)
	{
		return;
	}
	m_pChannel->setPaused(false);
}
void   TSound::SetVolumeUp()// 볼륨 설정 (0.0f ~ 1.0f)
{
	if (m_pChannel == nullptr)
	{
		return;
	}
	m_fVolume += 0.33f * g_fSPF;
	if (m_fVolume > 1.0f) m_fVolume = 1.0f;
	m_pChannel->setVolume(m_fVolume);
}
void   TSound::SetVolumeDown()// 볼륨 설정 (0.0f ~ 1.0f)
{
	if (m_pChannel == nullptr)
	{
		return;
	}
	m_fVolume -= 0.33f * g_fSPF;
	if (m_fVolume < 0.0f) m_fVolume = 0.0f;
	m_pChannel->setVolume(m_fVolume);
}
void   TSound::SetVolume(float volume)// 볼륨 설정 (0.0f ~ 1.0f)
{
	if (m_pChannel == nullptr)
	{
		return;
	}
	m_fVolume = volume;
	if (m_fVolume < 0.0f) m_fVolume = 0.0f;
	if (m_fVolume > 1.0f) m_fVolume = 1.0f;
	m_pChannel->setVolume(m_fVolume);
}
float  TSound::GetVolume() // 현재 볼륨 반환 (0.0f ~ 1.0f)
{ 
	return m_fVolume;
}
bool   TSound::IsPlaying() // 사운드가 재생중인지 확인
{ 
	if (m_pChannel == nullptr) return false;
	bool isPlaying = false;
	m_pChannel->isPlaying(&isPlaying);
	return isPlaying;
}
bool   TSound::IsPaused()// 사운드가 일시정지 상태인지 확인
{
	bool isPaused = false;
	m_pChannel->getPaused(&isPaused);
	return isPaused;
}
bool   TSound::IsStopped() // 사운드가 정지 상태인지 확인
{
	return (m_pChannel==nullptr) ? true : false;
}
bool   TSound::IsValid() // 사운드가 유효한지 확인
{
	return m_pSound != nullptr;
}

void TSound::Release()
{
	Stop();
	if (m_pSound != nullptr)
	{
		m_pSound->release();
		m_pSound = nullptr;
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