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

public:
	//�R���X�g���N�^
	Character(const string n, float x, float y, float vx, float vy, float mass,
		float wid, float hei, bool colli, bool draw) :
		Object2D(n, x, y, vx, vy, 0, 0, 0, 0, 0, mass, wid, hei, colli, draw) {
		cout << "����" << name << endl;
		GetData();
	}
	
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
	virtual void BehaviorOfCollision(const Object2D &other) {
		
		//�@���x�N�g���𓾂�
		Vector2f N;
		GetNormalVector(other, N);

		//0�x�N�g���Ȃ�P�ɔ���
		if ((N.x == 0) && (N.y == 0)) {
			vx *= -1;
			vy *= -1;
			return;
		}

		//���x�x�N�g���̋t�x�N�g��
		Vector2f v = { -vx,-vy };

		//�������t�Ȃ牽�����Ȃ�
		if (v*N <= 0) return;

		//���˕���
		Vector2f R = N * (2 * (v * N)) - v;
		vx = R.x;
		vy = R.y;
	}
};