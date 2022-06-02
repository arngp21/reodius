#include"Skill.h"
#include"../gamesystem/GameManager.h"

extern GameManager* gamemanager_;

Skill::Skill(const tnl::Vector3 start_pos, const int type) {
	priority_ = 100;
	pos_ = start_pos;
	type_ = type;
	if (type_ == static_cast<int>(GameManager::SkillType::BOM)) {
		speed_ = bom_speed_;
	}
	else if (type_ == static_cast<int>(GameManager::SkillType::BARRIER)) {
	}
	else if (type_ == static_cast<int>(GameManager::SkillType::OPTION)) {
		speed_ = gamemanager_->camera_speed_;
		for (int i = 0; i < 39; i++) {
			hoz_x[0] = start_pos.x;
			hoz_y[0] = start_pos.y;
		}
	}
	size_w = 150;
	size_h = 100;
	b_render = false;
	LoadDivGraph("graphics/bakudann.png", 3, 3, 1, 31, 29, img_bom);
	LoadDivGraph("graphics/bakuhatu.png", 16, 8, 2, 72, 72, img_explosion);
	LoadDivGraph("graphics/option.png", 2, 2, 1, 34, 33, img_option);
	img_barrier_ = gamemanager_->Loadimag("graphics/barrier1.png");
	img_barrier2_ = gamemanager_->Loadimag("graphics/barrier2.png");
	if (type_ == static_cast<int>(GameManager::SkillType::BOM)) {
		PlaySoundMem(gamemanager_->snd_normal_bullet, DX_PLAYTYPE_BACK, true);
	}
	else PlaySoundMem(gamemanager_->snd_healing, DX_PLAYTYPE_BACK, true);

	std::shared_ptr<Player>player = gamemanager_->GetPlayer();
}

void Skill::OnDisplayDead() {
	std::shared_ptr<EnemyManager>enemymanager = gamemanager_->GetEnemyManager();
	for (auto enemy : enemymanager->enemys_) {
		if ((gamemanager_->camera_.pos_.x - (GameManager::SCREEN_W_HALF) < enemy->pos_.x) &&
			(gamemanager_->camera_.pos_.x + (GameManager::SCREEN_W_HALF) > enemy->pos_.x)) {
			enemy->deadtype_ = static_cast<int>(DeadType::BULLET_HIT_DEATH);
			if (enemy->type_ != static_cast<int>(EnemyMoveType::BOSS)) {
				enemy->is_alive_ = false;//bomでbossが死なないように
			}
		}
	}
}

void Skill::Bommove(float deltatime) {
	pos_.x += speed_;
	if (pos_.x > gamemanager_->camera_.pos_.x + 200) {
		OnDisplayDead();
		b_render = true;
	}
	gamemanager_->IntersectSkill(type_, this);
}

void Skill::Barriermove(float deltatime) {
	std::shared_ptr<Player>player = gamemanager_->GetPlayer();
	pos_.x = player->pos_.x;
	pos_.y = player->pos_.y;
	gamemanager_->IntersectSkill(type_,this);
	if (hp_ <= 0) {
		is_alive_ = false;
		gamemanager_->icon[static_cast<int>(GameManager::IconType::BARRIER)]->b_barrier_alive = false;
	}
	if (!player->is_alive_)is_alive_ = false;
}

void Skill::Optionmove(float deltatime) {
	std::shared_ptr<Player>player = gamemanager_->GetPlayer();

	//1フレーム前のplayerの座標と現在のplayerの座標の差が1以上だったら
	if ((fabs(player->pos_.x - hoz_x[0]) > 1) || (fabs(player->pos_.y - hoz_y[0]) > 1)) {
		for (int i = 0; i < 40; i++) {
			int idx = 40 - i - 1;
			hoz_x[idx] = hoz_x[idx - 1];
			hoz_y[idx] = hoz_y[idx - 1];
		}
		hoz_x[0] = player->pos_.x;
		hoz_y[0] = player->pos_.y;
		pos_.x = hoz_x[OPTION_POS];
		pos_.y = hoz_y[OPTION_POS];
	}

	if (!player->is_alive_) {
		is_alive_ = false;
		gamemanager_->icon[static_cast<int>(GameManager::IconType::OPTION)]->b_barrier_alive = false;
	}

	if (b_option_create_bullet_) {
		OptionBulletShot();
		b_option_create_bullet_ = false;
	}
}

void Skill::OptionBulletShot() {
	std::shared_ptr<BulletManager> bulletmanager_ = gamemanager_->GetBulletManager();
	bulletmove move;
	if (gamemanager_->bullet_type_ == static_cast<int>(GameManager::BULLETTYPE::NORMAL)) {
		PlaySoundMem(gamemanager_->snd_normal_bullet, DX_PLAYTYPE_BACK, true);
		bulletmanager_->CreateBullet(static_cast<int>(GameManager::BULLETTYPE::NORMAL), pos_, move, shared_from_this());
	}
	else if (gamemanager_->bullet_type_ == static_cast<int>(GameManager::BULLETTYPE::LASER)) {
		PlaySoundMem(gamemanager_->snd_laser, DX_PLAYTYPE_BACK, true);
	bulletmanager_->CreateBullet(static_cast<int>(GameManager::BULLETTYPE::LASER), pos_, move, shared_from_this());
	}
	else if (gamemanager_->bullet_type_ == static_cast<int>(GameManager::BULLETTYPE::SHOTGUN)) {
		PlaySoundMem(gamemanager_->snd_normal_bullet, DX_PLAYTYPE_BACK, true);
		tnl::Vector3 hoz = move.move_;
		for (int i = 30; i <= 150; i += 30) {
			move.move_ = tnl::Vector3::TransformCoord(hoz, tnl::Matrix::RotationAxis(tnl::Vector3(0, 0, 1), tnl::ToRadian(i)));
			bulletmanager_->CreateBullet(static_cast<int>(GameManager::BULLETTYPE::SHOTGUN), pos_, move, shared_from_this());
		}
	}
	else if (gamemanager_->bullet_type_ == static_cast<int>(GameManager::BULLETTYPE::AROUND)) {
		PlaySoundMem(gamemanager_->snd_around, DX_PLAYTYPE_BACK, true);
		bulletmanager_->CreateBullet(static_cast<int>(GameManager::BULLETTYPE::AROUND), pos_, move, shared_from_this());
	}
}

void Skill::Update(float deltatime) {
	switch (type_) {
	case static_cast<int>(GameManager::SkillType::BOM):
		move = &Skill::Bommove;
		move(this, deltatime);
		break;
	case static_cast<int>(GameManager::SkillType::BARRIER):
		move = &Skill::Barriermove;
		move(this, deltatime);
		break;
	case static_cast<int>(GameManager::SkillType::OPTION):
		move = &Skill::Optionmove;
		move(this, deltatime);
		break;
	default:
		break;
	}
}

void Skill::Bomdraw(Camera* camera) {
	int x = pos_.x - camera->pos_.x + GameManager::SCREEN_W_HALF;
	int y = pos_.y - camera->pos_.y + GameManager::SCREEN_H_HALF;
	if (!b_render) {
		time_count_++;
		if (time_count_ == 9) {
			anime_flame_++;
			anime_flame_ %= 3;
			time_count_ = 0;
		};
		DrawRotaGraph(x, y, 1.0f, 0, img_bom[anime_flame_], true);
	}
	else {
		time_count_++;
		if (time_count_ < 256) {
			anime_flame_++;
			anime_flame_ %= 16;
			time_count_ = 0;
		}
		DrawRotaGraph(x, y, 10, 0, img_explosion[anime_flame_], true);
		if (anime_flame_ == 15) {
			is_alive_ = false;
		}
	}
}

void Skill::Barrierdraw(Camera* camera) {
	int x1 = pos_.x - (size_w >> 1);
	int y1 = pos_.y - (size_h >> 1);
	int x2 = pos_.x + (size_w >> 1);
	int y2 = pos_.y + (size_h >> 1);

	x1 = x1 - camera->pos_.x + GameManager::SCREEN_W_HALF;
	x2 = x2 - camera->pos_.x + GameManager::SCREEN_W_HALF;
	y1 = y1 - camera->pos_.y + GameManager::SCREEN_H_HALF;
	y2 = y2 - camera->pos_.y + GameManager::SCREEN_H_HALF;

	if (hp_ > barrier_hp_) DrawExtendGraph(x1, y1, x2, y2, img_barrier_, true);
	else DrawExtendGraph(x1, y1, x2, y2, img_barrier2_, true);
}

void Skill::Optiondraw(Camera* camera) {
	int x = pos_.x - camera->pos_.x + GameManager::SCREEN_W_HALF;
	int y = pos_.y - camera->pos_.y + GameManager::SCREEN_H_HALF;

	time_count_++;
	if (time_count_ == 12) {
		anime_flame_++;
		anime_flame_ %= 2;
		time_count_ = 0;
	};
	DrawRotaGraph(x, y, 1.5f, 0, img_option[anime_flame_], true);
}

void Skill::Render(Camera* camera) {
	switch (type_) {
	case static_cast<int>(GameManager::SkillType::BOM):
		draw = &Skill::Bomdraw;
		draw(this, camera);
		break;
	case static_cast<int>(GameManager::SkillType::BARRIER):
		draw = &Skill::Barrierdraw;
		draw(this, camera);
		break;
	case static_cast<int>(GameManager::SkillType::OPTION):
		draw = &Skill::Optiondraw;
		draw(this, camera);
	default:
		break;
	}
}