#pragma once
#include"BaseScene.h"
#include"Icon.h"
#include<memory>
#include "../../../dxlib_ext/dxlib_ext.h"

class PlayScene : public BaseScene {
public:
	//PlayScene();
	void SceneUpdate(float deltatime) override;
	void SceneDraw() override;

private:
	//MainPlayä÷êî
	bool SeqPlayMain(const float deltatime);
	//éÄÇÒÇ≈Ç©ÇÁïúãAÇ∑ÇÈÇ‹Ç≈ÇÃä÷êî
	bool SeqRestartInterbal(const float deltatime);
	//BossBattle
	bool SeqBossBattle(const float deltatime);
	
	bool b_init = false;
	bool b_reinit = false;
	bool b_change = false;
	bool b_snd_boss = false;

	float time_count_ = 0;
	const float SCENE_CANGE_INTERVAL = 9.0f;
	int arufa_ = 255;
	int img_player_hp_ = 0;

	tnl::Sequence<PlayScene>sequence_ =
		tnl::Sequence<PlayScene>(this, &PlayScene::SeqPlayMain);

};
