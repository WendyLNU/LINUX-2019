#pragma once
//#include "GoAction.h"

class CMEFServerDlg;
class GoAction;

// GoClient ����Ŀ��
//�ͻ����࣬��������ͨ�Ž���

class GoClient : public CAsyncSocket
{
public:
	GoClient();
	virtual ~GoClient();

	virtual void OnReceive(int nErrorCode);

public:

	int px;
	int py;

	bool isOk = false;

	GoAction* goaction;
	//���ô���ָ�룬�������GUI
	void initAction(GoAction* dig);

	void play();

	virtual void OnConnect(int nErrorCode);

	
};


