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

	int priority_ = 0;//�\�[�g

	std::list<int> ID_;//Object�Ɏ�������ID(���݂͓����蔻���Enemy�����g���Ă��Ȃ�)

	tnl::Vector3 pos_;
	tnl::Vector3 move_dir_;
	tnl::Vector3 gift_pos_;

	float speed_ = 0;
	bool is_alive_ = true;

	bool b_render = false;//��ʓ��ŕ`�悷�邩�ǂ���
	bool b_is_move = true;//����

	int size_w = 0;//Object�̃T�C�Y
	int size_h = 0;

	
};
