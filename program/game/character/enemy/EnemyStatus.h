#pragma once
#include"../../gamesystem/Object.h"
#include"../../gamesystem/Effect.h"

//敵が死んだ時の動き
enum DeadType {
	PLAYER_DEATH,
	BULLET_HIT_DEATH,
	ENEMY_SCREEN_OUT,
};

class EnemyMoveStateBase {
public:
};

class EnemyStatus : public Object{
public:
	DeadType deadtype_ = BULLET_HIT_DEATH;

	int hp_;
	bool b_ondisplay = false;

	std::shared_ptr<Effect> effect_;

	//アニメーション
	int anim_flame_count_ = 0;
	int anim_flame_ = 0;

	virtual void DeathEffect();
	//virtual void Move(EnemyMoveStateBase* state) {}//敵の動き
	virtual void EnemyAnimetion();//敵の画像アニメーションを動かす関数
};

//createEnemyで引数として使うクラス
class Enemy1MoveState : public EnemyMoveStateBase {
public:
	float delta_time;
};

class Enemy2MoveState : public EnemyMoveStateBase {
public:
	tnl::Vector3 p_pos;
	tnl::Vector3 en_pos;
};

class Enemy3MoveState : public EnemyMoveStateBase {
public:
	tnl::Vector3 p_pos;
	tnl::Vector3 en_pos;
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
	tnl::Vector3 en_pos;
};

class EnemyChild : public EnemyMoveStateBase {
public:
	tnl::Vector3 p_pos;
	tnl::Vector3 en_pos;
	float delta_time;
};

class EnemyBoss : public EnemyMoveStateBase {
public:
	tnl::Vector3 p_pos;
	tnl::Vector3 en_pos;
	float delta_time;
};