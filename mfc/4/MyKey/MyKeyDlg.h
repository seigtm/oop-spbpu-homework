﻿
// MyKeyDlg.h: файл заголовка
//

#pragma once


// Диалоговое окно CMyKeyDlg
class CMyKeyDlg : public CDialogEx {
    // Создание
public:
    CMyKeyDlg(CWnd* pParent = nullptr);  // стандартный конструктор

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_MYKEY_DIALOG };
#endif

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
    afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};
