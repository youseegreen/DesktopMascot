#include "World.h"

//1時刻進める
void World::Update() {
	for (auto chara : charaList) {
		chara->Update();
	}

	//衝突したかの判定
	for (auto chara1 = charaList.begin(); chara1 != charaList.end(); ++chara1) {
		auto chara2 = chara1;
		++chara2;	
		for (chara2; chara2 != charaList.end(); ++chara2) {
			if ((*chara1)->IsCollision(*(*chara2))) {
				//ここその場で衝突関数呼ぶか、Updateで処理するか悩む
				//とりあえず衝突時の処理関数を呼び出す
				//元の状態保存しやなあかん　けど　コピーコンストラクタを設定しなあかん
				//auto tmp = chara2;
				(*chara1)->BehaviorOfCollision(*(*chara2));
				(*chara2)->BehaviorOfCollision(*(*chara1));

			}
		}
	}
}

//レンダリング
void World::Draw() {
	for (auto chara : charaList) {
		chara->Draw();
	}
}

//キャラがいなければ追加する
void World::AddCharacter(const char *name) {
	for (auto chara : charaList) {
		if (chara->GetName() == name)return;
	}
	int maxSpeed = 10;	//これかえたい
	float x = (float)GetRand(worldX);
	float y = (float)GetRand(worldY);
	float vx = (float)GetRand(maxSpeed);
	float vy = (float)GetRand(maxSpeed);
	float mass = 10.0f;
	float wid = 10.0f;
	float hei = 10.0f;
	charaList.push_back(new Character(name, x, y, vx, vy, mass, wid, hei, true, true));
}

//キャラがいれば削除する
void World::DeleteCharacter(const char *name) {
	for (auto chara = charaList.begin(); chara != charaList.end(); ++chara) {
		if ((*chara)->GetName() == name) {
			auto tmp = chara;
			charaList.erase(chara);
			delete *tmp;
		}
	}
}