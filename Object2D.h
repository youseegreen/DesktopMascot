#pragma once
#include <DxLib.h>
#include "DataSet.h"
#include <string>
using namespace std;

class Object2D {
protected:
	//���O
	const string name;

	//�����n
	float x, y, vx, vy, ax, ay, fx, fy, theta, mass, width, height;
	bool collisionFrag;	//�����蔻�肪���邩�Ȃ���	

	//�`��n
	bool isDraw;	//�`�悷�邩�ǂ���

public:
	//�R���X�g���N�^
	Object2D(const string n, float tx, float ty, float tvx, float tvy, float tax, float tay,
		float tfx, float tfy, float ttheta, float tmass, float wid, float hei, bool colli, bool draw) :
		name(n), x(tx), y(ty), vx(tvx), vy(tvy), ax(tax), ay(tay), fx(tfx), fy(tfy),
		theta(ttheta), mass(tmass), width(wid), height(hei), collisionFrag(colli), isDraw(draw) {
	}
	//�f�X�g���N�^	�������Ȃ��Ė��Ȃ�
	~Object2D() {};
private:
	//�R�s�[�֎~
	Object2D(const Object2D &ori) {};

public:
	const string GetName() const{ 
		return name; 
	}
	virtual void Update(Input &input) {}	//�ʒu�̍X�V���s��
	virtual void GetData() {}	//�摜�≹���t�@�C�������[�h�@���̃N���X�͉������Ȃ�
	virtual void Draw() const {}	//�����_�����O�@���̃N���X�͉������Ȃ�

	//��`���̓���Ԃ��������ǂ���������Ԃ��@���̂�̉��ʌ݊�
	virtual bool IsCollision(const Object2D &other) const;

	//��`����2���ǂ����Ԃ��Ă��邩�𐔎��ŕԂ�
	/*�����̕Ԃ���*/
	/*���Ԃ��Ă��Ȃ���0*/
	/*�Ăяo�������A��������...*/
	/*�P�F����ł��Ԃ��Ă���
	  �Q�F�^��ł��Ԃ��Ă���
	�@�R�F�E��ł��Ԃ��Ă���
	  �S�F�����ł��Ԃ��Ă���
	  �T�F�������Ɉ͂܂�Ă���
	  �U�F�E���ł��Ԃ��Ă���
	  �V�F�����ł��Ԃ��Ă���
	  �W�F�^���ł��Ԃ��Ă���
	  �X�F�E���ł��Ԃ��Ă���
	  10�F�������Ă���
	  11�F�^�񒆏c�ɕ����Ă���
	  12�F�E�����Ă���
	  13�F�㕢���Ă���
	  14�F�^�񒆉��ɕ����Ă���
	  15�F�������Ă���
	  16�F�͂�ł���@�@�@*/
	virtual int WhereCollision(const Object2D &other) const;

	//�Ԃ����Ă��邱�Ƃ��킩���Ă���󋵂ŁA�@���x�N�g����Ԃ�
	virtual void GetNormalVector(const Object2D &other, Vector2f &vec) const; 

	//�����̂�ɓ��������ɌĂ񂾂ق��������̂���?
	virtual void BehaviorOfCollision(const Object2D &other){
		
	}

protected:
	//���̂Ƀ}�E�X�����N���b�N���Ă��邩?
	virtual bool IsLeftClick(Input &input) {
		if ((input.mouseX > x) && (input.mouseX < (x + width))
			&& (input.mouseY > y) && (input.mouseY < (y + height))
			&& input.mouseLeftState) return true;
		return false;
	}

	//���̂Ƀ}�E�X���E�N���b�N���Ă��邩?
	virtual bool IsRightClick(Input &input) {
		if ((input.mouseX > x) && (input.mouseX < (x + width))
			&& (input.mouseY > y) && (input.mouseY < (y + height))
			&& input.mouseRightState) return true;
		return false;
	}

	//���̂̏�Ƀ}�E�X���d�Ȃ��Ă��邩
	virtual bool IsMouseOn(Input &input) {
		if ((input.mouseX > x) && (input.mouseX < (x + width))
			&& (input.mouseY > y) && (input.mouseY < (y + height))) return true;
		return false;
	}
};