#include"EnemyBullet.h"
#include"../../gamesystem/GameManager.h"

extern GameManager* gamemanager_;

EnemyBullet::EnemyBullet(tnl::Vector3 start_pos, tnl::Vector3 dir) {  // move_dir ‚ð“n‚µ‚Ä‚¢‚é
	pos_ = start_pos;
	move_dir_ = dir;
	img_bullet_ = gamemanager_->Loadimag("graphics/enemybullet.png");
}

void EnemyBullet::Update(float deltatime) {

	pos_ += move_dir_ * 5;
	if (pos_.x > (gamemanager_->camera_.pos_.x + (gamemanager_->SCREEN_W >> 1)) ||
		(pos_.x < (gamemanager_->camera_.pos_.x - (gamemanager_->SCREEN_W >> 1))) ||
		(pos_.y > (gamemanager_->camera_.pos_.y + (gamemanager_->SCREEN_H >> 1))) ||
		(pos_.y < (gamemanager_->camera_.pos_.y - (gamemanager_->SCREEN_H >> 1)))) {
		is_alive_ = false;
	}
}

void EnemyBullet::Render(Camera* camera) {
	int x = pos_.x - camera->pos_.x + (GameManager::SCREEN_W >> 1);
	int y = pos_.y - camera->pos_.y + (GameManager::SCREEN_H >> 1);
	DrawRotaGraph(x, y, 1.5f, 0, img_bullet_, true);
}