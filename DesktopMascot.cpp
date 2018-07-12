#include "DesktopMascot.h"

#include <iostream>		
using namespace std;	

//静的メンバ変数定義
const int DesktopMascot::screenX = GetSystemMetrics(SM_CXSCREEN);
const int DesktopMascot::screenY = GetSystemMetrics(SM_CYSCREEN);
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

	//ボタンの生成	Charaフォルダ⇒名前の数生成したい
	int y = 0, size = 100;
	for (auto cName : charaNameList) {
		y++;
		buttonList.push_back(std::unique_ptr<PushButton>
			(new PushButton(cName, 0, y * size, size, size, true,
				[](const string name) {world->AddCharacter(name); },
				[](const string name) {world->DeleteCharacter(name); })));
	}
}



//メイン処理
void DesktopMascot::Execute() {
	//終了条件追加してもいいと思う
	while (ProcessMessage() == 0) {

		//ユーザー入力をゲットする　
		Input input;
		//今はマウスだけやが、キーボードとかもゲットしたい
		input.mouseLeftState = ((GetMouseInput() & MOUSE_INPUT_LEFT)) ? true : false;
		GetMousePoint(&(input.mouseX), &(input.mouseY));

		//ボタンの管理ここで行う	コールバック関数を使用している　Button.h
		for (auto itr = buttonList.begin(); itr != buttonList.end(); itr++) {
			(*itr)->UpDate(input);
		}

		//世界を一時刻進める
		world->Update(input);

		//ボタンの描画
		//マウスカーソルがボタンに近い時だけ表示する
		if ((input.mouseX < 300)&&(input.mouseX > 0)) {
			for (auto itr = buttonList.begin(); itr != buttonList.end(); itr++)
				(*itr)->Draw();
		}
		//世界の描画
		world->Draw();

		//表示
		GetDrawScreenSoftImage(0, 0, screenX, screenY, omoteHandle);
		UpdateLayerdWindowForSoftImage(omoteHandle);

		//塗りなおし
		ClearDrawScreen();
		DrawBox(0, 0, screenX, screenY, GetColor(255, 255, 255), TRUE);
	}
}


