#pragma once
#include "Object2D.h"

//AddCharaかDeleteCharaいれるためのやつ
typedef  void(*FUNCTION_POINTER)(const char *name);

//立下りボタン
class Button : public Object2D {
	Image img[2];	//onとoff
	bool state;		//on or off
	bool prev;		//一時刻前のマウスのクリック状態

	FUNCTION_POINTER fp;	//関数ポインタ
	bool callBackFrag;		//コールバック関数を使うかどうか

public:
	Button(const char *cName, float x, float y, 
			float wid, float hei, bool draw, FUNCTION_POINTER f = NULL) :
		Object2D(cName, x, y, 0, 0, 0,0,0,0,0,0,wid, hei, false, draw) {
		if (f != NULL) { fp = f; callBackFrag = true; }
		else { fp = NULL; callBackFrag = false; }
	}

	//データは何もない
	virtual void GetData(){}

	virtual bool OnOff() const{ return state; }

	//毎ループごとに呼び出す　stateにOnかOffか入れる
	virtual void UpDate(int mouseX, int mouseY, bool mouseState) {
		//ボタンは動かない
		if (IsIn(mouseX, mouseY)) {
			if (prev && !mouseState) {
				state = true;
				prev = false;
			}
			else if (mouseState) {
				prev = true;
				state = false;
			}
			else if (!prev && !mouseState) {
				prev = false;
				state = false;
			}
		}
		else {
			prev = false;
			state = false;
		}

		//コールバック関数の実行	今の場合キャラの追加or削除
		if (state)
			if(fp != NULL) fp(name);
	}

	//今のところ画像を入れる予定はないので、DrawBoxでつくる
	virtual void Draw() const{
		if (prev) {
			DrawBox(x, y, width, height, 0xFF0000, TRUE);
		}
		else {
			DrawBox(x, y, width, height, 0x0000FF, TRUE);
		}
	}

private:
	//マウスの位置が入っているかどうか
	bool IsIn(int mx, int my) const {
		if ((mx > x) && (mx < (x + width)) && (my > y) && (my < (y + height))) return true;
		return false;
	}
};