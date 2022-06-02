#pragma once
#include"Object.h"

class BackGraund : public Object {
public:
	BackGraund(tnl::Vector3 start_pos);

	enum class SCENEBACK {
		TITLEBACK,
		PLAYBACK,
	};
	int sceneback_ = static_cast<int>(SCENEBACK::TITLEBACK);

	bool startinterval = false;//チカチカさせるためのflag

private:
	//画像ハンドル
	int play_back_img_ = 0;

	//Updateで動かしたい
	float x1 = 0;
	float x2 = 0;
	float y1 = 0;
	float y2 = 0;
	
	//enter押した後startをチカチカさせたい
	float count = 0;

	void Update(float deltatime) override;
	void Render(Camera* camera) override;
};
