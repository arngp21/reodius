#pragma once
#include<list>
#include<memory>
#include"../../gamesystem/Object.h"
#include"Bullet.h"
#include"BulletStatus.h"
#include"Bullet.h"

class BulletManager : public Object {
public:
	
	BulletManager();

	//bullet��statuslist�ɓo�^
	std::list<std::shared_ptr<BulletStatus>> bullets_;

	std::string imgname;
	std::vector<std::vector<std::string>> loadBullet;
	//bullet����
	void CreateBullet(const int type, const tnl::Vector3 start_pos, bulletmove desc, std::shared_ptr<Object> parent);
	//is_alive_��false�ɂȂ�����list����폜
	void BulletErase();

	void Update(float deltatime) override;
	void Render(Camera* camera) override;
};
