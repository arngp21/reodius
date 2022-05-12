#pragma once
#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#include <tuple>
#include <stdint.h>

namespace tnl {
#define TNL_KEY_MAX 256

	class Input {
	private :
		Input(){}

		static HWND hwnd_;
		static LPDIRECTINPUT8 input_;
		static LPDIRECTINPUTDEVICE8 key_;
		static LPDIRECTINPUTDEVICE8 mouse_;
		static DIMOUSESTATE2 ms_;
		static DIMOUSESTATE2 old_ms_;
		static BYTE keys_[TNL_KEY_MAX];

	public :

		#define TNL_MOUSE_INPUT_LEFT	(0x01)
		#define TNL_MOUSE_INPUT_RIGHT	(0x02)
		#define TNL_MOUSE_INPUT_MIDDLE	(0x04)
		#define TNL_MOUSE_OUTPUT_LEFT	(0x08)
		#define TNL_MOUSE_OUTPUT_RIGHT	(0x10)
		#define TNL_MOUSE_OUTPUT_MIDDLE	(0x20)

		// マウス対応キー 一覧
		enum class eMouse {
			LEFT,
			RIGHT,
			CENTER,
		};
		enum class eMouseTrigger {
			IN_LEFT		= TNL_MOUSE_INPUT_LEFT,
			IN_RIGHT	= TNL_MOUSE_INPUT_RIGHT,
			IN_MIDDLE	= TNL_MOUSE_INPUT_MIDDLE,
			OUT_LEFT	= TNL_MOUSE_OUTPUT_LEFT,
			OUT_RIGHT	= TNL_MOUSE_OUTPUT_RIGHT,
			OUT_MIDDLE	= TNL_MOUSE_OUTPUT_MIDDLE
		};

		// キーボード対応キー 一覧
		enum class eKeys {
			KB_BACK		// バックスペース
			, KB_TAB		// タブ
			, KB_RETURN	// エンター
			, KB_LSHIFT	// 左シフト
			, KB_RSHIFT	// 右シフト
			, KB_LCONTROL	// 左コントロール
			, KB_RCONTROL	// 右コントロール
			, KB_ESCAPE	// エスケープ
			, KB_SPACE	    // スペース
			, KB_PGUP		// ＰａｇｅＵＰ
			, KB_PGDN		// ＰａｇｅＤｏｗｎ
			, KB_END		// エンド
			, KB_HOME		// ホーム
			, KB_LEFT		// 左
			, KB_UP		// 上
			, KB_RIGHT	    // 右
			, KB_DOWN		// 下
			, KB_INSERT	// インサート
			, KB_DELETE	// デリート

			, KB_MINUS		    // －
			, KB_YEN			// ￥
			, KB_PREVTRACK	    // ＾
			, KB_PERIOD		// ．
			, KB_SLASH		    // ／
			, KB_LALT			// 左ＡＬＴ
			, KB_RALT			// 右ＡＬＴ
			, KB_SCROLL		// ScrollLock
			, KB_SEMICOLON	    // ；
			, KB_COLON		    // ：
			, KB_LBRACKET		// ［
			, KB_RBRACKET		// ］
			, KB_AT			// ＠
			, KB_BACKSLASH	    // ＼
			, KB_COMMA		    // ，
			, KB_CAPSLOCK		// CaspLock
			, KB_PAUSE		    // PauseBreak

			, KB_NUMPAD0	// テンキー０
			, KB_NUMPAD1	// テンキー１
			, KB_NUMPAD2	// テンキー２
			, KB_NUMPAD3	// テンキー３
			, KB_NUMPAD4	// テンキー４
			, KB_NUMPAD5	// テンキー５
			, KB_NUMPAD6	// テンキー６
			, KB_NUMPAD7	// テンキー７
			, KB_NUMPAD8	// テンキー８
			, KB_NUMPAD9	// テンキー９
			, KB_MULTIPLY	// テンキー＊
			, KB_ADD		// テンキー＋
			, KB_SUBTRACT	// テンキー－
			, KB_DECIMAL	// テンキー．
			, KB_DIVIDE	// テンキー／
			, KB_NUMPADENTER	// テンキーのエンター

			, KB_F1	// Ｆ１
			, KB_F2	// Ｆ２
			, KB_F3	// Ｆ３
			, KB_F4	// Ｆ４
			, KB_F5	// Ｆ５
			, KB_F6	// Ｆ６
			, KB_F7	// Ｆ７
			, KB_F8	// Ｆ８
			, KB_F9	// Ｆ９
			, KB_F10	// Ｆ１０
			, KB_F11	// Ｆ１１
			, KB_F12	// Ｆ１２

			, KB_A	// Ａ
			, KB_B	// Ｂ
			, KB_C	// Ｃ
			, KB_D	// Ｄ
			, KB_E	// Ｅ
			, KB_F	// Ｆ
			, KB_G	// Ｇ
			, KB_H	// Ｈ
			, KB_I	// Ｉ
			, KB_J	// Ｊ
			, KB_K	// Ｋ
			, KB_L	// Ｌ
			, KB_M	// Ｍ
			, KB_N	// Ｎ
			, KB_O	// Ｏ
			, KB_P	// Ｐ
			, KB_Q	// Ｑ
			, KB_R	// Ｒ
			, KB_S	// Ｓ
			, KB_T	// Ｔ
			, KB_U	// Ｕ
			, KB_V	// Ｖ
			, KB_W	// Ｗ
			, KB_X	// Ｘ
			, KB_Y	// Ｙ
			, KB_Z	// Ｚ
			, KB_0	// ０
			, KB_1	// １
			, KB_2	// ２
			, KB_3	// ３
			, KB_4	// ４
			, KB_5	// ５
			, KB_6	// ６
			, KB_7	// ７
			, KB_8	// ８
			, KB_9	// ９
			, KB_MAX
		};

		// 初期化
		static void Initialize(HWND hwnd);
		// 更新
		static void Update();
		// 解放
		static void Release();

		// arg... tnl::Input::KB_***
		static bool IsKeyDown(eKeys key);
		static bool IsKeyDownTrigger(eKeys key);
		static bool IsKeyReleaseTrigger(eKeys key);

		// arg... tnl::Input::eMouse::LEFT
		// arg... tnl::Input::eMouse::RIGHT
		// arg... tnl::Input::eMouse::CENTER
		static bool IsMouseDown(eMouse _mouse);

		// arg... tnl::Input::eMouseTrigger::ON_LEFT
		// arg... tnl::Input::eMouseTrigger::OUT_RIGHT
		static bool IsMouseTrigger(eMouseTrigger _mouse);

		// マウス座標の取得
		static POINT GetMousePosition();
		// マウスホイールの変化量を取得
		static int32_t GetMouseWheel();

	};

}

using eKeys = tnl::Input::eKeys;
using eMouse = tnl::Input::eMouse;
using eMouseTrigger = tnl::Input::eMouseTrigger;

