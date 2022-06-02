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

	bool b_is_move = false;
	//boss�����񂾂Ƃ��̃G�t�F�N�g�i�����~5�j
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

	//�֐��|�C���^�ɑ�����Ďg���֐�
	//���i
	void MoveGostrigt(EnemyMoveStateBase* state);
	//�ǔ�
	void MoveChase(EnemyMoveStateBase* state);
	//�Œ�C��
	void MoveFixed(EnemyMoveStateBase* state);
	//�㉺�^��
	void MoveUpanddown(EnemyMoveStateBase* state);
	//�G�𐶐�����e
	void MoveCreateenemy(EnemyMoveStateBase* state);
	//��x�~�܂��Ă���player�Ɍ������ē����o��
	void MoveAcceleration(EnemyMoveStateBase* state);
	//�e���琶�������G�i�e�����j
	void MoveChild(EnemyMoveStateBase* state);
	//�e���琶�������G�Q�i�ǔ��j
	void MoveChild2(EnemyMoveStateBase* state);
	//Boss�B�e���T�����ɔ�΂��A�G�𐶐��Aplayer�ɍ��킹���㉺�^��
	void MoveBoss(EnemyMoveStateBase* state);

	int img_enemy1[4];//��
	int img_enemy2[4];//��
	int img_enemy3[4];//��
	int img_enemy4;//�q������
	int img_enemy5;//�l�p
	int img_boss_;
	int anime_time_count_ = 0;
	int anime_flame_ = 0;

	void Update(float deltatime) override;
	void Render(Camera* camera) override;
};
