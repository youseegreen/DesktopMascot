#include "Character.h"


//�f�[�^�̎擾
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
	//���߂͏Փ˔��肪����Δ��]����t���O���������?
	x += vx;
	y += vy;
}

