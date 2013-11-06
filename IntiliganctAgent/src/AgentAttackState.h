#pragma	once
#include "Agent.h"
#include "BonzeDogAgent.h"
#include "State.h"

class CBonzeDogAgent;// If I do not add this line, the class below can't find this class, WHY?!

#define	g_pAgentAttackState CAgentAttackState::GetInstance()

class CAgentAttackState : public CState<CBonzeDogAgent> {

public:

	CAgentAttackState();
	virtual ~CAgentAttackState();	// why?
	virtual	void EnterState(CBonzeDogAgent* agent);
	virtual void ExecuteState(CBonzeDogAgent* agent);
	virtual void ExitState(CBonzeDogAgent* agent);
	
	enum EStateID GetStateID(){
		return m_eStateID;
	}
public:
	static CAgentAttackState* GetInstance();
	void MovingStrategy(int& x, int& y);
private:
	enum EStateID	m_eStateID;
};