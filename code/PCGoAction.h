#pragma once
#include "GoAction.h"


class PCGoAction :
	public GoAction
{
public:
	
	PCGoAction(CMEFServerDlg*);
	~PCGoAction();

	//����
	void OnPoint(CPoint point);
	//����
	void OnUndo();
	
	//����Ϸ
	void  OnNewGame();
	//����
	void  OnPass();
};

