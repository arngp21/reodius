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
		 DIK_BACK		// �o�b�N�X�y�[�X�L�[
		,DIK_TAB		// �^�u�L�[
		,DIK_RETURN		// �G���^�[�L�[
		,DIK_LSHIFT		// ���V�t�g�L�[
		,DIK_RSHIFT		// �E�V�t�g�L�[
		,DIK_LCONTROL	// ���R���g���[���L�[
		,DIK_RCONTROL	// �E�R���g���[���L�[
		,DIK_ESCAPE		// �G�X�P�[�v�L�[
		,DIK_SPACE		// �X�y�[�X�L�[
		,DIK_PGUP		// �o�������t�o�L�[
		,DIK_PGDN		// �o�������c�������L�[
		,DIK_END		// �G���h�L�[
		,DIK_HOME		// �z�[���L�[
		,DIK_LEFT		// ���L�[
		,DIK_UP			// ��L�[
		,DIK_RIGHT		// �E�L�[
		,DIK_DOWN		// ���L�[
		,DIK_INSERT		// �C���T�[�g�L�[
		,DIK_DELETE		// �f���[�g�L�[

		,DIK_MINUS		// �|�L�[
		,DIK_YEN		// ���L�[
		,DIK_PREVTRACK	// �O�L�[
		,DIK_PERIOD		// �D�L�[
		,DIK_SLASH		// �^�L�[
		,DIK_LALT		// ���`�k�s�L�[
		,DIK_RALT		// �E�`�k�s�L�[
		,DIK_SCROLL		// ScrollLock�L�[
		,DIK_SEMICOLON	// �G�L�[
		,DIK_COLON		// �F�L�[
		,DIK_LBRACKET	// �m�L�[
		,DIK_RBRACKET	// �n�L�[
		,DIK_AT			// ���L�[
		,DIK_BACKSLASH	// �_�L�[
		,DIK_COMMA		// �C�L�[
		,DIK_CAPSLOCK	// CaspLock�L�[
		,DIK_PAUSE		// PauseBreak�L�[

		,DIK_NUMPAD0	// �e���L�[�O
		,DIK_NUMPAD1	// �e���L�[�P
		,DIK_NUMPAD2	// �e���L�[�Q
		,DIK_NUMPAD3	// �e���L�[�R
		,DIK_NUMPAD4	// �e���L�[�S
		,DIK_NUMPAD5	// �e���L�[�T
		,DIK_NUMPAD6	// �e���L�[�U
		,DIK_NUMPAD7	// �e���L�[�V
		,DIK_NUMPAD8	// �e���L�[�W
		,DIK_NUMPAD9	// �e���L�[�X
		,DIK_MULTIPLY	// �e���L�[���L�[
		,DIK_ADD		// �e���L�[�{�L�[
		,DIK_SUBTRACT	// �e���L�[�|�L�[
		,DIK_DECIMAL	// �e���L�[�D�L�[
		,DIK_DIVIDE	// �e���L�[�^�L�[
		,DIK_NUMPADENTER	// �e���L�[�̃G���^�[�L�[

		,DIK_F1	// �e�P�L�[
		,DIK_F2	// �e�Q�L�[
		,DIK_F3	// �e�R�L�[
		,DIK_F4	// �e�S�L�[
		,DIK_F5	// �e�T�L�[
		,DIK_F6	// �e�U�L�[
		,DIK_F7	// �e�V�L�[
		,DIK_F8	// �e�W�L�[
		,DIK_F9	// �e�X�L�[
		,DIK_F10	// �e�P�O�L�[
		,DIK_F11	// �e�P�P�L�[
		,DIK_F12	// �e�P�Q�L�[

		,DIK_A	// �`�L�[
		,DIK_B	// �a�L�[
		,DIK_C	// �b�L�[
		,DIK_D	// �c�L�[
		,DIK_E	// �d�L�[
		,DIK_F	// �e�L�[
		,DIK_G	// �f�L�[
		,DIK_H	// �g�L�[
		,DIK_I	// �h�L�[
		,DIK_J	// �i�L�[
		,DIK_K	// �j�L�[
		,DIK_L	// �k�L�[
		,DIK_M	// �l�L�[
		,DIK_N	// �m�L�[
		,DIK_O	// �n�L�[
		,DIK_P	// �o�L�[
		,DIK_Q	// �p�L�[
		,DIK_R	// �q�L�[
		,DIK_S	// �r�L�[
		,DIK_T	// �s�L�[
		,DIK_U	// �t�L�[
		,DIK_V	// �u�L�[
		,DIK_W	// �v�L�[
		,DIK_X	// �w�L�[
		,DIK_Y	// �x�L�[
		,DIK_Z	// �y�L�[
		,DIK_0	// �O�L�[
		,DIK_1	// �P�L�[
		,DIK_2	// �Q�L�[
		,DIK_3	// �R�L�[
		,DIK_4	// �S�L�[
		,DIK_5	// �T�L�[
		,DIK_6	// �U�L�[
		,DIK_7	// �V�L�[
		,DIK_8	// �W�L�[
		,DIK_9	// �X�L�[
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

		// �f�o�C�X�̐ݒ�   
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
