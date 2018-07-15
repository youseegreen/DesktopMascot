#include <iostream>
#include "FileFolderStream.h"
#include "DataSet.h"

using namespace std;

//データリスト変数　定義
std::map<std::string, DataSet> charaDataList;

//ネームリスト変数　定義
std::vector<std::string> charaNameList;


void LoadAllData() {
	//Charaファルダ内のすべてのフォルダの名前をゲットする
	MyFFStream::GetDirectoryName("Chara", charaNameList);
	cout << "読み込んだキャラ一覧" << endl;
	for(auto chara : charaNameList)
		cout << chara.c_str() << endl << endl;

	//各キャラごとに読み込み
	for (auto chara : charaNameList) {
		//入れる箱
		DataSet data;

		//画像データを全て読み込み
		string imagePass = chara + "\\Image";
		
		vector<string> imgName;
		MyFFStream::GetFileName(imagePass, imgName);
		for (auto img : imgName) {
			Image image;
			image.imgHandle = LoadGraph(img.c_str());
			//サイズを得る
			GetGraphSize(image.imgHandle, &(image.width), &(image.height));
			image.alphaFlag = false;

			data.imgList.push_back(image);
		}

		//音声データを全て読み込み
		string soundPass = chara + "\\Sound";

		vector<string> sndName;
		MyFFStream::GetFileName(imagePass, sndName);
		for (auto snd : sndName) {
			Sound sound;
			data.soundList.push_back(sound);
		}
			
		charaDataList[chara] = data;
	}
}