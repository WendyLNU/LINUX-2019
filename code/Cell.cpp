#include "stdafx.h"
#include "Cell.h"


Cell::Cell()
{
}


Cell::~Cell()
{
}

//��ʼ��������Ϣ
void Cell::Init(int x, int y) {
	this->x = x;
	this->y = y;
	status = Status::s_empty;
}

void Cell::updateStatus(Status status) {
	this->status = status;
}

//�Ƚ�����λ��״̬�Ƿ���ͬ������ͬ�μ��
bool Cell::equal(Cell cell) {
	if (x == cell.x && y == cell.y && status == cell.status) {
		return true;
	}
	return false;
}

//��ȡ����״̬
Status Cell::getStatus() {
	return status;
}

//�Ƿ����ڿո��
bool Cell::isEmpty() {
	return status == Status::s_empty;
}

//�Ƚ���ɫ����ָ��״̬�Ƚ��Ƿ���ͬ
bool Cell::isSameColor(Status cp) {
	return status == cp;
}

