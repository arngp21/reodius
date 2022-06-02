#pragma once
#include"../../gamesystem/Object.h"
#include"../../gamesystem/Effect.h"

//�G�����񂾎��̓���
enum class DeadType {
	PLAYER_DEATH,
	BULLET_HIT_DEATH,
	ENEMY_SCREEN_OUT,
};

class EnemyMoveStateBase {
public:
};

class EnemyStatus : public Object{
public:
	int deadtype_ = static_cast<int>(DeadType::BULLET_HIT_DEATH);

	int hp_;
	bool b_ondisplay_ = false;

	std::shared_ptr<Effect> effect_;

	//�A�j���[�V����
	int anim_flame_count_ = 0;
	int anim_flame_ = 0;

	virtual void DeathEffect();
	//virtual void Move(EnemyMoveStateBase* state) {}//�G�̓���
	virtual void EnemyAnimetion();//�G�̉摜�A�j���[�V�����𓮂����֐�
};

//createEnemy�ň����Ƃ��Ďg���N���X
class Enemy1MoveState : public EnemyMoveStateBase {
public:
	float delta_time;
};

class Enemy2MoveState : public EnemyMoveStateBase {
public:
	tnl::Vector3 p_pos;
};

class Enemy3MoveState : public EnemyMoveStateBase {
public:
	tnl::Vector3 p_pos;
	float delta_time;
};

class Enemy4MoveState : public EnemyMoveStateBase {
public:
	float delta_taime;
};

class Enemy5MoveState : public EnemyMoveStateBase {
public:
	float delta_time;
};

class Enemy6MoveState : public EnemyMoveStateBase {
public:
	tnl::Vector3 p_pos;
};

class EnemyChild : public EnemyMoveStateBase {
public:
	tnl::Vector3 p_pos;
	float delta_time;
};

class EnemyBoss : public EnemyMoveStateBase {
public:
	tnl::Vector3 p_pos;
	float delta_time;
};