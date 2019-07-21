
// MEFServerDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MEFServer.h"
#include "MEFServerDlg.h"
#include "afxdialogex.h"


//class GoAction;
//class PCGoAction;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMEFServerDlg �Ի���



CMEFServerDlg::CMEFServerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MEFSERVER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMEFServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMEFServerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_Server, &CMEFServerDlg::OnServer)
	ON_COMMAND(ID_Client, &CMEFServerDlg::OnClient)
	ON_WM_GETMINMAXINFO()
	ON_WM_SIZE()
	ON_WM_LBUTTONDOWN()
	ON_COMMAND(ID_undo, &CMEFServerDlg::Onundo)
	ON_COMMAND(ID_count, &CMEFServerDlg::Oncount)
	ON_COMMAND(ID_newgame, &CMEFServerDlg::Onnewgame)
	ON_COMMAND(ID_pass, &CMEFServerDlg::Onpass)
	ON_COMMAND(ID_onePC, &CMEFServerDlg::Ononepc)
	ON_COMMAND(ID_resetWin, &CMEFServerDlg::Onresetwin)
END_MESSAGE_MAP()


// CMEFServerDlg ��Ϣ�������

BOOL CMEFServerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	//on init program
	GetDlgItem(ID_ServerIp)->SetWindowText(_T("127.0.0.1"));
	goaction = NULL;

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CMEFServerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{

		if (nID == 61536) {//�رմ���
			if (::MessageBox(m_hWnd, _T("ȷ��Ҫ�뿪��\n"), _T("�뿪��Ϸ"), MB_OKCANCEL) != IDOK)//���ܵ�ȷ������ȡ���������ܵ�X�ص�����
			{
				return;
			}
			else {
				if (goaction != NULL) {//������δ���ӿͻ���ʱ����Ϊnull
					delete goaction; //�ͷſռ�
					goaction = NULL;
				}
			}
		
		}

		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�


//MFC���򴰿��ػ溯��

void CMEFServerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;
		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		//Ѹ���϶����ڣ��ᵼ���ػ��¼�����
		if (game) {
			//������Ϸ�����ػ�����
			resetBackGround();
			CDC* pDC = GetDC();
			guiGo.updateInf(GetDC());
		}
		else {
			showIPInput();
		}

		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CMEFServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



//�������ڴ�Сʱ���ػ�����
void CMEFServerDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	
	int min = cx;
	if (cy < min) {
		min = cy;
	}
	int GoBoardsize = min - guiGo.origin;
	int cell = GoBoardsize / SIZEOFBOARD;
	guiGo.setSize(cell);

	//û�п�ʼ��Ϸʱ���ܻ����̣���
	if (!game) {
		return;
	}
	
	resetBackGround();
	guiGo.updateInf(GetDC());

}



void CMEFServerDlg::OnServer()
{

	if (work && !agreeExitGame()) {
		// sure ?
		return;
	}
	goaction = NULL;
	CString ips;
	GetHostAddress(ips);
	GetDlgItem(ID_ServerIp)->SetWindowText(ips);
	golisten.Close();

	BOOL mport = golisten.Create(sPort, SOCK_STREAM);

	if (mport) {
		//�����˿ڳɹ�
		golisten.Listen(1);
		golisten.initDig(this);
		work = true;
		showIPInput();
	}
	else {
		//�����˿�ʧ��

		golisten.Close();
		MessageBox(_T("�Բ��𣬴򿪷���˿�ʧ�ܣ������Գ�����Ϊ�ͻ��ˡ�"));
	}

	// TODO: �ڴ���������������
}


void CMEFServerDlg::OnClient()
{

	if (work && !agreeExitGame()) {
		// sure ?
		return;
	}
	CString sip;
	GetDlgItem(ID_ServerIp)->GetWindowText(sip);//��ȡ�����ip��ַ
	// TODO: �ڴ���������������
	gogame.Close();
	gogame.Create();
	gogame.Connect(sip, sPort);

	goaction = new NetGoAction(this);
	gogame.initAction(goaction);
	work = true;
	//����ʧ��ʱ����״̬
}




void CMEFServerDlg::resetBackGround()
{
	CRect   rect;
	CPaintDC   dc(this);
	GetClientRect(rect);
	dc.FillSolidRect(rect, RGB(241, 224, 157));   //����Ϊ����������ľͷ��ɫ
}


void CMEFServerDlg::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	lpMMI->ptMinTrackSize.x = 650;   //x���  
	lpMMI->ptMinTrackSize.y = 550;   //y�߶�
	CDialogEx::OnGetMinMaxInfo(lpMMI);

	CDialogEx::OnGetMinMaxInfo(lpMMI);
}


//���������
void CMEFServerDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	//����
	if (!game) {
		return;
	}
	goaction->OnPoint(point);

	CDialogEx::OnLButtonDown(nFlags, point);
}


void CMEFServerDlg::Onundo()
{
	if (!game) {
		return;
	}
	goaction->OnUndo();
	//�Ƿ�����ɻ�
}


void CMEFServerDlg::Oncount()
{
	if (!game) {
		return;
	}
	//�Լ��鿴��Ϸ�ڰ�������
	goaction->OnCount();
}


void CMEFServerDlg::Onnewgame()
{
	if (!game) {
		return;
	}
	resetBackGround();
	goaction->OnNewGame();
	//��ȡ�Է�ȷ�ϣ�Ȼ������Ϸ

}


void CMEFServerDlg::Onpass()
{
	if (!game) {
		return;
	}
	goaction->OnPass();
}

//׼����ʼ��Ϸ��
void CMEFServerDlg::hideIPInput()
{
	GetDlgItem(ID_ServerIp)->ShowWindow(FALSE); //���ظ�ip�ؼ�
	GetDlgItem(ID_FILE_OPEN)->ShowWindow(FALSE); //����ip��ʾ�ؼ�
	resetBackGround();
}

//��ʼ����Ϸ
void CMEFServerDlg::newGame()
{
	resetBackGround();
	guiGo.initGo(GetDC());

}




//��ʼ������ϷPK
void CMEFServerDlg::Ononepc()
{
	if (game && !agreeExitGame()) {
		// sure ?
		return;
	}

	hideIPInput();
	game = true;
	work = true;
	goaction = new PCGoAction(this);

	goaction->initGoData();

}


bool CMEFServerDlg::agreeExitGame()
{
	if (::MessageBox(m_hWnd, _T("ȷ���뿪��ǰ��Ϸ��\n"), _T("�뿪"), MB_OKCANCEL) != IDOK)//���ܵ�ȷ������ȡ���������ܵ�X�ص�����
	{
		return false;
	}
	//ȷ���뿪ʱ��clear
	golisten.Close();
	gogame.Close();
	if (goaction != NULL) {
		delete goaction; //������δ���ӿͻ���ʱ����Ϊnull
		goaction = NULL;
	}

	game = false;
	work = false;

	return true;
}


//������ʾ��ر�ǩ
void CMEFServerDlg::showIPInput()
{
	resetBackGround();
	GetDlgItem(ID_ServerIp)->ShowWindow(true); //��ʾ��ip����ؼ�
	GetDlgItem(ID_FILE_OPEN)->ShowWindow(true); //����ip��ʾ�ؼ�
}


//�����ʾIP ȷ���������Ϸ����ʾIP�����
void CMEFServerDlg::Onresetwin()
{	//û�п�ʼ��Ϸ���򲻴���
	if (work && !agreeExitGame()) {
		return;
	}
	showIPInput();
}




//�رճ����뿪�¼����������ǵ�X��
void CMEFServerDlg::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���

	if (::MessageBox(m_hWnd, _T("ȷ��Ҫ�뿪��\n"), _T("�뿪��Ϸ"), MB_OKCANCEL) != IDOK)//���ܵ�ȷ������ȡ���������ܵ�X�ص�����
	{
		return;
	}
	else {
		if (goaction != NULL) {
			delete goaction; //������δ���ӿͻ���ʱ����Ϊnull
			goaction = NULL;
		}
	}

	CDialogEx::OnOK();
}


//��ȡ����ip��ַ
void CMEFServerDlg::GetHostAddress(CString &strIPAddr)
{
	WSADATA wsadata;
	if (0 != WSAStartup(MAKEWORD(2, 2), &wsadata))   //��ʼ��
	{
		AfxMessageBox(_T("��ʼ�����绷��ʧ��!"));
		return;
	}
	char    HostName[100];
	gethostname(HostName, sizeof(HostName));// ��ñ���������.
	hostent *p = gethostbyname(HostName); //�Ӽ�������õ�������Ϣ
	if (p == NULL)
	{
		AfxMessageBox(_T("�õ�����������Ϣʧ��!"));
		return;
	}
	strIPAddr = inet_ntoa(*(struct in_addr *)p->h_addr_list[0]);//��ip�����ַ�����ʽ
	WSACleanup();               //�ͷ�Winsock API
}
