#pragma once
#include"../gamesystem/Object.h"
#include"Skill.h"

class SkillManager : public Object {
public:
	SkillManager();
	std::list<std::shared_ptr<Skill>> skills;

	//Skillê∂ê¨ÅB1:Bom,2:Barria,3:Option
	void CreateSkill(const tnl::Vector3 start_pos,const int type);
private:
	void Update(float deltatime)override;
};