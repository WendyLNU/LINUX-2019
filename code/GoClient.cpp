// GoClient.cpp : ʵ���ļ�

#include "stdafx.h"
#include "MEFServerDlg.h"
#include "NetGoAction.h"
#include "GoAction.h"
#include "GoClient.h"

// GoClient

GoClient::GoClient()
{
}

GoClient::~GoClient()
{
}


// GoClient ��Ա����

//���ñ��ͻ���Χ�����
void GoClient::initAction(GoAction * dig)
{
	goaction = dig;
}


//�������ݣ�Ӧ�ý��յĸ�ʽx:y[:*]//max:250(char)
void GoClient::OnReceive(int nErrorCode)
{
	// �յ���Ϣ������
	char szTemp[250];
	ZeroMemory(szTemp, 250);
	int n = Receive(szTemp, 250);
	szTemp[n] = '\0';

	CString sTemp;
	sTemp.Format(_T("%s"), szTemp);
	//AfxMessageBox(sTemp);

	CString spx;
	CString spy;
	//CString ext;//may ��չ��Ϣ����
	AfxExtractSubString(spx, (LPCTSTR)sTemp, 0, ':');
	AfxExtractSubString(spy, (LPCTSTR)sTemp, 1, ':');

	px = _wtoi(spx);
	py = _wtoi(spy);

	//�������	
	play();

	CAsyncSocket::OnReceive(nErrorCode);
}

void GoClient::play() {

	if (px >= 0) {
		//����״̬����
		//�����쳣ʱ���Լ�����ӺϷ���
		CDC* pDC = goaction->winDig->GetDC();
		goaction->guiGo->oppositeGo(goaction->winDig->GetDC(), px, py);
		goaction->isMe = true;//��һ�����ⷽ����

	}
	else {
	
		switch (py)
		{
		case -1:
			//����ȷ�ϣ����ܵ���BUG������һ������a,��һ��ͬʱ����b����һagree��ʶ�������⣨2016/4/20��
			//
			if (!goaction->agree) {

				if (::MessageBox(goaction->winDig->m_hWnd, _T("�����������,�Ƿ�ͬ��\n"), _T("����"), MB_OKCANCEL) != IDOK)
				{
					//����ȷ�Ͼܾ�
					CString send = _T("-1:0");
					goaction->winDig->gogame.Send(send, send.GetLength() * 2);
					break;

				}
				//����ȷ��ͬ��
				CString send = _T("-1:-1");

				goaction->winDig->gogame.Send(send, send.GetLength() * 2);
			}
			goaction->guiGo->upGo(goaction->winDig->GetDC());
			goaction->turnBW();
			goaction->agree = false;
			break;

		case -2:
			goaction->guiGo->passStip(goaction->winDig->GetDC());
			goaction->isMe = true;
			break;
		case -3:
			break;
		case -4:
			//����Ϸȷ��//��������ȷ��
			if (!goaction->agree) {
				if (::MessageBox(goaction->winDig->m_hWnd, _T("������������Ϸ,�Ƿ�ͬ��\n"), _T("����Ϸ"), MB_OKCANCEL) != IDOK)
				{
					//����ȷ�Ͼܾ�
					CString send = _T("-1:0");
					goaction->winDig->gogame.Send(send, send.GetLength() * 2);
					break;
				}
				else {
					//����ȷ��ͬ��
					CString send = _T("-1:-4");
					goaction->winDig->gogame.Send(send, send.GetLength() * 2);//�ط�����Ϸ�ź�
					goaction->guiGo->initGo(goaction->winDig->GetDC());
				}
			}
			else {
				goaction->guiGo->initGo(goaction->winDig->GetDC());
			}
			goaction->agree = false;
			break;
		case -5:
			//�������
			if (!isOk) {
				CString send = _T("-1:-5");
				goaction->winDig->gogame.Send(send, send.GetLength() * 2);

			}
			isOk = true;
			goaction->OnNewGame();
			//��ʼ��Ϸ
			break;
		case 0:
			//����ܾ�����
			goaction->agree = false;
			break;
		default:
			break;
		}

	}

}


//�ͻ������ӷ�����¼�
void GoClient::OnConnect(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���
	if (nErrorCode) {
		isOk = false;
	}
	else {
		//���ӳɹ�����ʼ��Ϸ
		goaction->winDig->hideIPInput();
		goaction->initGoData();
		goaction->winDig->gogame.initAction(goaction);
		goaction->winDig->game = true;
		isOk = true;
	}
	CAsyncSocket::OnConnect(nErrorCode);
}
