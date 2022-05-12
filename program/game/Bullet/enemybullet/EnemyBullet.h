#pragma once
#include"../../gamesystem/Object.h"

class EnemyBullet : public Object {
public:

	EnemyBullet(tnl::Vector3 start_pos, tnl::Vector3 dir);
	//~EnemyBullet();
	const float radius_ = 5;//’e‚Ì”¼Œa
	int img_bullet_ = 0;

	void Update(float deltatime) override;
	void Render(Camera* camera) override;
};
