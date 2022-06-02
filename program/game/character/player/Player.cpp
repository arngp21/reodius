#include"Player.h"
#include"../../gamesystem/GameManager.h"

extern GameManager* gamemanager_;

Player::Player(const tnl::Vector3 &start_pos_) {
	player_img_ = gamemanager_->Loadimag("graphics/sentouki.png");
	pos_.x = start_pos_.x;
	pos_.y = start_pos_.y;
	speed_ = gamemanager_->camera_speed_;
	size_w = 80;
	size_h = 45;
	hp_ = gamemanager_->p_hp_;
}

Player::~Player() {

}

void Player::Update(float deltatime) {
	std::shared_ptr<BulletManager> bulletmanager_ = gamemanager_->GetBulletManager();
	std::shared_ptr<SkillManager> skillmanager_ = gamemanager_->GetSkillManager();
	if (!gamemanager_->b_player_move_start) {//play‚ð‰Ÿ‚µ‚½‚ç“®‚¯‚é‚æ‚¤‚É
	}
	else {
		if (gamemanager_->b_camera_stop)pos_.x += speed_;

		if (Move()) {
			//ƒL[‚ª‰Ÿ‚³‚ê‚½Žž‚Ìˆ—(‚Ü‚¾‚È‚¢)
		}

		//DebugMove();
		shot_interval += deltatime;//bullet‚Ì”­ŽËŠÔŠuŒvŽZ

		bulletmove move;
		if (tnl::Input::IsKeyDownTrigger(tnl::Input::eKeys::KB_1) && shot_interval > 0.1f) {
			if (gamemanager_->bullet_type_ == static_cast<int>(GameManager::BULLETTYPE::NORMAL)) {
				//normalbullet
				PlaySoundMem(gamemanager_->snd_normal_bullet, DX_PLAYTYPE_BACK, true);
				bulletmanager_->CreateBullet(static_cast<int>(GameManager::BULLETTYPE::NORMAL),pos_,move,shared_from_this());
			}
			else if (gamemanager_->bullet_type_ == static_cast<int>(GameManager::BULLETTYPE::LASER)) {
				//laserbullet
				PlaySoundMem(gamemanager_->snd_laser, DX_PLAYTYPE_BACK, true);
				bulletmanager_->CreateBullet(static_cast<int>(GameManager::BULLETTYPE::LASER), pos_, move, shared_from_this());
			}
			else if (gamemanager_->bullet_type_ == static_cast<int>(GameManager::BULLETTYPE::SHOTGUN)) {
				//shougunbullet
				PlaySoundMem(gamemanager_->snd_normal_bullet, DX_PLAYTYPE_BACK, true);
				tnl::Vector3 hoz = move.move_;
				for (int i = 30; i <= 150; i += 30) {//150/30‚Å5”­”­ŽË
					//‰ñ“]s—ñB//ToRadian‚Éi‚ð“ü‚ê‚ÄŠp“x‚ð•ÏX
					move.move_ = tnl::Vector3::TransformCoord(hoz, tnl::Matrix::RotationAxis(tnl::Vector3(0, 0, 1), tnl::ToRadian(i)));
					bulletmanager_->CreateBullet(static_cast<int>(GameManager::BULLETTYPE::SHOTGUN), pos_, move, shared_from_this());
				}
			}
			else if (gamemanager_->bullet_type_ == static_cast<int>(GameManager::BULLETTYPE::AROUND)) {
				//aroundbullet
				PlaySoundMem(gamemanager_->snd_around, DX_PLAYTYPE_BACK, true);
				bulletmanager_->CreateBullet(static_cast<int>(GameManager::BULLETTYPE::AROUND),pos_,move, shared_from_this());
			}

			shot_interval = 0;

			for (auto skill : skillmanager_->skills) {
				//skill
				if (skill->type_ == static_cast<int>(GameManager::SkillType::OPTION)) {
					skill->b_option_create_bullet_ = true;//option‚ª¶¬‚³‚ê‚Ä‚¢‚½‚ç’e‚ªo‚é‚æ‚¤‚É
				}
			}
		}

		//skill‚ÌŽÀsA¶¬
		if (gamemanager_->Item_count_ >= 0) {
			if (tnl::Input::IsKeyDownTrigger(tnl::Input::eKeys::KB_2)) {
				gamemanager_->icon[gamemanager_->Item_count_]->IconChoice();
			}
		}
	}
}

void Player::Render(Camera* camera) {
	int x1 = pos_.x - (size_w >> 1);
	int y1 = pos_.y - (size_h >> 1);
	int x2 = pos_.x + (size_w >> 1);
	int y2 = pos_.y + (size_h >> 1);

	x1 = x1 - camera->pos_.x + GameManager::SCREEN_W_HALF;
	x2 = x2 - camera->pos_.x + GameManager::SCREEN_W_HALF;
	y1 = y1 - camera->pos_.y + GameManager::SCREEN_H_HALF;
	y2 = y2 - camera->pos_.y + GameManager::SCREEN_H_HALF;

	//tnl::Vector3 pos((x1 + x2) / 2, (y1 + y2) / 2, 0);

	//DrawBox(x1, y1, x2, y2, GetColor(0, 100, 100), false);
	DrawRotaGraph((x1 + x2) / 2, (y1 + y2) / 2, 0.127f, 0, player_img_, true);
}

bool Player::Move()
{
	tnl::Vector3 c_pos_ = gamemanager_->camera_.pos_;
	int move_speed = speed_ * speed_magnification_;
	int count = 0;

	if (pos_.x >= (c_pos_.x - (GameManager::SCREEN_W_HALF - 60))) {
		if (tnl::Input::IsKeyDown(tnl::Input::eKeys::KB_LEFT)) {
			pos_.x -= (move_speed + back_speed_);
			count++;
		}
	}
	if (pos_.x <= c_pos_.x + GameManager::SCREEN_W_HALF) {
		if (tnl::Input::IsKeyDown(tnl::Input::eKeys::KB_RIGHT)) {
			pos_.x += move_speed;
			count++;
		}
	}
	if (pos_.y >= (c_pos_.y - (GameManager::SCREEN_H_HALF - 30))) {
		if (tnl::Input::IsKeyDown(tnl::Input::eKeys::KB_UP)) {
			pos_.y -= move_speed;
			count++;
		}
	}
	if (pos_.y <= (c_pos_.y + (GameManager::SCREEN_H_HALF - 85))) {
		if (tnl::Input::IsKeyDown(tnl::Input::eKeys::KB_DOWN)) {
			pos_.y += move_speed;
			count++;
		}
	}
	if (count != 0)return true;
	else return false;
}

void Player::DebugMove() {
	if (tnl::Input::IsKeyDownTrigger(tnl::Input::eKeys::KB_3)) {
		gamemanager_->Item_count_++;
	}
}
