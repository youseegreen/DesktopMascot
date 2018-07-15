#pragma once
#include "Object2D.h"
#include <iostream>

//AddChara��DeleteChara����邽�߂̂��
typedef  void(*FUNCTION_POINTER)(const string name);

//�v�b�V���X�C�b�`
class PushButton : public Object2D {
//	Image img[2];	//on��off
	Image *img;		//�`��p�Ɏg���摜
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
		img = NULL;
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
		GetData();
	}

	//DataSet����摜1�Ƃ��Ă���
	//������i�[����
	virtual void GetData() {
		auto itr = charaDataList.find(name);
		if (itr == charaDataList.end())return;	//�f�[�^���Ȃ����img = NULL

		if (charaDataList[name].imgList.size() <= 0)return;	//�摜���Ȃ����img = NULL
		img = &(charaDataList[name].imgList[0]);
	}

	//���݂̏��
	virtual bool OnOff() const { return state; }

	//���Z�b�g
	virtual void Reset() {
		state = false;
		prev = false;
	}

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
			DrawBox(x, y, x + width, y + height, GetColor(255,0,0), TRUE);
			if (img != NULL)
				DrawExtendGraph(x, y, x + width, y + height, img->imgHandle, TRUE);
		}
		else {			//�X�C�b�`��off
			DrawBox(x, y, x + width, y + height, GetColor(0, 0, 255), TRUE);
			if (img != NULL) {
				SetDrawBright(128, 128, 128);	//�P�x���Â�
				DrawExtendGraph(x, y, x + width, y + height, img->imgHandle, TRUE);
				SetDrawBright(255, 255, 255);	//�P�x��߂�
			}
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