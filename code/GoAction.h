#pragma once
#include "stdafx.h"
//#include "GOListen.h"
//#include "GoClient.h"
#include "GUIGo.h"
//#include "MEFServerDlg.h"
class CMEFServerDlg;


//���������࣬Ϊ֧�֣�������������Χ��
class GoAction
{
public:
	GoAction(CMEFServerDlg*);
	~GoAction();

public:

	CMEFServerDlg* winDig;//�Ի���ָ��

	int sPort = 6666;

	GUIGo* guiGo;//bug �ö��󱣴������Ӵ�С��Ϣ��ת��ʱ����Ӧ��ʧ


	//��ʶ�Ƿ���ϷIng
	bool game = false;
	bool agree = false;
	//��ʼ��Ϸ

	//����
	virtual void OnPoint(CPoint);
	//����
	virtual void OnUndo();
	//�鿴״̬
	virtual void  OnCount();
	//����Ϸ
	virtual void  OnNewGame();
	//����
	virtual void  OnPass();


	void initGoData();

public:
	//����ʱ���ڼ���Ƿ���Լ���
	bool isMe = true;
	void turnBW();

};

