#pragma once

#include <DxLib.h>
#include <string>
#include <memory>
#include "World.h"
#include "Button.h"


//�Ǘ��N���X�@�L�����̐�����world���s��
class DesktopMascot {
	static const int screenX;	//�f�X�N�g�b�v�̃T�C�Y
	static const int screenY;
	static World *world;		//���E�ւ̎Q��
	static int omoteHandle;		//�`��Ώۂ̃n���h��
	static list<std::unique_ptr<Button>> buttonList;	//�{�^���Ǘ��@���̃N���X�ōs��

	//�C���X�^���X�����֎~	�ÓI�N���X
	DesktopMascot();

public:
	//�������֐��@�K�����s���邱��
	static void Initialize();

	//���s�֐�	���C������
	static void Execute();	

	//�I���֐��@�K�����s���悤
	static void End() {
		delete world;
		DxLib_End();
	}

	//�G���[���N�������Ƃ��X�N���[���ɕ\��������
	static void PrintError(){ 
		//�G���[���N�����Ƃ������ɏ���
	}
};

