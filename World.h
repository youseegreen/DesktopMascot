#pragma once
#include "Character.h"
#include "DontMoveObject.h"
#include <list>

using namespace std;

class World {
private:
	const int worldX;
	const int worldY;
	list<Object2D *> objectList;	//CharaとDontMove分けるか迷う


public:
	World(int screenX, int screenY) :worldX(screenX), worldY(screenY) {
		//壁作る
		CreateWall();
	}

	~World() {
		objectList.clear();
	}

	//壁を配置する
	void CreateWall();

	//1時刻進める
	virtual void Update(Input &input);

	//レンダリング
	void Draw();

	//世界内にオブジェクトがいるかチェック　マージンは20
	bool IsObjectInWorld(const Object2D &obj, const int margin = 5);

	//同じ名前のキャラクタは一体しか存在できない
	void AddCharacter(const string name);
	void DeleteCharacter(const string name);
};