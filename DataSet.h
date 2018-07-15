#pragma once
#pragma warning (disable:4244)
#include <map>
#include <vector>
#include <string>
#include <DxLib.h>

//�摜�̊�{�f�[�^
struct Image {
	int imgHandle;		//�摜�ւ̃n���h��
	int width, height;	//�摜�̉����A�c��	
	bool alphaFlag;		//���߉摜���ǂ���
	bool *alpha;		//�����蔻��̗̈�
	~Image() { if (alphaFlag) delete[] alpha; }
};

//�����̊�{�f�[�^
struct Sound {

};

//�L�����̃f�[�^�Ƃ���S�������ŏW�߂Ă���
struct DataSet {
	std::vector<Image> imgList;
	std::vector<Sound> soundList;
};

//�L�����̃l�[�����X�g
extern std::vector<std::string> charaNameList;

//�L�����̃f�[�^��S���i�[�����}�b�v
extern std::map<std::string, DataSet> charaDataList;

//�L�����̃f�[�^��S�ēǂݍ��ފ֐�
extern void LoadAllData();

//���[�U�[���͂̃f�[�^�\��
struct Input {
	int mouseX;
	int mouseY;
	bool mouseLeftState;
	bool mouseRightState;
	bool mouseLeftClicked = false;
	bool mouseRightClicked = false;
};