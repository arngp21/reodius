#pragma once
#include"BaseScene.h"

class GameOverScene : public BaseScene {
public:
	GameOverScene();

	void SceneUpdate(float deltatime) override;
	void SceneDraw() override;

private:
	bool b_render = false;
	int arufa = 255;

};
