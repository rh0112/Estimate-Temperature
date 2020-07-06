/*予測用csvファイルの読み込み，予測結果の出力を行う関数*/

#include "header.h"

double predict(const char* infileName, double weight[VARIABLENUM], double ave[VARIABLENUM]) {
	double predictiondata[VARIABLENUM];
	make_predictiondata(infileName, predictiondata,ave);
	double result = 0;
	for (int i = 0; i < VARIABLENUM; i++) {
		result += predictiondata[i] * weight[i];
	}
	return result;
}

void make_predictiondata(const char* infileName, double returndata[VARIABLENUM],double ave[VARIABLENUM]) {
	FILE* fi;
	char s[CHARBUFF];

	char delim[] = ",";
	char* ctx;

	errno_t error;
	error = fopen_s(&fi, infileName, "r");
	int cnt = 0;
	if (error != 0)
		fprintf_s(stderr, "failed to open");
	else {
		for (int i = 0; i < 4; i++) {//1~4行目を飛ばす
			fgets(s, CHARBUFF, fi);
		}
		returndata[0] = 1;
		while (fgets(s, CHARBUFF, fi) != NULL) {
			strtok_s(s, delim, &ctx);//1つ目の部分文字列を飛ばす(年月日)
			returndata[cnt*4+1] = atof(strtok_s(NULL, delim, &ctx)) - ave[cnt * 4 + 1];
			returndata[cnt*4+2] = atof(strtok_s(NULL, delim, &ctx)) - ave[cnt * 4 + 2];
			returndata[cnt*4+3] = atof(strtok_s(NULL, delim, &ctx)) - ave[cnt * 4 + 3];
			returndata[cnt*4+4] = atof(strtok_s(NULL, delim, &ctx)) - ave[cnt * 4 + 4];
			cnt++;
		}
		fclose(fi);
	}
}