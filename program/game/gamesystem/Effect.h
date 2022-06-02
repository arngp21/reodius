#pragma once
#include"../gamesystem/Object.h"

class Effect : public Object {
public:
	Effect(const tnl::Vector3& get_move, const tnl::Vector3& get_pos, const int enemy_type);
	void init();
private:
	float count_ = 0;
	int radius_ = 3;
	int enemy_type_ = 0;

	int img_explosion[16];//bomのimg
	//アニメーション
	int anime_flame_ = 0;
	int time_count_ = 0;
	
	int rand_x = 0;
	int rand_y = 0;
	bool b_rand_init = false;
	//objectのinitializeを呼ぶ
	void Update(float deltatime) override;
	void Render(Camera* camera) override;
};
