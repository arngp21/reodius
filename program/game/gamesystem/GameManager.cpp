#include "GameManager.h"
#include"Scene/SceneManager.h"
#include "Object.h"

GameManager::GameManager() {
	snd_normal_bullet = LoadSoundMem("sound/normalbullet.mp3");//
	snd_laser = LoadSoundMem("sound/laser3.mp3");//
	snd_around = LoadSoundMem("sound/around.mp3");//
	snd_bom = LoadSoundMem("sound/bom.mp3");//
	snd_barrier = LoadSoundMem("sound/barrier.mp3");//
	snd_gameover = LoadSoundMem("sound/gameover.mp3");//
	snd_cursor = LoadSoundMem("sound/cursor.mp3");//
	snd_play = LoadSoundMem("sound/GB-RPG-B12-2(Battle1-Loop145).mp3");//
	snd_equip = LoadSoundMem("sound/equip.mp3");//
	snd_my_down = LoadSoundMem("sound/my_damage.mp3");//
	snd_coin = LoadSoundMem("sound/coin.mp3");
	snd_start = LoadSoundMem("sound/battle_start.mp3");
	snd_healing = LoadSoundMem("sound/healing.mp3");//
	snd_damage = LoadSoundMem("sound/damage3.mp3");//
	snd_boss = LoadSoundMem("sound/iwashiro_yoruyake.mp3");
}

void GameManager::Initialize()
{
	camera_.pos_ += tnl::Vector3(GameManager::SCREEN_W >> 1, GameManager::SCREEN_H >> 1, 0);

	backgraund_[0] = std::make_shared<BackGraund>(bk_start_pos1);
	backgraund_[0]->initialize();
	backgraund_[1] = std::make_shared<BackGraund>(bk_start_pos2);
	backgraund_[1]->initialize();

	bulletmanager_ = create<BulletManager>();

	player_ = std::make_shared<Player>(pl_start_pos_);
	player_->initialize();

	enemymanager_ = create<EnemyManager>();
	skillmanager_ = create<SkillManager>();
}

void GameManager::InitPlay() {
	player_ = std::make_shared<Player>(tnl::Vector3((camera_.pos_.x - SCREEN_W_HALF) - 120, SCREEN_FIRST - 10, 0));
	player_->initialize();
	Item_count_ = -1;
}

//--------------------------------------------------------------------------------

int GameManager::Loadimag(std::string img_handle) {
	int hoz_img;
	auto it = img_pas.find(img_handle);
	if (it == img_pas.end()) {
		hoz_img = LoadGraph(img_handle.c_str());
		img_pas.insert(std::make_pair(img_handle, hoz_img));
	}
	else {
		hoz_img = it->second;
	}

	return hoz_img;
}


//-------------------------collision-----------------------------------------------------
void GameManager::IntersectPlayer() {
	for (auto enemy : enemymanager_->enemys_) {
		if (tnl::IsIntersectRect(
			player_->pos_,
			player_->size_w,
			player_->size_h,
			enemy->pos_,
			enemy->size_w,
			enemy->size_h)) {
			if ((snd_my_down != 0) && (!CheckSoundMem(snd_my_down))) {
				PlaySoundMem(snd_my_down, DX_PLAYTYPE_BACK, true);
			}
			player_->is_alive_ = false;
		}
	}

	for (auto enemy_bullet : enemymanager_->enemy_bullets_) {
		if (tnl::IsIntersectRect(
			player_->pos_,
			player_->size_w,
			player_->size_h,
			enemy_bullet->pos_,
			enemy_bullet->radius_,
			enemy_bullet->radius_)) {
			if ((snd_my_down != 0) && (!CheckSoundMem(snd_my_down))) {
				PlaySoundMem(snd_my_down, DX_PLAYTYPE_BACK, true);
			}
			enemy_bullet->is_alive_ = false;
			player_->is_alive_ = false;
		}
	}

	for (auto enemy_drop : enemymanager_->enemy_drops_) {
		if (tnl::IsIntersectRect(
			player_->pos_,
			player_->size_w,
			player_->size_h,
			enemy_drop->pos_,
			enemy_drop->radius_,
			enemy_drop->radius_)) {
			PlaySoundMem(snd_coin, DX_PLAYTYPE_BACK, true);
			enemy_drop->is_alive_ = false;
			Item_count_++;
		}
	}
}

void GameManager::IntersectBullet() {
	auto bullet = bulletmanager_->bullets_.begin();

	while (bullet != bulletmanager_->bullets_.end()) {

		auto enemy = enemymanager_->enemys_.begin();
		bool is_continue = false;

		while (enemy != enemymanager_->enemys_.end()) {
			// “G‚Æ’e‚ª“–‚½‚Á‚½‚Æ‚«
			if (tnl::IsIntersectRect(
				(*enemy)->pos_,
				(*enemy)->size_w,
				(*enemy)->size_h,
				(*bullet)->pos_,
				(*bullet)->size_w,
				(*bullet)->size_h)) {

				if (bullet_type_ == static_cast<int>(BULLETTYPE::LASER)) {
					bool is_hit = false;
					for (auto id : (*enemy)->ID_) {
						if (id == (*bullet)->bullet_ID_) {// “G‚ªŽ‚Á‚Ä‚¢‚éu‚·‚Å‚É“–‚½‚Á‚½’e‚ÌIDƒŠƒXƒgv‚ð‚Ý‚ÄA¡“–‚½‚Á‚½’e‚Æ“¯‚¶ID‚ª‚ ‚Á‚½‚çcontinue‚·‚é
							is_hit = true;//‚±‚±‚Écontinue‚¾‚Æfor•¶‚ªcontinue‚³‚ê‚é
							break;
						}
					}
					if (is_hit) {
						++enemy;
						continue;
					}
					else {
						(*enemy)->hp_--;
						(*enemy)->ID_.emplace_back((*bullet)->bullet_ID_);// “G‚ªŽ‚Á‚Ä‚¢‚éu‚·‚Å‚É“–‚½‚Á‚½’e‚ÌIDƒŠƒXƒgv‚É“–‚½‚Á‚½’e‚ÌID‚ð“o˜^‚·‚é
					}
				}
				else {
					(*enemy)->hp_--;
					(*bullet)->is_alive_ = false;
				}

				if ((*enemy)->hp_ == 0) {
					if ((*enemy)->type_ == static_cast<int>(EnemyMoveType::BOSS)) b_boss_dead = true;
					else {
						(*enemy)->is_alive_ = false;
						enemy = enemymanager_->enemys_.erase(enemy);
					}
				}

				if (bullet_type_ != static_cast<int>(BULLETTYPE::LASER) && bullet != bulletmanager_->bullets_.end()) {
					bullet = bulletmanager_->bullets_.erase(bullet);
					return;
				}
				is_continue = true;
				continue;
			}
			++enemy;
		}
		if (is_continue) continue;
		++bullet;
	}
}

void GameManager::IntersectSkill(int type, Skill* call_parent) {
	if (type == static_cast<int>(SkillType::BOM)) {
		for (auto enemy : enemymanager_->enemys_) {
			if (tnl::IsIntersectRect(
				call_parent->pos_,
				call_parent->radius_,
				call_parent->radius_,
				enemy->pos_,
				enemy->size_w,
				enemy->size_h)) {
				PlaySoundMem(snd_bom, DX_PLAYTYPE_BACK, true);
				call_parent->OnDisplayDead();
				call_parent->b_render = true;
			}
		}
	}
	else if (type == static_cast<int>(SkillType::BARRIER)) {
		for (auto enemy : enemymanager_->enemys_) {
			if (tnl::IsIntersectRect(
				call_parent->pos_,
				call_parent->size_w,
				call_parent->size_h,
				enemy->pos_,
				enemy->size_w,
				enemy->size_h)) {
				PlaySoundMem(snd_barrier, DX_PLAYTYPE_BACK, true);
				call_parent->hp_--;
				enemy->is_alive_ = false;
			}
		}

		for (auto enemy_bullet : enemymanager_->enemy_bullets_) {

			if (tnl::IsIntersectRect(
				call_parent->pos_,
				call_parent->size_w,
				call_parent->size_h,
				enemy_bullet->pos_,
				enemy_bullet->radius_,
				enemy_bullet->radius_)) {
				PlaySoundMem(snd_barrier, DX_PLAYTYPE_BACK, true);
				call_parent->hp_--;
				enemy_bullet->is_alive_ = false;
			}
		}
	}
}

//-------------------------erace---------------------------------------------------------

void GameManager::ObjectEraceCheck() {

	{
		auto it = objects_.begin();
		while (it != objects_.end()) {
			if (!(*it)->is_alive_) {
				it = objects_.erase(it);
				continue;
			}
			it++;
		}
	}
}

//--------------------------------------------------------------------------------

void GameManager::PlayerDeadMove(float deltatime) {
	for (auto enemy : enemymanager_->enemys_) {
		if ((camera_.pos_.x - (SCREEN_W_HALF) < enemy->pos_.x) &&
			(camera_.pos_.x + (SCREEN_W_HALF) > enemy->pos_.x)) {
			enemy->deadtype_ = static_cast<int>(DeadType::PLAYER_DEATH);
			enemy->is_alive_ = false;
		}
	}

	for (auto enemy_bullet : enemymanager_->enemy_bullets_) {
		if ((camera_.pos_.x - (SCREEN_W_HALF) < enemy_bullet->pos_.x) &&
			(camera_.pos_.x + (SCREEN_W_HALF) > enemy_bullet->pos_.x)) {
			enemy_bullet->is_alive_ = false;
		}

	}

	for (auto bullet : bulletmanager_->bullets_) {
		if ((camera_.pos_.x - (SCREEN_W_HALF) < bullet->pos_.x) &&
			(camera_.pos_.x + (SCREEN_W_HALF) > bullet->pos_.x)) {
			bullet->is_alive_ = false;
		}
	}

	for (auto Item : enemymanager_->enemy_drops_) {
		if ((camera_.pos_.x - (SCREEN_W_HALF) < Item->pos_.x) &&
			(camera_.pos_.x + (SCREEN_W_HALF) > Item->pos_.x)) {
			Item->is_alive_ = false;
		}
	}

	bullet_type_ = static_cast<int>(BULLETTYPE::NORMAL);
	p_hp_--;
}

//-----------------------------------------------------------------------------------

void GameManager::IconProcessChange() {
	if (Item_count_ > ICON_MAX_NUM) {
		icon[ICON_MAX_NUM]->blue = 255;
		icon[ICON_MAX_NUM]->green = 255;
		Item_count_ = 0;
	}
	if (Item_count_ >= 0) {
		if (Item_hoz < Item_count_) {
			icon[Item_hoz]->blue = 255;
			icon[Item_hoz]->green = 255;
		}
		Item_hoz = Item_count_;
		icon[Item_count_]->blue = 0;
		icon[Item_count_]->green = 0;
	}
	else {
		icon[Item_hoz]->blue = 255;
		icon[Item_hoz]->green = 255;
	}
}

//------------------------------------------------------------------------------------

void GameManager::ObjectInit() {
	for (auto enemy : enemymanager_->enemys_) {
		enemy->deadtype_ = static_cast<int>(DeadType::PLAYER_DEATH);
	}
	objects_.clear();
	bulletmanager_->bullets_.clear();
	enemymanager_->enemys_.clear();
	icon.clear();
	Item_count_ = -1;
	Item_hoz = 0;
	scorkeep_ = 0;
	p_hp_ = 3;
	b_player_move_start = false;
	b_camera_stop = true;
	b_boss_dead = false;
	camera_.pos_ = { 0,0,0 };
	bullet_type_ = static_cast<int>(BULLETTYPE::NORMAL);
}

//------------------------Update-----Render---------------------------------------------

void GameManager::Update(float deltatime) {
	objects_.sort([](std::shared_ptr<Object> r, std::shared_ptr<Object> l) { return r->priority_ < l->priority_; });

	SceneManager::SceneManagerUpdate(deltatime);

	for (auto obj : objects_) {
		obj->Update(deltatime);
	}

}

void GameManager::Render(float deltatime) {
	SceneManager::SceneManagerRender();

	for (auto obj : objects_) {
		obj->Render(&camera_);
	}

}
