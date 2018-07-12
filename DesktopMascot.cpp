#include "DesktopMascot.h"

#include <iostream>		
using namespace std;	

//�ÓI�����o�ϐ���`
const int DesktopMascot::screenX = GetSystemMetrics(SM_CXSCREEN);
const int DesktopMascot::screenY = GetSystemMetrics(SM_CYSCREEN);
World *DesktopMascot::world;
int DesktopMascot::omoteHandle;
list<std::unique_ptr<PushButton>> DesktopMascot::buttonList;


//����������
void DesktopMascot::Initialize() {
	cout << "Screen(X,Y) = ( " << screenX << " , " << screenY << " )" << endl << endl;

	//DX���C�u����������
	if (DxLib_Init() == -1) return;

	//�E�B���h�E�̘g�������@2
	SetWindowStyleMode(2);

	//�E�B���h�E�̑傫����ς���
	SetGraphMode(screenX, screenY, 32);

	//�E�B���h�E���[�h�ɂ���
	ChangeWindowMode(TRUE);

	//�����ɂ���
	SetUseBackBufferTransColorFlag(TRUE);

	//��ʃn���h�����
	omoteHandle = MakeRGB8ColorSoftImage(screenX, screenY);

	//��A�N�e�B�u��Ԃł��ғ�������
	SetAlwaysRunFlag(TRUE);

	//���ߐF�𔒂ɐݒ肵�_�u���o�b�t�@�����O���g��
	SetDrawScreen(DX_SCREEN_BACK);
	SetTransColor(255, 255, 255);

	//�f�[�^�Z�b�g�̓ǂݍ���
	LoadAllData();

	//���[���h����
	world = new World(screenX, screenY);

	//�{�^���̐���	Chara�t�H���_�˖��O�̐�����������
	int y = 0, size = 100;
	for (auto cName : charaNameList) {
		y++;
		buttonList.push_back(std::unique_ptr<PushButton>
			(new PushButton(cName, 0, y * size, size, size, true,
				[](const string name) {world->AddCharacter(name); },
				[](const string name) {world->DeleteCharacter(name); })));
	}
}



//���C������
void DesktopMascot::Execute() {
	//�I�������ǉ����Ă������Ǝv��
	while (ProcessMessage() == 0) {

		//���[�U�[���͂��Q�b�g����@
		Input input;
		//���̓}�E�X�����₪�A�L�[�{�[�h�Ƃ����Q�b�g������
		input.mouseLeftState = ((GetMouseInput() & MOUSE_INPUT_LEFT)) ? true : false;
		GetMousePoint(&(input.mouseX), &(input.mouseY));

		//�{�^���̊Ǘ������ōs��	�R�[���o�b�N�֐����g�p���Ă���@Button.h
		for (auto itr = buttonList.begin(); itr != buttonList.end(); itr++) {
			(*itr)->UpDate(input);
		}

		//���E���ꎞ���i�߂�
		world->Update(input);

		//�{�^���̕`��
		//�}�E�X�J�[�\�����{�^���ɋ߂��������\������
		if ((input.mouseX < 300)&&(input.mouseX > 0)) {
			for (auto itr = buttonList.begin(); itr != buttonList.end(); itr++)
				(*itr)->Draw();
		}
		//���E�̕`��
		world->Draw();

		//�\��
		GetDrawScreenSoftImage(0, 0, screenX, screenY, omoteHandle);
		UpdateLayerdWindowForSoftImage(omoteHandle);

		//�h��Ȃ���
		ClearDrawScreen();
		DrawBox(0, 0, screenX, screenY, GetColor(255, 255, 255), TRUE);
	}
}


