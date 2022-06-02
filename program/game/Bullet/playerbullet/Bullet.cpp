#include"Bullet.h"
#include"../../gamesystem/GameManager.h"

extern GameManager* gamemanager_;
int Bullet::BulletID_ = 0;

Bullet::Bullet(const int type, const tnl::Vector3 start_pos, bulletmove desc, std::string img_name, std::shared_ptr<Object> parent)
{
	pos_.x = start_pos.x;
	pos_.y = start_pos.y;
	size_h = 4;
	size_w = 30;
	move_dir_ = desc.move_;//�����x�N�g���Bshotgun�Ŏg�p
	type_ = type;
	bullet_img_ = gamemanager_->Loadimag(img_name);//�摜�n���h��
	if (type == static_cast<int>(GameManager::BULLETTYPE::LASER)) {
		//Laser��ID�����A+���Ă���
		bullet_ID_ = BulletID_;
		BulletID_++;
		speed_ = 50;
	}
	else speed_ = 10;
	callParent = parent;//�Ă񂾌��̃C���X�^���X���擾
}

//------------------------------normalbullet------------------------------------------------------------

void Bullet::NormalMove(BulletMoveBase* state) {
	pos_.x += speed_;
	//��ʂ���o���琶���t���O��false��
	if (pos_.x > (gamemanager_->camera_.pos_.x + GameManager::SCREEN_W_HALF))is_alive_ = false;
}

//------------------------------laserbullet-------------------------------------------------------------

void Bullet::LaserMove(BulletMoveBase* state) {
	pos_.x += speed_;
	if (pos_.x > (gamemanager_->camera_.pos_.x + GameManager::SCREEN_W_HALF))is_alive_ = false;
}

//------------------------------shotgunbullet-----------------------------------------------------------

void Bullet::ShotgunMove(BulletMoveBase* state) {
	//state��MoveState*�ɕϊ����ď�����
	ShotgunMoveState* move_state = static_cast<ShotgunMoveState*>(state);
	//shotgun�͎��Ԃŏ�����
	alive_count_ += move_state->deltatime_;
	if (alive_count_ < SHOT_ALIVE_TIME_) pos_ += move_dir_ * speed_;
	else is_alive_ = false;
	if (pos_.x > (gamemanager_->camera_.pos_.x + GameManager::SCREEN_W_HALF)||
		(pos_.y > (gamemanager_->camera_.pos_.y + GameManager::SCREEN_H_HALF - 70)))is_alive_ = false;
}

//-----------------------------aroundbullet-------------------------------------------------------------

void Bullet::AroundMove(BulletMoveBase* state) {
	AroundMoveState* move_state = static_cast<AroundMoveState*>(state);
	std::shared_ptr<SkillManager> skillmanager = gamemanager_->GetSkillManager();
	std::shared_ptr<Player> player = gamemanager_->GetPlayer();
    alive_count_ += move_state->deltatime_;
	if (AROUND_ALIVE_TIME_ < alive_count_) {
		is_alive_ = false;
	}

	angle_ += 360.0f * (move_state->deltatime_ / 1.0f);//���鑬�x

	//pos_ = player->pos_;
	pos_ = callParent->pos_;

	pos_.y += cosf(tnl::ToRadian(angle_)) * (player->size_w * player_distans);//player�Ƃ̋���
	pos_.x += sinf(tnl::ToRadian(angle_)) * (player->size_w * player_distans);
}

//---------------------------------update-------------------------------------------------------

void Bullet::Update(float deltatime) {
	switch (type_) {
		//�֐��|�C���^�B�����̓N���X�ɂ���status�ŊǗ�
		NormalMoveState normalstate;
		LaserMoveState laserstate;
		ShotgunMoveState shotgunstate;
		AroundMoveState aroundstate;
	case static_cast<int>(GameManager::BULLETTYPE::NORMAL):
		move = &Bullet::NormalMove;
		move(this, &normalstate);
		break;
	case static_cast<int>(GameManager::BULLETTYPE::LASER):
		move = &Bullet::LaserMove;
		move(this, &laserstate);
		break;
	case static_cast<int>(GameManager::BULLETTYPE::SHOTGUN):
		shotgunstate.deltatime_ = deltatime;
		move = &Bullet::ShotgunMove;
		move(this, &shotgunstate);
		break;
	case static_cast<int>(GameManager::BULLETTYPE::AROUND):
		aroundstate.deltatime_ = deltatime;
		move = &Bullet::AroundMove;
		move(this, &aroundstate);
		break;
	default:
		break;
	}
}

//------------------------------------render-----------------------------------------

void Bullet::CircleDraw(Camera* camera) {
	int x = pos_.x - camera->pos_.x + GameManager::SCREEN_W_HALF;
	int y = pos_.y - camera->pos_.y + GameManager::SCREEN_H_HALF;
	DrawRotaGraph(x, y, 1.0f, 0, bullet_img_, true);
}

void Bullet::BoxDraw(Camera* camera) {
	int x1 = pos_.x - (size_w >> 1);
	int y1 = pos_.y - (size_h >> 1);
	int x2 = pos_.x + (size_w >> 1);
	int y2 = pos_.y + (size_h >> 1);

	x1 = x1 - camera->pos_.x + GameManager::SCREEN_W_HALF;
	x2 = x2 - camera->pos_.x + GameManager::SCREEN_W_HALF;
	y1 = y1 - camera->pos_.y + GameManager::SCREEN_H_HALF;
	y2 = y2 - camera->pos_.y + GameManager::SCREEN_H_HALF;
	DrawRotaGraph((x1 + x2) / 2, (y1 + y2) / 2, 1.0f, 0, bullet_img_, true);
}

void Bullet::Render(Camera* camera) {
	switch (type_) {
	case static_cast<int>(GameManager::BULLETTYPE::NORMAL):
		draw = &Bullet::CircleDraw;
		draw(this,camera);
		break;
	case static_cast<int>(GameManager::BULLETTYPE::LASER):
		draw = &Bullet::BoxDraw;//laser��box��
		draw(this, camera);
		break;
	case static_cast<int>(GameManager::BULLETTYPE::SHOTGUN):
		draw = &Bullet::CircleDraw;
		draw(this,camera);
		break;
	case static_cast<int>(GameManager::BULLETTYPE::AROUND):
		draw = &Bullet::CircleDraw;
		draw(this,camera);
		break;
	default:
		break;
	}
}