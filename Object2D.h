#pragma once
#include <DxLib.h>
#include "DataSet.h"

class Object2D {
protected:
	//名前
	const char *name;

	//物理系
	float x, y, vx, vy, ax, ay, fx, fy, theta, mass, width, height;
	bool collisionFrag;	//当たり判定があるかないか	

	//描画系
	bool isDraw;	//描画するかどうか

public:
	//コンストラクタ
	Object2D(const char *n, float tx, float ty, float tvx, float tvy, float tax, float tay,
		float tfx, float tfy, float ttheta, float tmass, float wid, float hei, bool colli, bool draw) :
		name(n), x(tx), y(ty), vx(tvx), vy(tvy), ax(tax), ay(tay), fx(tfx), fy(tfy),
		theta(ttheta), mass(tmass), width(wid), height(hei), collisionFrag(colli), isDraw(draw){

	}
	//デストラクタ	何もしなくて問題ない
	~Object2D() {};
private:
	//コピー禁止
	Object2D(const Object2D &ori) {};

public:
	const char *GetName() const{ return name; }
	virtual void Update() {};	//位置の更新を行う
	virtual void GetData() {}	//画像や音声ファイルをロード　このクラスは何もしない
	virtual bool IsCollision(Object2D &other) const{
		if (!collisionFrag || !other.collisionFrag) return false;	//衝突フラグoffならfalse

		if (((x + width) < other.x) || (x > (other.x + other.width))
			|| ((y + height) < other.y) || (y > (other.y + other.height))) {
			//alpharegionあるならここでさらにif文作成
			return false;
		}
		return true;
	}

	//これ上のやつに入った時に呼んだほうがいいのかな?
	virtual void BehaviorOfCollision(const Object2D &other){
		
	}
};