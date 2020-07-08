/*重回帰式の重みと予想気温をcsv,txtに出力する関数*/

#include "header.h"

//重みをcsvに出力する
void write_weight(const char* fileName, double weight[VARIABLENUM]) {
	FILE* fp;
	errno_t error;

	char s[CHARBUFF];

	error = fopen_s(&fp, fileName, "w");
	if (error != 0)
		fprintf_s(stderr, "failed to open!");
	else {
		for (int i = 0; i < VARIABLENUM; i++) {
			sprintf_s(s, "【x%d】,%lf\n", i, weight[i]);
			fputs(s, fp);
		}
		fclose(fp);
	}
}

//予測平均気温をtxtに出力する
void write_result(const char* fileName, double result) {
	FILE* fp;
	errno_t error;

	char s[CHARBUFF];

	error = fopen_s(&fp, fileName, "w");
	if (error != 0)
		fprintf_s(stderr, "failed to open!");
	else {
		sprintf_s(s, "【予測平均気温】%lf(℃)", result);
		fputs(s, fp);
		fclose(fp);
	}
}