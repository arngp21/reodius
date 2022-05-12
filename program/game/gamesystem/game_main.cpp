#include <time.h>
#include <list>
#include <map>
#include <algorithm>
#include"GameManager.h"
#include "game_main.h"
#include "../../dxlib_ext/dxlib_ext.h"
#include"Scene/SceneManager.h"

bool init = false;
GameManager* gamemanager_ = nullptr;

void gameMain(float delta_time) {

	if (!init) {
		srand(time(0));
		gamemanager_ = new GameManager();
		SceneManager::ChangeScene(SceneManager::TITLE);
		init = true;
	}

	gamemanager_->Update(delta_time);
	gamemanager_->Render(delta_time);

}

