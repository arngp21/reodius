#pragma once
#include"../../gamesystem/Object.h"

class BulletStatus : public Object {
public:
	int bullet_ID_ = 0;//laser�ɕK�v��ID�i��񓖂�������ʂ��Ȃ��j
	//int bullettype_ = static_cast<int>(BULLETTYPE::NORMAL);
};

//�����N���X
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