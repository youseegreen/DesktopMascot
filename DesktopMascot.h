#pragma once

#include <DxLib.h>
#include <string>
#include <memory>
#include "World.h"
#include "Button.h"


//管理クラス　キャラの生成はworldが行う
class DesktopMascot {
	static const int screenX;	//デスクトップのサイズ
	static const int screenY;
	static World *world;		//世界への参照
	static int omoteHandle;		//描画対象のハンドル
	static list<std::unique_ptr<Button>> buttonList;	//ボタン管理　このクラスで行う

	//インスタンス生成禁止	静的クラス
	DesktopMascot();

public:
	//初期化関数　必ず実行すること
	static void Initialize();

	//実行関数	メイン処理
	static void Execute();	

	//終了関数　必ず実行しよう
	static void End() {
		delete world;
		DxLib_End();
	}

	//エラーが起きたことをスクリーンに表示したい
	static void PrintError(){ 
		//エラーが起きたときここに書く
	}
};

