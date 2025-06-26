#pragma once
#include "TStd.h"

class TStateFsm
{
	std::map<int, int> m_events;
	int   m_iStateID; // ���� ID
public:
	void AddTransition(int event, int outState)
	{
		m_events.insert(std::make_pair(event, outState));
	}
	int GetTransition(int event)
	{
		if (m_events.find(event) != m_events.end())
		{
			return m_events[event];
		}
		return -1;
	}
	TStateFsm(int iState) : m_iStateID(iState) {}
};
template <typename T>
class TFsm
{
	std::map<int, TStateFsm*> m_states;
public:
	T   Definition; // ���� ����
public:
	// ���°�ü �� �̺�Ʈ �߰�
	void AddStateTransition(int inState,int  event,	int outState)
	{
		TStateFsm* pState = nullptr;
		if (m_states.find(inState) != m_states.end())
		{
			pState = m_states[inState];
		}
		else
		{
			pState = new TStateFsm(inState);
		}
		pState->AddTransition(event, outState);
		m_states.insert(std::make_pair(inState, pState));
	}
	// ���� �̺�Ʈ�� ���� ������ȯ�� ��ȯ
	int GetTransition(int currentState, int event)
	{
		auto it = m_states.find(currentState);
		if (it != m_states.end())
		{
			return it->second->GetTransition(event);
		}
		return -1; // ������ȯ�� ���� ���
	}
public:
	TFsm() {};
};
