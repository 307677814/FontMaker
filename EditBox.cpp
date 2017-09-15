// EditBox.cpp : ʵ���ļ�
#include "stdafx.h"
#include "FontMaker.h"
#include "EditBox.h"

static int UnicodeToUTF8(const WCHAR* input, char* output, int size)
{
	return WideCharToMultiByte(CP_UTF8, 0, input, -1, output, size, NULL, NULL);		
}

static int UTF8ToUnicode(const char* input, WCHAR* output, int size)
{
	return MultiByteToWideChar(CP_UTF8, 0, input, -1, output, size);
}

// CEditBox �Ի���
IMPLEMENT_DYNAMIC(CEditBox, CDialog)

CEditBox::CEditBox(CWnd* pParent /*=NULL*/)
	: CDialog(CEditBox::IDD, pParent)
{
	m_pzTable = (WCHAR*)malloc(4);
	wcscpy_s(m_pzTable, 4, L"0");
}

CEditBox::~CEditBox()
{
	if(m_pzTable != NULL)
	{
		free(m_pzTable);
	}
}

void CEditBox::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_TABLE, m_editTable);
}


BEGIN_MESSAGE_MAP(CEditBox, CDialog)
	ON_BN_CLICKED(IDC_BTN_LOAD, &CEditBox::OnBnClickedBtnLoad)
	ON_BN_CLICKED(IDC_BTN_SAVE, &CEditBox::OnBnClickedBtnSave)
	ON_BN_CLICKED(IDC_BTN_NUM, &CEditBox::OnBnClickedBtnNum)
	ON_BN_CLICKED(IDC_BTN_LETTER, &CEditBox::OnBnClickedBtnLetter)
	ON_BN_CLICKED(IDOK, &CEditBox::OnBnClickedOk)
END_MESSAGE_MAP()


// CEditBox ��Ϣ�������
void CEditBox::OnBnClickedBtnLoad()
{
	int len;
	CFile cf;
	WCHAR *pstr;
	CHAR  *pbuff;
	CString name;
	UINT size;
	CFileDialog fd(1,NULL,NULL,OFN_HIDEREADONLY|OFN_FILEMUSTEXIST|OFN_ENABLESIZING,L"�ı��ļ�|*.txt|�����ļ�|*.*||");
	if(fd.DoModal()!=IDOK)
	{
		return;
	}
	name = fd.GetPathName();
	if(!cf.Open(name,CFile::modeRead|CFile::shareDenyNone))
	{
		MessageBox(L"�޷����ļ�!",L"����ʧ��",MB_OK|MB_ICONINFORMATION);
		return;
	}
	size = (UINT)cf.GetLength();
	pbuff = (CHAR*)malloc(size+2);
	if(pbuff == NULL)
	{
		cf.Close();
		MessageBox(L"�ڴ治��!",L"����ʧ��",MB_OK|MB_ICONINFORMATION);
		return;
	}
	pstr = (WCHAR*)malloc(size*2+2);
	if(pstr == NULL)
	{
		free(pbuff);
		cf.Close();
		MessageBox(L"�ڴ治��!",L"����ʧ��",MB_OK|MB_ICONINFORMATION);
		return;
	}
	memset(pbuff,0,size+2);
	if(cf.Read(pbuff,size)!=size)
	{
		free(pbuff);
		free(pstr);
		cf.Close();
		MessageBox(L"��ȡ�ļ�ʱ��������!",L"����ʧ��",MB_OK|MB_ICONINFORMATION);
		return;
	}
	len = UTF8ToUnicode(pbuff,pstr,size*2);
	m_editTable.SetWindowText(pstr);
	free(pbuff);
	free(pstr);
	cf.Close();
}

void CEditBox::OnBnClickedBtnSave()
{
	int len;
	CFile cf;
	WCHAR *pstr;
	CHAR  *pbuff;
	CString name;
	CFileDialog fd(0,NULL,NULL,OFN_OVERWRITEPROMPT|OFN_ENABLESIZING,L"�����ļ�|*.*||");
	if(fd.DoModal()!=IDOK)
	{
		return;
	}
	name = fd.GetPathName();
	if(!cf.Open(name,CFile::modeCreate|CFile::modeReadWrite|CFile::shareDenyNone))
	{
		MessageBox(L"�޷������ļ�!",L"����ʧ��",MB_OK|MB_ICONINFORMATION);
		return;
	}
	len = m_editTable.GetWindowTextLength();
	pstr = (WCHAR*)malloc(len*2+2);
	pbuff= (CHAR*)malloc(len*2+2);
	m_editTable.GetWindowText(pstr,len+1);
	len = UnicodeToUTF8(pstr,pbuff,len*2+2);
	cf.Write(pbuff,len-1);
	free(pstr);
	free(pbuff);
	cf.Close();
}

void CEditBox::OnBnClickedBtnNum()
{
	m_editTable.ReplaceSel(L"0123456789");
	m_editTable.SetFocus();
}

void CEditBox::OnBnClickedBtnLetter()
{
	m_editTable.ReplaceSel(L"abcdefghijklmnopqrstuvwxyz");
	m_editTable.ReplaceSel(L"ABCDEFGHIJKLMNOPQRSTUVWXYZ");
	m_editTable.SetFocus();
}

void CEditBox::OnBnClickedOk()
{
	int len;
	len = m_editTable.GetWindowTextLength();
	if(len<=0)
	{
		MessageBox(L"�����Ϊ��!",L"����",MB_OK|MB_ICONWARNING);
		return;
	}
	if(m_pzTable!=NULL)
	{
		free(m_pzTable);
	}
	m_pzTable = (WCHAR*)malloc(len*2+2);
	if(m_pzTable != NULL)
	{
		m_editTable.GetWindowText(m_pzTable,len+1);
	}
	OnOK();
}

BOOL CEditBox::OnInitDialog()
{
	CDialog::OnInitDialog();
	SetWindowText(L"�Զ������");
	if(m_pzTable!=NULL)
	{
		m_editTable.SetWindowText(m_pzTable);
	}
	return TRUE;
}
