/*回帰式を求めるためのcsvファイルの読み込み・処理を行う関数群*/

#include "header.h"

//サンプルファイルから構造体を作成し，その要素数を返す
int make_datalist(const char* infileName, Weatherdata* data) {
	FILE* fi;
	char s[CHARBUFF];

	char delim[] = ",";
	char* ctx;

	errno_t error;
	error = fopen_s(&fi, infileName, "r");
	int cnt = 1;
	if (error != 0)
		fprintf_s(stderr, "failed to open");
	else {
		for (int i = 0; i < 4; i++) {//1~4行目を飛ばす
			fgets(s, CHARBUFF, fi);
		}
		//最初の10日間の説明変数を格納する
		data[0].explanatory_variable[0] = 1;
		for (int i = 0; i < 10; i++) {
			fgets(s, CHARBUFF, fi);
			strtok_s(s, delim, &ctx);//1つ目の部分文字列を飛ばす(年月日)
			data[0].explanatory_variable[i * 4 + 1] = atof(strtok_s(NULL, delim, &ctx));//平均気温
			data[0].explanatory_variable[i * 4 + 2] = atof(strtok_s(NULL, delim, &ctx));//日照時間
			data[0].explanatory_variable[i * 4 + 3] = atof(strtok_s(NULL, delim, &ctx));//降水量
			data[0].explanatory_variable[i * 4 + 4] = atof(strtok_s(NULL, delim, &ctx));//平均風速
		}
		while (fgets(s, CHARBUFF, fi) != NULL) {
			strtok_s(s, delim, &ctx);//1つ目の部分文字列を飛ばす(年月日)
			data[cnt - 1].temperature = atof(strtok_s(NULL, delim, &ctx));
			//次の日に説明変数を格納
			data[cnt].explanatory_variable[0] = 1;
			for (int i = 1; i < 37; i++) {//次の日の説明変数の内，9日分は前日の説明変数とかぶっているので格納
				data[cnt].explanatory_variable[i] = data[cnt - 1].explanatory_variable[i + 4];
			}
			data[cnt].explanatory_variable[VARIABLENUM - 4] = data[cnt - 1].temperature;        //平均気温
			data[cnt].explanatory_variable[VARIABLENUM - 3] = atof(strtok_s(NULL, delim, &ctx));//日照時間
			data[cnt].explanatory_variable[VARIABLENUM - 2] = atof(strtok_s(NULL, delim, &ctx));//降水量
			data[cnt].explanatory_variable[VARIABLENUM - 1] = atof(strtok_s(NULL, delim, &ctx));//平均風速
			cnt++;
		}
		fclose(fi);
	}
	return cnt - 1;
}