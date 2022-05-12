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
	if (sceneback_ == TITLEBACK) {
		x1 = pos_.x - (GameManager::SCREEN_W >> 1);
		x2 = pos_.x + (GameManager::SCREEN_W >> 1);
		y1 = pos_.y - (GameManager::SCREEN_H >> 1);
		y2 = pos_.y + (GameManager::SCREEN_H >> 1);
		pos_.x -= speed_;
		
		if (x2 <= (gamemanager_->camera_.pos_.x - (gamemanager_->SCREEN_W >> 1))) {
			pos_.x += (GameManager::SCREEN_W << 1);
		}
	}
	else if (sceneback_ == PLAYBACK) {
		if (x2 <= (gamemanager_->camera_.pos_.x - (gamemanager_->SCREEN_W >> 1))) {
			x1 += (GameManager::SCREEN_W << 1);
			x2 += (GameManager::SCREEN_W << 1);
		}
	}
}

void BackGraund::Render(Camera* camera) {
	if (sceneback_ == TITLEBACK || sceneback_ == PLAYBACK) {
		int img_x1 = x1;
		int img_x2 = x2;
		int img_y1 = y1;
		int img_y2 = y2;
		img_x1 = img_x1 - camera->pos_.x + (GameManager::SCREEN_W >> 1);
		img_x2 = img_x2 - camera->pos_.x + (GameManager::SCREEN_W >> 1);
		img_y1 = img_y1 - camera->pos_.y + (GameManager::SCREEN_H >> 1);
		img_y2 = img_y2 - camera->pos_.y + (GameManager::SCREEN_H >> 1);

		DrawExtendGraph(img_x1, img_y1, img_x2, img_y2, play_back_img_, true);
		
		if (sceneback_ == TITLEBACK) {
			SetFontSize(120);
			DrawStringEx(250, 200, -1, "REODIUS2");
			SetFontSize(50);

			if (startinterval)count += 0.1f;
			if (count < 0.5f) {
				DrawStringEx(450, 400, -1, "START");
			}
			else {
				count = 0;
			}
		}
	}
}