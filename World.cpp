#include "World.h"

using namespace std;

//1�����i�߂�
void World::Update(Input &input) {
	for (auto object : objectList) {
		object->Update(input);
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
				//auto tmp = object2;
				(*object1)->BehaviorOfCollision(*(*object2));
				(*object2)->BehaviorOfCollision(*(*object1));
			}
		}
	}
}

//�ǂ����
void World::CreateWall() {
	int margin = 300;
	objectList.push_back(new DontMoveObjectNoImage
		("leftWall", -margin, 0, 0, 100, margin, worldY, true));
	objectList.push_back(new DontMoveObjectNoImage
		("rightWall", worldX, 0, 0, 100, margin, worldY, true));
	objectList.push_back(new DontMoveObjectNoImage
		("upWall", 0, -margin, 0, 100, worldX, margin, true));
	objectList.push_back(new DontMoveObjectNoImage
		("downWall", 0, worldY, 0, 100, worldX, margin, true));
}

//�����_�����O
void World::Draw() {
	for (auto object : objectList) {
		object->Draw();
	}
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
	float mass = 10.0f;
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