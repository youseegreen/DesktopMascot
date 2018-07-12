#pragma once
#include "Character.h"
#include "DontMoveObject.h"
#include <list>

using namespace std;

class World {
private:
	const int worldX;
	const int worldY;
	list<Object2D *> objectList;	//Chara��DontMove�����邩����


public:
	World(int screenX, int screenY) :worldX(screenX), worldY(screenY) {
		//�Ǎ��
		CreateWall();
	}

	~World() {
		objectList.clear();
	}

	//�ǂ�z�u����
	void CreateWall();

	//1�����i�߂�
	virtual void Update(Input &input);

	//�����_�����O
	void Draw();

	//�������O�̃L�����N�^�͈�̂������݂ł��Ȃ�
	void AddCharacter(const string name);
	void DeleteCharacter(const string name);
};