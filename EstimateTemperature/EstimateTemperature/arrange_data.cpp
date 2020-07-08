/*��A�������߂邽�߂�csv�t�@�C���̓ǂݍ��݁E�������s���֐��Q*/

#include "header.h"

//�T���v���t�@�C������\���̂��쐬���C���̗v�f����Ԃ�
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
		for (int i = 0; i < 4; i++) {//1~4�s�ڂ��΂�
			fgets(s, CHARBUFF, fi);
		}
		//�ŏ���10���Ԃ̐����ϐ����i�[����
		data[0].explanatory_variable[0] = 1;
		for (int i = 0; i < 10; i++) {
			fgets(s, CHARBUFF, fi);
			strtok_s(s, delim, &ctx);//1�ڂ̕�����������΂�(�N����)
			data[0].explanatory_variable[i * 4 + 1] = atof(strtok_s(NULL, delim, &ctx));//���ϋC��
			data[0].explanatory_variable[i * 4 + 2] = atof(strtok_s(NULL, delim, &ctx));//���Ǝ���
			data[0].explanatory_variable[i * 4 + 3] = atof(strtok_s(NULL, delim, &ctx));//�~����
			data[0].explanatory_variable[i * 4 + 4] = atof(strtok_s(NULL, delim, &ctx));//���ϕ���
		}
		while (fgets(s, CHARBUFF, fi) != NULL) {
			strtok_s(s, delim, &ctx);//1�ڂ̕�����������΂�(�N����)
			data[cnt - 1].temperature = atof(strtok_s(NULL, delim, &ctx));
			//���̓��ɐ����ϐ����i�[
			data[cnt].explanatory_variable[0] = 1;
			for (int i = 1; i < 37; i++) {//���̓��̐����ϐ��̓��C9�����͑O���̐����ϐ��Ƃ��Ԃ��Ă���̂Ŋi�[
				data[cnt].explanatory_variable[i] = data[cnt - 1].explanatory_variable[i + 4];
			}
			data[cnt].explanatory_variable[VARIABLENUM - 4] = data[cnt - 1].temperature;        //���ϋC��
			data[cnt].explanatory_variable[VARIABLENUM - 3] = atof(strtok_s(NULL, delim, &ctx));//���Ǝ���
			data[cnt].explanatory_variable[VARIABLENUM - 2] = atof(strtok_s(NULL, delim, &ctx));//�~����
			data[cnt].explanatory_variable[VARIABLENUM - 1] = atof(strtok_s(NULL, delim, &ctx));//���ϕ���
			cnt++;
		}
		fclose(fi);
	}
	return cnt - 1;
}