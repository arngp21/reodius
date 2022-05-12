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

	bool StartMove(const float deltatime);//始まったときからタイトルスタートを押せるようになるまでのシーン
	bool TitleMain(const float deltatime);//タイトルメイン、

	tnl::Sequence<TitleScene>sequence_ =
		tnl::Sequence<TitleScene>(this, &TitleScene::StartMove);

	enum class Tscene {
		START,
		MAIN
	};
	Tscene nowSeq = Tscene::START;
	void ChangeSequence(Tscene changeSeq);

	//gamestartを押してから始まるまでのディレイ
	bool b_start_delay = false;
	float delay_count = 0;
};