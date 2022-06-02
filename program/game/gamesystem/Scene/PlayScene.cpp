#include"PlayScene.h"
#include"../GameManager.h"
#include"SceneManager.h"
#include<memory>

extern GameManager* gamemanager_;

bool PlayScene::SeqPlayMain(const float deltatime) {
	if (!b_init) {
		img_player_hp_ = gamemanager_->Loadimag("graphics/sentouki.png");
		gamemanager_->loadIcon = tnl::LoadCsv("csv/LoadIcon.csv");//�Q�[������UI
		for (int i = 1; i < gamemanager_->loadIcon.size(); ++i) {
			int start_x = std::atoi(gamemanager_->loadIcon[i][1].c_str());
			int start_y = std::atoi(gamemanager_->loadIcon[i][2].c_str());
			int sz_w = std::atoi(gamemanager_->loadIcon[i][3].c_str());
			int sz_h = std::atoi(gamemanager_->loadIcon[i][4].c_str());
			int type = std::atoi(gamemanager_->loadIcon[i][5].c_str());
			//std::string img = PlayScene::loadIcon[i][5];

			std::shared_ptr<Icon> icon_hoz = std::make_shared<Icon>(start_x, start_y, type, sz_w, sz_h);
			icon_hoz->initialize();
			gamemanager_->icon.push_back(icon_hoz);
		}
		//backgraund�̔w�i�`�F���W(title����play��)
		std::shared_ptr<BackGraund> backgraund[2];
		backgraund[0] = gamemanager_->GetBackGraund(0);
		backgraund[1] = gamemanager_->GetBackGraund(1);
		backgraund[0]->sceneback_ = static_cast<int>(BackGraund::SCENEBACK::PLAYBACK);
		backgraund[1]->sceneback_ = static_cast<int>(BackGraund::SCENEBACK::PLAYBACK);
		gamemanager_->b_player_move_start = true;

		PlaySoundMem(gamemanager_->snd_play, DX_PLAYTYPE_LOOP, true);
		b_init = true;
	}

	if (gamemanager_->b_camera_stop) {
		//boss�ɓ��B������camera��stop
		gamemanager_->camera_.pos_ += tnl::Vector3(gamemanager_->camera_speed_, 0, 0);
	}
	else {
		StopSoundMem(gamemanager_->snd_play);
		if (!b_snd_boss) {
			PlaySoundMem(gamemanager_->snd_boss, DX_PLAYTYPE_LOOP, true);
			ChangeVolumeSoundMem(255 * 80 / 100, gamemanager_->snd_boss);
			b_snd_boss = true;
		}
	}
	//�����蔻��
	gamemanager_->IntersectPlayer();
	gamemanager_->IntersectBullet();
	//icon�̈ړ�
	gamemanager_->IconProcessChange();

	if (!gamemanager_->player_->is_alive_) {
		gamemanager_->PlayerDeadMove(deltatime);
		b_change = false;
		sequence_.change(&PlayScene::SeqRestartInterbal);
		if (!gamemanager_->b_camera_stop)gamemanager_->p_hp_ = 0;
	}

	gamemanager_->ObjectEraceCheck();

	return true;
}

bool PlayScene::SeqRestartInterbal(const float deltatime) {
	//���X�^�[�g����Ƃ��ɉ�ʂ��ꎞ�I�ɈÂ������邭���āA�������W����ĊJ
	if (!b_change) {
		if (arufa_ >= 0) arufa_ -= 2;
		else {
			b_change = true;
			b_reinit = true;
		}
	}
	else {
		std::shared_ptr<Player> player_ = gamemanager_->GetPlayer();
		if (arufa_ < 255) {
			arufa_ += 2;
			player_->pos_.x += 1;
			player_->pos_.y += 1;
		}
		else sequence_.change(&PlayScene::SeqPlayMain);
	}

	if (b_reinit) {//restart�̏�����
		gamemanager_->InitPlay();
		b_reinit = false;
	}

	gamemanager_->ObjectEraceCheck();//object��is_alive��false�ɂȂ�����erace������(option)	
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, arufa_);
	return true;
}

bool PlayScene::SeqBossBattle(const float deltatime) {

	gamemanager_->IntersectPlayer();
	gamemanager_->IntersectBullet();

	gamemanager_->IconProcessChange();
	//bossbattle�ł͈�x���񂾂�I���
	if (!gamemanager_->player_->is_alive_) gamemanager_->p_hp_ = 0;

	gamemanager_->ObjectEraceCheck();
	return true;
}

void PlayScene::SceneUpdate(float deltatime) {
	sequence_.update(deltatime);
	//hp��0�Ȃ�����gameover
	if(!gamemanager_->player_->is_alive_ && gamemanager_->p_hp_ < 0) SceneManager::ChangeScene(SceneManager::GAMEOVER);
	//clear
	if (gamemanager_->b_clear_change) {
		time_count_ += 0.1f;
		if(time_count_ > SCENE_CANGE_INTERVAL)SceneManager::ChangeScene(SceneManager::CLEAR);
	}
}

void PlayScene::SceneDraw() {
	DrawRotaGraph(55, 735, 0.1f, 0, img_player_hp_, true);
	DrawStringEx(100,730,-1,"�~%d",gamemanager_->p_hp_);
	DrawStringEx(200, 730, -1, "%d", gamemanager_->scorkeep_);
	DrawStringEx(180, 700, -1, "SCORE", gamemanager_->scorkeep_);
}

