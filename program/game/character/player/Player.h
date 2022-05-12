#pragma once
#include"../../gamesystem/Object.h"
#include"../../gamesystem/Scene/Icon.h"

class Player : public Object {
public:
	Player(const tnl::Vector3 &strat_pos_);
	~Player();

	float speed_magnification_ = 1.5f;//speedに足していく変数
	float back_speed_ = 2;//後ろに戻るときにかけていく変数(speed_magnification_と一緒に値が増えるためconstではない)
	int hp_ = 0;//gamemanagerのconsthp代入

private:

	int item_ = 0;//playerがとったitem
	int player_img_ = 0;//画像ハンドル

	int create_count_ = 0;
	float time_count_ = 0;
	bool b_create_around = false;//衛星弾を4発ずつ出したいので、boolで管理

	float shot_interval = 0;

	void Update(float deltatime) override;
	void Render(Camera* camera) override;

	bool Move();//playerの動き(キー入力)boolにして値を返すことで押されてないときも感知できる
};
