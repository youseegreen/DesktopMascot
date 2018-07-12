#pragma once
#pragma warning (disable:4244)
#include <map>
#include <vector>
#include <string>
#include <DxLib.h>

//画像の基本データ
struct Image {
	int imgHandle;		//画像へのハンドル
	int width, height;	//画像の横幅、縦幅	
	bool alphaFrag;		//透過画像かどうか
	bool *alpha;		//当たり判定の領域
	~Image() { if (alphaFrag) delete[] alpha; }
};

//音声の基本データ
struct Sound {

};

//キャラのデータとかを全部ここで集めておく
struct DataSet {
	std::vector<Image> imgList;
	std::vector<Sound> soundList;
};

//キャラのネームリスト
extern std::vector<std::string> charaNameList;

//キャラのデータを全部格納したマップ
extern std::map<std::string, DataSet> charaDataList;

//キャラのデータを全て読み込む関数
extern void LoadAllData();


struct Vector2f {
	float x;
	float y;
	void Normalize() {
		float s = sqrtf(x*x + y * y);
		x /= s;
		y /= s;
	}
	float operator*(const Vector2f &other)const {
		return (x * other.x + y * other.y);
	}
	Vector2f operator*(const float scalar)const {
		Vector2f ret = { x * scalar,y * scalar };
		return ret;
	}
	Vector2f operator-(const Vector2f &other)const {
		Vector2f ret = { x - other.x,y - other.y };
		return ret;
	}
};

//ユーザー入力のデータ構造
struct Input {
	int mouseX;
	int mouseY;
	bool mouseLeftState;
	bool mouseRightState;
};