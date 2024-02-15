
// HelloDlg.h: файл заголовка
//

#pragma once


// Диалоговое окно CHelloDlg
class CHelloDlg : public CDialogEx {
    // Создание
public:
    CHelloDlg(CWnd* pParent = nullptr);  // стандартный конструктор

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_HELLO_DIALOG };
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
    afx_msg void OnBnClickedButton1();
    afx_msg void OnExitButton();
    afx_msg void OnSayhelloButton();
    afx_msg void OnBeepButton();
};
