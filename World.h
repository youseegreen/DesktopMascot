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

	//1時刻進める
	void Update();

	//レンダリング
	void Draw();

	//同じ名前のキャラクタは一体しか存在できない
	void AddCharacter(const char *name);
	void DeleteCharacter(const char *name);
};