#include "DesktopMascot.h"

#include <iostream>		
using namespace std;	

//�ÓI�����o�ϐ���`
const int DesktopMascot::screenX = GetSystemMetrics(SM_CXSCREEN);
const int DesktopMascot::screenY = GetSystemMetrics(SM_CYSCREEN);
int DesktopMascot::threX1;
int DesktopMascot::threY1;
int DesktopMascot::threX2;
int DesktopMascot::threY2;
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

	//�{�^���̐���	CharaNum�ɂ���ĕς��Ă���
	const int charaNum = (int)charaNameList.size();
	const int space = 100, size = 90, offset = screenY - 200;
	const int left = (screenX - space * charaNum) / 2;
	int i = 0;
	for (auto cName : charaNameList) {
		
		buttonList.push_back(std::unique_ptr<PushButton>
			(new PushButton(cName, left + i * space + (space - size)/2, 
				offset, size, size, true,
				[](const string name) { world->AddCharacter(name); },
				[](const string name) { world->DeleteCharacter(name); })));
		i++;
	}

	//���C�����[�v���Ƀ{�^���\������G���A��ݒ肷��
	const int margin = 100;
	threX1 = left - margin;
	threX2 = screenX - threX1;
	threY1 = offset - margin;
	threY2 = offset + size + margin;
}



//���C������
void DesktopMascot::Execute() {
	//���[�U�[���͂��Q�b�g����ϐ�
	Input input;

	//�I�������ǉ����Ă������Ǝv��
	while (ProcessMessage() == 0) {

		//���[�U�[���͂��Q�b�g����@
		
		//���̓}�E�X�����₪�A�L�[�{�[�h�Ƃ����Q�b�g������
		bool tmpLeft = ((GetMouseInput() & MOUSE_INPUT_LEFT)) ? true : false;
		input.mouseLeftClicked = (tmpLeft && !(input.mouseLeftState)) ? true : false;
		input.mouseLeftState = tmpLeft;

		bool tmpRight = ((GetMouseInput() & MOUSE_INPUT_RIGHT)) ? true : false;
		input.mouseRightClicked = (tmpRight && !(input.mouseRightState)) ? true : false;
		input.mouseRightState = tmpRight;

		GetMousePoint(&(input.mouseX), &(input.mouseY));

		//�{�^���̊Ǘ������ōs��	�R�[���o�b�N�֐����g�p���Ă���@Button.h
		for (auto itr = buttonList.begin(); itr != buttonList.end(); itr++) {
			(*itr)->UpDate(input);
		}

		//���E���ꎞ���i�߂�
		world->Update(input);

		//�{�^���̕`��
		//�}�E�X�J�[�\�����{�^���ɋ߂��������\������
		if ((input.mouseX < threX2)&&(input.mouseX > threX1)&&
			(input.mouseY < threY2) && (input.mouseY > threY1)) {
			for (auto itr = buttonList.begin(); itr != buttonList.end(); itr++)
				(*itr)->Draw();
		}

		//���E�̕`��
		world->Draw();

		//�E�B���h�E���őO�ʂɕ\������
		// http://dixq.net/forum/viewtopic.php?f=3&t=10766
		HWND hWnd = GetMainWindowHandle();
		SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		//--

		//�\��
		GetDrawScreenSoftImage(0, 0, screenX, screenY, omoteHandle);
		UpdateLayerdWindowForSoftImage(omoteHandle);

		//�h��Ȃ���
		ClearDrawScreen();
		DrawBox(0, 0, screenX, screenY, GetColor(255, 255, 255), TRUE);
	}
}

//�{�^�������Z�b�g�Aworld���炻�̃L����������
void DesktopMascot::ResetCharacter(const string name) {
	for (auto itr = buttonList.begin(); itr != buttonList.end(); itr++) {
		//�ړI�̃{�^����T���ă��Z�b�g
		if ((*itr)->GetName() == name) {
			(*itr)->Reset();
			break;
		}
	}

	//world��delete�\��
	world->DeleteCharacter(name);
}
