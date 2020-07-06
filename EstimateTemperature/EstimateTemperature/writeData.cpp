/*�d��A���̏d�݂Ɨ\�z�C����csv�ɏo�͂���֐�*/

#include "header.h"

void write_data(const char* fileName, double weight[VARIABLENUM], double result) {
	FILE* fp;
	errno_t error;

	char s[CHARBUFF];

	error = fopen_s(&fp, fileName, "w");
	if (error != 0)
		fprintf_s(stderr, "failed to open!");
	else {
		for (int i = 0; i < VARIABLENUM; i++) {
			sprintf_s(s, "�yx%d�z%lf,", i, weight[i]);
			fputs(s, fp);
		}
		sprintf_s(s, "\n�y�\�����ϋC���z%lf",result);
		fputs(s, fp);
		fclose(fp);
	}
}