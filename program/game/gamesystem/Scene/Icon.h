#pragma once
#include"../Object.h"

class Icon : public Object {
public:

	enum class IconType {
		SPEED_UP,
		LASER,
		SHOTGUN,
		AROUND,
		BOM,
		BARRIER,
		OPTION,
		HP,
	};

	Icon(const int start_x,const int start_y,const int type, const int sz_w, const int sz_h);

	void IconChoice();
	int red = 255;
	int blue = 255;
	int green = 255;
	bool b_barrier_alive = false;
	bool b_option_alive = false;

private:
	int img = 0;
	int type_ = 0;

	void Render(Camera* camera) override;
};

