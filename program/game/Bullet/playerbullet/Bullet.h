#pragma once
#include"BulletStatus.h"
#include<functional>

struct bulletmove {
	tnl::Vector3 move_ = { 0,-1,0 };//shotgunで使用
};

class Bullet : public BulletStatus {
public:
	Bullet(const int type, const tnl::Vector3 start_pos , bulletmove desc, std::string img_name);

	static int BulletID_;//laserで使用
private:
	std::function<void(Bullet*, float deltatime)> move;

	//shotgunとaroundが生きていられる時間
	const float AR_ALIVE_TIME_ = 2;
	const float SO_ALIVE_TIME_ = 0.85f;

	float alive_count_ = 0;
	float angle_ = 0;//aroundbulletを回す
	int type_ = 0;//これでタイプ分け
	int bullet_img_ = 0;//画像ハンドル

	void NormalMove(float deltatime);
	void ShotgunMove(float deltatime);
	void LaserMove(float deltatime);
	void AroundMove(float deltatime);

	std::function<void(Bullet*, Camera* camera)> draw;

	void BoxDraw(Camera* camera);
	void CircleDraw(Camera* camera);

	void Update(float deltatime) override;
	void Render(Camera* camera) override;
};