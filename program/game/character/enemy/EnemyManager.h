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

	//csv読み込み用
	std::vector<std::vector<std::string>> loadEnemy;

	//敵の種類、出現座標(x,y),生成数,行動タイプ,スピード,HP
	void CreateEnemy(int type, int pos_x, int pos_y, int size_w, int size_h, int cre_num, int action_type, float speed, int hp, int scor);
	void CreateChildEnemy(const int pos, const int pos_y,int cre_type);

	//画面内に入ったら描画する関数
	void OnDisplyRender();
	//敵、敵の弾が画面の外に出たら消す
	void ScreenOut();
	//is_alive_がfalseになったらlistから削除
	void EnemyErase();
	//enemyのbullet生成関数(start_posとmove_dirでplayerの方向へ出す)
	void CreateEnemyBullet(tnl::Vector3 start_pos, tnl::Vector3 dir);

	void Update(float deltatime) override;
	void Render(Camera* camera) override;
};
