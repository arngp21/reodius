#include"TitleScene.h"
#include"../GameManager.h"
#include"SceneManager.h"

extern GameManager* gamemanager_;

TitleScene::TitleScene() {
	gamemanager_->Initialize();
}

bool TitleScene::StartMove(const float deltatime) {
	std::shared_ptr<Player> player_ = gamemanager_->GetPlayer();
	//‰Šú“®ì
	if (player_->pos_.x < 200) {
		player_->pos_.x += 1.5f;
		player_->pos_.y -= 1.5f;
	}
	else {
		ChangeSequence(Tscene::MAIN);
	}

	return true;
}

bool TitleScene::TitleMain(const float deltatime) {
	if (tnl::Input::IsKeyDownTrigger(tnl::Input::eKeys::KB_RETURN)) {
		b_start_delay = true;
		std::shared_ptr<BackGraund>backgraund[2];
		backgraund[0] = gamemanager_->GetBackGraund(0);
		backgraund[1] = gamemanager_->GetBackGraund(1);
		backgraund[0]->startinterval = true;
		backgraund[1]->startinterval = true;
		PlaySoundMem(gamemanager_->snd_start, DX_PLAYTYPE_BACK, true);
	}
	
	if (b_start_delay)delay_count += deltatime;

	return true;
}

void TitleScene::ChangeSequence(Tscene changeSeq) {
	nowSeq = changeSeq;
	if (nowSeq == Tscene::MAIN) {
		sequence_.change(&TitleScene::TitleMain);
	}
}

void TitleScene::SceneUpdate(float deltatime) {
	sequence_.update(deltatime);
	//¡‚ÌƒV[ƒ“‚ªstartmove‚¶‚á‚È‚¢‚©‚Â@dalaycount>1.2f‚¾‚Á‚½‚ç
	if (nowSeq != Tscene::START && delay_count > 1.2f)SceneManager::ChangeScene(SceneManager::PLAY);
}

void TitleScene::SceneDraw() {
}