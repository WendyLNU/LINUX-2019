// GOListen.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MEFServer.h"

#include "GOListen.h"
#include "MEFServerDlg.h"
#include "NetGoAction.h"


// GOListen
// GOListen ��Ա����

//���ܿͻ������Ӻ󣬿�ʼ��Ϸ
void GOListen::OnAccept(int nErrorCode)
{
	//	//���ٽ����м��߽�����Ϸ
	if (Gdig->game != true) {

		Gdig->hideIPInput();
		Accept(Gdig->gogame);
		Gdig->goaction = new NetGoAction(Gdig);
		Gdig->gogame.initAction(Gdig->goaction);
		Gdig->goaction->initGoData();
		Gdig->game = true;

	}
	CAsyncSocket::OnAccept(nErrorCode);
}

//���ô���ָ��
void GOListen::initDig(CMEFServerDlg* dig) {
	Gdig = dig;
}
