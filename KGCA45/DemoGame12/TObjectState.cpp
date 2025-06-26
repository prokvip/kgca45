#include "TObjectState.h"
#include "ANpc.h"
TObjectState::TObjectState(ANpc* pOwner) : m_pOwner(pOwner)
{

}
TObjectState::TObjectState() : m_pOwner(nullptr)
{

}