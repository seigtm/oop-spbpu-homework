
// GraphDlg.h: файл заголовка
//

#pragma once
#include "CSetDlg.h"

// Диалоговое окно CGraphDlg
class CGraphDlg : public CDialogEx {
    // Создание
public:
    CGraphDlg(CWnd* pParent = nullptr);  // стандартный конструктор

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_GRAPH_DIALOG };
#endif

    CSetDlg m_dlg;

    int m_Radius;
    int m_Direction;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);  // поддержка DDX/DDV


    // Реализация
protected:
    HICON m_hIcon;

    // Созданные функции схемы сообщений
    virtual BOOL OnInitDialog();
    afx_msg void OnPaint();
    afx_msg HCURSOR OnQueryDragIcon();
    DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnExitButton();
    afx_msg void OnDestroy();
    afx_msg void OnTimer(UINT_PTR nIDEvent);
    afx_msg void OnDrawgraphicsButton();
};
