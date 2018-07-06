#pragma once
#include <DxLib.h>
#include "DataSet.h"

class Object2D {
protected:
	//���O
	const char *name;

	//�����n
	float x, y, vx, vy, ax, ay, fx, fy, theta, mass, width, height;
	bool collisionFrag;	//�����蔻�肪���邩�Ȃ���	

	//�`��n
	bool isDraw;	//�`�悷�邩�ǂ���

public:
	//�R���X�g���N�^
	Object2D(const char *n, float tx, float ty, float tvx, float tvy, float tax, float tay,
		float tfx, float tfy, float ttheta, float tmass, float wid, float hei, bool colli, bool draw) :
		name(n), x(tx), y(ty), vx(tvx), vy(tvy), ax(tax), ay(tay), fx(tfx), fy(tfy),
		theta(ttheta), mass(tmass), width(wid), height(hei), collisionFrag(colli), isDraw(draw){

	}
	//�f�X�g���N�^	�������Ȃ��Ė��Ȃ�
	~Object2D() {};
private:
	//�R�s�[�֎~
	Object2D(const Object2D &ori) {};

public:
	const char *GetName() const{ return name; }
	virtual void Update() {};	//�ʒu�̍X�V���s��
	virtual void GetData() {}	//�摜�≹���t�@�C�������[�h�@���̃N���X�͉������Ȃ�
	virtual bool IsCollision(Object2D &other) const{
		if (!collisionFrag || !other.collisionFrag) return false;	//�Փ˃t���Ooff�Ȃ�false

		if (((x + width) < other.x) || (x > (other.x + other.width))
			|| ((y + height) < other.y) || (y > (other.y + other.height))) {
			//alpharegion����Ȃ炱���ł����if���쐬
			return false;
		}
		return true;
	}

	//�����̂�ɓ��������ɌĂ񂾂ق��������̂���?
	virtual void BehaviorOfCollision(const Object2D &other){
		
	}
};