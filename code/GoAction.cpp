#include "stdafx.h"
#include "MEFServerDlg.h"
#include "GoAction.h"


//���� ����
//����Χ��
//����Χ��
//�̳нӿ�

GoAction::GoAction(CMEFServerDlg* winDig)
{
	this->winDig = winDig;
	this->guiGo = &winDig->guiGo;
}


GoAction::~GoAction()
{
}


void GoAction::OnPoint(CPoint point)
{
}

void GoAction::OnUndo()
{
}

void GoAction::OnNewGame()
{

}

void GoAction::OnPass()
{
}

//���¸�����Ϣ
void GoAction::OnCount()
{
	guiGo->showCountBlack(winDig->GetDC());
}
//������Χ��
void GoAction::initGoData()
{	
	guiGo->initGo(winDig->GetDC());
}

//����Χ�� �����ӻ������ ״̬
void GoAction::turnBW()
{
	if (isMe) {
		isMe = false;
	}
	else {
		isMe = true;
	}
}
