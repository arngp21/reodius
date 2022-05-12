#pragma once
#include"BaseScene.h"
#include<memory>
#include "../../../dxlib_ext/dxlib_ext.h"

class Player;

class TitleScene : public BaseScene {
public:
	void SceneUpdate(float deltatime) override;
	void SceneDraw() override;
	TitleScene();

private:

	bool StartMove(const float deltatime);//�n�܂����Ƃ�����^�C�g���X�^�[�g��������悤�ɂȂ�܂ł̃V�[��
	bool TitleMain(const float deltatime);//�^�C�g�����C���A

	tnl::Sequence<TitleScene>sequence_ =
		tnl::Sequence<TitleScene>(this, &TitleScene::StartMove);

	enum class Tscene {
		START,
		MAIN
	};
	Tscene nowSeq = Tscene::START;
	void ChangeSequence(Tscene changeSeq);

	//gamestart�������Ă���n�܂�܂ł̃f�B���C
	bool b_start_delay = false;
	float delay_count = 0;
};