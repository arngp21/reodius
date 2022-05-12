#include"SceneManager.h"

BaseScene* SceneManager::now_Scene = nullptr;

void SceneManager::ChangeScene(SCENE scene) {
	if (now_Scene != nullptr) {
		delete now_Scene;
		now_Scene = nullptr;
	}

	switch (scene)
	{
	case SCENE::TITLE:
		now_Scene = new TitleScene();
		break;
	case SCENE::PLAY:
		now_Scene = new PlayScene();
		break;
	case SCENE::GAMEOVER:
		now_Scene = new GameOverScene();
		break;
	case SCENE::CLEAR:
		now_Scene = new ClearScene();
		break;
	default:
		break;
	}
}

void SceneManager::SceneManagerUpdate(float deltatime) {
	now_Scene->SceneUpdate(deltatime);
}

void SceneManager::SceneManagerRender() {
	now_Scene->SceneDraw();
}