#include "GameOverScene.h"
#include"../GameManager.h"
#include"SceneManager.h"

extern GameManager* gamemanager_;

GameOverScene::GameOverScene() {
	StopSoundMem(gamemanager_->snd_play);
	StopSoundMem(gamemanager_->snd_boss);
	PlaySoundMem(gamemanager_->snd_gameover, DX_PLAYTYPE_BACK, true);
	ChangeVolumeSoundMem(200, gamemanager_->snd_gameover);
	gamemanager_->ObjectInit();
}

void GameOverScene::SceneUpdate(float deltatime)
{
	if (tnl::Input::IsKeyDownTrigger(tnl::Input::eKeys::KB_RETURN)) SceneManager::ChangeScene(SceneManager::TITLE);
}

void GameOverScene::SceneDraw()
{
	SetFontSize(120);
	DrawStringEx(250, 200, GetColor(250, 0, 0), "GAME OVER");
	SetFontSize(50);
	DrawStringEx(300, 500, -1, "Enter‚Åƒ^ƒCƒgƒ‹‚Ö");
}
