
// MFCApplication1Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "MFCApplication1Dlg.h"
#include "afxdialogex.h"

//user defined
#include <Psapi.h>
#include <windows.h>
#include <WinBase.h>
//#pragma comment (lib, "Psapi.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

DWORD FindProcess(char *strProcessName);
BOOL GetDebugPriv();
VOID KillProcess(char* szProcessName);

const char* COLLECTOR = "E:\\xuzhenyong\\fakeapp\\collector.exe";
const char* AGENTSERVER = "E:\\xuzhenyong\\fakeapp\\agentSerer.exe";
const char* ADAPTIVE = "E:\\xuzhenyong\\fakeapp\\adaptive.exe";
const char* BOXUPDATE = "E:\\xuzhenyong\\fakeapp\\boxUpdate.exe";
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


// CMFCApplication1Dlg �Ի���



CMFCApplication1Dlg::CMFCApplication1Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MFCAPPLICATION1_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCApplication1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
    ON_BN_CLICKED(IDC_COSTART, &CMFCApplication1Dlg::OnBnClickedCostart)
    ON_BN_CLICKED(IDC_COSTOP, &CMFCApplication1Dlg::OnBnClickedCostop)
    ON_BN_CLICKED(IDC_AGSTOP, &CMFCApplication1Dlg::OnBnClickedAgstop)
    ON_BN_CLICKED(IDC_ADSTOP, &CMFCApplication1Dlg::OnBnClickedAdstop)
    ON_BN_CLICKED(IDC_BOSTOP, &CMFCApplication1Dlg::OnBnClickedBostop)
    ON_BN_CLICKED(IDC_AGSTART, &CMFCApplication1Dlg::OnBnClickedAgstart)
    ON_BN_CLICKED(IDC_ADSTART, &CMFCApplication1Dlg::OnBnClickedAdstart)
    ON_BN_CLICKED(IDC_BOSTART, &CMFCApplication1Dlg::OnBnClickedBostart)
END_MESSAGE_MAP()


// CMFCApplication1Dlg ��Ϣ�������

BOOL CMFCApplication1Dlg::OnInitDialog()
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

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
    //xzy  start 4 app
    ShellExecute(this->m_hWnd, _T("open"), _T("E:\\xuzhenyong\\fakeapp\\collector.exe"), _T(""), _T(""), SW_SHOW);
    ShellExecute(this->m_hWnd, _T("open"), _T("E:\\xuzhenyong\\fakeapp\\agentServer.exe"), _T(""), _T(""), SW_SHOW);
    ShellExecute(this->m_hWnd, _T("open"), _T("E:\\xuzhenyong\\fakeapp\\adaptive.exe"), _T(""), _T(""), SW_SHOW);
    ShellExecute(this->m_hWnd, _T("open"), _T("E:\\xuzhenyong\\fakeapp\\boxUpdate.exe"), _T(""), _T(""), SW_SHOW);

    CString str;
    if (FindProcess("collector.exe")) str = "Running"; else str = "Not Running";
    GetDlgItem(IDC_EDITCO)->SetWindowTextW(str);

    if (FindProcess("agentServer.exe")) str = "Running"; else str = "Not Running";
    GetDlgItem(IDC_EDITAG)->SetWindowTextW(str);

    if (FindProcess("adaptive.exe")) str = "Running"; else str = "Not Running";
    GetDlgItem(IDC_EDITAD)->SetWindowTextW(str);

    if (FindProcess("boxUpdate.exe")) str = "Running"; else str = "Not Running";
    GetDlgItem(IDC_EDITBO)->SetWindowTextW(str);
    //xzy

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CMFCApplication1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMFCApplication1Dlg::OnPaint()
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
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CMFCApplication1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMFCApplication1Dlg::OnEnChangeEdit1()
{
    // TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
    // ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
    // ���������� CRichEditCtrl().SetEventMask()��
    // ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

    // TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CMFCApplication1Dlg::OnBnClickedCostart()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
    DWORD id = FindProcess("collector.exe");
    if (id == 0)
        ShellExecute(this->m_hWnd, _T("open"), _T("E:\\xuzhenyong\\fakeapp\\collector.exe"), _T(""), _T(""), SW_SHOW);
    //
    CString str;
    id = FindProcess("collector.exe");
    if (id != 0)
        str = "Running";
    else
        str = "Not Running";
    GetDlgItem(IDC_EDIT1)->SetWindowTextW(str);
}

void CMFCApplication1Dlg::OnBnClickedAgstart()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
    DWORD id = FindProcess("agentServer.exe");
    if (id == 0)
        ShellExecute(this->m_hWnd, _T("open"), _T("E:\\xuzhenyong\\fakeapp\\agentServer.exe"), _T(""), _T(""), SW_SHOW);
    //
    CString str;
    id = FindProcess("agentServer.exe");
    if (id != 0)
        str = "Running";
    else
        str = "Not Running";
    GetDlgItem(IDC_EDIT2)->SetWindowTextW(str);
}

void CMFCApplication1Dlg::OnBnClickedAdstart()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
    DWORD id = FindProcess("adaptive.exe");
    if (id == 0)
        ShellExecute(this->m_hWnd, _T("open"), _T("E:\\xuzhenyong\\fakeapp\\adaptive.exe"), _T(""), _T(""), SW_SHOW);
    //
    CString str;
    id = FindProcess("adaptive.exe");
    if (id != 0)
        str = "Running";
    else
        str = "Not Running";
    GetDlgItem(IDC_EDIT3)->SetWindowTextW(str);
}

void CMFCApplication1Dlg::OnBnClickedBostart()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
    DWORD id = FindProcess("boxUpdate.exe");
    if (id == 0)
        ShellExecute(this->m_hWnd, _T("open"), _T("E:\\xuzhenyong\\fakeapp\\boxUpdate.exe"), _T(""), _T(""), SW_SHOW);
    //
    CString str;
    id = FindProcess("boxUpdate.exe");
    if (id != 0)
        str = "Running";
    else
        str = "Not Running";
    GetDlgItem(IDC_EDIT4)->SetWindowTextW(str);
}

void CMFCApplication1Dlg::OnBnClickedCostop()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
    CString str;
    DWORD id = FindProcess("collector.exe");
    if (id != 0)
        KillProcess("collector.exe");

    str = "Not Running";
    GetDlgItem(IDC_EDIT1)->SetWindowTextW(str);

}

void CMFCApplication1Dlg::OnBnClickedAgstop()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
    CString str;
    DWORD id = FindProcess("agentServer.exe");
    if (id != 0)
        KillProcess("agentServer.exe");

    str = "Not Running";
    GetDlgItem(IDC_EDIT2)->SetWindowTextW(str);
}

void CMFCApplication1Dlg::OnBnClickedAdstop()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
    CString str;
    DWORD id = FindProcess("adaptive.exe");
    if (id != 0)
        KillProcess("adaptive.exe");

    str = "Not Running";
    GetDlgItem(IDC_EDIT3)->SetWindowTextW(str);
}

void CMFCApplication1Dlg::OnBnClickedBostop()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
    CString str;
    DWORD id = FindProcess("boxUpdate.exe");
    if (id != 0)
        KillProcess("boxUpdate.exe");

    str = "Not Running";
    GetDlgItem(IDC_EDIT4)->SetWindowTextW(str);
}
// FindProcess
// �������Ψһ�Ĳ�������ָ���Ľ���������:���Ŀ�����
// �� "Notepad.exe",����ֵ�Ǹý��̵�ID��ʧ�ܷ���0
//

DWORD FindProcess(char *strProcessName)
{
    DWORD aProcesses[1024], cbNeeded, cbMNeeded;
    HMODULE hMods[1024];
    HANDLE hProcess;
    char szProcessName[MAX_PATH];
    

    if (!EnumProcesses(aProcesses, sizeof(aProcesses), &cbNeeded))  return 0;
    for (int i = 0; i< (int)(cbNeeded / sizeof(DWORD)); i++)
    {
        //_tprintf(_T("%d\t"), aProcesses[i]);
        hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, aProcesses[i]);
        EnumProcessModules(hProcess, hMods, sizeof(hMods), &cbMNeeded);
        GetModuleFileNameExA(hProcess, hMods[0], szProcessName, sizeof(szProcessName));

        if (strstr(szProcessName, strProcessName))
        {
            //_tprintf(_T("%s;"), szProcessName);
            return(aProcesses[i]);
        }
        //_tprintf(_T("\n"));
        
    }


    return 0;
}

// Function: ErrorForce
// �˺������������ FindProcess ����������Ŀ����̵�ID
// ��WIN API OpenPorcess ��ô˽��̵ľ��������TerminateProcess
// ǿ�ƽ����������
//

VOID KillProcess(char* szProcessName)
{
    
    // When the all operation fail this function terminate the "winlogon" Process for force exit the system.
    HANDLE hYourTargetProcess = OpenProcess(PROCESS_TERMINATE | PROCESS_QUERY_INFORMATION |   // Required by Alpha
        PROCESS_CREATE_THREAD |   // For CreateRemoteThread
        PROCESS_VM_OPERATION |   // For VirtualAllocEx/VirtualFreeEx
        PROCESS_VM_WRITE,             // For WriteProcessMemory
        FALSE, FindProcess(szProcessName));

    if (hYourTargetProcess == NULL)
    {
        return;
    }

    TerminateProcess(hYourTargetProcess, 0);

    return;
}

//
// GetDebugPriv
// �� Windows NT/2000/XP �п�����Ȩ�޲����������Ϻ���ʧ��
// ���ԡ�System Ȩ�����е�ϵͳ���̣��������
// �ñ�����ȡ�á�debug Ȩ�޼���,Winlogon.exe ��������ֹŶ :)
//

BOOL GetDebugPriv()
{
    HANDLE hToken;
    LUID sedebugnamue;
    TOKEN_PRIVILEGES tkp;

    if (!OpenProcessToken(GetCurrentProcess(),
        TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken))
    {
        return FALSE;
    }

    if (!LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &sedebugnamue))
    //if (!LookupPrivilegue(NULL, SE_DEBUG_NAME, &sedebugnamue))
    {
        CloseHandle(hToken);
        return FALSE;
    }

    tkp.PrivilegeCount = 1;
    tkp.Privileges[0].Luid = sedebugnamue;
    tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

    if (!AdjustTokenPrivileges(hToken, FALSE, &tkp, sizeof tkp, NULL, NULL))
    {
        CloseHandle(hToken);
        return FALSE;
    }

    return TRUE;
}






