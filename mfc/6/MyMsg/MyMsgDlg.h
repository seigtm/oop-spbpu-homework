
// MyMsgDlg.h: файл заголовка
//

#pragma once


// Диалоговое окно CMyMsgDlg
class CMyMsgDlg : public CDialogEx {
    // Создание
public:
    CMyMsgDlg(CWnd* pParent = nullptr);  // стандартный конструктор

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_MYMSG_DIALOG };
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
    CString m_ResultsEdit;
    afx_msg void OnExitButton();
    afx_msg void OnOkcancelButton();
    afx_msg void OnYesnocancelButton();
    afx_msg void OnRetrycancelButton();
    afx_msg void OnYesnoButton();
};
