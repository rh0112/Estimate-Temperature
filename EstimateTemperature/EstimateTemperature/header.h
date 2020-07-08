#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>


#define VARIABLENUM 41  //説明変数の数
#define MAXSIZE 512 //サンプルデータの最大データ数
#define CHARBUFF 124

/*構造体宣言*/
struct  Weatherdata
{
	double temperature;        //気温(重回帰分析での目的変数)
	double explanatory_variable[VARIABLENUM]; //10日前～1日前までの平均気温,日照時間，降水量，平均風速(重回帰分析での説明変数)．なお，1個目の変数は1とする(ダミー変数)
};

/*関数プロトタイプ宣言*/
void get_ini(char* returnValue, const char* filename, const char* sectionname, const char* keyword);
void getCurrentDirectory(char* currentDirectory);
bool readChar(const char* section, const char* keyword, const char* defaultValue, char* returnValue, const char* filePath);
int make_datalist(const char* infileName, Weatherdata* data);
void MRA(Weatherdata* data, int datanum, double returnweight[VARIABLENUM], double returnave[VARIABLENUM]);
double predict(const char* infileName, double weight[VARIABLENUM], double ave[VARIABLENUM]);
void make_predictiondata(const char* infileName, double returndata[VARIABLENUM], double ave[VARIABLENUM]);
void write_weight(const char* fileName, double weight[VARIABLENUM]);
void write_result(const char* fileName, double result);
