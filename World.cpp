#include "World.h"

using namespace std;

//1時刻進める
void World::Update(Input &input) {
	for (auto object : objectList) {
		object->Update(input);
	}

	//衝突したかの判定
	for (auto object1 = objectList.begin(); object1 != objectList.end(); ++object1) {
		auto object2 = object1;
		++object2;	
		for (object2; object2 != objectList.end(); ++object2) {
			if ((*object1)->IsCollision(*(*object2))) {
				//ここその場で衝突関数呼ぶか、Updateで処理するか悩む
				//とりあえず衝突時の処理関数を呼び出す
				//元の状態保存しやなあかん　けど　コピーコンストラクタを設定しなあかん
				//auto tmp = object2;
				(*object1)->BehaviorOfCollision(*(*object2));
				(*object2)->BehaviorOfCollision(*(*object1));
			}
		}
	}
}

//壁を作る
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

//レンダリング
void World::Draw() {
	for (auto object : objectList) {
		object->Draw();
	}
}

//キャラがいなければ追加する
void World::AddCharacter(const string name) {
	for (auto object : objectList) {
		if (object->GetName() == name)return;
	}
	int maxSpeed = 5;	//これかえたい
	float x = (float)GetRand(0.8 * worldX);
	float y = (float)GetRand(0.8 * worldY);
	float vx = (float)GetRand(maxSpeed * 2) - maxSpeed;
	float vy = (float)GetRand(maxSpeed * 2) - maxSpeed;
	float mass = 10.0f;
	float wid = 10.0f;
	float hei = 10.0f;
	objectList.push_back(new Character(name, x, y, vx, vy, mass, wid, hei, true, true));
}

//キャラがいれば削除する
void World::DeleteCharacter(const string name) {
	for (auto object = objectList.begin(); object != objectList.end(); ++object) {
		if ((*object)->GetName() == name) {
			auto tmp = object;
			objectList.erase(object);
			delete *tmp;
		}
	}
}