#pragma once

#include "Object2D.h"

//�L�����N�^�[��{�`
class Character : public Object2D {
	//�摜�n
	DataSet *pointer2DataSet;		//�f�[�^�Z�b�g�ւ̎Q��
	std::vector<Image> *imgList;	//��������̉摜�f�[�^�ւ̎Q��
	std::vector<Sound> *sndList;	//��������̉����f�[�^�ւ̎Q��

	Image *nowImg;		//���ݎQ�ƒ��̃C���[�W
	int nowNum;			//���݂̔ԍ�

public:
	//�R���X�g���N�^
	Character(const char *n, float x, float y, float vx, float vy, float mass,
		float wid, float hei, bool colli, bool draw) :
		Object2D(n, x, y, vx, vy, 0, 0, 0, 0, 0, mass, wid, hei, colli, draw) {

	}
	
	//DataSet.h����Chaeacter�ɕK�v�ȑS�f�[�^�E���Ă���
	virtual void GetData();

	//update
	virtual void Update(); 

	//�����_�����O
	virtual void Draw() const {
		if (nowImg->imgHandle != 1)return;
		DrawGraph(x, y, nowImg->imgHandle, TRUE);
	}

	//�Փˎ��̐U�镑��
	virtual void BehaviorOfCollision(Object2D &other) {
		vx *= -1;
		vy *= -1;
	}
};