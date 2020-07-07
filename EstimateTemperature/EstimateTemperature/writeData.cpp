/*�d��A���̏d�݂Ɨ\�z�C����csv,txt�ɏo�͂���֐�*/

#include "header.h"

void write_weight(const char* fileName, double weight[VARIABLENUM]) {
	FILE* fp;
	errno_t error;

	char s[CHARBUFF];

	error = fopen_s(&fp, fileName, "w");
	if (error != 0)
		fprintf_s(stderr, "failed to open!");
	else {
		for (int i = 0; i < VARIABLENUM; i++) {
			sprintf_s(s, "�yx%d�z,%lf\n", i, weight[i]);
			fputs(s, fp);
		}
		fclose(fp);
	}
}

void write_result(const char* fileName, double result) {
	FILE* fp;
	errno_t error;

	char s[CHARBUFF];

	error = fopen_s(&fp, fileName, "w");
	if (error != 0)
		fprintf_s(stderr, "failed to open!");
	else {
		sprintf_s(s, "�y�\�����ϋC���z%lf(��)", result);
		fputs(s, fp);
		fclose(fp);
	}
}