#pragma once
#include "Object2D.h"

//�����h�����Ĕw�i�I�u�W�F�N�g���΂悢�Ǝv��

//�ǂ�݂��Ȃ��ǐ�p�@�������Ă��ꏊ���ς��Ȃ�
class DontMoveObjectNoImage :public Object2D {


public:
	DontMoveObjectNoImage(const char *n, float x, float y, float theta,
		float mass, float wid, float hei, bool colli) :
		Object2D(n, x, y, 0, 0, 0, 0, 0, 0, theta, mass, wid, hei, colli, false) {
	}

	virtual void GetData() { 
		//�������Ȃ�
	}

	//�X�V
	virtual void Update() {
		//�������Ȃ��@���݂��邾��
	}

	//�����_�����O�@
	virtual void Draw()const {
		//�������Ȃ��@���݂��邾��
	}
};