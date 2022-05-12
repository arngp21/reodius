#pragma once

class BaseScene {
public:
	virtual ~BaseScene(){}
	virtual void SceneUpdate(float deltatime){}
	virtual void SceneDraw(){}
};
