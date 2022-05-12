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

		// �}�E�X�Ή��L�[ �ꗗ
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

		// �L�[�{�[�h�Ή��L�[ �ꗗ
		enum class eKeys {
			KB_BACK		// �o�b�N�X�y�[�X
			, KB_TAB		// �^�u
			, KB_RETURN	// �G���^�[
			, KB_LSHIFT	// ���V�t�g
			, KB_RSHIFT	// �E�V�t�g
			, KB_LCONTROL	// ���R���g���[��
			, KB_RCONTROL	// �E�R���g���[��
			, KB_ESCAPE	// �G�X�P�[�v
			, KB_SPACE	    // �X�y�[�X
			, KB_PGUP		// �o�������t�o
			, KB_PGDN		// �o�������c������
			, KB_END		// �G���h
			, KB_HOME		// �z�[��
			, KB_LEFT		// ��
			, KB_UP		// ��
			, KB_RIGHT	    // �E
			, KB_DOWN		// ��
			, KB_INSERT	// �C���T�[�g
			, KB_DELETE	// �f���[�g

			, KB_MINUS		    // �|
			, KB_YEN			// ��
			, KB_PREVTRACK	    // �O
			, KB_PERIOD		// �D
			, KB_SLASH		    // �^
			, KB_LALT			// ���`�k�s
			, KB_RALT			// �E�`�k�s
			, KB_SCROLL		// ScrollLock
			, KB_SEMICOLON	    // �G
			, KB_COLON		    // �F
			, KB_LBRACKET		// �m
			, KB_RBRACKET		// �n
			, KB_AT			// ��
			, KB_BACKSLASH	    // �_
			, KB_COMMA		    // �C
			, KB_CAPSLOCK		// CaspLock
			, KB_PAUSE		    // PauseBreak

			, KB_NUMPAD0	// �e���L�[�O
			, KB_NUMPAD1	// �e���L�[�P
			, KB_NUMPAD2	// �e���L�[�Q
			, KB_NUMPAD3	// �e���L�[�R
			, KB_NUMPAD4	// �e���L�[�S
			, KB_NUMPAD5	// �e���L�[�T
			, KB_NUMPAD6	// �e���L�[�U
			, KB_NUMPAD7	// �e���L�[�V
			, KB_NUMPAD8	// �e���L�[�W
			, KB_NUMPAD9	// �e���L�[�X
			, KB_MULTIPLY	// �e���L�[��
			, KB_ADD		// �e���L�[�{
			, KB_SUBTRACT	// �e���L�[�|
			, KB_DECIMAL	// �e���L�[�D
			, KB_DIVIDE	// �e���L�[�^
			, KB_NUMPADENTER	// �e���L�[�̃G���^�[

			, KB_F1	// �e�P
			, KB_F2	// �e�Q
			, KB_F3	// �e�R
			, KB_F4	// �e�S
			, KB_F5	// �e�T
			, KB_F6	// �e�U
			, KB_F7	// �e�V
			, KB_F8	// �e�W
			, KB_F9	// �e�X
			, KB_F10	// �e�P�O
			, KB_F11	// �e�P�P
			, KB_F12	// �e�P�Q

			, KB_A	// �`
			, KB_B	// �a
			, KB_C	// �b
			, KB_D	// �c
			, KB_E	// �d
			, KB_F	// �e
			, KB_G	// �f
			, KB_H	// �g
			, KB_I	// �h
			, KB_J	// �i
			, KB_K	// �j
			, KB_L	// �k
			, KB_M	// �l
			, KB_N	// �m
			, KB_O	// �n
			, KB_P	// �o
			, KB_Q	// �p
			, KB_R	// �q
			, KB_S	// �r
			, KB_T	// �s
			, KB_U	// �t
			, KB_V	// �u
			, KB_W	// �v
			, KB_X	// �w
			, KB_Y	// �x
			, KB_Z	// �y
			, KB_0	// �O
			, KB_1	// �P
			, KB_2	// �Q
			, KB_3	// �R
			, KB_4	// �S
			, KB_5	// �T
			, KB_6	// �U
			, KB_7	// �V
			, KB_8	// �W
			, KB_9	// �X
			, KB_MAX
		};

		// ������
		static void Initialize(HWND hwnd);
		// �X�V
		static void Update();
		// ���
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

		// �}�E�X���W�̎擾
		static POINT GetMousePosition();
		// �}�E�X�z�C�[���̕ω��ʂ��擾
		static int32_t GetMouseWheel();

	};

}

using eKeys = tnl::Input::eKeys;
using eMouse = tnl::Input::eMouse;
using eMouseTrigger = tnl::Input::eMouseTrigger;

