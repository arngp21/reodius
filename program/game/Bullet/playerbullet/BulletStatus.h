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

	int bullet_ID_ = 0;//laser�ɕK�v��ID�i��񓖂������牓���Ȃ��j
	BULLETTYPE bullettype_;
};