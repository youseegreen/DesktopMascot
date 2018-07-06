#pragma once
#include "Character.h"
#include <list>

using namespace std;

class World {
private:
	const int worldX;
	const int worldY;
	list<Character *> charaList;


public:
	World(int screenX, int screenY) :worldX(screenX), worldY(screenY) {

	}

	//1�����i�߂�
	void Update();

	//�����_�����O
	void Draw();

	//�������O�̃L�����N�^�͈�̂������݂ł��Ȃ�
	void AddCharacter(const char *name);
	void DeleteCharacter(const char *name);
};