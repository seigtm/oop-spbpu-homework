
// TestDlg.h: файл заголовка
//

#pragma once


// Диалоговое окно CTestDlg
class CTestDlg : public CDialogEx {
    // Создание
public:
    CTestDlg(CWnd* pParent = nullptr);  // стандартный конструктор

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_TEST_DIALOG };
#endif

protected:
    virtual void DoDataExchange(CDataExchange* pDX);  // поддержка DDX/DDV


    // Реализация
protected:
    HICON m_hIcon;

    // Созданные функции схемы сообщений
    virtual BOOL OnInitDialog();
    afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
    afx_msg void OnPaint();
    afx_msg HCURSOR OnQueryDragIcon();
    DECLARE_MESSAGE_MAP()
public:
    CEdit m_TestEdit;
    BOOL m_EnableCheck;
    BOOL m_VisibleCheck;
    afx_msg void OnExitButton();
    afx_msg void OnTestButton();
    afx_msg void OnClearButton();
    afx_msg void OnVisibleCheck();
    afx_msg void OnChangeTestEdit();
    afx_msg void OnEnabledCheck();
};
