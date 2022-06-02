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
	//画面サイズ（固定）
	static constexpr int SCREEN_W = 1024;
	static constexpr int SCREEN_H = 768;
	static constexpr int SCREEN_W_HALF = SCREEN_W >> 1;
	static constexpr int SCREEN_H_HALF = SCREEN_H >> 1;
	static constexpr int SCREEN_FIRST = 0;

	//テンプレート。shared_ptrでのemplace_back//引数なしのコンストラクタ用
	template <class C >
	static std::shared_ptr<C> create() {
		std::shared_ptr<C>ptr = std::make_shared<C>();
		ptr->initialize(); //Objectのinitializeが呼ばれる。
		return ptr;
	}

	GameManager();
	//サウンド
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
	//bullet
	enum class BULLETTYPE {
		NORMAL,//ノーマル
		LASER,//レーザー
		SHOTGUN,//ショットガン
		AROUND,//衛星弾
	};
	int bullet_type_ = static_cast<int>(BULLETTYPE::NORMAL);

	//------------------------------------------------------------------
	//skill
	enum class SkillType {
		BOM,
		BARRIER,
		OPTION
	};

	//-----------------------------------------------------------------
	//icon
	enum class IconType {
		SPEED,
		LASER,
		SHOTGUN,
		AROUND,
		BOM,
		BARRIER,
		OPTION
	};

	const float camera_speed_ = 1.5f;//スクロール速度
	Camera camera_;

	int p_hp_ = 3;//プレイヤーのHP//playerはdeleteされるのでここに書く()
	tnl::Vector3 pl_start_pos_ = { 0,300,0 };
	std::shared_ptr<Player> player_ = nullptr;
	inline std::shared_ptr<Player> GetPlayer(){
		return player_;
	}
	void InitPlay();

	int Item_count_ = -1;
	const int ICON_MAX_NUM = 6;
	int Item_hoz = 0;

	std::vector<std::shared_ptr<Icon>> icon;
	std::vector<std::vector<std::string>> loadIcon;

	std::shared_ptr<EnemyManager> enemymanager_ = nullptr;
	inline std::shared_ptr<EnemyManager> GetEnemyManager(){
		return enemymanager_;
	}

	tnl::Vector3 bk_start_pos1 = { SCREEN_W_HALF ,(SCREEN_H_HALF - 70),0 };//背景の初期座用
	tnl::Vector3 bk_start_pos2 = { (SCREEN_W + SCREEN_W_HALF), (SCREEN_H_HALF - 70), 0 };
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
	//スコア保存
	int scorkeep_ = 0;

	//---------------------------------------------------------------------
	bool b_player_move_start = false;//タイトル画面でplayerが動かないように
	bool b_camera_stop = true;//bossが出てきたときにカメラが止まるように
	bool b_boss_dead = false;
	bool b_clear_change = false;
	//---------------------------------------------------------------------
	//一回画像をロードしたら使いまわしができる関数

	std::unordered_map<std::string, int> img_pas;
	int Loadimag(std::string img_handle);

	//--------------------------------------------------------------------------------
	//当たり判定
	//敵とplayer、敵の弾とplayer
	void IntersectPlayer();
	//敵とplayerの弾
	void IntersectBullet();
	//skillと敵の当たり判定
	void IntersectSkill(int type,Skill* call_parent);

	//---------------------------------------------------------------------------------
	//ゲーム開始時に行う初期化関数
	void Initialize();
	//playerが死んだとき画面内のオブジェクトを消す
	void PlayerDeadMove(float deltatime);
	//listのerace処理
	void ObjectEraceCheck();
	//restartする際の初期化
	void ObjectInit();
	//スキルアイコンの赤い表示の変化
	void IconProcessChange();
	void Update(float delta_time);
	void Render(float delta_time);
};
