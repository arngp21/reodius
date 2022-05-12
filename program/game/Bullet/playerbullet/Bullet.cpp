#include"Bullet.h"
#include"../../gamesystem/GameManager.h"

extern GameManager* gamemanager_;
int Bullet::BulletID_ = 0;

Bullet::Bullet(const int type, const tnl::Vector3 start_pos,  bulletmove desc, std::string img_name) {
	//img_bullet_ = gamemanager_->Loadimag("graphics/laserbullet.png");
	pos_.x = start_pos.x;
	pos_.y = start_pos.y;
	size_h = 4;
	size_w = 60;
	move_dir_ = desc.move_;
	type_ = type;
	bullet_img_ = gamemanager_->Loadimag(img_name);
	if (type == LASER) {
		bullettype_ = LASER;
		bullet_ID_ = BulletID_;
		BulletID_++;
		speed_ = 50;
	}
	else speed_ = 10;
}

void Bullet::NormalMove(float deltatime) {
	pos_.x += speed_;
	if (pos_.x > (gamemanager_->camera_.pos_.x + GameManager::SCREEN_W / 2))is_alive_ = false;
}

void Bullet::LaserMove(float deltatime) {
	pos_.x += speed_;
	if (pos_.x > (gamemanager_->camera_.pos_.x + GameManager::SCREEN_W / 2))is_alive_ = false;
}

void Bullet::ShotgunMove(float deltatime) {
	alive_count_ += deltatime;
	if (alive_count_ < SO_ALIVE_TIME_) {
		pos_ += move_dir_ * speed_;
	}
	else {
		is_alive_ = false;
	}
	if (pos_.x > (gamemanager_->camera_.pos_.x + GameManager::SCREEN_W / 2))is_alive_ = false;
}

void Bullet::AroundMove(float deltatime) {
	std::shared_ptr<SkillManager> skillmanager_ = gamemanager_->GetSkillManager();
	std::shared_ptr<Player> player_ = gamemanager_->GetPlayer();
    alive_count_ += deltatime;
	if (AR_ALIVE_TIME_ < alive_count_) {
		is_alive_ = false;
	}

	angle_ += 360.0f * (deltatime / 1.0f);//Žü‚é‘¬“x

	pos_ = player_->pos_;
	for (auto skill : skillmanager_->skills) {
		if (skill->type_ == 2) {
			pos_ = skill->pos_;
		}
	}

	pos_.y += cosf(tnl::ToRadian(angle_)) * (gamemanager_->player_->size_w * 1.7f);//player‚Æ‚Ì‹——£
	pos_.x += sinf(tnl::ToRadian(angle_)) * (gamemanager_->player_->size_w * 1.7f);
}

void Bullet::Update(float deltatime) {
	switch (type_) {
	case NORMAL:
		move = &Bullet::NormalMove;
		move(this, deltatime);
		break;
	case LASER:
		move = &Bullet::LaserMove;
		move(this, deltatime);
		break;
	case SHOTGUN:
		move = &Bullet::ShotgunMove;
		move(this, deltatime);
		break;
	case AROUND:
		move = &Bullet::AroundMove;
		move(this, deltatime);
		break;
	default:
		break;
	}
}

void Bullet::CircleDraw(Camera* camera) {
	int x = pos_.x - camera->pos_.x + (GameManager::SCREEN_W >> 1);
	int y = pos_.y - camera->pos_.y + (GameManager::SCREEN_H >> 1);
	DrawRotaGraph(x, y, 1.0f, 0, bullet_img_, true);
}

void Bullet::BoxDraw(Camera* camera) {
	int x1 = pos_.x - (size_w >> 1);
	int y1 = pos_.y - (size_h >> 1);
	int x2 = pos_.x + (size_w >> 1);
	int y2 = pos_.y + (size_h >> 1);

	x1 = x1 - camera->pos_.x + (GameManager::SCREEN_W >> 1);
	x2 = x2 - camera->pos_.x + (GameManager::SCREEN_W >> 1);
	y1 = y1 - camera->pos_.y + (GameManager::SCREEN_H >> 1);
	y2 = y2 - camera->pos_.y + (GameManager::SCREEN_H >> 1);
	DrawRotaGraph((x1 + x2) / 2, (y1 + y2) / 2, 1.0f,0, bullet_img_, true);
}

void Bullet::Render(Camera* camera) {
	switch (type_) {
	case NORMAL:
		draw = &Bullet::CircleDraw;
		draw(this,camera);
		break;
	case LASER:
		draw = &Bullet::BoxDraw;
		draw(this, camera);
		break;
	case SHOTGUN:
		draw = &Bullet::CircleDraw;
		draw(this,camera);
		break;
	case AROUND:
		draw = &Bullet::CircleDraw;
		draw(this,camera);
		break;
	default:
		break;
	}
}