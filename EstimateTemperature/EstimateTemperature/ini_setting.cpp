/*iniファイルの読み込み・書き込みを行う関数群*/

#include "header.h"

//指定されたセクション，キーに従ってiniファイルから，第1引数に値を格納
void get_ini(char* returnValue, const char* filename, const char* sectionname, const char* keyword) {
	/*現在のディレクトリを取得*/
	char currentDirectory[CHARBUFF];
	getCurrentDirectory(currentDirectory);

	/*iniファイルのパス*/
	char settingFile[CHARBUFF];
	sprintf_s(settingFile, "%s\\%s", currentDirectory, filename);

	/*iniファイルから値を取得*/
	readChar(sectionname, keyword, "", returnValue, settingFile);
}

//現在のディレクトリを取得
void getCurrentDirectory(char* currentDirectory) {
	GetCurrentDirectory(CHARBUFF, currentDirectory);
}

//iniファイルから値(char)を取得
bool  readChar(const char* section, const char* keyword, const char* defaultValue, char* returnValue, const char* filePath) {
	if (GetPrivateProfileString(section, keyword, defaultValue, returnValue, CHARBUFF, filePath) != 0) {
		return true;
	}
	else {
		return false;
	}
}
