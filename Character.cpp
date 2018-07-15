#include "Character.h"

//�f�[�^�̎擾
void Character::GetData() {
	auto itr = charaDataList.find(name);
	if (itr == charaDataList.end())return;	//�f�[�^���Ȃ���΃��^�[��

	pointer2DataSet = &(charaDataList[name]);
	imgList = &(pointer2DataSet->imgList);
	sndList = &(pointer2DataSet->soundList);

	//nowImg��ύX�����Ƃ��ɂ́Awidth��height�ς���悤�ɂ���
	if (imgList->size() > 0) {
		nowImg = &((*imgList)[0]);
		width = nowImg->width;
		height = nowImg->height;
	}
}

void Character::Update(Input &input) {
	//�N���b�N����Ă�������Ă���
	if (IsLeftJustClicked(input)) {
		moveState = 1;
		collisionFlag = false;
	}
	//���Ă�����Ԃ����N���b�N����Ȃ��Ȃ�Γ����Ȃ�����
	if (!(input.mouseLeftState)&&(moveState == 1)) {
		moveState = 2;
		collisionFlag = true;
	}
	//�E�N���b�N���ꂽ�瓮�����蓮���Ȃ������肷��悤�ɂ���
	if (IsRightJustClicked(input)) {
		moveState = (moveState == 0) ? 2 : 0;
		collisionFlag = true;
	}

	//�E�N���b�N�Ń��[�h�`�F���W�A���߂�͕̂ʃ��[�h�ɂ�����

	switch (moveState) {
	case 1:		//�}�E�X�J�[�\���ɂ��Ă���
		x = input.mouseX - width * 0.3;
		y = input.mouseY - height * 0.3;
		break;
	case 2:		//�Î~����
		break;
	default:	//�����I�ȓ���
		x += vx;
		y += vy;
		break;
	}
}


//�Փˎ��̐U�镑���@���������璵�˕Ԃ�Ƃ�����H�v������
void Character::BehaviorOfCollision(const Object2D &other) {
	//�@���x�N�g���𓾂�	
	Vector2f N;
	GetNormalVector(other, N);	//���蕨�̕�������1

	//0�x�N�g���Ȃ�P�ɔ���	�@���˂���ƏՓˌJ��Ԃ��̂ň��R�����g�A�E�g
	if (N == 0.0f) {
	//	vx *= -1;
	//	vy *= -1;
		return;
	}

	//���x�x�N�g��
	Vector2f v(vx, vy);

	//�������t�Ȃ牽�����Ȃ�	�����ꂢ�邩������񂯂ǈ��O��
	if (v*N < 0) return;		//��������Ɩ��@��񓖂��������̂Ƃ͉��񂩐ڐG����Ȃ����ق����悢

	//����̏���get����@Object2D��Character�ɂ���K�v������
	Character ene(other);
	Vector2f vene(ene.vx, ene.vy);

	//���˕���
	//���肪�ǂȂ�m2�����ɂ���@�ǂ�mass = -1�Ƃ���
	if (ene.mass == INT_MAX)
		v = -(1 + ref * ene.ref)*((v*N)*N) + v;
	else {
		v = (-ene.mass / (mass + ene.mass))*(1 + ref * ene.ref)
				*((v - vene)*N)*N + v;
	}
	vx = v.x;
	vy = v.y;
}