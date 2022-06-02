#include"Effect.h"
#include"GameManager.h"

extern GameManager* gamemanager_;

Effect::Effect(const tnl::Vector3 &get_move,const tnl::Vector3 &get_pos,const int enemy_type) {
	speed_ = 5;
	move_dir_ = get_move;
	pos_ = get_pos;
	enemy_type_ = enemy_type;
	LoadDivGraph("graphics/bakuhatu.png", 16, 8, 2, 72, 72, img_explosion);
}

void Effect::Update(float deltatime) {
	if (enemy_type_ == static_cast<int>(EnemyMoveType::BOSS)) {
	}
	else {
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
}

void Effect::init() {
	initialize();
}

void Effect::Render(Camera* camera) {
	if (enemy_type_ == static_cast<int>(EnemyMoveType::BOSS)) {
		time_count_++;
		if (!b_rand_init) {
			rand_x = (GetRand(350) + (pos_.x - camera->pos_.x + GameManager::SCREEN_W_HALF)) - 150;//
		    rand_y = (GetRand(350) + (pos_.y - camera->pos_.y + GameManager::SCREEN_H_HALF)) - 150;
			b_rand_init = true;
		}
		if (time_count_ < 256) {
			anime_flame_++;
			anime_flame_ %= 16;
			time_count_ = 0;
		}
		DrawRotaGraph(rand_x, rand_y, 5, 0, img_explosion[anime_flame_], true);
		if (anime_flame_ == 15) {
			PlaySoundMem(gamemanager_->snd_bom, DX_PLAYTYPE_BACK, true);
			is_alive_ = false;
		}
	}
	else DrawCircle(pos_.x, pos_.y, radius_, -1);
}