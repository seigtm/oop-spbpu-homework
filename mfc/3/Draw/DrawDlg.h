
// DrawDlg.h: файл заголовка
//

#pragma once


// Диалоговое окно CDrawDlg
class CDrawDlg : public CDialogEx {
    // Создание
public:
    CDrawDlg(CWnd* pParent = nullptr);  // стандартный конструктор

    int m_PrevX;
    int m_PrevY;

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_DRAW_DIALOG };
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
    afx_msg void OnExitButton();
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};
