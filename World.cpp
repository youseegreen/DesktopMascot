#include "World.h"

//1�����i�߂�
void World::Update() {
	for (auto chara : charaList) {
		chara->Update();
	}

	//�Փ˂������̔���
	for (auto chara1 = charaList.begin(); chara1 != charaList.end(); ++chara1) {
		auto chara2 = chara1;
		++chara2;	
		for (chara2; chara2 != charaList.end(); ++chara2) {
			if ((*chara1)->IsCollision(*(*chara2))) {
				//�������̏�ŏՓˊ֐��ĂԂ��AUpdate�ŏ������邩�Y��
				//�Ƃ肠�����Փˎ��̏����֐����Ăяo��
				//���̏�ԕۑ�����Ȃ�����@���ǁ@�R�s�[�R���X�g���N�^��ݒ肵�Ȃ�����
				//auto tmp = chara2;
				(*chara1)->BehaviorOfCollision(*(*chara2));
				(*chara2)->BehaviorOfCollision(*(*chara1));

			}
		}
	}
}

//�����_�����O
void World::Draw() {
	for (auto chara : charaList) {
		chara->Draw();
	}
}

//�L���������Ȃ���Βǉ�����
void World::AddCharacter(const char *name) {
	for (auto chara : charaList) {
		if (chara->GetName() == name)return;
	}
	int maxSpeed = 10;	//���ꂩ������
	float x = (float)GetRand(worldX);
	float y = (float)GetRand(worldY);
	float vx = (float)GetRand(maxSpeed);
	float vy = (float)GetRand(maxSpeed);
	float mass = 10.0f;
	float wid = 10.0f;
	float hei = 10.0f;
	charaList.push_back(new Character(name, x, y, vx, vy, mass, wid, hei, true, true));
}

//�L����������΍폜����
void World::DeleteCharacter(const char *name) {
	for (auto chara = charaList.begin(); chara != charaList.end(); ++chara) {
		if ((*chara)->GetName() == name) {
			auto tmp = chara;
			charaList.erase(chara);
			delete *tmp;
		}
	}
}