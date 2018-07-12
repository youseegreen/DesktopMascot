#pragma once
#include "Object2D.h"
#include <iostream>

//AddCharaかDeleteCharaいれるためのやつ
typedef  void(*FUNCTION_POINTER)(const string name);

//プッシュスイッチ
class PushButton : public Object2D {
//	Image img[2];	//onとoff
	bool state;		//現在OnかOffかを示す
	bool prev;		//立下り検出用

	//関数ポインタ
	FUNCTION_POINTER onFunc;	//Off⇒関数ポインタ
	FUNCTION_POINTER offFunc;	//On⇒Offなった時に呼ばれる
	bool callBackFrag;		//コールバック関数を使うかどうか

public:
	PushButton(const string cName, float x, float y,
		float wid, float hei,bool draw, 
		FUNCTION_POINTER fon = NULL,FUNCTION_POINTER foff = NULL) :
		Object2D(cName, x, y, 0, 0, 0, 0, 0, 0, 0, 0, wid, hei, false, draw) {
		state = false;
		prev = false;
		if (fon != NULL) { 
			 onFunc = fon;
			 offFunc = foff;
			 callBackFrag = true;
		}
		else { 
			onFunc = NULL;
			offFunc = NULL;
			callBackFrag = false;
		}
	}

	//データは何もない　
	virtual void GetData() {}

	//現在の状態
	virtual bool OnOff() const { return state; }

	//コールバック関数を登録してない時の処理まだ
	//この関数はめっちゃ簡略化できるけど、今後のために詳しく書いてある
	//毎ループごとに呼び出す　立下りと立ち上がりを検出する
	virtual void UpDate(Input &input) {
		if (IsMouseOn(input)) {	//マウスがかぶっているか?
			//かぶっているならば

			if (!prev && input.mouseLeftState) {
				//前時刻で押されていずに、現在時刻で押されている
				//(クリック発生)ならば
				//トグル反転を行う
				state = !state;
				prev = input.mouseLeftState;

				//さらにコールバック関数を呼ぶ
				if (callBackFrag) {
					if (state)onFunc(name);	//off⇒on関数
					if (!state)offFunc(name);	//on⇒off関数
				}
			}
			else if (prev && input.mouseLeftState) {
				//前時刻も現在時刻も押されている
				//(おしっぱ)ならば
				//現状保持
				state = state;
				prev = input.mouseLeftState;
			}
			else if (!prev && !(input.mouseLeftState)) {
				//前時刻も現在時刻も押されていない
				//(マウスがボタンの上にあるだけ)ならば
				//現状保持
				state = state;
				prev = input.mouseLeftState;
			}
			else if (prev && !(input.mouseLeftState)) {
				//前時刻押されていて現時刻押されていない
				//(手が離された)ならば
				//ステート保持してprevを変更
				state = state;
				prev = input.mouseLeftState;
			}
		}
		else {
			state = state;
			prev = input.mouseLeftState;
		}
	}

	//今のところ画像を入れる予定はないので、DrawBoxでつくる
	virtual void Draw() const {
		if (state) {	//スイッチがon（へこんでいる）
			DrawBox(x, y, x + width, y + height, 0xFFFF, TRUE);
		}
		else {			//スイッチがoff
			DrawBox(x, y, x + width, y + height, 0x00FF, TRUE);
		}
	}

private:

	/*
	//マウスの位置が入っているかどうか
	bool IsIn(int &mx, int &my) const {
		if ((mx > x) && (mx < (x + width)) && (my > y) && (my < (y + height))) return true;
		return false;
	}
	*/
};