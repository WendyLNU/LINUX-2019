#pragma once
#include "GoAction.h"
class GOListen;
class GoClient;

class NetGoAction :
	public GoAction
{
public:

	NetGoAction(CMEFServerDlg*);
	~NetGoAction();
	//����
	void OnPoint(CPoint point);
	//����
	void OnUndo();

	//����Ϸ
	void  OnNewGame();
	//����
	void  OnPass();

public:
	
	GoClient* gogame;//����������Ϸ����

	
};

