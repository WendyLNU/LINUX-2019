#pragma once
#include "stdafx.h"
#include "Go.h"


//ά�����̽��棬�������¼����ã��ڲ�����Χ���ڲ����ݡ�

class GUIGo
{
public:

	Go go;//Χ���ڲ��߼�����
	int count = 1;//������

	int alen = 19; //Χ�壬19*19
	int size = 24;//����ߴ�
	int cell_h = 12;//���Ӱ뾶
	int origin = 30;//ԭ�����꣨x=y��
	
	int extsize = 4;//�����ϵ�뾶
	int extlen = 6;////19*19Χ������6
	int ext;//�ر��֮�����

	int sizeofbroad;//���̳���
	int broadrange;//�������귶Χ
	int base;//�������ĵ��������


	//������Դ��ˢ
	CBrush bblack;
	CBrush bwrite;
	CBrush background;

	//���ʣ�������߲���
	CPen penblack;
	CPen penwrite;
	CPen clearcell;


	GUIGo();
	~GUIGo();

	void setSize(int newSize);//���򴰿ڴ�С�ı�ʱ���������Ӵ�С��Ϣ
	
	//��ʼ�� or �¿���
	void initGo(CDC* pDC);

	//����Ϸʱ������������Ҫ�ػ�
	void updateInf(CDC* pDC);

	//����
	void upGo(CDC* pDC);

	//��������Ȩ
	void passStip(CDC* pDC);

	//�����壬����Ƿ���Ч//��Ч�����Է�
	int px=-1;
	int py=-1;

	bool clickGo(CDC* pDC, CPoint point);

	bool oppositeGo(CDC* pDC,int ax ,int ay);

	void addCell(CDC* pDC, Cell cell, cellcolor cc);

	void removeCell(CDC* pDC, Cell cell);
	//���ĳ���������
	//��������ʱ������Ƿ�Ϊ�ؼ��㣨��
	void addBroad(CDC* pDC, int ax, int ay);

	//��ʼ������
	void initBoard(CDC* pDC);

	//��ʾ��ʾ��Ϣ
	void updateTips(CDC* pDC);

	//��ʾ��ǰ�֣�ͳ�ƽ��
	void showCountBlack(CDC* pDC);

	//��ʾ����
	void showLog(CDC* pDC);


};

