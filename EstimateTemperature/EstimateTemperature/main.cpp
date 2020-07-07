#include "header.h"

int main() {

	/*サンプルデータファイル名の読み込み*/
	char samplefilename[CHARBUFF];
	get_ini(samplefilename, "setting.ini", "input", "samplefilename");

	/*サンプルデータからデータを構造体配列に格納*/
	Weatherdata sampledata[MAXSIZE];
	int sampledatanum = make_datalist(samplefilename, sampledata);

	/*重回帰分析を行い，それぞれの変数の重みを求める*/
	//各説明変数(初期)の平均も求めておく
	double ave[VARIABLENUM];
	double weight[VARIABLENUM];
	MRA(sampledata, sampledatanum, weight,ave);

	/*重みをstdoutに出力*/
	for (int i = 0; i < VARIABLENUM; i++) {
		fprintf_s(stdout, "【x%d】%lf\t", i, weight[i]);
		if (i % 4 == 0) {
			fprintf_s(stdout, "\n");
		}
	}


	/*予測用データファイル名の読み込み*/
	char predictfilename[CHARBUFF];
	get_ini(predictfilename, "setting.ini", "input", "predictionfilename");

	/*予測用の説明変数から，予想平均気温を求め，stdoutに出力*/
	double result = predict(predictfilename, weight,ave);
	fprintf_s(stdout, "\n【予測平均気温】%lf(℃)\n", result);


	/*出力ファイル名の読み込み*/
	char outfilename1[CHARBUFF];
	get_ini(outfilename1,"setting.ini","output","filename1");
	char outfilename2[CHARBUFF];
	get_ini(outfilename2, "setting.ini", "output", "filename2");

	/*重回帰式の重みと予想気温をcsvに出力*/
	write_weight(outfilename1, weight);
	write_result(outfilename2, result);
	
	return 0;
}