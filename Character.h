#pragma once

#include "Object2D.h"
#include <iostream>
using namespace std;

//�L�����N�^�[��{�`
class Character : public Object2D {
	//�摜�n
	DataSet *pointer2DataSet;		//�f�[�^�Z�b�g�ւ̎Q��
	std::vector<Image> *imgList;	//��������̉摜�f�[�^�ւ̎Q��
	std::vector<Sound> *sndList;	//��������̉����f�[�^�ւ̎Q��

	Image *nowImg;		//���ݎQ�ƒ��̃C���[�W
	int nowNum;			//���݂̔ԍ�

	//AI�n
	int moveState;	//���Ă���@�����_���Ƃ����@int��enum�ɂ�����

public:
	//�R���X�g���N�^
	Character(const string n, float x, float y, float vx, float vy, float mass,
		float wid, float hei, bool colli, bool draw) :
		Object2D(n, x, y, vx, vy, 0, 0, 0, 0, 0, mass, wid, hei, colli, draw) {
		cout << "����" << name << endl;
		GetData();
		moveState = 0;	//0�F�����_��
	}

	//�R�s�[�R���X�g���N�^
	Character(const Character &chara) :Object2D(chara) {
		pointer2DataSet = chara.pointer2DataSet;
		imgList = chara.imgList;
		sndList = chara.sndList;
		nowImg = chara.nowImg;
		nowNum = chara.nowNum;
		moveState = chara.moveState;
	}
	//Object2D�̕ʃI�u�W�F�N�g������Ƃ��̂��߂Ɂ@�ꎞ���p�O��AChara�ϐ��͉������Ȃ�
	Character(const Object2D &obj) :Object2D(obj) { }

	
	//DataSet.h����Chaeacter�ɕK�v�ȑS�f�[�^�E���Ă���
	virtual void GetData();

	//update
	virtual void Update(Input &input); 

	//�����_�����O
	virtual void Draw() const {
		if (nowImg->imgHandle == -1)return;
		DrawGraph(x, y, nowImg->imgHandle, TRUE);
	}

	//�Փˎ��̐U�镑��
	virtual void BehaviorOfCollision(const Object2D &other);
};