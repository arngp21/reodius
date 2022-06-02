#include"EnemyBullet.h"
#include"../../gamesystem/GameManager.h"

extern GameManager* gamemanager_;

EnemyBullet::EnemyBullet(tnl::Vector3 start_pos, tnl::Vector3 dir) {  // move_dir ‚ð“n‚µ‚Ä‚¢‚é
	pos_ = start_pos;
	move_dir_ = dir;
	img_bullet_ = gamemanager_->Loadimag("graphics/enemybullet.png");
}

void EnemyBullet::Update(float deltatime) {
	//player‚Ì•ûŒü‚É”ò‚Ô
	pos_ += move_dir_ * 5;
	//‰æ–ÊŠO‚©‚ço‚½‚çŽ€‚Ê
	if (pos_.x > (gamemanager_->camera_.pos_.x + (GameManager::SCREEN_W_HALF)) ||
		(pos_.x < (gamemanager_->camera_.pos_.x - (GameManager::SCREEN_W_HALF))) ||
		(pos_.y > (gamemanager_->camera_.pos_.y + (GameManager::SCREEN_H_HALF) - 70)) ||
		(pos_.y < (gamemanager_->camera_.pos_.y - (GameManager::SCREEN_H_HALF)))) {
		is_alive_ = false;
	}
}

void EnemyBullet::Render(Camera* camera) {
	int x = pos_.x - camera->pos_.x + (GameManager::SCREEN_W_HALF);
	int y = pos_.y - camera->pos_.y + (GameManager::SCREEN_H_HALF);
	DrawRotaGraph(x, y, 1.5f, 0, img_bullet_, true);
}