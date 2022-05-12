#include"EnemyDrop.h"
#include"../../gamesystem/GameManager.h"

extern GameManager* gamemanager_;

EnemyDrop::EnemyDrop(tnl::Vector3 start_pos) {
	LoadDivGraph("graphics/coin.png", 6, 6, 1, 76, 97, img);
	pos_ = start_pos;
}

void EnemyDrop::Update(float dltatime) {
	if (pos_.x < (gamemanager_->camera_.pos_.x -(GameManager::SCREEN_W >> 1))) is_alive_ = false;
}

void EnemyDrop::Render(Camera* camera) {
	int x = pos_.x - camera->pos_.x + (GameManager::SCREEN_W >> 1);
	int y = pos_.y - camera->pos_.y + (GameManager::SCREEN_H >> 1);
	DrawRotaGraph(x, y, 0.5f, 0, img[anime_flame_] ,true);

	time_count_++;
	if (time_count_ == 16) {
		anime_flame_++;
		anime_flame_ %= 4;
		time_count_ = 0;
	};
}