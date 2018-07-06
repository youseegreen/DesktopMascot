#pragma once
#include "Object2D.h"

//これを派生して背景オブジェクト作ればよいと思う

//壁やみえない壁専用　当たられても場所が変わらない
class DontMoveObjectNoImage :public Object2D {


public:
	DontMoveObjectNoImage(const char *n, float x, float y, float theta,
		float mass, float wid, float hei, bool colli) :
		Object2D(n, x, y, 0, 0, 0, 0, 0, 0, theta, mass, wid, hei, colli, false) {
	}

	virtual void GetData() { 
		//何もしない
	}

	//更新
	virtual void Update() {
		//何もしない　存在するだけ
	}

	//レンダリング　
	virtual void Draw()const {
		//何もしない　存在するだけ
	}
};