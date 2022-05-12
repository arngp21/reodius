#pragma once
#include <memory>
#include"Camera.h"
#include "../../dxlib_ext/dxlib_ext.h"


class Object : public std::enable_shared_from_this<Object>{

public:
	virtual ~Object(){}
	virtual void initialize();
	virtual void OnDisplyRender() {}
	virtual void Update(float deltatime) {}
	virtual void Render(Camera* camera) {}

//protected:

	int priority_ = 0;//ソート

	std::list<int> ID_;//Objectに持たせるID(現在は当たり判定でEnemyしか使っていない)

	tnl::Vector3 pos_;
	tnl::Vector3 move_dir_;
	tnl::Vector3 gift_pos_;

	float speed_ = 0;
	bool is_alive_ = true;

	bool b_render = false;//画面内で描画するかどうか
	bool b_is_move = true;//動き

	int size_w = 0;//Objectのサイズ
	int size_h = 0;

	
};
