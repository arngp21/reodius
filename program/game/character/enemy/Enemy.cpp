#include"Enemy.h"
#include"../../gamesystem/GameManager.h"
#include"EnemyDrop.h"
#include"../../gamesystem/Scene/SceneManager.h"

extern GameManager* gamemanager_;

Enemy::Enemy(const int type, const int pos_x, const int pos_y, const int sz_w, const int sz_h, const int ac_type, const int hp, const float sp, const int scor) {
	pos_.x = pos_x;
	pos_.y = pos_y;
	speed_ = sp;
	size_w = sz_w;
	size_h = sz_h;
	hp_ = hp;
	type_ = type;
	scor_ = scor;
	posy_max_ = pos_.y - 60;
	deadtype_ = BULLET_HIT_DEATH;
	LoadDivGraph("graphics/enemy1.png", 4, 4, 1, 75, 75, img_enemy1);
	LoadDivGraph("graphics/enemy2.png", 4, 4, 1, 75, 60, img_enemy2);
	LoadDivGraph("graphics/enemy3.png", 4, 4, 1, 75, 75, img_enemy3);
	img_enemy5 = gamemanager_->Loadimag("graphics/Game_052.png");
	img_enemy4 = gamemanager_->Loadimag("graphics/enemy4.png");
	img_boss_ = gamemanager_->Loadimag("graphics/Game_boss.png");
}

Enemy::~Enemy() {
	std::shared_ptr<EnemyManager>enemymanager_ = gamemanager_->GetEnemyManager();
	if (deadtype_ == BULLET_HIT_DEATH) {
		DeathEffect();
		if (type_ != static_cast<int>(EnemyMoveType::CHILD) && type_ != static_cast<int>(EnemyMoveType::CHILD2)) {
			std::shared_ptr<EnemyDrop> en_dor = std::make_shared<EnemyDrop>(pos_);
			enemymanager_->enemy_drops_.emplace_back(en_dor);
			en_dor->initialize();
		}
		PlaySoundMem(gamemanager_->snd_damage, DX_PLAYTYPE_BACK, true);
		gamemanager_->scorkeep_ += scor_;
	}
	else if (deadtype_ == PLAYER_DEATH) {

	}
	else if (deadtype_ == ENEMY_SCREEN_OUT) {

	}
}

void Enemy::MoveGostrigt(EnemyMoveStateBase* state) {
	pos_.x -= speed_;
	if (pos_.x > (gamemanager_->camera_.pos_.x) + (gamemanager_->SCREEN_W / 4)) {
		pos_.y++;
	}
}

void Enemy::MoveChase(EnemyMoveStateBase* state) {
	Enemy2MoveState* move_state = static_cast<Enemy2MoveState*>(state);

	pos_.x -= speed_;
	if (pos_.x > move_state->p_pos.x) {
		move_dir_ = move_state->p_pos - move_state->en_pos;
		move_dir_.normalize();
		pos_ += move_dir_ * 2.5f;
	}
	else {
		pos_ += move_dir_ * 2;
	}
}

void Enemy::MoveFixed(EnemyMoveStateBase* state) {
	Enemy3MoveState* move_state = static_cast<Enemy3MoveState*>(state);

	create_count_ += move_state->delta_time;
	if (create_count_ > 1.5f) {
		move_dir_ = move_state->p_pos - move_state->en_pos;
		move_dir_.normalize();
		gamemanager_->enemymanager_->CreateEnemyBullet(move_state->en_pos, move_dir_);
		create_count_ = 0;
	}
}

void Enemy::MoveUpanddown(EnemyMoveStateBase* state) {
	Enemy4MoveState* move_state = static_cast<Enemy4MoveState*>(state);

	pos_.x -= speed_;
	angle += 4;
	float a = sinf(tnl::ToRadian(angle));
	pos_.y += a * 6;
}

void Enemy::MoveCreateenemy(EnemyMoveStateBase* state) {
	Enemy5MoveState* move_state = static_cast<Enemy5MoveState*>(state);

	create_count_ += move_state->delta_time;

	if (create_count_ > 2.5f) {
		gamemanager_->enemymanager_->CreateChildEnemy(pos_.x, pos_.y, static_cast<int>(EnemyMoveType::CHILD));
		create_count_ = 0;
	}
}

void Enemy::MoveAcceleration(EnemyMoveStateBase* state) {
	Enemy6MoveState* move_state = static_cast<Enemy6MoveState*>(state);

	if (move_state->p_pos.x < move_state->en_pos.x) {
		if (pos_.x < gamemanager_->camera_.pos_.x + (GameManager::SCREEN_W / 3)) {
			move_dir_ = move_state->p_pos - move_state->en_pos;
			move_dir_.normalize();
			pos_ += move_dir_ * 2.5f;
			pos_.x -= speed_;
		}
	}
	else {
		pos_.x -= speed_;
		pos_ += move_dir_ * 2;
	}
}

void Enemy::MoveChild(EnemyMoveStateBase* state) {
	EnemyChild* move_state = static_cast<EnemyChild*>(state);

	if (!is_move) {
		if (pos_.y > posy_max_) {
			pos_.y -= 2;
		}
		else is_move = true;
	}
	else {
		create_count_ += move_state->delta_time;
		if (create_count_ > 2.0f) {
			move_dir_ = move_state->p_pos - move_state->en_pos;
			move_dir_.normalize();
			gamemanager_->enemymanager_->CreateEnemyBullet(move_state->en_pos, move_dir_);
			create_count_ = 0;
		}
		pos_.x -= speed_;
	}
}

void Enemy::MoveChild2(EnemyMoveStateBase* state) {
	EnemyChild* move_state = static_cast<EnemyChild*>(state);

	pos_.x -= speed_;
	if (pos_.x > move_state->p_pos.x) {
		move_dir_ = move_state->p_pos - move_state->en_pos;
		move_dir_.normalize();
		pos_ += move_dir_ * 2.5f;
	}
	else {
		pos_ += move_dir_ * 2;
	}
}

void Enemy::MoveBoss(EnemyMoveStateBase* state) {
	EnemyBoss* move_state = static_cast<EnemyBoss*>(state);

	if (pos_.y < gamemanager_->player_->pos_.y) {
		pos_.y += speed_;
	}
	else pos_.y -= speed_;

	if (pos_.x < (gamemanager_->camera_.pos_.x + GameManager::SCREEN_W / 3)) {
		gamemanager_->b_camera_stop = false;
	}
	int create_type = 0;
	create_count_ += move_state->delta_time;
	if (create_count_ > 0.7f) {
		create_type = rand() % 4;
		create_count_ = 0;
		if (create_type == 1) {
			move_dir_ = move_state->p_pos - move_state->en_pos;
			move_dir_.normalize();
			gamemanager_->enemymanager_->CreateEnemyBullet(move_state->en_pos, move_dir_);
		}
		else if (create_type == 2) {
			gamemanager_->enemymanager_->CreateChildEnemy(pos_.x - 200, pos_.y, static_cast<int>(EnemyMoveType::CHILD));
		}
		else {
			gamemanager_->enemymanager_->CreateChildEnemy(pos_.x - 200, pos_.y, static_cast<int>(EnemyMoveType::CHILD2));
		}
	}
}

void Enemy::Update(float deltatime) {
	if (b_ondisplay) {
		//
		Enemy1MoveState state1;
		Enemy2MoveState state2;
		Enemy3MoveState state3;
		Enemy4MoveState state4;
		Enemy5MoveState state5;
		Enemy6MoveState state6;
		EnemyBoss stateboss;
		EnemyChild stateC;

		switch (type_) {
		case static_cast<int>(EnemyMoveType::GOSTRIGHT):
			state1.delta_time = deltatime;
			move = &Enemy::MoveGostrigt;
			move(this, &state1);
			break;
		case static_cast<int>(EnemyMoveType::CHASE):
			state2.p_pos = gamemanager_->player_->pos_;
			state2.en_pos = pos_;
			move = &Enemy::MoveChase;
			move(this, &state2);
			break;
		case static_cast<int>(EnemyMoveType::FIXED):
			state3.delta_time = deltatime;
			state3.en_pos = pos_;
			state3.p_pos = gamemanager_->player_->pos_;
			move = &Enemy::MoveFixed;
			move(this, &state3);
			break;
		case static_cast<int>(EnemyMoveType::UPANDDOWN):
			state4.delta_taime = deltatime;
			move = &Enemy::MoveUpanddown;
			move(this, &state4);
			break;
		case static_cast<int>(EnemyMoveType::CREATEENEMY):
			state5.delta_time = deltatime;
			move = &Enemy::MoveCreateenemy;
			move(this, &state5);
			break;
		case static_cast<int>(EnemyMoveType::ACCELERATION):
			state6.p_pos = gamemanager_->player_->pos_;
			state6.en_pos = pos_;
			move = &Enemy::MoveAcceleration;
			move(this, &state6);
			break;
		case static_cast<int>(EnemyMoveType::BOSS):
			stateboss.delta_time = deltatime;
			stateboss.en_pos = pos_;
			stateboss.p_pos = gamemanager_->player_->pos_;
			move = &Enemy::MoveBoss;
			move(this, &stateboss);
			break;
		case static_cast<int>(EnemyMoveType::CHILD):
			stateC.delta_time = deltatime;
			stateC.p_pos = gamemanager_->player_->pos_;
			stateC.en_pos = pos_;
			move = &Enemy::MoveChild;
			move(this, &stateC);
			break;
		case static_cast<int>(EnemyMoveType::CHILD2):
			stateC.delta_time = deltatime;
			stateC.p_pos = gamemanager_->player_->pos_;
			stateC.en_pos = pos_;
			move = &Enemy::MoveChild2;
			move(this, &stateC);
			break;
		default:
			break;
		}
	}
}

void Enemy::Render(Camera* camera) {
	if (b_render) {
		//enemyanimetion();
		int x1 = pos_.x - (size_w >> 1);
		int y1 = pos_.y - (size_h >> 1);
		int x2 = pos_.x + (size_w >> 1);
		int y2 = pos_.y + (size_h >> 1);

		x1 = x1 - camera->pos_.x + (GameManager::SCREEN_W >> 1);
		x2 = x2 - camera->pos_.x + (GameManager::SCREEN_W >> 1);
		y1 = y1 - camera->pos_.y + (GameManager::SCREEN_H >> 1);
		y2 = y2 - camera->pos_.y + (GameManager::SCREEN_H >> 1);

		/*tnl::Vector3 pos((x1 + x2) / 2, (y1 + y2) / 2, 0);*/

		time_count_++;
		if (time_count_ == 16) {
			anime_flame_++;
			anime_flame_ %= 4;
			time_count_ = 0;
		};

		switch (type_) {
		case static_cast<int>(EnemyMoveType::GOSTRIGHT):
			DrawRotaGraph((x1 + x2) / 2, (y1 + y2) / 2, 1.0f, 1.6f, img_enemy1[anime_flame_], true);
			break;
		case static_cast<int>(EnemyMoveType::CHASE):
			DrawRotaGraph((x1 + x2) / 2, (y1 + y2) / 2, 1.0f, 1.6f, img_enemy2[anime_flame_], true);
			break;
		case static_cast<int>(EnemyMoveType::FIXED):
			DrawRotaGraph((x1 + x2) / 2, (y1 + y2) / 2, 1.0f, 1.6f, img_enemy3[anime_flame_], true);
			break;
		case static_cast<int>(EnemyMoveType::UPANDDOWN):
			DrawRotaGraph((x1 + x2) / 2, (y1 + y2) / 2, 1.0f, 1.6f, img_enemy2[anime_flame_], true);
			break;
		case static_cast<int>(EnemyMoveType::CREATEENEMY):
			DrawRotaGraph((x1 + x2) / 2, (y1 + y2) / 2, 1.7f, 0, img_enemy4, true);
			break;
		case static_cast<int>(EnemyMoveType::ACCELERATION):
			//DrawBox(x1, y1, x2, y2, -1, true);
			DrawRotaGraph((x1 + x2) / 2, (y1 + y2) / 2, 0.45f, 0, img_enemy5, true);
			break;
		case static_cast<int>(EnemyMoveType::BOSS):
			DrawRotaGraph((x1 + x2) / 2, (y1 + y2) / 2, 1.3f, 0, img_boss_, true);
			//4DrawBox(x1, y1, x2, y2, -1, false);
			break;
		case static_cast<int>(EnemyMoveType::CHILD):
			DrawRotaGraph((x1 + x2) / 2, (y1 + y2) / 2, 1.0f, 1.6f, img_enemy1[anime_flame_], true);
			break;
		case static_cast<int>(EnemyMoveType::CHILD2):
			DrawRotaGraph((x1 + x2) / 2, (y1 + y2) / 2, 1.0f, 1.6f, img_enemy2[anime_flame_], true);
			break;
		default:
			break;
		}
	}
	gift_pos_ = { pos_.x - camera->pos_.x + (GameManager::SCREEN_W >> 1),pos_.y - camera->pos_.y + (GameManager::SCREEN_H >> 1),0 };
}