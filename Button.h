#pragma once
#include "Object2D.h"
#include <iostream>

//AddChara��DeleteChara����邽�߂̂��
typedef  void(*FUNCTION_POINTER)(const string name);

//������{�^��
class Button : public Object2D {
	Image img[2];	//on��off
	bool state;		//on or off
	bool prev;		//�ꎞ���O�̃}�E�X�̃N���b�N���

	FUNCTION_POINTER fp;	//�֐��|�C���^
	bool callBackFrag;		//�R�[���o�b�N�֐����g�����ǂ���

public:
	Button(const string cName, float x, float y, 
			float wid, float hei, bool draw, FUNCTION_POINTER f = NULL) :
		Object2D(cName, x, y, 0, 0, 0,0,0,0,0,0,wid, hei, false, draw) {
		if (f != NULL) { fp = f; callBackFrag = true; }
		else { fp = NULL; callBackFrag = false; }
	}

	//�f�[�^�͉����Ȃ�
	virtual void GetData(){}

	virtual bool OnOff() const{ return state; }


	//���������������Ȃ��Ɨ�����{�^���̖����ʂ����Ȃ�����...
	//�����[�v���ƂɌĂяo���@state��On��Off�������
	virtual void UpDate(int mouseX, int mouseY, bool mouseState) {
		if (IsIn(mouseX, mouseY)) {
		//�}�E�X�����Ԃ��Ă���Ȃ��
			if (prev && !mouseState) {
				//�O�����Ă�
				state = true;
				prev = false;
			}
			else if (mouseState) {
				prev = true;
				state = false;
			}
			else if (!prev && !mouseState) {
				prev = false;
				state = false;
			}
		}
		else {
			prev = false;
			state = false;
		}

		//�R�[���o�b�N�֐��̎��s	���̏ꍇ�L�����̒ǉ�or�폜
		if (state) {
			if (callBackFrag) {
				fp(name);
				cout << "ok" << endl;
			}
		}
	}

	//���̂Ƃ���摜������\��͂Ȃ��̂ŁADrawBox�ł���
	virtual void Draw() const{
		if (prev) {
			DrawBox(x, y, width, height, 0xFFFF, TRUE);
		}
		else {
			DrawBox(x, y, width, height, 0x00FF, TRUE);
		}
	}

private:
	//�}�E�X�̈ʒu�������Ă��邩�ǂ���
	bool IsIn(int mx, int my) const {
		if ((mx > x) && (mx < (x + width)) && (my > y) && (my < (y + height))) return true;
		return false;
	}
};