#pragma once
#include <DxLib.h>
#include "MyVector2f.h"
#include "DataSet.h"
#include <string>
using namespace std;

class Object2D {
protected:
	//名前
	const string name;

	//物理系
	float x, y, vx, vy, ax, ay, fx, fy, theta, mass, width, height;
	float ref, omega;	//反射率、角速度
	bool collisionFlag;	//当たり判定があるかないか	

	//描画系
	bool isDraw;	//描画するかどうか

public:
	//コンストラクタ
	Object2D(const string n, float tx, float ty, float tvx, float tvy, float tax, float tay,
		float tfx, float tfy, float ttheta, float tmass, float wid, float hei, bool colli, bool draw) :
		name(n), x(tx), y(ty), vx(tvx), vy(tvy), ax(tax), ay(tay), fx(tfx), fy(tfy),
		theta(ttheta), mass(tmass), width(wid), height(hei), collisionFlag(colli), isDraw(draw) {
		ref = 1.0f;
	}
	//デストラクタ	何もしなくて問題ない
	virtual ~Object2D() {};

	//コピー禁止⇒一時保持用に許可することにしました
	Object2D(const Object2D &ori) : name(ori.name){	//constは初めに
		x = ori.x; y = ori.y; vx = ori.vx; vy = ori.vy;
		ax = ori.ax; ay = ori.ay; fx = ori.fx; fy = ori.fy;
		theta = ori.theta; omega = ori.omega; mass = ori.mass;
		width = ori.width; height = ori.height; ref = ori.ref;
		collisionFlag = ori.collisionFlag;	//当たり判定があるかないか
		isDraw = ori.collisionFlag;	//描画するかどうか
	};
	void operator=(const Object2D &ori) {
		//名前引き継げない
		x = ori.x; y = ori.y; vx = ori.vx; vy = ori.vy;
		ax = ori.ax; ay = ori.ay; fx = ori.fx; fy = ori.fy;
		theta = ori.theta; omega = ori.omega; mass = ori.mass;
		width = ori.width; height = ori.height; ref = ori.ref;
		collisionFlag = ori.collisionFlag;	//当たり判定があるかないか
		isDraw = ori.collisionFlag;	//描画するかどうか
	};


public:
	const string GetName() const{ 
		return name; 
	}
	virtual void Update(Input &input) {}	//位置の更新を行う
	virtual void GetData() {}	//画像や音声ファイルをロード　このクラスは何もしない
	virtual void Draw() const {}	//レンダリング　このクラスは何もしない

									//ゲッター
	virtual void GetPosition(float &tx, float &ty) const {
		tx = x;
		ty = y;
	}
	virtual void GetSize(float &wid, float &hei) const {
		wid = width;
		hei = height;
	}

	//矩形物体二つがぶつかったかどうかだけを返す　下のやつの下位互換
	virtual bool IsCollision(const Object2D &other) const;

	//矩形物体2つがどうかぶっているかを数字で返す　ぶつかってない：0
	virtual int WhereCollision(const Object2D &other) const;

	//衝突してない場合も0返すので注意　IsCollisionで判定した後使うべき
	//相手に向かっていく方向の法線ベクトルを返す　よくわかりませんのは全部0にしたから修正して　
	virtual void GetNormalVector(const Object2D &other, Vector2f &vec) const; 

	//これ上のやつに入った時に呼んだほうがいいのかな?
	virtual void BehaviorOfCollision(const Object2D &other){
		
	}

protected:
	//物体にマウスが左クリックしているか?
	virtual bool IsLeftClick(Input &input) {
		if ((input.mouseX > x) && (input.mouseX < (x + width))
			&& (input.mouseY > y) && (input.mouseY < (y + height))
			&& input.mouseLeftState) return true;
		return false;
	}

	//物体の上でマウスがちょうど左クリックしたか?
	virtual bool IsLeftJustClicked(Input &input) {
		if ((input.mouseX > x) && (input.mouseX < (x + width))
			&& (input.mouseY > y) && (input.mouseY < (y + height))
			&& input.mouseLeftClicked) return true;
		return false;
	}

	//物体にマウスが右クリックしているか?
	virtual bool IsRightClick(Input &input) {
		if ((input.mouseX > x) && (input.mouseX < (x + width))
			&& (input.mouseY > y) && (input.mouseY < (y + height))
			&& input.mouseRightState) return true;
		return false;
	}

	//物体の上でマウスがちょうど右クリックしたか?
	virtual bool IsRightJustClicked(Input &input) {
		if ((input.mouseX > x) && (input.mouseX < (x + width))
			&& (input.mouseY > y) && (input.mouseY < (y + height))
			&& input.mouseRightClicked) return true;
		return false;
	}

	//物体の上にマウスが重なっているか
	virtual bool IsMouseOn(Input &input) {
		if ((input.mouseX > x) && (input.mouseX < (x + width))
			&& (input.mouseY > y) && (input.mouseY < (y + height))) return true;
		return false;
	}
};