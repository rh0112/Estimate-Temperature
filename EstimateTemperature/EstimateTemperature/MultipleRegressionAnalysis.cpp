/*�d��A���͂̏������s���֐�*/

#include "header.h"

void MRA(Weatherdata* data, int datanum, double returnweight[VARIABLENUM], double returnave[VARIABLENUM]) {

	/*�����ϐ��s��̒��S��*/
	//�e�������ς̕��ς����߂�
	for (int i = 0; i < datanum; i++) {
		for (int l = 1; l < VARIABLENUM; l++) {
			returnave[l] += (data[i].explanatory_variable[l]/datanum);
		}
	}
	//���ꂼ��̒l���畽�ς�����(�_�~�[�ϐ�������)
	for (int i = 0; i < datanum; i++) {
		for (int l = 1; l < VARIABLENUM; l++) {
			data[i].explanatory_variable[l]= data[i].explanatory_variable[l]- returnave[l];
		}
	}

	/*�����ϐ��s��̓]�u�Ɛ����ϐ��s����|�����킹��F(1)*/
	//�����ϐ��s��̓]�u�����߂�
	double XT[VARIABLENUM][MAXSIZE];
	for (int i = 0; i < VARIABLENUM; i++) {
		for (int l = 0; l < datanum; l++) {
			XT[i][l] = data[l].explanatory_variable[i];
		}
	}
	//�|�����킹��
	double XTX[VARIABLENUM][VARIABLENUM];
	for (int i = 0; i < VARIABLENUM; i++) {
		for (int l = 0; l < VARIABLENUM; l++) {
			XTX[i][l] = 0.0;
			for (int k = 0; k < datanum; k++) {
				XTX[i][l] += (XT[i][k] * data[k].explanatory_variable[l]);
			}
		}
	}

	/*(1)�̋t�s������߂�F(2)*/
	double inv_XTX[VARIABLENUM][VARIABLENUM];
	double buf;
	//�P�ʍs������
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
	//�|���o���@
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

	/*(2)�Ɛ����ϐ��s��̓]�u���|�����킹��F(3)*/
	double invXTX_XT[VARIABLENUM][MAXSIZE];
	for (int i = 0; i < VARIABLENUM; i++) {
		for (int l = 0; l < datanum; l++) {
			invXTX_XT[i][l] = 0.0;
			for (int k = 0; k < VARIABLENUM; k++) {
				invXTX_XT[i][l] += inv_XTX[i][k]* XT[k][l];
			}
		}
	}

	/*(3)�ƖړI�ϐ��s����|�����킹��*/
	for (int i = 0; i < VARIABLENUM; i++) {
		returnweight[i] = 0.0;
		for (int k = 0; k < datanum; k++) {
			returnweight[i] += invXTX_XT[i][k] * data[k].temperature;
		}
	}

}