#include"BackGraund.h"
#include"GameManager.h"
#include"../gamesystem/Scene/SceneManager.h"

extern GameManager* gamemanager_;

BackGraund::BackGraund(tnl::Vector3 start_pos) {
	play_back_img_ = gamemanager_->Loadimag("graphics/uchuu.jpg");
	pos_ = start_pos;
	speed_ = gamemanager_->camera_speed_;
	b_render = true;
}

void BackGraund::Update(float deltatime) {
	if (sceneback_ == static_cast<int>(SCENEBACK::TITLEBACK)) {
		x1 = pos_.x - GameManager::SCREEN_W_HALF;
		x2 = pos_.x + GameManager::SCREEN_W_HALF;
		y1 = pos_.y - GameManager::SCREEN_H_HALF;
		y2 = pos_.y + GameManager::SCREEN_H_HALF;
		pos_.x -= speed_;
		
		if (x2 <= (gamemanager_->camera_.pos_.x - GameManager::SCREEN_W_HALF)) pos_.x += (GameManager::SCREEN_W << 1);//‰æ–Ê¶’[‚És‚Á‚½‚çÀ•W‚ð1024*2‰ÁŽZ
	}
	else if (sceneback_ == static_cast<int>(SCENEBACK::PLAYBACK)) {
		if (x2 <= (gamemanager_->camera_.pos_.x - GameManager::SCREEN_W_HALF)) {
			x1 += (GameManager::SCREEN_W << 1);
			x2 += (GameManager::SCREEN_W << 1);
		}
	}
}

void BackGraund::Render(Camera* camera) {
	if (sceneback_ == static_cast<int>(SCENEBACK::TITLEBACK) || sceneback_ == static_cast<int>(SCENEBACK::PLAYBACK)) {
		int img_x1 = x1;
		int img_x2 = x2;
		int img_y1 = y1;
		int img_y2 = y2;
		img_x1 = img_x1 - camera->pos_.x + GameManager::SCREEN_W_HALF;
		img_x2 = img_x2 - camera->pos_.x + GameManager::SCREEN_W_HALF;
		img_y1 = img_y1 - camera->pos_.y + GameManager::SCREEN_H_HALF;
		img_y2 = img_y2 - camera->pos_.y + GameManager::SCREEN_H_HALF;

		DrawExtendGraph(img_x1, img_y1, img_x2, img_y2, play_back_img_, true);
		
		if (sceneback_ == static_cast<int>(SCENEBACK::TITLEBACK)) {
			SetFontSize(120);
			DrawStringEx(140, 200, -1, "SpaceShooter");
			SetFontSize(50);

			if (startinterval)count += 0.1f;
			if (count < 0.5f) DrawStringEx(450, 400, -1, "START");
			else count = 0;
		}
	}
}