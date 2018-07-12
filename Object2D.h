#pragma once
#include <DxLib.h>
#include "DataSet.h"
#include <string>
using namespace std;

class Object2D {
protected:
	//名前
	const string name;

	//物理系
	float x, y, vx, vy, ax, ay, fx, fy, theta, mass, width, height;
	bool collisionFrag;	//当たり判定があるかないか	

	//描画系
	bool isDraw;	//描画するかどうか

public:
	//コンストラクタ
	Object2D(const string n, float tx, float ty, float tvx, float tvy, float tax, float tay,
		float tfx, float tfy, float ttheta, float tmass, float wid, float hei, bool colli, bool draw) :
		name(n), x(tx), y(ty), vx(tvx), vy(tvy), ax(tax), ay(tay), fx(tfx), fy(tfy),
		theta(ttheta), mass(tmass), width(wid), height(hei), collisionFrag(colli), isDraw(draw) {
	}
	//デストラクタ	何もしなくて問題ない
	~Object2D() {};
private:
	//コピー禁止
	Object2D(const Object2D &ori) {};

public:
	const string GetName() const{ 
		return name; 
	}
	virtual void Update(Input &input) {}	//位置の更新を行う
	virtual void GetData() {}	//画像や音声ファイルをロード　このクラスは何もしない
	virtual void Draw() const {}	//レンダリング　このクラスは何もしない

	//矩形物体二つがぶつかったかどうかだけを返す　下のやつの下位互換
	virtual bool IsCollision(const Object2D &other) const;

	//矩形物体2つがどうかぶっているかを数字で返す
	/*数字の返し方*/
	/*かぶっていない⇒0*/
	/*呼び出し側が、引数側の...*/
	/*１：左上でかぶっている
	  ２：真上でかぶっている
	　３：右上でかぶっている
	  ４：左横でかぶっている
	  ５：引数側に囲まれている
	  ６：右横でかぶっている
	  ７：左下でかぶっている
	  ８：真下でかぶっている
	  ９：右下でかぶっている
	  10：左覆っている
	  11：真ん中縦に覆っている
	  12：右覆っている
	  13：上覆っている
	  14：真ん中横に覆っている
	  15：下覆っている
	  16：囲んでいる　　　*/
	virtual int WhereCollision(const Object2D &other) const;

	//ぶつかっていることがわかっている状況で、法線ベクトルを返す
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

	//物体にマウスが右クリックしているか?
	virtual bool IsRightClick(Input &input) {
		if ((input.mouseX > x) && (input.mouseX < (x + width))
			&& (input.mouseY > y) && (input.mouseY < (y + height))
			&& input.mouseRightState) return true;
		return false;
	}

	//物体の上にマウスが重なっているか
	virtual bool IsMouseOn(Input &input) {
		if ((input.mouseX > x) && (input.mouseX < (x + width))
			&& (input.mouseY > y) && (input.mouseY < (y + height))) return true;
		return false;
	}
};