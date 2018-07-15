#include "DesktopMascot.h"

#include <iostream>		
using namespace std;	

//静的メンバ変数定義
const int DesktopMascot::screenX = GetSystemMetrics(SM_CXSCREEN);
const int DesktopMascot::screenY = GetSystemMetrics(SM_CYSCREEN);
int DesktopMascot::threX1;
int DesktopMascot::threY1;
int DesktopMascot::threX2;
int DesktopMascot::threY2;
World *DesktopMascot::world;
int DesktopMascot::omoteHandle;
list<std::unique_ptr<PushButton>> DesktopMascot::buttonList;


//初期化処理
void DesktopMascot::Initialize() {
	cout << "Screen(X,Y) = ( " << screenX << " , " << screenY << " )" << endl << endl;

	//DXライブラリ初期化
	if (DxLib_Init() == -1) return;

	//ウィンドウの枠を消す　2
	SetWindowStyleMode(2);

	//ウィンドウの大きさを変える
	SetGraphMode(screenX, screenY, 32);

	//ウィンドウモードにする
	ChangeWindowMode(TRUE);

	//透明にする
	SetUseBackBufferTransColorFlag(TRUE);

	//画面ハンドル作る
	omoteHandle = MakeRGB8ColorSoftImage(screenX, screenY);

	//非アクティブ状態でも稼働させる
	SetAlwaysRunFlag(TRUE);

	//透過色を白に設定しダブルバッファリングを使う
	SetDrawScreen(DX_SCREEN_BACK);
	SetTransColor(255, 255, 255);

	//データセットの読み込み
	LoadAllData();

	//ワールド生成
	world = new World(screenX, screenY);

	//ボタンの生成	CharaNumによって変えていく
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

	//メインループ時にボタン表示するエリアを設定する
	const int margin = 100;
	threX1 = left - margin;
	threX2 = screenX - threX1;
	threY1 = offset - margin;
	threY2 = offset + size + margin;
}



//メイン処理
void DesktopMascot::Execute() {
	//ユーザー入力をゲットする変数
	Input input;

	//終了条件追加してもいいと思う
	while (ProcessMessage() == 0) {

		//ユーザー入力をゲットする　
		
		//今はマウスだけやが、キーボードとかもゲットしたい
		bool tmpLeft = ((GetMouseInput() & MOUSE_INPUT_LEFT)) ? true : false;
		input.mouseLeftClicked = (tmpLeft && !(input.mouseLeftState)) ? true : false;
		input.mouseLeftState = tmpLeft;

		bool tmpRight = ((GetMouseInput() & MOUSE_INPUT_RIGHT)) ? true : false;
		input.mouseRightClicked = (tmpRight && !(input.mouseRightState)) ? true : false;
		input.mouseRightState = tmpRight;

		GetMousePoint(&(input.mouseX), &(input.mouseY));

		//ボタンの管理ここで行う	コールバック関数を使用している　Button.h
		for (auto itr = buttonList.begin(); itr != buttonList.end(); itr++) {
			(*itr)->UpDate(input);
		}

		//世界を一時刻進める
		world->Update(input);

		//ボタンの描画
		//マウスカーソルがボタンに近い時だけ表示する
		if ((input.mouseX < threX2)&&(input.mouseX > threX1)&&
			(input.mouseY < threY2) && (input.mouseY > threY1)) {
			for (auto itr = buttonList.begin(); itr != buttonList.end(); itr++)
				(*itr)->Draw();
		}

		//世界の描画
		world->Draw();

		//ウィンドウを最前面に表示する
		// http://dixq.net/forum/viewtopic.php?f=3&t=10766
		HWND hWnd = GetMainWindowHandle();
		SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		//--

		//表示
		GetDrawScreenSoftImage(0, 0, screenX, screenY, omoteHandle);
		UpdateLayerdWindowForSoftImage(omoteHandle);

		//塗りなおし
		ClearDrawScreen();
		DrawBox(0, 0, screenX, screenY, GetColor(255, 255, 255), TRUE);
	}
}

//ボタンをリセット、worldからそのキャラを消す
void DesktopMascot::ResetCharacter(const string name) {
	for (auto itr = buttonList.begin(); itr != buttonList.end(); itr++) {
		//目的のボタンを探してリセット
		if ((*itr)->GetName() == name) {
			(*itr)->Reset();
			break;
		}
	}

	//worldにdelete申請
	world->DeleteCharacter(name);
}
