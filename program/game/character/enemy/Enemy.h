#pragma once
#include <functional>
#include"EnemyStatus.h"

enum class EnemyMoveType {
	CHILD,
	CHILD2,
	GOSTRIGHT,
	CHASE,
	FIXED,
	UPANDDOWN,
	CREATEENEMY,
	ACCELERATION,
	BOSS
};

class Enemy : public EnemyStatus {
public:
	Enemy(const int type_, const int pos_x,const int pos_y, const int sz_w, const int sz_h, const int ac_type, const int hp,const float sp, const int scor);
	~Enemy();
	int type_ = 0;
private:
	//関数ポインタ
	//functionで受け皿を作ってあげる()
	std::function<void(Enemy*, EnemyMoveStateBase* state)> move;

	bool b_is_move = false;
	//bossが死んだときのエフェクト（爆発×5）
	void BossEffect(float deltatime);
	float boss_create_bullet_count_ = 0;
	float boss_create_enemy_count_ = 0;

	float time_count_ = 0;
	int count = 0;
	const float BOSS_EFFECT_INTERVAL = 1.5;

	const float BOSS_CREATE_BULLET_INTERVAL_ = 0.75;
	const float BOSS_CREATE_ENEMY_INTERVAL_ = 1.1;
	float posy_max_ = 0;
	int angle_ = 0;
	int scor_ = 0;

	//関数ポインタに代入して使う関数
	//直進
	void MoveGostrigt(EnemyMoveStateBase* state);
	//追尾
	void MoveChase(EnemyMoveStateBase* state);
	//固定砲台
	void MoveFixed(EnemyMoveStateBase* state);
	//上下運動
	void MoveUpanddown(EnemyMoveStateBase* state);
	//敵を生成する親
	void MoveCreateenemy(EnemyMoveStateBase* state);
	//一度止まってからplayerに向かって動き出す
	void MoveAcceleration(EnemyMoveStateBase* state);
	//親から生成される敵（弾生成）
	void MoveChild(EnemyMoveStateBase* state);
	//親から生成される敵２（追尾）
	void MoveChild2(EnemyMoveStateBase* state);
	//Boss。弾を５方向に飛ばす、敵を生成、playerに合わせた上下運動
	void MoveBoss(EnemyMoveStateBase* state);

	int img_enemy1[4];//赤
	int img_enemy2[4];//緑
	int img_enemy3[4];//紫
	int img_enemy4;//子供生成
	int img_enemy5;//四角
	int img_boss_;
	int anime_time_count_ = 0;
	int anime_flame_ = 0;

	void Update(float deltatime) override;
	void Render(Camera* camera) override;
};
