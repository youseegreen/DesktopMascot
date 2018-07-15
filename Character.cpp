#include "Character.h"

//データの取得
void Character::GetData() {
	auto itr = charaDataList.find(name);
	if (itr == charaDataList.end())return;	//データがなければリターン

	pointer2DataSet = &(charaDataList[name]);
	imgList = &(pointer2DataSet->imgList);
	sndList = &(pointer2DataSet->soundList);

	//nowImgを変更したときには、widthとheight変えるようにする
	if (imgList->size() > 0) {
		nowImg = &((*imgList)[0]);
		width = nowImg->width;
		height = nowImg->height;
	}
}

void Character::Update(Input &input) {
	//クリックされていたらついていく
	if (IsLeftJustClicked(input)) {
		moveState = 1;
		collisionFlag = false;
	}
	//ついていく状態かつ左クリックされなくなれば動かなくする
	if (!(input.mouseLeftState)&&(moveState == 1)) {
		moveState = 2;
		collisionFlag = true;
	}
	//右クリックされたら動いたり動かなかったりするようにする
	if (IsRightJustClicked(input)) {
		moveState = (moveState == 0) ? 2 : 0;
		collisionFlag = true;
	}

	//右クリックでモードチェンジ、つかめるのは別モードにしたい

	switch (moveState) {
	case 1:		//マウスカーソルについていく
		x = input.mouseX - width * 0.3;
		y = input.mouseY - height * 0.3;
		break;
	case 2:		//静止する
		break;
	default:	//物理的な動き
		x += vx;
		y += vy;
		break;
	}
}


//衝突時の振る舞い　当たったら跳ね返るところを工夫したい
void Character::BehaviorOfCollision(const Object2D &other) {
	//法線ベクトルを得る	
	Vector2f N;
	GetNormalVector(other, N);	//相手物体方向長さ1

	//0ベクトルなら単に反射	　反射すると衝突繰り返すので一回コメントアウト
	if (N == 0.0f) {
	//	vx *= -1;
	//	vy *= -1;
		return;
	}

	//速度ベクトル
	Vector2f v(vx, vy);

	//向きが逆なら何もしない	←これいるかもしれんけど一回外す
	if (v*N < 0) return;		//←これわりと問題　一回当たった物体とは何回か接触判定なくすほうがよい

	//相手の情報をgetする　Object2D⇒Characterにする必要がある
	Character ene(other);
	Vector2f vene(ene.vx, ene.vy);

	//反射方向
	//相手が壁ならm2→∞にする　壁はmass = -1とする
	if (ene.mass == INT_MAX)
		v = -(1 + ref * ene.ref)*((v*N)*N) + v;
	else {
		v = (-ene.mass / (mass + ene.mass))*(1 + ref * ene.ref)
				*((v - vene)*N)*N + v;
	}
	vx = v.x;
	vy = v.y;
}