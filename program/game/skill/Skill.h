#pragma once
#include"../gamesystem/Object.h"

class Skill : public Object {
public:
	Skill(const tnl::Vector3 start_pos,const int type);
	//��ʓ��ɂ���G�I�u�W�F�N�g������
	void OnDisplayDead();

	int hp_ = 4;
	int radius = 15;
	double hoz_x[40];
	double hoz_y[40];
	int type_ = 0;

	bool b_option_create = false;

	enum class SkillType {
		BOM,
		BARRIER,
		OPTION
	};

private:

	tnl::Vector3 hoz_distancemoved_;

	float bom_speed_ = 6;
	int img_bom[3];
	int img_explosion[16];

	int img_option[2];
	const int OPTION_POS = 15;//(��)

	int img_barrier = 0;
	int img_barrier2 = 0;

	//�A�j���[�V����
	int anime_flame_ = 0;;
	int time_count_ = 0;

	//-------------------����-------------------------------
	//�֐��|�C���^(fanction�Ń��b�v)�����̓N���X��
	std::function<void(Skill*,float deltatime)> move;
	//�{���̓���
	void Bommove(float deltatime);
	//�o���A�̓���
	void Barriermove(float deltatime);
	//�I�v�V�����̓���(��납����Ă���)
	void Optionmove(float deltatime);
	//�I�v�V�������o���e�̏���
	void OptionBulletShot();

	//------------------�`��-------------------------------
	std::function<void(Skill*, Camera* camera)> draw;
	void Bomdraw(Camera* camera);
	void Barrierdraw(Camera* camera);
	void Optiondraw(Camera* camera);

	void Update(float deltatime) override;
	void Render(Camera* camera) override;

};