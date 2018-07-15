#include "Object2D.h"


bool Object2D::IsCollision(const Object2D &other) const {
	if (!collisionFlag || !other.collisionFlag) return false;	//�Փ˃t���Ooff�Ȃ�false

	if (((x + width) <= other.x) || (x >= (other.x + other.width))
		|| ((y + height) <= other.y) || (y >= (other.y + other.height))) {
		//alpharegion����Ȃ炱���ł����if���쐬
		return false;
	}
	return true;
}

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
int Object2D::WhereCollision(const Object2D &other) const {
	if (!IsCollision(other))return 0;	//�������Ă��Ȃ��Ȃ�0��Ԃ�
	//���̎��_�œ������Ă��邱�Ƃ͊m��
	int xnum, ynum;
	bool xspe = false;	
	bool yspe = false;

	//�Ō�͐�΂�1����
	if ((other.x + other.width) >(x + width)) {
		if (x < other.x) {
			//1,4,7,10�ɂ��ڂ���	3�ł����1�]��
			xnum = 0;
		}
		else {
			//2,5,8,11�ɂ��ڂ���	3�ł����2�]��
			xnum = 1;
		}
	}
	else {
		//3,6,9,12   13,14,15,16�ɂ��ڂ���
		if (x > other.x) {
			//3,6,9,12�ɂ��ڂ���
			xnum = 2;
		}
		else {
			//13,14,15,16�ɂ��ڂ���
			xspe = true;
		}
	}

	if ((other.y + other.height) > (y + height)) {
		//1�`6  13,14�ɂ��ڂ���
		if (y < other.y) {
			//1,2,3,13�ɂ��ڂ���	3*0
			ynum = 0;
		}
		else {
			//4,5,6,14�ɂ��ڂ���	3*1
			ynum = 1;
		}
	}
	else {
		//7�`9,15  10,11,12,16�ɂ��ڂ���
		if (y > other.y) {
			//7,8,9,15�ɂ��ڂ���
			ynum = 2;
		}
		else {
			//10,11,12,16�ɂ��ڂ���
			yspe = true;
		}
	}

	if (yspe && xspe)return 16;	//16��
	if (xspe) {	//yspe = false;
		return (13 + ynum);		//13,14,15��	
	}
	if (yspe) { //xspe = false;	//10,11,12��
		return (10 + xnum);
	}
	//yspe = xspe = false;		
	return (3 * ynum + xnum + 1);	//1�`9��
}

//�Փ˂��ĂȂ��ꍇ��0�Ԃ��̂Œ��Ӂ@IsCollision�Ŕ��肵����g���ׂ�
//����Ɍ������Ă��������̖@���x�N�g����Ԃ��@�悭�킩��܂���̂͑S��0�ɂ�������C�����ā@
void Object2D::GetNormalVector(const Object2D &other, Vector2f &vec) const {
	vec.x = vec.y = 0.0f;
	
	//�Փ˂̎d��������
	int number = WhereCollision(other);

	//�Փ˂̎d���ɂ���ďꍇ��������
	switch (number) {
	case 1:	//���ォ�Ԃ��Ă���
		vec.x = -other.y + y + height;
		vec.y = -other.x + x + width;
		vec.NormalizeSelf();
		return;
	case 3:
		vec.x = -y - height + other.y;
		vec.y = -x + other.x + other.width;
		vec.NormalizeSelf();
		return;
	case 7:
		vec.x = -other.y - other.height + y;
		vec.y = -other.x + x + width;
		vec.NormalizeSelf();
		return;
	case 9:
		vec.x = -other.y - other.height + y;
		vec.y = -other.x - other.width + x;
		vec.NormalizeSelf();
		return;
	case 2:
	case 13:
		vec.y = 1.0f;
		return;
	case 4:
	case 10:
		vec.x = 1.0f;
		return;
	case 6:
	case 12:
		vec.x = -1.0f;
		return;
	case 8:
	case 15:
		vec.y = -1.0f;
		return;
	case 11:
	case 14:
	case 5:		//�S����
	case 16:	//�S����
	default:	//�Ԃ����Ă��Ȃ�
		return;
	}
}