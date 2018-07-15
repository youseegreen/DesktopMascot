#include "World.h"
#include "DesktopMascot.h"
using namespace std;

//1時刻進める
void World::Update(Input &input) {
	for (auto object : objectList) {
		object->Update(input);
		//物体が世界に入っているかをcheck
		if (!(IsObjectInWorld(*object))) {	
			//物体が世界からでているならば、
			//DesktopMascotクラスにキャラをリセットするように要請
			DesktopMascot::ResetCharacter(object->GetName());
		}
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
				Object2D tmp(*(*object1));
				(*object1)->BehaviorOfCollision(*(*object2));
				(*object2)->BehaviorOfCollision(tmp);
			}
		}
	}
}

//壁を作る
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

//レンダリング
void World::Draw() {
	for (auto object : objectList) {
		object->Draw();
	}
}

//オブジェクトが世界に収まっているか
bool World::IsObjectInWorld(const Object2D &obj, const int margin) {
	//矩形の角点getする
	float x1, y1, x2, y2;
	obj.GetPosition(x1, y1);
	obj.GetSize(x2, y2);
	x2 += x1;
	y2 += y1;

	//x1,x2,y1,y2をもとに入っているかを判断する
	if (x2 < -margin)return false;		//世界の左にいる
	if (x1 > worldX + margin)return false;	//世界の右にいる
	if (y2 < -margin)return false;		//世界の上にいる
	if (y1 > worldY + margin)return false;	//世界の下にいる
	return true;
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
	float mass = (float)GetRand(10);
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