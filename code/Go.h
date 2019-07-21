#pragma once
#include <map>
#include <vector>
#include "Cell.h"
using namespace std;

class Go
{
public:
	Go();
	~Go();

	void startGo();//�������Ϣ


	Cell go[20][20];
	map<int, vector<Cell> > dropbackup;//���ڼ�¼���е���ʷ��¼����������Ϣ�ᶪ����

	int count = 1;//��ּ���,����ɫ���


	Status checkcolor;//Ҫ�ݹ���������ɫ
	vector<Cell> tp;//���ʱ��¼����û��������
	vector<Cell> die;//��ʱ��¼������ʱ��������ķ���
	bool ans;  //����Ƿ�������,�Լ�ȷ��die�Ƿ���Ч
	bool path[20][20]; //��ʱ����߹���·����ֹ�ظ�
	vector<Cell> cpath;//��ʱ��¼�����߹�·��



	void isDie(int x, int y);//�ж�x��y�����������Ƿ����������� ���� vector<Cell> tp
	
	void checkStarus(int x, int y);//x y �����Ӻ󣬼��

	bool Point(Cell tmp);//���ӣ�tmp  ��xy����

	//���ص�ǰ�֣�����Ե��ӣ���GUI���½���
	vector<Cell> PointCheck();

	//�������֣�
	void passStip();
	//�ϲ�Ӧ������������飬�Ƿ�Ϊ��ʼ״̬û�м�¼����,�����߲������߲����������(��������)
	vector<Cell> undo();

	//׼�����ĸ�������չ
	void prepareExt(int x, int y, int check[4][2]);

	void chearPath();

	void CellUpdate(Cell ce, Status s);//������ʾ��ʾ��Ϣ��next ��ɫ

	
public:
	//�����������������ʱ����
	bool flagBlack;
	bool flagWrite;
	bool flagEmpty[20][20]; //��ʱ��������Ŀո񣬷�ֹ�ظ�����
	float tcountEmpty;

	float getBlackCell();
	//������ϵ���֣��������ӷ�����ʤ����
	//��˫���������������󣬶�����һ���Ļ���ͻ���Χס�ĵ�����Ϊ��λ���м�����
	void isBlackEmpty(int x, int y);

	float countCell();//��ȡ������Ŀ


	//����x,y���ӵ���ɫ��Ϣ
	Status infGo(int x, int y);

};

