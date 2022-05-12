#pragma once
#include"Camera.h"
#include"../character/player/Player.h"
#include"../character/enemy/EnemyManager.h"
#include"../Bullet/playerbullet/BulletManager.h"
#include"../skill/SkillManager.h"
#include"BackGraund.h"
#include <time.h>
#include <list>
#include <map>
#include <algorithm>
#include<memory>
#include "../../dxlib_ext/dxlib_ext.h"
#include<math.h>
#include<numbers>

class GameManager {
public:
	//��ʃT�C�Y�i�Œ�j
	static constexpr int SCREEN_W = 1024;
	static constexpr int SCREEN_H = 768;

	//�e���v���[�g�Bshared_ptr�ł�emplace_back//�����Ȃ��̃R���X�g���N�^�p
	template <class C >
	static std::shared_ptr<C> create() {
		std::shared_ptr<C>ptr = std::make_shared<C>();
		ptr->initialize(); //Object��initialize���Ă΂��B
		return ptr;
	}

	GameManager();
	//�T�E���h
	int snd_normal_bullet = 0;
	int snd_laser = 0;
	int snd_around = 0;
	int snd_bom = 0;
	int snd_barrier = 0;
	int snd_gameover = 0;
	int snd_damage = 0;
	int snd_cursor = 0;
	int snd_play = 0;
	int snd_equip = 0;
	int snd_my_down = 0;
	int snd_coin = 0;
	int snd_start = 0;
	int snd_healing = 0;
	int snd_boss = 0;
	//~GameManager();

	//-------------------------------------------------------------------
	//�e�̎��()
	enum BULLET_TYPE {
		NORMAL,//�m�[�}��
		LASER,//���[�U�[
		SHOTGUN,//�V���b�g�K��
		AROUND,//�q���e
	};
	BULLET_TYPE bullet_type = NORMAL;

	//------------------------------------------------------------------

	const float camera_speed_ = 1.5f;//�X�N���[�����x
	Camera camera_;

	int p_hp_ = 3;//�v���C���[��HP//player��delete�����̂ł����ɏ���()
	tnl::Vector3 pl_start_pos = { 0,300,0 };
	std::shared_ptr<Player> player_ = nullptr;
	inline std::shared_ptr<Player> GetPlayer(){
		return player_;
	}
	void InitPlay();

	int Item_count_ = -1;
	int Item_hoz = 0;

	std::vector<std::shared_ptr<Icon>> icon;
	std::vector<std::vector<std::string>> loadIcon;

	std::shared_ptr<EnemyManager> enemymanager_ = nullptr;
	inline std::shared_ptr<EnemyManager> GetEnemyManager(){
		return enemymanager_;
	}

	tnl::Vector3 bk_start_pos1 = { SCREEN_W >> 1,((SCREEN_H >> 1) - 70),0 };
	tnl::Vector3 bk_start_pos2 = { 1536, ((SCREEN_H >> 1) - 70), 0 };
	std::shared_ptr<BackGraund> backgraund_[2] = { nullptr,nullptr };
	inline std::shared_ptr<BackGraund> GetBackGraund(int type){
		if (type == 0) {
			return backgraund_[0];
		}
		else if (type == 1)return backgraund_[1];
	}

	std::list<std::shared_ptr<Object>> objects_;

	std::shared_ptr<BulletManager> bulletmanager_ = nullptr;
	inline std::shared_ptr<BulletManager> GetBulletManager() {
		return bulletmanager_;
	}

	std::shared_ptr<SkillManager> skillmanager_ = nullptr;
	inline std::shared_ptr<SkillManager> GetSkillManager() {
		return skillmanager_;
	}

	//----------------------------------------------------------------------
	//�X�R�A�ۑ�
	int scorkeep_ = 0;

	//---------------------------------------------------------------------
	bool b_start_player = false;
	bool b_camera_stop = true;
	bool b_boss_dead = false;

	//---------------------------------------------------------------------
	//���摜�����[�h������g���܂킵���ł���֐�

	std::unordered_map<std::string, int> img_pas;
	int Loadimag(std::string img_handle);

	//--------------------------------------------------------------------------------
	//�����蔻��
	//�G��player�A�G�̒e��player
	void IntersectPlayer();
	//�G��player�̒e
	void IntersectBullet();
	//skill�ƓG�̓����蔻��
	void IntersectSkill(int type);

	//---------------------------------------------------------------------------------
	//�Q�[���J�n���ɍs��init�֐�
	void Initialize();
	//player�����񂾂Ƃ���ʓ��̃I�u�W�F�N�g������
	void PlayerDeadMove(float deltatime);
	//list��erace����
	void ObjectEraceCheck();
	//restart����ۂ̏�����
	void ObjectInit();
	//�X�L���A�C�R���̐Ԃ��\���̕ω�
	void IconProcessChange();
	void Update(float delta_time);
	void Render(float delta_time);
};
