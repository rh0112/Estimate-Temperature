/*予測用csvファイルの読み込み，予測結果の出力を行う関数*/

#include "header.h"

//予測用の説明変数とそれぞれの重みを掛け合わせ，予測平均気温を返す
double predict(const char* infileName, double weight[VARIABLENUM], double ave[VARIABLENUM]) {
	/*データの整理*/
	double predictiondata[VARIABLENUM];
	make_predictiondata(infileName, predictiondata, ave);

	/*説明変数と重みを掛け合わせる*/
	double result = 0;
	for (int i = 0; i < VARIABLENUM; i++) {
		result += predictiondata[i] * weight[i];
	}

	return result;
}

//ave[]によってcsvから読み込んだ予測用データを中心化し，40個の説明変数を配列に格納する
void make_predictiondata(const char* infileName, double returndata[VARIABLENUM], double ave[VARIABLENUM]) {
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
			returndata[cnt * 4 + 1] = atof(strtok_s(NULL, delim, &ctx)) - ave[cnt * 4 + 1];//平均気温
			returndata[cnt * 4 + 2] = atof(strtok_s(NULL, delim, &ctx)) - ave[cnt * 4 + 2];//日照時間
			returndata[cnt * 4 + 3] = atof(strtok_s(NULL, delim, &ctx)) - ave[cnt * 4 + 3];//降水量
			returndata[cnt * 4 + 4] = atof(strtok_s(NULL, delim, &ctx)) - ave[cnt * 4 + 4];//平均風速
			cnt++;
		}
		fclose(fi);
	}
}