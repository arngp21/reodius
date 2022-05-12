#include"Effect.h"
#include"GameManager.h"

Effect::Effect(const tnl::Vector3 &get_move,const tnl::Vector3 &get_pos) {
	speed_ = 5;
	move_dir_ = get_move;
	pos_ = get_pos;
}

void Effect::Update(float deltatime) {
	count_ += 0.01f;

	if (count_ < 0.1f) {
		pos_ += move_dir_ * speed_;
	}
	else
	{
		if (count_ > 0.2f) {
			pos_ += (move_dir_ * speed_) * -1;
			if (count_ > 0.3f) {
				is_alive_ = false;
			}
		}
	}
}

void Effect::init() {
	initialize();
}

void Effect::Render(Camera* camera) {
	DrawCircle(pos_.x, pos_.y, radius_, -1);
}