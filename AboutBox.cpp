// AboutBox.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FontMaker.h"
#include "AboutBox.h"


// CAboutBox �Ի���
IMPLEMENT_DYNAMIC(CAboutBox, CDialog)

CAboutBox::CAboutBox(CWnd* pParent /*=NULL*/)
	: CDialog(CAboutBox::IDD, pParent)
{

}

CAboutBox::~CAboutBox()
{
}

void CAboutBox::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CAboutBox, CDialog)
END_MESSAGE_MAP()


// CAboutBox ��Ϣ�������
static WCHAR szLicense[]=
{
	L"������������������������ʹ�úʹ��������.\r\n",
};

static WCHAR szVersion[]=
{
	L"�������: ͨ�õ�����ȡ����\r\n"
	L"����汾: 1.1.2\r\n"
	L"��������: 2017.10.12\r\n"
	L"�������: �ǳ��ض�\r\n"
	L"��ϵ��ʽ: 446252221@qq.com\r\n"
};

BOOL CAboutBox::OnInitDialog()
{
	CDialog::OnInitDialog();
	SetDlgItemText(IDC_EDIT1,szVersion);
	SetDlgItemText(IDC_EDIT2,szLicense);
	return TRUE;
}
