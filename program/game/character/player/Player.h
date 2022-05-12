#pragma once
#include"../../gamesystem/Object.h"
#include"../../gamesystem/Scene/Icon.h"

class Player : public Object {
public:
	Player(const tnl::Vector3 &strat_pos_);
	~Player();

	float speed_magnification_ = 1.5f;//speed�ɑ����Ă����ϐ�
	float back_speed_ = 2;//���ɖ߂�Ƃ��ɂ����Ă����ϐ�(speed_magnification_�ƈꏏ�ɒl�������邽��const�ł͂Ȃ�)
	int hp_ = 0;//gamemanager��consthp���

private:

	int item_ = 0;//player���Ƃ���item
	int player_img_ = 0;//�摜�n���h��

	int create_count_ = 0;
	float time_count_ = 0;
	bool b_create_around = false;//�q���e��4�����o�������̂ŁAbool�ŊǗ�

	float shot_interval = 0;

	void Update(float deltatime) override;
	void Render(Camera* camera) override;

	bool Move();//player�̓���(�L�[����)bool�ɂ��Ēl��Ԃ����Ƃŉ�����ĂȂ��Ƃ������m�ł���
};
