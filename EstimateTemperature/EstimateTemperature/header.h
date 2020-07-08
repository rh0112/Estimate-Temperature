#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>


#define VARIABLENUM 41  //�����ϐ��̐�
#define MAXSIZE 512 //�T���v���f�[�^�̍ő�f�[�^��
#define CHARBUFF 124

/*�\���̐錾*/
struct  Weatherdata
{
	double temperature;        //�C��(�d��A���͂ł̖ړI�ϐ�)
	double explanatory_variable[VARIABLENUM]; //10���O�`1���O�܂ł̕��ϋC��,���Ǝ��ԁC�~���ʁC���ϕ���(�d��A���͂ł̐����ϐ�)�D�Ȃ��C1�ڂ̕ϐ���1�Ƃ���(�_�~�[�ϐ�)
};

/*�֐��v���g�^�C�v�錾*/
void get_ini(char* returnValue, const char* filename, const char* sectionname, const char* keyword);
void getCurrentDirectory(char* currentDirectory);
bool readChar(const char* section, const char* keyword, const char* defaultValue, char* returnValue, const char* filePath);
int make_datalist(const char* infileName, Weatherdata* data);
void MRA(Weatherdata* data, int datanum, double returnweight[VARIABLENUM], double returnave[VARIABLENUM]);
double predict(const char* infileName, double weight[VARIABLENUM], double ave[VARIABLENUM]);
void make_predictiondata(const char* infileName, double returndata[VARIABLENUM], double ave[VARIABLENUM]);
void write_weight(const char* fileName, double weight[VARIABLENUM]);
void write_result(const char* fileName, double result);
