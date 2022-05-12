#include"SkillManager.h"
#include"../gamesystem/GameManager.h"

SkillManager::SkillManager() {
	
}

void SkillManager::CreateSkill(const tnl::Vector3 start_pos, const int type) {
	std::shared_ptr<Skill> skill_ = std::make_shared<Skill>(start_pos,type);
	skills.emplace_back(skill_);
	skill_->initialize();
}

void SkillManager::Update(float deltatime) {
	{
		auto it = skills.begin();
		while (it != skills.end()) {
			if (!(*it)->is_alive_) {
				it = skills.erase(it);
				continue;
			}
			it++;
		}
	}
}