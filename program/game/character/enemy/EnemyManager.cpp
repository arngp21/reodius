#include"EnemyManager.h"
#include"../../gamesystem/GameManager.h"
#include"../../gamesystem/Scene/SceneManager.h"
#include"Enemy.h"

extern GameManager* gamemanager_;

EnemyManager::EnemyManager() {
	loadEnemy = tnl::LoadCsv("csv/LoadEnemy.csv");

	for (int i = 3; i < loadEnemy.size(); ++i) {

		//[0] = ID:[1] = type:[2] = 名前:[3] = pos.x:[4] = pos.y:[5] = size_w:[6] = size_h:[7] = 生成数:[8] = 行動タイプ:[9] = speed:[10] = hp
		//atoi int 型に変換//c_strはchar*型に変換	
		int id = std::atoi(loadEnemy[i][0].c_str());
		int type = std::stoi(loadEnemy[i][1].c_str());
		//int name = std::atoi(loadEnemy[i][2].c_str());
		int pos_x = std::atoi(loadEnemy[i][3].c_str());
		int pos_y = std::atoi(loadEnemy[i][4].c_str());
		int size_w = std::atoi(loadEnemy[i][5].c_str());
		int size_h = std::atoi(loadEnemy[i][6].c_str());
		int cre_num = std::atoi(loadEnemy[i][7].c_str());
		int action_type = std::atoi(loadEnemy[i][8].c_str());
		float sp = std::atof(loadEnemy[i][9].c_str());
		int hp = std::atoi(loadEnemy[i][10].c_str());
		int sc = std::atoi(loadEnemy[i][11].c_str());

		CreateEnemy(type, pos_x, pos_y, size_w, size_h, cre_num, action_type, sp, hp, sc);
	}
}

void EnemyManager::OnDisplyRender() {
	for (auto en_render : enemys_) {
		if (gamemanager_->camera_.pos_.x + (gamemanager_->SCREEN_W / 2) > en_render->pos_.x) {
			en_render->b_ondisplay = true;
			en_render->b_render = true;
		}
	}
}

void EnemyManager::ScreenOut() {
	for (auto enemy : enemys_) {
		if (enemy->pos_.x < (gamemanager_->camera_.pos_.x - (gamemanager_->SCREEN_W / 2))) {
			enemy->deadtype_ = ENEMY_SCREEN_OUT;
			enemy->is_alive_ = false;
		}
	}
}

void EnemyManager::CreateEnemyBullet(tnl::Vector3 start_pos, tnl::Vector3 dir) {
	std::shared_ptr<EnemyBullet> enemy_bullet_ = std::make_shared<EnemyBullet>(start_pos, dir);
	enemy_bullets_.emplace_back(enemy_bullet_);
	enemy_bullet_->initialize();
}

void EnemyManager::CreateEnemy(int type, int pos_x, int pos_y, int size_w, int size_h, int cre_num, int action_type, float speed, int hp,int scor) {
	if (type != 0 && type != 1) {
		pos_x += gamemanager_->camera_.pos_.x;
	}

	for (int i = 0; i < cre_num; i++) {
		std::shared_ptr<Enemy> enemy = std::make_shared<Enemy>(type, pos_x + (i * 100), pos_y, size_w, size_h, action_type, hp, speed, scor);
		enemys_.emplace_back(enemy);
		enemy->initialize();
	}
}

void EnemyManager::CreateChildEnemy(const int pos_x, const int pos_y,int cre_type ) {
	int id = std::atoi(loadEnemy[1+cre_type][0].c_str());
	int type = std::atoi(loadEnemy[1 + cre_type][1].c_str());
	//int name = std::atoi(loadEnemy[1][2].c_str());
	//int posx = std::atoi(loadEnemy[1][3].c_str());
	//int posy = std::atoi(loadEnemy[1][4].c_str());
	int size_w = std::atoi(loadEnemy[1 + cre_type][5].c_str());
	int size_h = std::atoi(loadEnemy[1 + cre_type][6].c_str());
	int cre_num = std::atoi(loadEnemy[1 + cre_type][7].c_str());
	int action_type = std::atoi(loadEnemy[1 + cre_type][8].c_str());
	float sp = std::atof(loadEnemy[1 + cre_type][9].c_str());
	int hp = std::atoi(loadEnemy[1 + cre_type][10].c_str());
	int sc = std::atoi(loadEnemy[1 + cre_type][11].c_str());

	CreateEnemy(type, pos_x, pos_y, size_w, size_h, cre_num, action_type, sp, hp, sc);
}

void EnemyManager::EnemyErase() {
	{
		auto it = enemys_.begin();
		while (it != enemys_.end()) {
			if (!(*it)->is_alive_) {
				it = enemys_.erase(it);
				continue;
			}
			it++;
		}
	}

	{
		auto it = enemy_bullets_.begin();
		while (it != enemy_bullets_.end()) {
			if (!(*it)->is_alive_) {
				it = enemy_bullets_.erase(it);
				continue;
			}
			it++;
		}
	}

	{
		auto it = enemy_drops_.begin();
		while (it != enemy_drops_.end()) {
			if (!(*it)->is_alive_) {
				it = enemy_drops_.erase(it);
				continue;
			}
			it++;
		}
	}
}

void EnemyManager::Update(float deltatime) {
	OnDisplyRender();
	ScreenOut();
	EnemyErase();
}

void EnemyManager::Render(Camera* camera) {
}