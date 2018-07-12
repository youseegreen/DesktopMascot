#pragma once
#include "Object2D.h"
#include <iostream>

//AddChara��DeleteChara����邽�߂̂��
typedef  void(*FUNCTION_POINTER)(const string name);

//�v�b�V���X�C�b�`
class PushButton : public Object2D {
//	Image img[2];	//on��off
	bool state;		//����On��Off��������
	bool prev;		//�����茟�o�p

	//�֐��|�C���^
	FUNCTION_POINTER onFunc;	//Off�ˊ֐��|�C���^
	FUNCTION_POINTER offFunc;	//On��Off�Ȃ������ɌĂ΂��
	bool callBackFrag;		//�R�[���o�b�N�֐����g�����ǂ���

public:
	PushButton(const string cName, float x, float y,
		float wid, float hei,bool draw, 
		FUNCTION_POINTER fon = NULL,FUNCTION_POINTER foff = NULL) :
		Object2D(cName, x, y, 0, 0, 0, 0, 0, 0, 0, 0, wid, hei, false, draw) {
		state = false;
		prev = false;
		if (fon != NULL) { 
			 onFunc = fon;
			 offFunc = foff;
			 callBackFrag = true;
		}
		else { 
			onFunc = NULL;
			offFunc = NULL;
			callBackFrag = false;
		}
	}

	//�f�[�^�͉����Ȃ��@
	virtual void GetData() {}

	//���݂̏��
	virtual bool OnOff() const { return state; }

	//�R�[���o�b�N�֐���o�^���ĂȂ����̏����܂�
	//���̊֐��͂߂�����ȗ����ł��邯�ǁA����̂��߂ɏڂ��������Ă���
	//�����[�v���ƂɌĂяo���@������Ɨ����オ������o����
	virtual void UpDate(Input &input) {
		if (IsMouseOn(input)) {	//�}�E�X�����Ԃ��Ă��邩?
			//���Ԃ��Ă���Ȃ��

			if (!prev && input.mouseLeftState) {
				//�O�����ŉ�����Ă����ɁA���ݎ����ŉ�����Ă���
				//(�N���b�N����)�Ȃ��
				//�g�O�����]���s��
				state = !state;
				prev = input.mouseLeftState;

				//����ɃR�[���o�b�N�֐����Ă�
				if (callBackFrag) {
					if (state)onFunc(name);	//off��on�֐�
					if (!state)offFunc(name);	//on��off�֐�
				}
			}
			else if (prev && input.mouseLeftState) {
				//�O���������ݎ�����������Ă���
				//(��������)�Ȃ��
				//����ێ�
				state = state;
				prev = input.mouseLeftState;
			}
			else if (!prev && !(input.mouseLeftState)) {
				//�O���������ݎ�����������Ă��Ȃ�
				//(�}�E�X���{�^���̏�ɂ��邾��)�Ȃ��
				//����ێ�
				state = state;
				prev = input.mouseLeftState;
			}
			else if (prev && !(input.mouseLeftState)) {
				//�O����������Ă��Č�����������Ă��Ȃ�
				//(�肪�����ꂽ)�Ȃ��
				//�X�e�[�g�ێ�����prev��ύX
				state = state;
				prev = input.mouseLeftState;
			}
		}
		else {
			state = state;
			prev = input.mouseLeftState;
		}
	}

	//���̂Ƃ���摜������\��͂Ȃ��̂ŁADrawBox�ł���
	virtual void Draw() const {
		if (state) {	//�X�C�b�`��on�i�ւ���ł���j
			DrawBox(x, y, x + width, y + height, 0xFFFF, TRUE);
		}
		else {			//�X�C�b�`��off
			DrawBox(x, y, x + width, y + height, 0x00FF, TRUE);
		}
	}

private:

	/*
	//�}�E�X�̈ʒu�������Ă��邩�ǂ���
	bool IsIn(int &mx, int &my) const {
		if ((mx > x) && (mx < (x + width)) && (my > y) && (my < (y + height))) return true;
		return false;
	}
	*/
};