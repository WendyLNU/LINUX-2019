

#pragma once
// GOListen ����Ŀ��
class CMEFServerDlg;

//�������ȴ��ͻ��˼�����
class GOListen : public CAsyncSocket
{
public:

	virtual void OnAccept(int nErrorCode);

public:
	CMEFServerDlg* Gdig;
	void initDig(CMEFServerDlg* dig);
};



