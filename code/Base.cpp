#include "stdafx.h"

enum cellcolor { b, w };//������ɫ��Ϣ����
enum Status { s_empty, s_black, s_write };//��������״̬

//���̴�С
static int SIZEOFBOARD = 19;

//�ж������Ƿ���������
static bool isOnBoard(int x, int y) {
	if (x >= 0 && y >= 0) {
		if (x < SIZEOFBOARD && y < SIZEOFBOARD) {
			return true;
		}
	}
	return false;
}
