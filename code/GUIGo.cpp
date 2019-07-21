#include "stdafx.h"
#include "GUIGo.h"

//ά�����̽��棬�������¼����ã��ڲ�����Χ���ڲ����ݡ�

GUIGo::~GUIGo()
{
}

//��ʼ�����캯����׼�������������Դ����

GUIGo::GUIGo() {
	alen = SIZEOFBOARD;
	//
	penblack.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	clearcell.CreatePen(PS_SOLID, 1, RGB(241, 224, 157));
	penwrite.CreatePen(PS_SOLID, 1, RGB(255, 255, 255));

	bblack.CreateSolidBrush(RGB(0, 0, 0));
	bwrite.CreateSolidBrush(RGB(255, 255, 255));
	background.CreateSolidBrush(RGB(241, 224, 157));

}

//�����򴰿ڸı��С�����������������̴�С��

void GUIGo::setSize(int newSize) {

	extsize = newSize / 6;
	size = newSize;
	cell_h = size / 2;
	sizeofbroad = (alen - 1)*size;
	broadrange = origin + sizeofbroad;
	base = origin + (alen / 2)  * size;
	ext = extlen * size;//19*19Χ������6
	
}

//��ʼ�� or �¿���
void GUIGo::initGo(CDC* pDC) {

	setSize(size);
	count = 1;
	py = px = -1;
	go.startGo();//�ڲ��������
	initBoard(pDC);//reset background
	updateTips(pDC);

};

//����Ϸʱ������������Ҫ�ػ档����
void GUIGo::updateInf(CDC* pDC) {

	initBoard(pDC);
	updateTips(pDC);

	for (int i = 0; i <= SIZEOFBOARD; i++) {
		for (int j = 0; j <= SIZEOFBOARD; j++) {
			Status cre = go.infGo(i, j);
			if (cre == s_empty) {
				continue;
			}
			//
			Cell cell = go.go[i][j];
			if (cre == s_write) {
				addCell(pDC, cell, w);
			}
			else {
				addCell(pDC, cell, b);
			}
		}
	}
}

//����
void GUIGo::upGo(CDC* pDC) {

	if (count > 1) {
		count--;
		//�����߲������߲����������
		vector<Cell> re = go.undo();//С��0��ʾ�˲���Ȩ
		if (re.size() > 0) {

			removeCell(pDC, re.at(0));//ˢ��GUI���Ƴ����壬
			//�������壬�������,��ɫ��count-1һ��
			cellcolor cf;
			cellcolor next;
			if ((count - 1) % 2 == 1) {
				cf = b;
				next = w;
			}
			else {
				cf = w;
				next = b;
			}
			for (unsigned int i = 1; i < re.size(); i++) {
				Cell back = re.at(i);
				addCell(pDC, back, cf);
			}
		}
		updateTips(pDC);
	}
}

//��������Ȩ
void GUIGo::passStip(CDC* pDC) {

	py = px = -1;
	go.passStip();
	count++;
	updateTips(pDC);
}



//������ʱ������Ƿ���Ч
bool GUIGo::oppositeGo(CDC* pDC, int ax, int ay) {
	//����x y����
	px = ax;
	py = ay;

	Cell cg;
	if (!isOnBoard(ax, ay)) {
		return false;//�Ƿ�������
	}

	cg.Init(ax, ay);
	cellcolor next;
	cellcolor nowcolor;
	if (count % 2 == 1) {
		cg.updateStatus(s_black);
		next = w;
		nowcolor = b;
	}
	else {
		cg.updateStatus(s_write);
		next = b;
		nowcolor = w;
	}

	//���Ӽ��
	if (!go.Point(cg)) {
		return false;
	}
	addCell(pDC, cg, nowcolor);

	//���ӷ���
	vector<Cell> ret = go.PointCheck();
	if (ret.size() > 1) {
		for (unsigned int i = 1; i < ret.size(); i++) {
			removeCell(pDC, ret.at(i));
		}
	}
	count++;
	updateTips(pDC);
	return true;

}


//���壬����Ƿ���Ч
bool GUIGo::clickGo(CDC* pDC, CPoint point) {
	//��������
	int ax = int((point.x - origin) / (float)size + 0.48);
	int ay = int((point.y - origin) / (float)size + 0.48);

	return oppositeGo(pDC, ax, ay);
}


//������ӵ�����
void GUIGo::addCell(CDC* pDC, Cell cell, cellcolor cc) {

	int ax = origin + (cell.x)*size;
	int ay = origin + (cell.y)*size;
	CBrush *oldbrush;   //��ˢ
	CPen *oldpen;

	if (cc == b) {
		oldbrush = pDC->SelectObject(&bblack);
		oldpen = pDC->SelectObject(&penblack);
	}
	else {
		oldbrush = pDC->SelectObject(&bwrite);
		oldpen = pDC->SelectObject(&penwrite);
	}
	pDC->Ellipse(ax - cell_h, ay - cell_h, ax + cell_h, ay + cell_h);
	pDC->SelectObject(oldbrush);
	pDC->SelectObject(oldpen);
}

//�Ƴ�����ĳ����
void GUIGo::removeCell(CDC* pDC, Cell cell) {

	//����ϵ�����ϱ��Ϊ1��1��ʼʵ��Ϊ0��0��0-18��1-19��
	int ax = cell.x;
	int ay = cell.y;
	ax = origin + ax * size;
	ay = origin + ay * size;

	CBrush *oldbrush;   //��ˢ

	oldbrush = pDC->SelectObject(&background);
	//pDC->Ellipse(ax - cell_h, ay - cell_h, ax + cell_h, ay + cell_h);//�������
	//�Ա���ɫ�������Ӵ�С��ͬ�ĵ㣬��������
	pDC->SelectObject(clearcell);
	//pDC->MoveTo(ax, ay);
	//pDC->LineTo(ax, ay);//��ֹ��ʼ��������
	pDC->Ellipse(ax - cell_h, ay - cell_h, ax + cell_h, ay + cell_h);
	pDC->SelectObject(&penblack);

	int xf, xe;
	int yf, ye;
	xf = ax - cell_h;
	xe = ax + cell_h;
	//���������Ƿ񳬳�����
	if (xf < origin) {
		xf = origin;
	}
	if (xe > broadrange) {
		xe = broadrange;
	}

	yf = ay - cell_h;
	ye = ay + cell_h;
	if (yf < origin) {
		yf = origin;
	}
	if (ye > broadrange) {
		ye = broadrange;
	}

	//����������
	pDC->MoveTo(xf, ay);
	pDC->LineTo(xe, ay);//ǰ����ջ��ߡ�����

	pDC->MoveTo(ax, yf);
	pDC->LineTo(ax, ye);

	pDC->SelectObject(oldbrush);
	//����Ƿ��ǹؼ���,���������
	addBroad(pDC, cell.x, cell.y);
}

//���ĳ���������ʱ
//��������ʱ������Ƿ�Ϊ�ؼ��㣨��
void GUIGo::addBroad(CDC* pDC, int ax, int ay) {

	CBrush *oldbrush;   //��ˢ
	oldbrush = pDC->SelectObject(&bblack);
	if (ax == 3 || ax == 9 || ax == 15) {
		if (ay == 3 || ay == 9 || ay == 15) {
			ax = ax; ay = ay;
			ax = origin + ax*size; ay = origin + ay*size;
			pDC->Ellipse(ax + extsize, ay + extsize, ax - extsize, ay - extsize);
		}
	}
	pDC->SelectObject(oldbrush);
}


//��ʼ�����̽���
void GUIGo::initBoard(CDC* pDC) {

	//����ɻ�ˢ,��
	CBrush *oldbrush = pDC->SelectObject(&background);
	CPen *oldpen = pDC->SelectObject(&clearcell);
	pDC->Rectangle(0 ,0 , origin + sizeofbroad + 300, origin + sizeofbroad + 300);// �������

	pDC->SelectObject(&penblack);
	CPoint t;
	//���̻��ߣ�ÿ���ݺử��
	for (int i = 0; i < alen; i++) {
		//����
		t.x = origin;
		t.y = origin + i*size;
		pDC->MoveTo(t);
		t.x = broadrange;
		pDC->LineTo(t);
		//����
		t.x = t.y;
		t.y = origin;
		pDC->MoveTo(t);
		t.y = broadrange;
		pDC->LineTo(t);
	}

	//��������ϵľŸ��ؼ���

	pDC->SelectObject(&bblack);
	pDC->Ellipse(base + extsize, base + extsize, base - extsize, base - extsize);
	pDC->Ellipse(base + extsize + ext, base + extsize + ext, base - extsize + ext, base - extsize + ext);
	pDC->Ellipse(base + extsize - ext, base + extsize - ext, base - extsize - ext, base - extsize - ext);
	pDC->Ellipse(base + extsize, base + extsize - ext, base - extsize, base - extsize - ext);
	pDC->Ellipse(base + extsize, base + extsize + ext, base - extsize, base - extsize + ext);
	pDC->Ellipse(base + extsize - ext, base + extsize, base - extsize - ext, base - extsize);
	pDC->Ellipse(base + extsize + ext, base + extsize, base - extsize + ext, base - extsize);
	pDC->Ellipse(base + extsize - ext, base + extsize + ext, base - extsize - ext, base - extsize + ext);
	pDC->Ellipse(base + extsize + ext, base + extsize - ext, base - extsize + ext, base - extsize - ext);


	pDC->SelectObject(oldbrush);
	pDC->SelectObject(oldpen);

}

//��ʾ��ʾ��Ϣ
void GUIGo::updateTips(CDC* pDC) {

	cellcolor next;//��ȡ��һ������ɫ����ʾ��ʾ
	if (count % 2 == 0) {
		next = w;
	}
	else {
		next = b;
	}

	Cell markcolor;
	markcolor.x = alen + 2;
	markcolor.y = alen / 2;
	addCell(pDC, markcolor, next);//���next��������Ϣ��
	showLog(pDC);
}


//��ʾ��ǰ�֣�ͳ�Ƶ��ӽ��
void GUIGo::showCountBlack(CDC* pDC) {

	//�õ�ͳ�ƽ��
	float sum = go.countCell();

	pDC->SetBkColor(RGB(255, 255, 255));//������ɫ
	pDC->SetBkMode(OPAQUE);//����ģʽ
	pDC->SetTextAlign(TA_LEFT | TA_BOTTOM);//�����ı����뷽ʽ

	CString stx;
	CString sty;
	CString aaa = _T("�� :  ");
	CString asp = _T("    ");
	sty.Format(TEXT("%.2f"), sum);
	stx.Append(asp);
	stx.Append(aaa);
	stx.Append(sty);
	stx.Append(asp);
	pDC->TextOut(broadrange + 60, base - 100, stx);
	sum = alen*alen - sum;//�������ƣ�
	stx = "";
	aaa = _T("�� :  ");
	sty.Format(TEXT("%.2f"), sum);
	stx.Append(asp);
	stx.Append(aaa);
	stx.Append(sty);
	stx.Append(asp);
	pDC->TextOut(broadrange + 60, base - 140, stx);
}

//��ʾ���������һ��λ����Ϣ
void GUIGo::showLog(CDC* pDC) {
	pDC->SetBkColor(RGB(255, 255, 255));//������ɫ
	pDC->SetBkMode(OPAQUE);//����ģʽ
	pDC->SetTextAlign(TA_LEFT | TA_BOTTOM);//�����ı����뷽ʽ
	CString stx;
	stx.Format(TEXT("%d"), count - 1);

	CString nowpoint;
	nowpoint.Format(TEXT(": %d * %d "),px+1,py+1);
	stx.Append(nowpoint);
	stx.Append(_T("    "));
	pDC->TextOut(broadrange + 60, base - 60, stx);


}

