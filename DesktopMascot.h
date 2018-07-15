#pragma once

#include <DxLib.h>
#include <string>
#include <memory>
#include "World.h"
#include "PushButton.h"


//�Ǘ��N���X�@�L�����̐�����world���s��
class DesktopMascot {
	static const int screenX;	//�f�X�N�g�b�v�̃T�C�Y
	static const int screenY;
	static World *world;		//���E�ւ̎Q��
	static int omoteHandle;		//�`��Ώۂ̃n���h��
	static list<std::unique_ptr<PushButton>> buttonList;	//�{�^���Ǘ��@���̃N���X�ōs��

	static int threX1, threX2, threY1, threY2;	//�}�E�X�J�[�\�����ǂ��ɂ�����{�^���\�����邩

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

	//�{�^�������Z�b�g�Aworld���炻�̃L����������
	static void ResetCharacter(const string name);
};

