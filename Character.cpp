#include "Character.h"


//データの取得
void Character::GetData() {
	auto itr = charaDataList.find(name);
	if (itr == charaDataList.end())return;

	pointer2DataSet = &(charaDataList[name]);
	imgList = &(pointer2DataSet->imgList);
	sndList = &(pointer2DataSet->soundList);

	if (imgList->size() > 0) {
		nowImg = &((*imgList)[0]);
	}
}

void Character::Update() {
	//初めは衝突判定があれば反転するフラグだけ入れる?
	x += vx;
	y += vy;
}

