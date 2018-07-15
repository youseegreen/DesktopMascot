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

	//AI系
	int moveState;	//ついてくる　ランダムとかやる　intをenumにしたい

public:
	//コンストラクタ
	Character(const string n, float x, float y, float vx, float vy, float mass,
		float wid, float hei, bool colli, bool draw) :
		Object2D(n, x, y, vx, vy, 0, 0, 0, 0, 0, mass, wid, hei, colli, draw) {
		cout << "私は" << name << endl;
		GetData();
		moveState = 0;	//0：ランダム
	}

	//コピーコンストラクタ
	Character(const Character &chara) :Object2D(chara) {
		pointer2DataSet = chara.pointer2DataSet;
		imgList = chara.imgList;
		sndList = chara.sndList;
		nowImg = chara.nowImg;
		nowNum = chara.nowNum;
		moveState = chara.moveState;
	}
	//Object2Dの別オブジェクトを見るときのために　一時利用前提、Chara変数は何もしない
	Character(const Object2D &obj) :Object2D(obj) { }

	
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
	virtual void BehaviorOfCollision(const Object2D &other);
};