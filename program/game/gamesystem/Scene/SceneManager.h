#pragma once
#include"BaseScene.h"
#include"TitleScene.h"
#include"PlayScene.h"
#include"GameOverScene.h"
#include"ClearScene.h"

class SceneManager{
public:
	//SceneManager();

	enum SCENE {
		TITLE,
		PLAY,
		GAMEOVER,
		CLEAR
	};
	SCENE scene;

	static void ChangeScene(SCENE scene);//scene‚ğ•Ï‚¦‚é‚Æ‚«‚É‚Ù‚©‚Ìcpp‚©‚çŒÄ‚ÔŠÖ”
	static void SceneManagerUpdate(float deltatime);
	static void SceneManagerRender();

//:
	static BaseScene* now_Scene;//Œ»İ‚ÌƒV[ƒ“
};
