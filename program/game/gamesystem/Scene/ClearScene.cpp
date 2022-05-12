#include"ClearScene.h"
#include"../GameManager.h"
#include"SceneManager.h"

extern GameManager* gamemanager_;

ClearScene::ClearScene(){
	score = gamemanager_->scorkeep_;
	StopSoundMem(gamemanager_->snd_play);
	StopSoundMem(gamemanager_->snd_boss);
	gamemanager_->ObjectInit();
	img_back = gamemanager_->Loadimag("graphics/uchuu.jpg");
}

void ClearScene::SceneUpdate(float deltatime) {
	if (tnl::Input::IsKeyDownTrigger(tnl::Input::eKeys::KB_RETURN)) {
		SceneManager::ChangeScene(SceneManager::TITLE);
	}
}

void ClearScene::SceneDraw() {
	DrawExtendGraph(0, 0, GameManager::SCREEN_W, GameManager::SCREEN_H,img_back, true);
	SetFontSize(120);
	DrawStringEx(GameManager::SCREEN_W / 6,GameManager::SCREEN_H / 3,-1,"GAME CLEAR!!");
	SetFontSize(90);
	DrawStringEx(GameManager::SCREEN_W / 3, (GameManager::SCREEN_H / 3) + 100, -1, "SCORE %d", score);
}