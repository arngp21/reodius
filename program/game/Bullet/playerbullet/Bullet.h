#pragma once
#include"BulletStatus.h"
#include<functional>
#include<memory>

class Object;
struct bulletmove {
	tnl::Vector3 move_ = { 0,-1,0 };//shotgun�Ŏg�p
};

class Bullet : public BulletStatus {
public:
	Bullet(const int type, const tnl::Vector3 start_pos, bulletmove desc, std::string img_name, std::shared_ptr<Object>parent);

	static int BulletID_;//laser�Ŏg�p�Bstatic�ɂ��邱�Ƃŕϐ��͈����
private:
	std::function<void(Bullet*, BulletMoveBase* state)> move;

	//�N���Ăяo�����̂�
	std::shared_ptr<Object>callParent = nullptr;
	
	//shotgun��around�������Ă����鎞��
	const float AROUND_ALIVE_TIME_ = 2;
	const float SHOT_ALIVE_TIME_ = 0.85f;

	float alive_count_ = 0;
	float angle_ = 0;//aroundbullet����
	int type_ = 0;//����Ń^�C�v����
	int bullet_img_ = 0;//�摜�n���h��

	void NormalMove(BulletMoveBase* state);
	void ShotgunMove(BulletMoveBase* state);
	void LaserMove(BulletMoveBase* state);
	void AroundMove(BulletMoveBase* state);
	const float player_distans = 1.7;

	std::function<void(Bullet*, Camera* camera)> draw;

	void BoxDraw(Camera* camera);
	void CircleDraw(Camera* camera);

	void Update(float deltatime) override;
	void Render(Camera* camera) override;
};