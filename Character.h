#pragma once

#include "Object2D.h"

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
	Character(const char *n, float x, float y, float vx, float vy, float mass,
		float wid, float hei, bool colli, bool draw) :
		Object2D(n, x, y, vx, vy, 0, 0, 0, 0, 0, mass, wid, hei, colli, draw) {

	}
	
	//DataSet.hからChaeacterに必要な全データ拾ってくる
	virtual void GetData();

	//update
	virtual void Update(); 

	//レンダリング
	virtual void Draw() const {
		if (nowImg->imgHandle != 1)return;
		DrawGraph(x, y, nowImg->imgHandle, TRUE);
	}

	//衝突時の振る舞い
	virtual void BehaviorOfCollision(Object2D &other) {
		vx *= -1;
		vy *= -1;
	}
};