
// MEFServerDlg.h : ͷ�ļ�
//


#pragma once
#include "GoAction.h"
#include "PCGoAction.h"
#include "NetGoAction.h"
#include "GOListen.h"
#include "GoClient.h"
#include "GUIGo.h"


// CMEFServerDlg �Ի���
class CMEFServerDlg : public CDialogEx
{
// ����
public:
	CMEFServerDlg(CWnd* pParent = NULL);	// ��׼���캯��



// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MEFSERVER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:

	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
	afx_msg void OnSize(UINT nType, int cx, int cy);

	void GetHostAddress(CString &strIPAddr);

	GoAction* goaction;//��������������Ϸ����Ϸ��װ

	GOListen golisten;//����˼���
	GoClient goclient;//�ͻ��ˣ�������Ϸ

	int sPort = 6666;
	GoClient gogame;//����������Ϸ����

	GUIGo guiGo;

	//��Դ��ʶ��
	bool work = false;

	//��ʶ�Ƿ���ϷIng
	bool game = false;

	
	bool isOnePC = false;
	bool agree = false;


	//��ʼ��Ϸ
	
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);//����
	afx_msg void Onundo();//����
	afx_msg void Oncount();//����
	afx_msg void Onnewgame();//����Ϸ
	afx_msg void Onpass();//����
	

	afx_msg void Onresetwin();//��ʾIP����ؼ������뿪��ǰ��Ϸ��
	afx_msg void OnServer();//����������
	afx_msg void OnClient();//�򿪿ͻ���
	afx_msg void Ononepc();//�������˶�ս


	void newGame();
	
	void hideIPInput();
	void resetBackGround();
	
	bool agreeExitGame(); //ͬ���뿪��Ϸʱ��������Ϸ���ݣ��رմ򿪵���Դ
	void showIPInput();
	
	virtual void OnOK();
};
