#include <assert.h>
#include "tnl_input.h"
#include "tnl_util.h"
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

namespace tnl {
	HWND Input::hwnd_;
	LPDIRECTINPUT8 Input::input_ = nullptr;
	LPDIRECTINPUTDEVICE8 Input::key_ = nullptr;
	LPDIRECTINPUTDEVICE8 Input::mouse_;
	DIMOUSESTATE2 Input::ms_;
	DIMOUSESTATE2 Input::old_ms_;

	BYTE Input::keys_[TNL_KEY_MAX];


	static int xor_mouse[33] = {
		1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,
		1,1,1
	};
	static int trg_mouse[33] = {
		0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,
		0,0,0
	};

	static unsigned char mouses[6] = {
		TNL_MOUSE_INPUT_LEFT
		,TNL_MOUSE_INPUT_RIGHT
		,TNL_MOUSE_INPUT_MIDDLE
		,TNL_MOUSE_OUTPUT_LEFT
		,TNL_MOUSE_OUTPUT_RIGHT
		,TNL_MOUSE_OUTPUT_MIDDLE
	};

	static int kb_xor_down[256] = { 0 };
	static int kb_trg_down[256] = { 0 };
	static int kb_xor_release[256] = { 0 };
	static int kb_trg_release[256] = { 0 };
	static unsigned char kb_keys[static_cast<uint32_t>(Input::eKeys::KB_MAX)] = {
		 DIK_BACK		// バックスペースキー
		,DIK_TAB		// タブキー
		,DIK_RETURN		// エンターキー
		,DIK_LSHIFT		// 左シフトキー
		,DIK_RSHIFT		// 右シフトキー
		,DIK_LCONTROL	// 左コントロールキー
		,DIK_RCONTROL	// 右コントロールキー
		,DIK_ESCAPE		// エスケープキー
		,DIK_SPACE		// スペースキー
		,DIK_PGUP		// ＰａｇｅＵＰキー
		,DIK_PGDN		// ＰａｇｅＤｏｗｎキー
		,DIK_END		// エンドキー
		,DIK_HOME		// ホームキー
		,DIK_LEFT		// 左キー
		,DIK_UP			// 上キー
		,DIK_RIGHT		// 右キー
		,DIK_DOWN		// 下キー
		,DIK_INSERT		// インサートキー
		,DIK_DELETE		// デリートキー

		,DIK_MINUS		// －キー
		,DIK_YEN		// ￥キー
		,DIK_PREVTRACK	// ＾キー
		,DIK_PERIOD		// ．キー
		,DIK_SLASH		// ／キー
		,DIK_LALT		// 左ＡＬＴキー
		,DIK_RALT		// 右ＡＬＴキー
		,DIK_SCROLL		// ScrollLockキー
		,DIK_SEMICOLON	// ；キー
		,DIK_COLON		// ：キー
		,DIK_LBRACKET	// ［キー
		,DIK_RBRACKET	// ］キー
		,DIK_AT			// ＠キー
		,DIK_BACKSLASH	// ＼キー
		,DIK_COMMA		// ，キー
		,DIK_CAPSLOCK	// CaspLockキー
		,DIK_PAUSE		// PauseBreakキー

		,DIK_NUMPAD0	// テンキー０
		,DIK_NUMPAD1	// テンキー１
		,DIK_NUMPAD2	// テンキー２
		,DIK_NUMPAD3	// テンキー３
		,DIK_NUMPAD4	// テンキー４
		,DIK_NUMPAD5	// テンキー５
		,DIK_NUMPAD6	// テンキー６
		,DIK_NUMPAD7	// テンキー７
		,DIK_NUMPAD8	// テンキー８
		,DIK_NUMPAD9	// テンキー９
		,DIK_MULTIPLY	// テンキー＊キー
		,DIK_ADD		// テンキー＋キー
		,DIK_SUBTRACT	// テンキー－キー
		,DIK_DECIMAL	// テンキー．キー
		,DIK_DIVIDE	// テンキー／キー
		,DIK_NUMPADENTER	// テンキーのエンターキー

		,DIK_F1	// Ｆ１キー
		,DIK_F2	// Ｆ２キー
		,DIK_F3	// Ｆ３キー
		,DIK_F4	// Ｆ４キー
		,DIK_F5	// Ｆ５キー
		,DIK_F6	// Ｆ６キー
		,DIK_F7	// Ｆ７キー
		,DIK_F8	// Ｆ８キー
		,DIK_F9	// Ｆ９キー
		,DIK_F10	// Ｆ１０キー
		,DIK_F11	// Ｆ１１キー
		,DIK_F12	// Ｆ１２キー

		,DIK_A	// Ａキー
		,DIK_B	// Ｂキー
		,DIK_C	// Ｃキー
		,DIK_D	// Ｄキー
		,DIK_E	// Ｅキー
		,DIK_F	// Ｆキー
		,DIK_G	// Ｇキー
		,DIK_H	// Ｈキー
		,DIK_I	// Ｉキー
		,DIK_J	// Ｊキー
		,DIK_K	// Ｋキー
		,DIK_L	// Ｌキー
		,DIK_M	// Ｍキー
		,DIK_N	// Ｎキー
		,DIK_O	// Ｏキー
		,DIK_P	// Ｐキー
		,DIK_Q	// Ｑキー
		,DIK_R	// Ｒキー
		,DIK_S	// Ｓキー
		,DIK_T	// Ｔキー
		,DIK_U	// Ｕキー
		,DIK_V	// Ｖキー
		,DIK_W	// Ｗキー
		,DIK_X	// Ｘキー
		,DIK_Y	// Ｙキー
		,DIK_Z	// Ｚキー
		,DIK_0	// ０キー
		,DIK_1	// １キー
		,DIK_2	// ２キー
		,DIK_3	// ３キー
		,DIK_4	// ４キー
		,DIK_5	// ５キー
		,DIK_6	// ６キー
		,DIK_7	// ７キー
		,DIK_8	// ８キー
		,DIK_9	// ９キー
	};


	void Input::Initialize( HWND hwnd ) {
		hwnd_ = hwnd;
		HRESULT hr = S_OK;
		memset(keys_, 0, sizeof(keys_));

		hr = DirectInput8Create(GetModuleHandle(0), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)(&input_), NULL);
		if (FAILED(hr)) { assert(false); }

		hr = input_->CreateDevice(GUID_SysKeyboard, &key_, NULL);
		if (FAILED(hr)) { assert(false); }

		hr = key_->SetDataFormat(&c_dfDIKeyboard);
		if (FAILED(hr)) { assert(false); }

		hr = key_->SetCooperativeLevel(hwnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);
		if (FAILED(hr)) { assert(false); }

		key_->Acquire();



		hr = input_->CreateDevice(GUID_SysMouse, &mouse_, NULL);
		if (FAILED(hr)) { assert(false); }

		hr = mouse_->SetDataFormat(&c_dfDIMouse2);
		if (FAILED(hr)) { assert(false); }

		hr = mouse_->SetCooperativeLevel(hwnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
		if (FAILED(hr)) { assert(false); }

		// デバイスの設定   
		DIPROPDWORD diprop;
		diprop.diph.dwSize = sizeof(diprop);
		diprop.diph.dwHeaderSize = sizeof(diprop.diph);
		diprop.diph.dwObj = 0;
		diprop.diph.dwHow = DIPH_DEVICE;
		diprop.dwData = DIPROPAXISMODE_REL;   
		hr = mouse_->SetProperty(DIPROP_AXISMODE, &diprop.diph);
		if (FAILED(hr)) { assert(false); }
		mouse_->Acquire();


		for (int i = 0; i < static_cast<uint32_t>(Input::eKeys::KB_MAX); ++i) {
			kb_xor_release[i] = 1;
		}

	}

	void Input::Update() {
		key_->GetDeviceState(sizeof(keys_), &keys_);
		if (FAILED(mouse_->GetDeviceState(sizeof(DIMOUSESTATE2), &ms_))) mouse_->Acquire();

		memset(kb_trg_down, 0, sizeof(kb_trg_down));
		memset(kb_trg_release, 0, sizeof(kb_trg_release));
		memset(trg_mouse, 0, sizeof(trg_mouse));

		for (int i = 0; i < 100; i++) {
			if ( 0x80 & keys_[ kb_keys[i] ] ) {
				kb_trg_down[kb_keys[i]] = (kb_xor_down[kb_keys[i]] ^ 0x01);
				kb_xor_down[kb_keys[i]] = 0x01;

				kb_xor_release[kb_keys[i]] = 0;

			}
			else {
				kb_xor_down[kb_keys[i]] = 0;

				kb_trg_release[kb_keys[i]] = (kb_xor_release[kb_keys[i]] ^ 0x01);
				kb_xor_release[kb_keys[i]] = 0x01;
			}
		}

		for (int i = 0; i < 3; i++) {
			if (ms_.rgbButtons[i] & 0x80) {

				// input
				trg_mouse[mouses[i]] = (xor_mouse[mouses[i]] ^ 0x01);
				xor_mouse[mouses[i]] = 0x01;

				// output
				xor_mouse[mouses[i + 3]] = 0;
			}
			else {
				// input
				xor_mouse[mouses[i]] = 0;

				// output
				trg_mouse[mouses[i + 3]] = (xor_mouse[mouses[i + 3]] ^ 0x01);
				xor_mouse[mouses[i + 3]] = 0x01;
			}
		}

	}

	void Input::Release() {
		input_->Release();
		key_->Release();
	}

	bool Input::IsKeyDown(eKeys key) {
		return 0x80 & keys_[kb_keys[static_cast<uint32_t>(key)]];
	}

	bool Input::IsKeyDownTrigger(eKeys key) {
		if (0 != kb_trg_down[kb_keys[static_cast<uint32_t>(key)]]) return true;
		return false;
	}

	bool Input::IsKeyReleaseTrigger(eKeys key) {
		if (0 != kb_trg_release[kb_keys[static_cast<uint32_t>(key)]]) return true;
		return false;
	}

	bool Input::IsMouseDown(eMouse _mouse) {
		return 0x80 & ms_.rgbButtons[static_cast<uint32_t>(_mouse)];
	}

	bool Input::IsMouseTrigger(eMouseTrigger _mouse) {
		if (0 != trg_mouse[static_cast<uint32_t>(_mouse)]) return true;
		return false;
	}

	POINT Input::GetMousePosition() {
		POINT pt;
		GetCursorPos(&pt);
		ScreenToClient(hwnd_, &pt);
		return pt;
	}

	int32_t Input::GetMouseWheel() {
		return ms_.lZ;
	}
}
