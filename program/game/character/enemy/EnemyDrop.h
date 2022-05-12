#pragma once
#include"../../gamesystem/Object.h"

class EnemyDrop : public Object {
public:
	EnemyDrop(tnl::Vector3 start_pos);
	float radius_ = 10;

private:
	int img[6];
	int time_count_ = 0;
	int anime_flame_ = 0;

	void Update(float deltatime) override;
	void Render(Camera* camera) override;
};
