#include "Character.h"


//�f�[�^�̎擾
void Character::GetData() {
	auto itr = charaDataList.find(name);
	if (itr == charaDataList.end())return;	//�f�[�^���Ȃ���΃��^�[��

	pointer2DataSet = &(charaDataList[name]);
	imgList = &(pointer2DataSet->imgList);
	sndList = &(pointer2DataSet->soundList);

	//nowImg��ύX�����Ƃ��ɂ́Awidth��height�ς���悤�ɂ���
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

