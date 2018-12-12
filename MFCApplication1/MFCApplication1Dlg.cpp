
// MFCApplication1Dlg.cpp : 实现文件
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
// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CMFCApplication1Dlg 对话框



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


// CMFCApplication1Dlg 消息处理程序

BOOL CMFCApplication1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
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

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFCApplication1Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMFCApplication1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMFCApplication1Dlg::OnEnChangeEdit1()
{
    // TODO:  如果该控件是 RICHEDIT 控件，它将不
    // 发送此通知，除非重写 CDialogEx::OnInitDialog()
    // 函数并调用 CRichEditCtrl().SetEventMask()，
    // 同时将 ENM_CHANGE 标志“或”运算到掩码中。

    // TODO:  在此添加控件通知处理程序代码
}


void CMFCApplication1Dlg::OnBnClickedCostart()
{
    // TODO: 在此添加控件通知处理程序代码
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
    // TODO: 在此添加控件通知处理程序代码
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
    // TODO: 在此添加控件通知处理程序代码
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
    // TODO: 在此添加控件通知处理程序代码
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
    // TODO: 在此添加控件通知处理程序代码
    CString str;
    DWORD id = FindProcess("collector.exe");
    if (id != 0)
        KillProcess("collector.exe");

    str = "Not Running";
    GetDlgItem(IDC_EDIT1)->SetWindowTextW(str);

}

void CMFCApplication1Dlg::OnBnClickedAgstop()
{
    // TODO: 在此添加控件通知处理程序代码
    CString str;
    DWORD id = FindProcess("agentServer.exe");
    if (id != 0)
        KillProcess("agentServer.exe");

    str = "Not Running";
    GetDlgItem(IDC_EDIT2)->SetWindowTextW(str);
}

void CMFCApplication1Dlg::OnBnClickedAdstop()
{
    // TODO: 在此添加控件通知处理程序代码
    CString str;
    DWORD id = FindProcess("adaptive.exe");
    if (id != 0)
        KillProcess("adaptive.exe");

    str = "Not Running";
    GetDlgItem(IDC_EDIT3)->SetWindowTextW(str);
}

void CMFCApplication1Dlg::OnBnClickedBostop()
{
    // TODO: 在此添加控件通知处理程序代码
    CString str;
    DWORD id = FindProcess("boxUpdate.exe");
    if (id != 0)
        KillProcess("boxUpdate.exe");

    str = "Not Running";
    GetDlgItem(IDC_EDIT4)->SetWindowTextW(str);
}
// FindProcess
// 这个函数唯一的参数是你指定的进程名，如:你的目标进程
// 是 "Notepad.exe",返回值是该进程的ID，失败返回0
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
// 此函数中用上面的 FindProcess 函数获得你的目标进程的ID
// 用WIN API OpenPorcess 获得此进程的句柄，再以TerminateProcess
// 强制结束这个进程
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
// 在 Windows NT/2000/XP 中可能因权限不够导致以上函数失败
// 如以　System 权限运行的系统进程，服务进程
// 用本函数取得　debug 权限即可,Winlogon.exe 都可以终止哦 :)
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






