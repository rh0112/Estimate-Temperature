/*�\���pcsv�t�@�C���̓ǂݍ��݁C�\�����ʂ̏o�͂��s���֐�*/

#include "header.h"

//�\���p�̐����ϐ��Ƃ��ꂼ��̏d�݂��|�����킹�C�\�����ϋC����Ԃ�
double predict(const char* infileName, double weight[VARIABLENUM], double ave[VARIABLENUM]) {
	/*�f�[�^�̐���*/
	double predictiondata[VARIABLENUM];
	make_predictiondata(infileName, predictiondata, ave);

	/*�����ϐ��Əd�݂��|�����킹��*/
	double result = 0;
	for (int i = 0; i < VARIABLENUM; i++) {
		result += predictiondata[i] * weight[i];
	}

	return result;
}

//ave[]�ɂ����csv����ǂݍ��񂾗\���p�f�[�^�𒆐S�����C40�̐����ϐ���z��Ɋi�[����
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
		for (int i = 0; i < 4; i++) {//1~4�s�ڂ��΂�
			fgets(s, CHARBUFF, fi);
		}
		returndata[0] = 1;
		while (fgets(s, CHARBUFF, fi) != NULL) {
			strtok_s(s, delim, &ctx);//1�ڂ̕�����������΂�(�N����)
			returndata[cnt * 4 + 1] = atof(strtok_s(NULL, delim, &ctx)) - ave[cnt * 4 + 1];//���ϋC��
			returndata[cnt * 4 + 2] = atof(strtok_s(NULL, delim, &ctx)) - ave[cnt * 4 + 2];//���Ǝ���
			returndata[cnt * 4 + 3] = atof(strtok_s(NULL, delim, &ctx)) - ave[cnt * 4 + 3];//�~����
			returndata[cnt * 4 + 4] = atof(strtok_s(NULL, delim, &ctx)) - ave[cnt * 4 + 4];//���ϕ���
			cnt++;
		}
		fclose(fi);
	}
}