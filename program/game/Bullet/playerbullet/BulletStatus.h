#pragma once
#include"../../gamesystem/Object.h"

enum BULLETTYPE {
	NORMAL,
	LASER,
	SHOTGUN,
	AROUND,
};

class BulletStatus : public Object {
public:

	int bullet_ID_ = 0;//laserに必要なID（一回当たったら遠さない）
	BULLETTYPE bullettype_;
};