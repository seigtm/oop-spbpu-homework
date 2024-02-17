
// SpeedDlg.h: файл заголовка
//

#pragma once


// Диалоговое окно CSpeedDlg
class CSpeedDlg : public CDialogEx {
    // Создание
public:
    CSpeedDlg(CWnd* pParent = nullptr);  // стандартный конструктор

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_SPEED_DIALOG };
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
    // int m_SpeedEdit;
    // int m_SpeedEdit;
    int m_SpeedEdit;
    afx_msg void OnChangeSpeedEdit();
    afx_msg void OnFileCurrentspeed();
    afx_msg void OnFileExit();
    afx_msg void OnHelpAbout();
    afx_msg void OnHelpSayhello();
};
