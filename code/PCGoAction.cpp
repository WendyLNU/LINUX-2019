#include "stdafx.h"
#include "MEFServerDlg.h"
#include "PCGoAction.h"


//������Ϸ��

PCGoAction::PCGoAction(CMEFServerDlg * winDig):GoAction(winDig)
{
	this->winDig = winDig;
}

PCGoAction::~PCGoAction()
{
}

void PCGoAction::OnPoint(CPoint point)
{	
	//����
	if (guiGo->clickGo(winDig->GetDC(), point)) {

	}
}

void PCGoAction::OnUndo()
{
	if (guiGo->count == 1) {
		return;
	}
	guiGo->upGo(winDig->GetDC());
}

void PCGoAction::OnNewGame()
{
	guiGo->initGo(winDig->GetDC());
}

void PCGoAction::OnPass()
{
	guiGo->passStip(winDig->GetDC());
}
