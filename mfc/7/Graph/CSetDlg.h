#pragma once
#include "afxdialogex.h"


// Диалоговое окно CSetDlg

class CSetDlg : public CDialog {
    DECLARE_DYNAMIC(CSetDlg)

public:
    CSetDlg(CWnd* pParent = nullptr);  // стандартный конструктор
    virtual ~CSetDlg();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_CSetDlg };
#endif
    int m_RedRadio;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);  // поддержка DDX/DDV

    // Generated message map functions
    afx_msg void OnRedRadio();
    afx_msg void OnBlueRadio();
    afx_msg void OnGreenRadio();

    DECLARE_MESSAGE_MAP()
};
