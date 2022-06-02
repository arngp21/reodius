#include"Icon.h"
#include"../GameManager.h"

extern GameManager* gamemanager_;

Icon::Icon(const int start_x, const int start_y, const int type, const int sz_w, const int sz_h) {
	pos_.x = start_x;
	pos_.y = start_y;
	type_ = type;
	//img = gamemanager_->Loadimag(imgname);
	size_w = sz_w;
	size_h = sz_h;
	img = gamemanager_->Loadimag("graphics/sentouki.png");
}

void Icon::IconChoice() {
	std::shared_ptr<Player> player_ = gamemanager_->GetPlayer();
	std::shared_ptr<SkillManager> skill_= gamemanager_->GetSkillManager();
	if (type_ == static_cast<int>(IconType::SPEED_UP)) {
		player_->speed_magnification_ += 0.5f;
		player_->back_speed_ += 0.05f;
		gamemanager_->Item_count_ = -1;
	}
	else if (type_ == static_cast<int>(IconType::LASER)) {
		if (gamemanager_->bullet_type_ != static_cast<int>(GameManager::BULLETTYPE::LASER)) {
			gamemanager_->bullet_type_ = static_cast<int>(GameManager::BULLETTYPE::LASER);
			gamemanager_->Item_count_ = -1;
		}
	}
	else if (type_ == static_cast<int>(IconType::SHOTGUN)) {
		if (gamemanager_->bullet_type_ != static_cast<int>(GameManager::BULLETTYPE::SHOTGUN)) {
			gamemanager_->bullet_type_ = static_cast<int>(GameManager::BULLETTYPE::SHOTGUN);
			gamemanager_->Item_count_ = -1;
		}
	}
	else if (type_ == static_cast<int>(IconType::AROUND)) {
		if (gamemanager_->bullet_type_ != static_cast<int>(GameManager::BULLETTYPE::AROUND)) {
			gamemanager_->bullet_type_ = static_cast<int>(GameManager::BULLETTYPE::AROUND);
			gamemanager_->Item_count_ = -1;
		}
	}
	else if (type_ == static_cast<int>(IconType::BOM)) {
		gamemanager_->skillmanager_->CreateSkill(player_->pos_, static_cast<int>(GameManager::SkillType::BOM));
		gamemanager_->Item_count_ = -1;
	}
	else if (type_ == static_cast<int>(IconType::BARRIER)) {
		if (!b_barrier_alive) {
			gamemanager_->skillmanager_->CreateSkill(player_->pos_, static_cast<int>(GameManager::SkillType::BARRIER));
			gamemanager_->Item_count_ = -1;
			b_barrier_alive = true;
		}
		/*for (auto skill : skill_->skills) {
			if(skill->type_ == static_cast<int>(skill->SkillType::BARRIER))
		}*/
	}
	else if (type_ == static_cast<int>(IconType::OPTION)) {
		if (!b_option_alive) {
			gamemanager_->skillmanager_->CreateSkill(player_->pos_, static_cast<int>(GameManager::SkillType::OPTION));
			gamemanager_->Item_count_ = -1;
			b_option_alive = true;
		}
	}
}

void Icon::Render(Camera* camera) {
	int x1 = pos_.x - (size_w >> 1);
	int y1 = pos_.y - (size_h >> 1);
	int x2 = pos_.x + (size_w >> 1);
	int y2 = pos_.y + (size_h >> 1);

	DrawBox(x1, y1, x2, y2, GetColor(red, blue, green), false);
	SetFontSize(20);

	if (type_ == static_cast<int>(IconType::SPEED_UP)) {
		DrawStringEx(pos_.x - 40, pos_.y - 10, -1, "SPEED_UP");
	}
	else if (type_ == static_cast<int>(IconType::LASER)) {
		if (gamemanager_->bullet_type_ != static_cast<int>(GameManager::BULLETTYPE::LASER))DrawStringEx(pos_.x - 25, pos_.y - 10, -1, "LASER");
	}
	else if (type_ == static_cast<int>(IconType::SHOTGUN)) {
		if (gamemanager_->bullet_type_ != static_cast<int>(GameManager::BULLETTYPE::SHOTGUN))DrawStringEx(pos_.x - 40, pos_.y-10, -1, "SHOTGUN");
	}
	else if (type_ == static_cast<int>(IconType::AROUND)) {
		if (gamemanager_->bullet_type_ != static_cast<int>(GameManager::BULLETTYPE::AROUND))DrawStringEx(pos_.x - 30, pos_.y-10, -1, "AROUND");
	}
	else if (type_ == static_cast<int>(IconType::BOM)) {
		DrawStringEx(pos_.x - 20, pos_.y-10, -1, "BOM");
	}
	else if (type_ == static_cast<int>(IconType::BARRIER)) {
		if (!b_barrier_alive) DrawStringEx(pos_.x - 35, pos_.y - 10, -1, "BARRIER");
	}
	else if (type_ == static_cast<int>(IconType::OPTION)) {
		if(!b_option_alive) DrawStringEx(pos_.x - 35, pos_.y - 10, -1, "OPTION");
	}
}