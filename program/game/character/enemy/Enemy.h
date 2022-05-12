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
	//�֐��|�C���^
	//function�Ŏ󂯎M������Ă�����()
	std::function<void(Enemy*, EnemyMoveStateBase* state)> move;

	bool is_move = false;
	float create_count_ = 0;
	float posy_max_ = 0;
	int angle = 0;
	int scor_ = 0;

	//�֐��|�C���^�ɑ�����Ďg���֐�
	void MoveGostrigt(EnemyMoveStateBase* state);
	void MoveChase(EnemyMoveStateBase* state);
	void MoveFixed(EnemyMoveStateBase* state);
	void MoveUpanddown(EnemyMoveStateBase* state);
	void MoveCreateenemy(EnemyMoveStateBase* state);
	void MoveAcceleration(EnemyMoveStateBase* state);
	void MoveChild(EnemyMoveStateBase* state);
	void MoveChild2(EnemyMoveStateBase* state);
	void MoveBoss(EnemyMoveStateBase* state);

	int img_enemy1[4];//��
	int img_enemy2[4];//��
	int img_enemy3[4];//��
	int img_enemy4;//�ł�����
	int img_enemy5;//�l�p
	int img_boss_;
	int time_count_ = 0;
	int anime_flame_ = 0;

	void Update(float deltatime) override;
	void Render(Camera* camera) override;
};
