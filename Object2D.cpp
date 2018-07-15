#include "Object2D.h"


bool Object2D::IsCollision(const Object2D &other) const {
	if (!collisionFlag || !other.collisionFlag) return false;	//衝突フラグoffならfalse

	if (((x + width) <= other.x) || (x >= (other.x + other.width))
		|| ((y + height) <= other.y) || (y >= (other.y + other.height))) {
		//alpharegionあるならここでさらにif文作成
		return false;
	}
	return true;
}

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
int Object2D::WhereCollision(const Object2D &other) const {
	if (!IsCollision(other))return 0;	//当たっていないなら0を返す
	//この時点で当たっていることは確定
	int xnum, ynum;
	bool xspe = false;	
	bool yspe = false;

	//最後は絶対に1足す
	if ((other.x + other.width) >(x + width)) {
		if (x < other.x) {
			//1,4,7,10にしぼられる	3でわって1余り
			xnum = 0;
		}
		else {
			//2,5,8,11にしぼられる	3でわって2余り
			xnum = 1;
		}
	}
	else {
		//3,6,9,12   13,14,15,16にしぼられる
		if (x > other.x) {
			//3,6,9,12にしぼられる
			xnum = 2;
		}
		else {
			//13,14,15,16にしぼられる
			xspe = true;
		}
	}

	if ((other.y + other.height) > (y + height)) {
		//1～6  13,14にしぼられる
		if (y < other.y) {
			//1,2,3,13にしぼられる	3*0
			ynum = 0;
		}
		else {
			//4,5,6,14にしぼられる	3*1
			ynum = 1;
		}
	}
	else {
		//7～9,15  10,11,12,16にしぼられる
		if (y > other.y) {
			//7,8,9,15にしぼられる
			ynum = 2;
		}
		else {
			//10,11,12,16にしぼられる
			yspe = true;
		}
	}

	if (yspe && xspe)return 16;	//16済
	if (xspe) {	//yspe = false;
		return (13 + ynum);		//13,14,15済	
	}
	if (yspe) { //xspe = false;	//10,11,12済
		return (10 + xnum);
	}
	//yspe = xspe = false;		
	return (3 * ynum + xnum + 1);	//1～9済
}

//衝突してない場合も0返すので注意　IsCollisionで判定した後使うべき
//相手に向かっていく方向の法線ベクトルを返す　よくわかりませんのは全部0にしたから修正して　
void Object2D::GetNormalVector(const Object2D &other, Vector2f &vec) const {
	vec.x = vec.y = 0.0f;
	
	//衝突の仕方を見る
	int number = WhereCollision(other);

	//衝突の仕方によって場合分けする
	switch (number) {
	case 1:	//左上かぶっている
		vec.x = -other.y + y + height;
		vec.y = -other.x + x + width;
		vec.NormalizeSelf();
		return;
	case 3:
		vec.x = -y - height + other.y;
		vec.y = -x + other.x + other.width;
		vec.NormalizeSelf();
		return;
	case 7:
		vec.x = -other.y - other.height + y;
		vec.y = -other.x + x + width;
		vec.NormalizeSelf();
		return;
	case 9:
		vec.x = -other.y - other.height + y;
		vec.y = -other.x - other.width + x;
		vec.NormalizeSelf();
		return;
	case 2:
	case 13:
		vec.y = 1.0f;
		return;
	case 4:
	case 10:
		vec.x = 1.0f;
		return;
	case 6:
	case 12:
		vec.x = -1.0f;
		return;
	case 8:
	case 15:
		vec.y = -1.0f;
		return;
	case 11:
	case 14:
	case 5:		//全方位
	case 16:	//全方位
	default:	//ぶつかっていない
		return;
	}
}