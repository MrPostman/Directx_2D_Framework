#pragma	once

class CGraphics;
typedef	struct _SpriteWH {
	int width, height;
} SPRITEWH;
/* A base agent class, all agent in this project 
 * Should inherited from this class
 */
class	CAgent {
public:
	// Main run function of agent
	virtual void Run(int cx, int cy)=0;
	// Update agent data every frame
	virtual void UpdateData() = 0;
	// Update agent state every frame
	virtual	void UpdateState() = 0;
	// Init the agent information
	virtual	bool InitAgent(CGraphics* ) = 0;
};