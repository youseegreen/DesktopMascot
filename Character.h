#pragma once

#include "Object2D.h"
#include <iostream>
using namespace std;

//キャラクター基本形
class Character : public Object2D {
	//画像系
	DataSet *pointer2DataSet;		//データセットへの参照
	std::vector<Image> *imgList;	//たくさんの画像データへの参照
	std::vector<Sound> *sndList;	//たくさんの音声データへの参照

	Image *nowImg;		//現在参照中のイメージ
	int nowNum;			//現在の番号

public:
	//コンストラクタ
	Character(const string n, float x, float y, float vx, float vy, float mass,
		float wid, float hei, bool colli, bool draw) :
		Object2D(n, x, y, vx, vy, 0, 0, 0, 0, 0, mass, wid, hei, colli, draw) {
		cout << "私は" << name << endl;
		GetData();
	}
	
	//DataSet.hからChaeacterに必要な全データ拾ってくる
	virtual void GetData();

	//update
	virtual void Update(Input &input); 

	//レンダリング
	virtual void Draw() const {
		if (nowImg->imgHandle == -1)return;
		DrawGraph(x, y, nowImg->imgHandle, TRUE);
	}

	//衝突時の振る舞い
	virtual void BehaviorOfCollision(const Object2D &other) {
		
		//法線ベクトルを得る
		Vector2f N;
		GetNormalVector(other, N);

		//0ベクトルなら単に反射
		if ((N.x == 0) && (N.y == 0)) {
			vx *= -1;
			vy *= -1;
			return;
		}

		//速度ベクトルの逆ベクトル
		Vector2f v = { -vx,-vy };

		//向きが逆なら何もしない
		if (v*N <= 0) return;

		//反射方向
		Vector2f R = N * (2 * (v * N)) - v;
		vx = R.x;
		vy = R.y;
	}
};