
// MFCApplication1Dlg.h : ͷ�ļ�
//

#pragma once


// CMFCApplication1Dlg �Ի���
class CMFCApplication1Dlg : public CDialogEx
{
// ����
public:
	CMFCApplication1Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCAPPLICATION1_DIALOG };
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
    afx_msg void OnBnClickedButton1();
    afx_msg void OnBnClickedCollector();
    afx_msg void OnEnChangeEdit1();
    afx_msg void OnBnClickedCostart();
//USER DEFINED
private:
    bool isCollectorMonitored;
    bool isAgentServerMonitored;
    bool isAdapterMonitored;
    bool isBoxUpdateMonitored;
public:
    afx_msg void OnBnClickedCostop();
    afx_msg void OnBnClickedAgstop();
    afx_msg void OnBnClickedAdstop();
    afx_msg void OnBnClickedBostop();
    afx_msg void OnBnClickedAgstart();
    afx_msg void OnBnClickedAdstart();
    afx_msg void OnBnClickedBostart();
};
