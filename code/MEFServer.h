
// MEFServer.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMEFServerApp: 
// �йش����ʵ�֣������ MEFServer.cpp
//

class CMEFServerApp : public CWinApp
{
public:
	CMEFServerApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMEFServerApp theApp;