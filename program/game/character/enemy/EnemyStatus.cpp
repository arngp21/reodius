#include"EnemyStatus.h"
#include"../../gamesystem/GameManager.h"

extern  GameManager* gamemanager_;

void EnemyStatus::DeathEffect() {
	tnl::Vector3 pos(1, 0, 0);
	//gift_pos_ = pos_;
	if (pos_.x > (gamemanager_->camera_.pos_.x - (gamemanager_->SCREEN_W / 2))) {
		for (int i = 0; i < 360; i += 60) {
			pos.normalize();
			move_dir_ = tnl::Vector3::TransformCoord(pos, tnl::Matrix::RotationAxis(tnl::Vector3(0, 0, 1), tnl::ToRadian(i)));
			std::shared_ptr<Effect> ef = std::make_shared<Effect>(move_dir_, gift_pos_);
			//ef->initialize();
			ef->init();
		}
	}
}

void EnemyStatus::EnemyAnimetion() {

}
