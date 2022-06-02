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
	posy_max_ = pos_.y - 60;//windowの下までいかないように
	LoadDivGraph("graphics/enemy1.png", 4, 4, 1, 75, 75, img_enemy1);
	LoadDivGraph("graphics/enemy2.png", 4, 4, 1, 75, 60, img_enemy2);
	LoadDivGraph("graphics/enemy3.png", 4, 4, 1, 75, 75, img_enemy3);
	img_enemy5 = gamemanager_->Loadimag("graphics/Game_052.png");
	img_enemy4 = gamemanager_->Loadimag("graphics/enemy4.png");
	img_boss_ = gamemanager_->Loadimag("graphics/Game_boss.png");
}

Enemy::~Enemy() {
	std::shared_ptr<EnemyManager>enemymanager_ = gamemanager_->GetEnemyManager();
	if (deadtype_ == static_cast<int>(DeadType::BULLET_HIT_DEATH)) {
		DeathEffect();//エフェクト生成
		//コインの生成
		if (type_ != static_cast<int>(EnemyMoveType::CHILD) && type_ != static_cast<int>(EnemyMoveType::CHILD2) && type_ != static_cast<int>(EnemyMoveType::BOSS)) {
			std::shared_ptr<EnemyDrop> en_dor = std::make_shared<EnemyDrop>(pos_);
			enemymanager_->enemy_drops_.emplace_back(en_dor);
			en_dor->initialize();
		}
		PlaySoundMem(gamemanager_->snd_damage, DX_PLAYTYPE_BACK, true);
		gamemanager_->scorkeep_ += scor_;
	}
	else if (deadtype_ == static_cast<int>(DeadType::PLAYER_DEATH)) {
	}
	else if (deadtype_ == static_cast<int>(DeadType::ENEMY_SCREEN_OUT)) {
	}
}

//---------------------------------effect-----------------------------------------------------

void Enemy::BossEffect(float deltatime)
{
	tnl::Vector3 pos(1, 0, 0);
	std::shared_ptr<EnemyManager>enemymanager = gamemanager_->GetEnemyManager();
	time_count_ += 0.1f;
	if (time_count_ > BOSS_EFFECT_INTERVAL) {
		std::shared_ptr<Effect> ef = std::make_shared<Effect>(pos, pos_, static_cast<int>(EnemyMoveType::BOSS));
		ef->init();
		count++;
		time_count_ = 0;
	}

	if (count > 5) {
		is_alive_ = false;
		gamemanager_->b_clear_change = true;
	}
}

//-------------------------------------直進------------------------------------------------

void Enemy::MoveGostrigt(EnemyMoveStateBase* state) {
	pos_.x -= speed_;
	//直進。画面の４分の１で下がる
	if (pos_.x > (gamemanager_->camera_.pos_.x) + (gamemanager_->SCREEN_W / 4)) pos_.y++;
}

//-------------------------------------追尾-----------------------------------------------

void Enemy::MoveChase(EnemyMoveStateBase* state) {
	//playerを追う
	Enemy2MoveState* move_state = static_cast<Enemy2MoveState*>(state);
	pos_.x -= speed_;
	if (pos_.x > move_state->p_pos.x) {
		move_dir_ = move_state->p_pos - pos_;
		move_dir_.normalize();
		pos_ += move_dir_ * 2.5f;
	}
	else {
		pos_ += move_dir_ * 2;
	}
}

//-----------------------------------固定砲台-----------------------------------------------

void Enemy::MoveFixed(EnemyMoveStateBase* state) {
	Enemy3MoveState* move_state = static_cast<Enemy3MoveState*>(state);

	boss_create_bullet_count_ += move_state->delta_time;
	if (boss_create_bullet_count_ > 1.5f) {
		move_dir_ = move_state->p_pos - pos_;//playerのベクトル計算
		move_dir_.normalize();
		gamemanager_->enemymanager_->CreateEnemyBullet(pos_, move_dir_);
		boss_create_bullet_count_ = 0;
	}
}

//----------------------------------上下運動--------------------------------------------------

void Enemy::MoveUpanddown(EnemyMoveStateBase* state) {
	Enemy4MoveState* move_state = static_cast<Enemy4MoveState*>(state);

	pos_.x -= speed_;
	angle_ += 4;
	float a = sinf(tnl::ToRadian(angle_));
	pos_.y += a * 6;
}

//----------------------------------親----------------------------------------------------------

void Enemy::MoveCreateenemy(EnemyMoveStateBase* state) {
	Enemy5MoveState* move_state = static_cast<Enemy5MoveState*>(state);

	boss_create_bullet_count_ += move_state->delta_time;

	if (boss_create_bullet_count_ > 2.5f) {
		gamemanager_->enemymanager_->CreateChildEnemy(pos_.x, pos_.y, static_cast<int>(EnemyMoveType::CHILD));
		boss_create_bullet_count_ = 0;
	}
}

//---------------------------------止まる→動く-------------------------------------------------

void Enemy::MoveAcceleration(EnemyMoveStateBase* state) {
	Enemy6MoveState* move_state = static_cast<Enemy6MoveState*>(state);

	if (move_state->p_pos.x < pos_.x) {
		if (pos_.x < gamemanager_->camera_.pos_.x + (GameManager::SCREEN_W / 3)) {
			move_dir_ = move_state->p_pos - pos_;
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

//-------------------------------子供１--------------------------------------------

void Enemy::MoveChild(EnemyMoveStateBase* state) {
	EnemyChild* move_state = static_cast<EnemyChild*>(state);
	std::shared_ptr<EnemyManager>enemymanager_ = gamemanager_->GetEnemyManager();

	if (!b_is_move) {
		if (pos_.y > posy_max_) {
			pos_.y -= 2;
		}
		else b_is_move = true;
	}
	else {
		boss_create_bullet_count_ += move_state->delta_time;
		if (boss_create_bullet_count_ > 2.0f) {
			move_dir_ = move_state->p_pos - pos_;
			move_dir_.normalize();
			enemymanager_->CreateEnemyBullet(pos_, move_dir_);
			boss_create_bullet_count_ = 0;
		}
		pos_.x -= speed_;
	}
}

//-------------------------------------子供２------------------------------------------

void Enemy::MoveChild2(EnemyMoveStateBase* state) {
	EnemyChild* move_state = static_cast<EnemyChild*>(state);

	pos_.x -= speed_;
	if (pos_.x > move_state->p_pos.x) {
		move_dir_ = move_state->p_pos - pos_;
		move_dir_.normalize();
		pos_ += move_dir_ * 2.5f;
	}
	else {
		pos_ += move_dir_ * 2;
	}
}

//----------------------------------ボス----------------------------------------------

void Enemy::MoveBoss(EnemyMoveStateBase* state) {
	EnemyBoss* move_state = static_cast<EnemyBoss*>(state);
	if (!gamemanager_->b_boss_dead) {
		std::shared_ptr<EnemyManager>enemymanager_ = gamemanager_->GetEnemyManager();

		//playerに合わせて上下するように
		if (pos_.y < gamemanager_->player_->pos_.y) {
			pos_.y += speed_;
		}
		else pos_.y -= speed_;

		if (pos_.x < (gamemanager_->camera_.pos_.x + GameManager::SCREEN_W / 3)) {
			gamemanager_->b_camera_stop = false;//bossが出きったらカメラを止める
		}

		//bulletを生成
		boss_create_bullet_count_ += move_state->delta_time;
		if (boss_create_bullet_count_ > BOSS_CREATE_BULLET_INTERVAL_) {
			tnl::Vector3 hoz = { 0,1,0 };
			move_dir_ = move_state->p_pos - pos_;
			move_dir_.normalize();
			for (int i = 30; i <= 150; i += 30) {
				tnl::Vector3 move_ = tnl::Vector3::TransformCoord(hoz, tnl::Matrix::RotationAxis(tnl::Vector3(0, 0, 1), tnl::ToRadian(i)));
				enemymanager_->CreateEnemyBullet(pos_, move_);
			}
			boss_create_bullet_count_ = 0;
		}

		//enemyを生成
		boss_create_enemy_count_ += move_state->delta_time;
		if (boss_create_enemy_count_ > BOSS_CREATE_ENEMY_INTERVAL_) {
			int create_type = 0;
			create_type = rand() % 2;
			if (create_type == 0) {
				enemymanager_->CreateChildEnemy(pos_.x - 200, pos_.y, static_cast<int>(EnemyMoveType::CHILD));
			}
			else {
				enemymanager_->CreateChildEnemy(pos_.x - 200, pos_.y, static_cast<int>(EnemyMoveType::CHILD2));
			}
			boss_create_enemy_count_ = 0;
		}
	}
	else BossEffect(move_state->delta_time);
}

//----------------------------------update-------------------------------------

void Enemy::Update(float deltatime) {
	if (b_ondisplay_) {
		//引数クラスのプロトタイプ宣言
		Enemy1MoveState state1;
		Enemy2MoveState state2;
		Enemy3MoveState state3;
		Enemy4MoveState state4;
		Enemy5MoveState state5;
		Enemy6MoveState state6;
		EnemyBoss stateboss;
		EnemyChild stateC;

		std::shared_ptr<Player> player = gamemanager_->GetPlayer();
		switch (type_) {
		case static_cast<int>(EnemyMoveType::GOSTRIGHT):
			state1.delta_time = deltatime;
			move = &Enemy::MoveGostrigt;
			move(this, &state1);
			break;
		case static_cast<int>(EnemyMoveType::CHASE):
			state2.p_pos = player->pos_;
			move = &Enemy::MoveChase;
			move(this, &state2);
			break;
		case static_cast<int>(EnemyMoveType::FIXED):
			state3.delta_time = deltatime;
			state3.p_pos = player->pos_;
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
			state6.p_pos = player->pos_;
			move = &Enemy::MoveAcceleration;
			move(this, &state6);
			break;
		case static_cast<int>(EnemyMoveType::BOSS):
			stateboss.delta_time = deltatime;
			stateboss.p_pos = player->pos_;
			move = &Enemy::MoveBoss;
			move(this, &stateboss);
			break;
		case static_cast<int>(EnemyMoveType::CHILD):
			stateC.delta_time = deltatime;
			stateC.p_pos = player->pos_;
			move = &Enemy::MoveChild;
			move(this, &stateC);
			break;
		case static_cast<int>(EnemyMoveType::CHILD2):
			stateC.delta_time = deltatime;
			stateC.p_pos = player->pos_;
			move = &Enemy::MoveChild2;
			move(this, &stateC);
			break;
		default:
			break;
		}
	}
}

//-----------------------------------render-----------------------------------

void Enemy::Render(Camera* camera) {
	if (b_render) {
		//enemyanimetion();
		int x1 = pos_.x - (size_w >> 1);
		int y1 = pos_.y - (size_h >> 1);
		int x2 = pos_.x + (size_w >> 1);
		int y2 = pos_.y + (size_h >> 1);

		x1 = x1 - camera->pos_.x + GameManager::SCREEN_W_HALF;
		x2 = x2 - camera->pos_.x + GameManager::SCREEN_W_HALF;
		y1 = y1 - camera->pos_.y + GameManager::SCREEN_H_HALF;
		y2 = y2 - camera->pos_.y + GameManager::SCREEN_H_HALF;

		/*tnl::Vector3 pos((x1 + x2) / 2, (y1 + y2) / 2, 0);*/

		anime_time_count_++;
		if (anime_time_count_ == 16) {
			anime_flame_++;
			anime_flame_ %= 4;
			anime_time_count_ = 0;
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
			DrawRotaGraph((x1 + x2) / 2, (y1 + y2) / 2, 0.35f, 0, img_enemy5, true);
			break;
		case static_cast<int>(EnemyMoveType::BOSS):
			DrawRotaGraph((x1 + x2) / 2, (y1 + y2) / 2, 1.25f, 0, img_boss_, true);
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
		//DrawBox(x1, y1, x2, y2, GetColor(0, 100, 100), false);
	}
	//effectに渡す座標
	gift_pos_ = { pos_.x - camera->pos_.x + GameManager::SCREEN_W_HALF,pos_.y - camera->pos_.y + GameManager::SCREEN_H_HALF,0 };
}