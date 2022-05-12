#pragma once
#include"BaseScene.h"

class ClearScene : public BaseScene {
public:
	ClearScene();
	void SceneUpdate(float deltatime) override;
	void SceneDraw() override;

private:
	int img_back = 0;
	int score = 0;
};
