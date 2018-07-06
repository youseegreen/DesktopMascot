#pragma once

#include <algorithm>
#include <filesystem>

using namespace std;
namespace sys = std::experimental::filesystem;

namespace MyFFStream {
	/*ディレクトリ内のファイルやディレクトリを列挙する関数群*/
	void GetFileAndDirectoryName(const std::string& dir_name,
		vector<string> &fileNames, vector<string> &dirNames) {
		sys::path p(dir_name);	//拠点
		std::for_each(sys::directory_iterator(p), sys::directory_iterator(),
			[&](const sys::path& p) {
			if (sys::is_regular_file(p)) { // ファイルなら...
				fileNames.push_back(p.string());
			}
			else if (sys::is_directory(p)) { // ディレクトリなら...
				dirNames.push_back(p.string());
			}
		});
	}

	void GetFileName(const std::string& dir_name, vector<string> &fileNames) {
		sys::path p(dir_name);	//拠点
		std::for_each(sys::directory_iterator(p), sys::directory_iterator(),
			[&](const sys::path& p) {
			if (sys::is_regular_file(p)) { // ファイルなら...
				fileNames.push_back(p.string());
			}
		});
	}

	void GetDirectoryName(const std::string& dir_name, vector<string> &dirNames) {
		sys::path p(dir_name);	//拠点
		std::for_each(sys::directory_iterator(p), sys::directory_iterator(),
			[&](const sys::path& p) {
			if (sys::is_directory(p)) { // ディレクトリなら...
				dirNames.push_back(p.string());
			}
		});
	}
	///////////////////////////////////////////////////////////////////////////////////

	/*フォルダ作成プログラムとかも作っていきたい*/

}