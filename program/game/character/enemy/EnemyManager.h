#pragma once
#include<list>
#include<memory>
#include"../../gamesystem/Object.h"
#include"EnemyStatus.h"
#include"Enemy.h"
#include"../../Bullet/enemybullet/EnemyBullet.h"
#include"EnemyDrop.h"

class EnemyManager : public Object {
public:
	EnemyManager();
	//~EnemyManager();

	float create_count = 0;
	std::list<std::shared_ptr<Enemy>> enemys_;
	std::list<std::shared_ptr<EnemyBullet>> enemy_bullets_;
	std::list<std::shared_ptr<EnemyDrop>>enemy_drops_;

	//csv�ǂݍ��ݗp
	std::vector<std::vector<std::string>> loadEnemy;

	//�G�̎�ށA�o�����W(x,y),������,�s���^�C�v,�X�s�[�h,HP
	void CreateEnemy(int type, int pos_x, int pos_y, int size_w, int size_h, int cre_num, int action_type, float speed, int hp, int scor);
	void CreateChildEnemy(const int pos, const int pos_y,int cre_type);

	//��ʓ��ɓ�������`�悷��֐�
	void OnDisplyRender();
	//�G�A�G�̒e����ʂ̊O�ɏo�������
	void ScreenOut();
	//is_alive_��false�ɂȂ�����list����폜
	void EnemyErase();
	//enemy��bullet�����֐�(start_pos��move_dir��player�̕����֏o��)
	void CreateEnemyBullet(tnl::Vector3 start_pos, tnl::Vector3 dir);

	void Update(float deltatime) override;
	void Render(Camera* camera) override;
};
