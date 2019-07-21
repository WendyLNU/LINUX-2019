#include "stdafx.h"
#include "Go.h"


Go::Go()
{
}


Go::~Go()
{
}

//��ʼ���
void Go::startGo() {
	for (int i = 0; i <= SIZEOFBOARD; i++) {
		for (int j = 0; j <= SIZEOFBOARD; j++) {
			go[i][j].Init(i, j);
			path[i][j] = false;
		}
	}
	dropbackup.clear();//�߲���Ӱ�죬����ɫ��Ϊ���Ĭ�ϣ�
	die.clear();
	cpath.clear();
	count = 1;
};

//���õ��Ƿ�������������
void Go::isDie(int x, int y) {
	//�Ƿ��������ϣ���ֹpath����Խ�硣������
	if (path[x][y] || ans == false) {
		//�Ѿ��߹���path�����ǣ������Ѿ���������ȡ�����
		return;
	}

	//Ϊ��Ӧֹͣ���μ��
	if (go[x][y].isEmpty()) {
		ans = false;
	}
	else {
		Cell ce = go[x][y];
		path[x][y] = true;//����߹�������ɫ�ĵ�
		cpath.push_back(ce);//��¼ÿ�����(�ղ��ɱ�ǣ���Ӱ��������)��������������
		if (go[x][y].isSameColor(checkcolor)) {//��ͬ��ɫ��������չ
			die.push_back(ce);//����Ӧ���Ǹ���һ�����󣬷�����(����ĺ�������ʹ���޸�ce��Ӱ��die��ŵ���Ϣ) = =
			int check[4][2];
			prepareExt(x, y, check);
			for (int i = 0; i < 4; i++) {
				if (isOnBoard(check[i][0], check[i][1])) {
					isDie(check[i][0], check[i][1]);
				}
			}
		}
	}
}

//����������
void Go::checkStarus(int x, int y) {

	int check[4][2];
	prepareExt(x, y, check);
	//�˴�4�����Ӧ�û���Ӱ��
	for (int i = 0; i < 4; i++) {
		ans = true;//����empty���false��
		die.clear();//��ɾ���ϴ�״̬
					//��������ʱ�����������
		if (isOnBoard(check[i][0], check[i][1])) {
			isDie(check[i][0], check[i][1]);
			chearPath();
			//�����֮������path���´μ��,����die,ans����Ƿ���Ч
			if (ans) {
				for (Cell ce : die) {
					tp.push_back(ce);
				}
			}
		}

	}


}

//���壬������
bool Go::Point(Cell tmp) {

	int x = tmp.x;
	int y = tmp.y;

	//�Ƿ��Ѿ�������
	if (!go[x][y].isEmpty()) {
		return false;
	}

	tp.clear();
	tp.push_back(tmp);
	go[x][y] = tmp;

	Status recheck;
	if (count % 2) {
		recheck = s_black;
		checkcolor = s_write;
	}
	else {
		recheck = s_write;
		checkcolor = s_black;
	}

	checkStarus(x, y);//���״̬�Ƿ����
	if (tp.size() > 1) {
		//������ӣ�һ��֮��ͬ������?
		vector<Cell> parent = dropbackup[count - 1];
		if (parent.size() == 2 && tp.size() == 2) {
			if (parent.at(0).equal(tp.at(1)) && parent.at(1).equal(tp.at(0))) {
				go[x][y].updateStatus(s_empty);
				return false;
			}
		}
		//ȷ����Ч~//�������
		for (unsigned int i = 1; i < tp.size(); i++) {
			CellUpdate(tp.at(i), s_empty);
		}

	}
	else {
		//û����ʱ������Լ��ǲ��ǹ���
		ans = true;//����empty���false��
		die.clear();//��ɾ���ϴ�״̬
		checkcolor = recheck;
		isDie(x, y);
		chearPath();
		if (ans) {//���β�����Ч
				  //�ָ�go[x][y]...
			go[x][y].updateStatus(s_empty);
			return false;
		}
	}

	dropbackup.insert(pair<int, vector<Cell> >(count, tp));
	count++;
	return true;
	//��������//�������ӣ������¼���������ڻ��塣
	//��һ����Ҫ��������GUI�仯��PointCheck��
}

//���ص�ǰ�֣�����Ե��ӣ���GUI���½���
vector<Cell> Go::PointCheck() {
	return dropbackup[count - 1];//���һ��Ϊ�ŵ㣬������
}


//�������֣�����
void Go::passStip() {
	tp.clear();
	dropbackup.insert(pair<int, vector<Cell> >(count, tp));
	count++;
}

//���壺�����߲������߲����������(��������)
//�ϲ�Ӧ������������飬�Ƿ�Ϊ��ʼ״̬û�м�¼����,
vector<Cell> Go::undo() {
	vector<Cell> re;
	if (count > 1) {
		count--;
		re = dropbackup[count];
		dropbackup.erase(count);

		if (re.size() == 0) {//������Ȩ���
			return re;
		}

		Status bb = re.at(0).status;
		CellUpdate(re.at(0), s_empty);

		if (re.size() > 1) {
			Status diecell;//�Ե��ӣ���ɫ�϶������෴
			if (bb == s_black) {
				diecell = s_write;
			}
			else {
				diecell = s_black;
			}
			//re tp...����ճ�����µĴ�������¡�����
			for (unsigned int i = 1; i < re.size(); i++) {
				CellUpdate(re.at(i), diecell);
			}
		}
	}
	//�ϲ����������
	return re;
}

//׼�����ĸ�������չ
void Go::prepareExt(int x, int y, int check[4][2]) {

	check[0][0] = x - 1;
	check[0][1] = y;

	check[1][0] = x;
	check[1][1] = y - 1;

	check[2][0] = x + 1;
	check[2][1] = y;

	check[3][0] = x;
	check[3][1] = y + 1;

}

void Go::chearPath() {
	for (Cell ce : cpath) {
		path[ce.x][ce.y] = false;
	}
	cpath.clear();
}

void Go::CellUpdate(Cell ce, Status s) {
	go[ce.x][ce.y].updateStatus(s);
}



float Go::getBlackCell() {
	float sum = 0;
	for (int i = 0; i < SIZEOFBOARD; i++) {
		for (int j = 0; j < SIZEOFBOARD; j++) {
			flagEmpty[i][j] = false;//׼���ո����
			if (go[i][j].isSameColor(s_black)) {
				sum += 1;
			}
		}
	}
	return sum;
}
//������ϵ���֣��������ӷ�����ʤ����
//��˫���������������󣬶�����һ���Ļ���ͻ���Χס�ĵ�����Ϊ��λ���м�����

void Go::isBlackEmpty(int x, int y) {

	if (flagEmpty[x][y]) {
		return;
	}

	if (go[x][y].isEmpty()) {

		flagEmpty[x][y] = true;
		tcountEmpty++;
		int check[4][2];
		prepareExt(x, y, check);

		for (int i = 0; i < 4; i++) {
			if (isOnBoard(check[i][0], check[i][1])) {
				isBlackEmpty(check[i][0], check[i][1]);
			}
		}

	}
	else {
		if (go[x][y].isSameColor(s_black)) {
			flagBlack = true;
		}
		else {
			flagWrite = true;
		}
	}

}

//
float Go::countCell() {
	float num = 0;
	num = getBlackCell();
	//����ո�

	for (int i = 0; i < SIZEOFBOARD; i++) {
		for (int j = 0; j < SIZEOFBOARD; j++) {
			if (go[i][j].isEmpty() && (!flagEmpty[i][j])) {
				flagBlack = flagWrite = false;
				tcountEmpty = 0;
				isBlackEmpty(i, j);

				if (flagBlack) {
					if (flagWrite) {
						//ͬʱ�����ڰ��ӣ�˫��ƽ�ֿո�
						num = num + (tcountEmpty) / 2;
					}
					else {
						//ֻ�к��ӣ����ռ�ո�����
						num = num + tcountEmpty;
					}
				}

			}
		}
	}
	return num;
}

//����x,y���ӵ���ɫ��Ϣ
Status Go::infGo(int x, int y) {
	return go[x][y].status;
}
