/*重回帰分析の処理を行う関数*/

#include "header.h"

void MRA(Weatherdata* data, int datanum, double returnweight[VARIABLENUM], double returnave[VARIABLENUM]) {

	/*説明変数行列の中心化*/
	//各説明平均の平均を求める
	for (int i = 0; i < datanum; i++) {
		for (int l = 1; l < VARIABLENUM; l++) {
			returnave[l] += (data[i].explanatory_variable[l]/datanum);
		}
	}
	//それぞれの値から平均を引く(ダミー変数を除く)
	for (int i = 0; i < datanum; i++) {
		for (int l = 1; l < VARIABLENUM; l++) {
			data[i].explanatory_variable[l]= data[i].explanatory_variable[l]- returnave[l];
		}
	}

	/*説明変数行列の転置と説明変数行列を掛け合わせる：(1)*/
	//説明変数行列の転置を求める
	double XT[VARIABLENUM][MAXSIZE];
	for (int i = 0; i < VARIABLENUM; i++) {
		for (int l = 0; l < datanum; l++) {
			XT[i][l] = data[l].explanatory_variable[i];
		}
	}
	//掛け合わせる
	double XTX[VARIABLENUM][VARIABLENUM];
	for (int i = 0; i < VARIABLENUM; i++) {
		for (int l = 0; l < VARIABLENUM; l++) {
			XTX[i][l] = 0.0;
			for (int k = 0; k < datanum; k++) {
				XTX[i][l] += (XT[i][k] * data[k].explanatory_variable[l]);
			}
		}
	}

	/*(1)の逆行列を求める：(2)*/
	double inv_XTX[VARIABLENUM][VARIABLENUM];
	double buf;
	//単位行列を作る
	for (int i = 0; i < VARIABLENUM; i++) {
		for (int l = 0; l < VARIABLENUM; l++) {
			if (i == l) {
				inv_XTX[i][l] = 1.0;
			}
			else {
				inv_XTX[i][l] = 0.0;
			}
		}
	}
	//掃き出し法
	for (int i = 0; i < VARIABLENUM; i++) {
		buf = 1 / XTX[i][i];
		for (int l = 0; l < VARIABLENUM; l++) {
			XTX[i][l] *= buf;
			inv_XTX[i][l] *= buf;
		}
		for (int l = 0; l < VARIABLENUM; l++) {
			if (i != l) {
				buf = XTX[l][i];
				for (int k = 0; k < VARIABLENUM; k++) {
					XTX[l][k] -= XTX[i][k] * buf;
					inv_XTX[l][k] -= inv_XTX[i][k] * buf;
				}
			}
		}
	}

	/*(2)と説明変数行列の転置を掛け合わせる：(3)*/
	double invXTX_XT[VARIABLENUM][MAXSIZE];
	for (int i = 0; i < VARIABLENUM; i++) {
		for (int l = 0; l < datanum; l++) {
			invXTX_XT[i][l] = 0.0;
			for (int k = 0; k < VARIABLENUM; k++) {
				invXTX_XT[i][l] += inv_XTX[i][k]* XT[k][l];
			}
		}
	}

	/*(3)と目的変数行列を掛け合わせる*/
	for (int i = 0; i < VARIABLENUM; i++) {
		returnweight[i] = 0.0;
		for (int k = 0; k < datanum; k++) {
			returnweight[i] += invXTX_XT[i][k] * data[k].temperature;
		}
	}

}