#pragma once
#include"../gamesystem/Object.h"

class Effect : public Object {
public:
	Effect(const tnl::Vector3 &get_move,const tnl::Vector3 &get_pos);
	float count_ = 0;
	int radius_ = 3;
	
	//object‚Ìinitialize‚ðŒÄ‚Ô
	void init();
	void Update(float deltatime) override;
	void Render(Camera* camera) override;
};
