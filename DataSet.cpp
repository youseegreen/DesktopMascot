#include <iostream>
#include "FileFolderStream.h"
#include "DataSet.h"

using namespace std;

//�f�[�^���X�g�ϐ��@��`
std::map<std::string, DataSet> charaDataList;

//�l�[�����X�g�ϐ��@��`
std::vector<std::string> charaNameList;


void LoadAllData() {
	//Chara�t�@���_���̂��ׂẴt�H���_�̖��O���Q�b�g����
	MyFFStream::GetDirectoryName("Chara", charaNameList);
	cout << "�ǂݍ��񂾃L�����ꗗ" << endl;
	for(auto chara : charaNameList)
		cout << chara.c_str() << endl << endl;

	//�e�L�������Ƃɓǂݍ���
	for (auto chara : charaNameList) {
		//����锠
		DataSet data;

		//�摜�f�[�^��S�ēǂݍ���
		string imagePass = chara + "\\Image";
		
		vector<string> imgName;
		MyFFStream::GetFileName(imagePass, imgName);
		for (auto img : imgName) {
			Image image;
			image.imgHandle = LoadGraph(img.c_str());
			//�T�C�Y�𓾂�
			GetGraphSize(image.imgHandle, &(image.width), &(image.height));
			image.alphaFlag = false;

			data.imgList.push_back(image);
		}

		//�����f�[�^��S�ēǂݍ���
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