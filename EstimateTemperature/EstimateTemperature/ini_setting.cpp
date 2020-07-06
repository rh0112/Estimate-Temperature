/*ini�t�@�C���̓ǂݍ��݁E�������݂��s���֐��Q*/

#include "header.h"

void get_ini(char* returnValue, const char* filename, const char* sectionname, const char* keyword) {
    /*���݂̃f�B���N�g�����擾*/
    char currentDirectory[CHARBUFF];
    getCurrentDirectory(currentDirectory);

    /*ini�t�@�C���̃p�X*/
    char settingFile[CHARBUFF];
    sprintf_s(settingFile, "%s\\%s", currentDirectory, filename);

    /*ini�t�@�C������l���擾*/
    readChar(sectionname, keyword, "", returnValue, settingFile);
}

void getCurrentDirectory(char* currentDirectory) {
    GetCurrentDirectory(CHARBUFF, currentDirectory);
}

bool  readChar(const char* section, const char* keyword, const char* defaultValue, char* returnValue, const char* filePath) {
    if (GetPrivateProfileString(section, keyword, defaultValue, returnValue, CHARBUFF, filePath) != 0) {
        return true;
    }
    else {
        return false;
    }
}
