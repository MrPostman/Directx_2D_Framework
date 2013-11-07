#include "AgentWalkState.h"

CAgentWalkState::CAgentWalkState()
	:
m_theta(0)
{
	m_eStateID = Walk;
}

CAgentWalkState::~CAgentWalkState()
{
}

CAgentWalkState* CAgentWalkState::GetInstance()
{
	static CAgentWalkState agentWalkState;
	return &agentWalkState;
}

void CAgentWalkState::EnterState(CBonzeDogAgent* agent)
{
	agent->SetCurStateID(Walk);
	agent->ClearSpriteIndex();
	agent->SetMoveStrategy(g_pAgentWalkState);
}

void CAgentWalkState::ExecuteState(CBonzeDogAgent* agent)
{
	if(agent->IsCtrlKeyPressed())
		agent->ChangeState(g_pAgentHeatRushState);
	if(agent->IsLALTKeyPressed())
		agent->ChangeState(g_pAgentAttackState);
	if(agent->GetAgentPosX() == 471 && agent->GetAgentPosY() == 403)// a spefic spot and 
		agent->ChangeState(g_pAgentFireState);
}

void CAgentWalkState::ExitState(CBonzeDogAgent* agent)
{
}

void CAgentWalkState::MovingStrategy(int& x, int& y)
{						
	// most straight forward moving method
	// ++x;
	// ++y;

	// ����ԲȦ��,�뾶Ϊ50p
	x = 300 + 200 * std::cos(m_theta);
	y = 300 + 200 * std::sin(m_theta);
	m_theta += 2 * PI / 360;
}