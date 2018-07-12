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
//	if(IsLeftClick(input))

	x += vx;
	y += vy;
}

