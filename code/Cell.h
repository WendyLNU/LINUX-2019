#pragma once
#include "Base.cpp"

class Cell
{
public:
	int x;
	int y;
	Status status;

	Cell();

	void Init(int x, int y);//��ʼ������

	void updateStatus(Status status);//��������״̬
	
	bool equal(Cell cell);//�Ƚ�����λ��״̬�Ƿ���ͬ������ͬ�μ��

	Status getStatus();
	
	bool isEmpty();//�Ƿ����ڿո��
	bool isSameColor(Status cp);//��ָ��״̬�Ƚ��Ƿ���ͬ

	
	~Cell();
};

