#pragma once
#include"../../gamesystem/Object.h"

class BulletStatus : public Object {
public:
	int bullet_ID_ = 0;//laserに必要なID（一回当たったら通さない）
	//int bullettype_ = static_cast<int>(BULLETTYPE::NORMAL);
};

//引数クラス
class BulletMoveBase {
public:
};

class NormalMoveState : public BulletMoveBase {
public:
};

class LaserMoveState : public BulletMoveBase {
public:
};

class ShotgunMoveState : public BulletMoveBase {
public:
	float deltatime_;
};

class AroundMoveState : public BulletMoveBase {
public:
	float deltatime_;
};