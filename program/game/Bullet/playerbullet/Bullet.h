#pragma once
#include"BulletStatus.h"
#include<functional>
#include<memory>

class Object;
struct bulletmove {
	tnl::Vector3 move_ = { 0,-1,0 };//shotgunで使用
};

class Bullet : public BulletStatus {
public:
	Bullet(const int type, const tnl::Vector3 start_pos, bulletmove desc, std::string img_name, std::shared_ptr<Object>parent);

	static int BulletID_;//laserで使用。staticにすることで変数は一つだけ
private:
	std::function<void(Bullet*, BulletMoveBase* state)> move;

	//誰が呼び出したのか
	std::shared_ptr<Object>callParent = nullptr;
	
	//shotgunとaroundが生きていられる時間
	const float AROUND_ALIVE_TIME_ = 2;
	const float SHOT_ALIVE_TIME_ = 0.85f;

	float alive_count_ = 0;
	float angle_ = 0;//aroundbulletを回す
	int type_ = 0;//これでタイプ分け
	int bullet_img_ = 0;//画像ハンドル

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