
// BmpOpenDlg.h: файл заголовка
//

#pragma once

// Диалоговое окно CBmpOpenDlg
class CBmpOpenDlg : public CDialogEx {
    // Создание
public:
    CBmpOpenDlg(CWnd* pParent = nullptr);  // стандартный конструктор

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_BMPOPEN_DIALOG };
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
    afx_msg void OnFileExit();

private:
    BITMAP bm;    // Параметры изображения, такие как размер и т.д.
    HBITMAP hbm;  // Указатель на объект картинки в памяти.
public:
    afx_msg void OnFileOpen();
};
