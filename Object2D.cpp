#include "Object2D.h"


bool Object2D::IsCollision(const Object2D &other) const {
	if (!collisionFrag || !other.collisionFrag) return false;	//�Փ˃t���Ooff�Ȃ�false

	if (((x + width) <= other.x) || (x >= (other.x + other.width))
		|| ((y + height) <= other.y) || (y >= (other.y + other.height))) {
		//alpharegion����Ȃ炱���ł����if���쐬
		return false;
	}
	return true;
}

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

//�悭�킩��܂���ł����@�C������
void Object2D::GetNormalVector(const Object2D &other, Vector2f &vec) const {
	vec.x = vec.y = 0.0f;
	
	//�Փ˂̎d��������
	int number = WhereCollision(other);

	//�Փ˂̎d���ɂ���ďꍇ��������
	switch (number) {
	case 1:	//���ォ�Ԃ��Ă���
		vec.x = other.y - y - height;
		vec.y = other.x - x - width;
		vec.Normalize();
		return;
	case 2:
		vec.x = 0.0f;
		vec.y = -1.0f;
		return;
	case 3:
		vec.x = y + height - other.y;
		vec.y = x - other.x - other.width;
		vec.Normalize();
		return;
	case 4:
		vec.x = -1.0f;
		vec.y = 0.0f;
		return;
	case 5:
		vec.x = 0.0f;
		vec.y = 0.0f;
		return;
	case 6:
		vec.x = 1.0f;
		vec.y = 0.0f;
		return;
	case 7:
		vec.x = other.y + other.height - y;
		vec.y = other.x - x - width;
		vec.Normalize();
		return;
	case 8:
		vec.x = 0.0f;
		vec.y = 1.0f;
		return;
	case 9:
		vec.x = other.y + other.height - y;
		vec.y = other.x + other.width - x;
		vec.Normalize();
		return;
	case 10:
		vec.x = -1.0f;
		vec.y = 0.0f;
		return;
	case 11:
		vec.x = 0.0f;
		vec.y = 0.0f;
		return;
	case 12:
		vec.x = 1.0f;
		vec.y = 0.0f;
		return;
	case 13:
		vec.x = 0.0f;
		vec.y = -1.0f;
		return;
	case 14:
		vec.x = 0.0f;
		vec.y = 0.0f;
		return;
	case 15:
		vec.x = 0.0f;
		vec.y = 1.0f;
		return;
	case 16:
		vec.x = 0.0f;
		vec.y = 0.0f;
		return;
	default:	//�Ԃ����Ă��Ȃ�
		vec.x = 0.0f;
		vec.y = 0.0f;
		return;
	}

}