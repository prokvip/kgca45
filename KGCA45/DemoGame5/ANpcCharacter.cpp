#include "ANpcCharacter.h"

void   ANpcCharacter::Tick()
{
	TVector2 pos = GetPosition();
	m_vDirection.Normalized();
	pos = pos + m_vDirection * m_fSpeed * g_fSPF;

	if (pos.x > 800.0f) {
		pos.x = 800.0f;
		m_vDirection.x *= -1.0f;
	}
	if (pos.x < 0.0f) {
		pos.x = 0.0f;
		m_vDirection.x *= -1.0f;
	}
	if (pos.y > 600.0f) {
		pos.y = 600.0f;
		m_vDirection.y *= -1.0f;
	}
	if (pos.y < 0.0f) {
		pos.y = 0.0f;
		m_vDirection.y *= -1.0f;
	}
	SetPosition(pos);
}