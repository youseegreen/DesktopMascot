#include "World.h"
#include "DesktopMascot.h"
using namespace std;

//1�����i�߂�
void World::Update(Input &input) {
	for (auto object : objectList) {
		object->Update(input);
		//���̂����E�ɓ����Ă��邩��check
		if (!(IsObjectInWorld(*object))) {	
			//���̂����E����łĂ���Ȃ�΁A
			//DesktopMascot�N���X�ɃL���������Z�b�g����悤�ɗv��
			DesktopMascot::ResetCharacter(object->GetName());
		}
	}

	//�Փ˂������̔���
	for (auto object1 = objectList.begin(); object1 != objectList.end(); ++object1) {
		auto object2 = object1;
		++object2;	
		for (object2; object2 != objectList.end(); ++object2) {
			if ((*object1)->IsCollision(*(*object2))) {
				//�������̏�ŏՓˊ֐��ĂԂ��AUpdate�ŏ������邩�Y��
				//�Ƃ肠�����Փˎ��̏����֐����Ăяo��
				//���̏�ԕۑ�����Ȃ�����@���ǁ@�R�s�[�R���X�g���N�^��ݒ肵�Ȃ�����
				Object2D tmp(*(*object1));
				(*object1)->BehaviorOfCollision(*(*object2));
				(*object2)->BehaviorOfCollision(tmp);
			}
		}
	}
}

//�ǂ����
void World::CreateWall() {
	float margin = 300;
	objectList.push_back(new DontMoveObjectNoImage
		("leftWall", -margin, 0.0f, 0.0f, INT_MAX, margin, worldY, true));
	objectList.push_back(new DontMoveObjectNoImage
		("rightWall", worldX, 0.0f, 0.0f, INT_MAX, margin, worldY, true));
	objectList.push_back(new DontMoveObjectNoImage
		("upWall", 0.0f, -margin, 0.0f, INT_MAX, worldX, margin, true));
	objectList.push_back(new DontMoveObjectNoImage
		("downWall", 0.0f, worldY, 0.0f, INT_MAX, worldX, margin, true));
}

//�����_�����O
void World::Draw() {
	for (auto object : objectList) {
		object->Draw();
	}
}

//�I�u�W�F�N�g�����E�Ɏ��܂��Ă��邩
bool World::IsObjectInWorld(const Object2D &obj, const int margin) {
	//��`�̊p�_get����
	float x1, y1, x2, y2;
	obj.GetPosition(x1, y1);
	obj.GetSize(x2, y2);
	x2 += x1;
	y2 += y1;

	//x1,x2,y1,y2�����Ƃɓ����Ă��邩�𔻒f����
	if (x2 < -margin)return false;		//���E�̍��ɂ���
	if (x1 > worldX + margin)return false;	//���E�̉E�ɂ���
	if (y2 < -margin)return false;		//���E�̏�ɂ���
	if (y1 > worldY + margin)return false;	//���E�̉��ɂ���
	return true;
}

//�L���������Ȃ���Βǉ�����
void World::AddCharacter(const string name) {
	for (auto object : objectList) {
		if (object->GetName() == name)return;
	}
	int maxSpeed = 5;	//���ꂩ������
	float x = (float)GetRand(0.8 * worldX);
	float y = (float)GetRand(0.8 * worldY);
	float vx = (float)GetRand(maxSpeed * 2) - maxSpeed;
	float vy = (float)GetRand(maxSpeed * 2) - maxSpeed;
	float mass = (float)GetRand(10);
	float wid = 10.0f;
	float hei = 10.0f;
	objectList.push_back(new Character(name, x, y, vx, vy, mass, wid, hei, true, true));
}

//�L����������΍폜����
void World::DeleteCharacter(const string name) {
	for (auto object = objectList.begin(); object != objectList.end(); ++object) {
		if ((*object)->GetName() == name) {
			auto tmp = object;
			objectList.erase(object);
			delete *tmp;
		}
	}
}