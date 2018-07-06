#pragma once

#include <algorithm>
#include <filesystem>

using namespace std;
namespace sys = std::experimental::filesystem;

namespace MyFFStream {
	/*�f�B���N�g�����̃t�@�C����f�B���N�g����񋓂���֐��Q*/
	void GetFileAndDirectoryName(const std::string& dir_name,
		vector<string> &fileNames, vector<string> &dirNames) {
		sys::path p(dir_name);	//���_
		std::for_each(sys::directory_iterator(p), sys::directory_iterator(),
			[&](const sys::path& p) {
			if (sys::is_regular_file(p)) { // �t�@�C���Ȃ�...
				fileNames.push_back(p.string());
			}
			else if (sys::is_directory(p)) { // �f�B���N�g���Ȃ�...
				dirNames.push_back(p.string());
			}
		});
	}

	void GetFileName(const std::string& dir_name, vector<string> &fileNames) {
		sys::path p(dir_name);	//���_
		std::for_each(sys::directory_iterator(p), sys::directory_iterator(),
			[&](const sys::path& p) {
			if (sys::is_regular_file(p)) { // �t�@�C���Ȃ�...
				fileNames.push_back(p.string());
			}
		});
	}

	void GetDirectoryName(const std::string& dir_name, vector<string> &dirNames) {
		sys::path p(dir_name);	//���_
		std::for_each(sys::directory_iterator(p), sys::directory_iterator(),
			[&](const sys::path& p) {
			if (sys::is_directory(p)) { // �f�B���N�g���Ȃ�...
				dirNames.push_back(p.string());
			}
		});
	}
	///////////////////////////////////////////////////////////////////////////////////

	/*�t�H���_�쐬�v���O�����Ƃ�������Ă�������*/

}