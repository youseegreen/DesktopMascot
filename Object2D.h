#pragma once
#include <DxLib.h>
#include "MyVector2f.h"
#include "DataSet.h"
#include <string>
using namespace std;

class Object2D {
protected:
	//���O
	const string name;

	//�����n
	float x, y, vx, vy, ax, ay, fx, fy, theta, mass, width, height;
	float ref, omega;	//���˗��A�p���x
	bool collisionFlag;	//�����蔻�肪���邩�Ȃ���	

	//�`��n
	bool isDraw;	//�`�悷�邩�ǂ���

public:
	//�R���X�g���N�^
	Object2D(const string n, float tx, float ty, float tvx, float tvy, float tax, float tay,
		float tfx, float tfy, float ttheta, float tmass, float wid, float hei, bool colli, bool draw) :
		name(n), x(tx), y(ty), vx(tvx), vy(tvy), ax(tax), ay(tay), fx(tfx), fy(tfy),
		theta(ttheta), mass(tmass), width(wid), height(hei), collisionFlag(colli), isDraw(draw) {
		ref = 1.0f;
	}
	//�f�X�g���N�^	�������Ȃ��Ė��Ȃ�
	virtual ~Object2D() {};

	//�R�s�[�֎~�ˈꎞ�ێ��p�ɋ����邱�Ƃɂ��܂���
	Object2D(const Object2D &ori) : name(ori.name){	//const�͏��߂�
		x = ori.x; y = ori.y; vx = ori.vx; vy = ori.vy;
		ax = ori.ax; ay = ori.ay; fx = ori.fx; fy = ori.fy;
		theta = ori.theta; omega = ori.omega; mass = ori.mass;
		width = ori.width; height = ori.height; ref = ori.ref;
		collisionFlag = ori.collisionFlag;	//�����蔻�肪���邩�Ȃ���
		isDraw = ori.collisionFlag;	//�`�悷�邩�ǂ���
	};
	void operator=(const Object2D &ori) {
		//���O�����p���Ȃ�
		x = ori.x; y = ori.y; vx = ori.vx; vy = ori.vy;
		ax = ori.ax; ay = ori.ay; fx = ori.fx; fy = ori.fy;
		theta = ori.theta; omega = ori.omega; mass = ori.mass;
		width = ori.width; height = ori.height; ref = ori.ref;
		collisionFlag = ori.collisionFlag;	//�����蔻�肪���邩�Ȃ���
		isDraw = ori.collisionFlag;	//�`�悷�邩�ǂ���
	};


public:
	const string GetName() const{ 
		return name; 
	}
	virtual void Update(Input &input) {}	//�ʒu�̍X�V���s��
	virtual void GetData() {}	//�摜�≹���t�@�C�������[�h�@���̃N���X�͉������Ȃ�
	virtual void Draw() const {}	//�����_�����O�@���̃N���X�͉������Ȃ�

									//�Q�b�^�[
	virtual void GetPosition(float &tx, float &ty) const {
		tx = x;
		ty = y;
	}
	virtual void GetSize(float &wid, float &hei) const {
		wid = width;
		hei = height;
	}

	//��`���̓���Ԃ��������ǂ���������Ԃ��@���̂�̉��ʌ݊�
	virtual bool IsCollision(const Object2D &other) const;

	//��`����2���ǂ����Ԃ��Ă��邩�𐔎��ŕԂ��@�Ԃ����ĂȂ��F0
	virtual int WhereCollision(const Object2D &other) const;

	//�Փ˂��ĂȂ��ꍇ��0�Ԃ��̂Œ��Ӂ@IsCollision�Ŕ��肵����g���ׂ�
	//����Ɍ������Ă��������̖@���x�N�g����Ԃ��@�悭�킩��܂���̂͑S��0�ɂ�������C�����ā@
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

	//���̂̏�Ń}�E�X�����傤�Ǎ��N���b�N������?
	virtual bool IsLeftJustClicked(Input &input) {
		if ((input.mouseX > x) && (input.mouseX < (x + width))
			&& (input.mouseY > y) && (input.mouseY < (y + height))
			&& input.mouseLeftClicked) return true;
		return false;
	}

	//���̂Ƀ}�E�X���E�N���b�N���Ă��邩?
	virtual bool IsRightClick(Input &input) {
		if ((input.mouseX > x) && (input.mouseX < (x + width))
			&& (input.mouseY > y) && (input.mouseY < (y + height))
			&& input.mouseRightState) return true;
		return false;
	}

	//���̂̏�Ń}�E�X�����傤�ǉE�N���b�N������?
	virtual bool IsRightJustClicked(Input &input) {
		if ((input.mouseX > x) && (input.mouseX < (x + width))
			&& (input.mouseY > y) && (input.mouseY < (y + height))
			&& input.mouseRightClicked) return true;
		return false;
	}

	//���̂̏�Ƀ}�E�X���d�Ȃ��Ă��邩
	virtual bool IsMouseOn(Input &input) {
		if ((input.mouseX > x) && (input.mouseX < (x + width))
			&& (input.mouseY > y) && (input.mouseY < (y + height))) return true;
		return false;
	}
};