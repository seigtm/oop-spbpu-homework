
// FourUpDlg.h: файл заголовка
//

#pragma once


// Диалоговое окно CFourUpDlg
class CFourUpDlg : public CDialogEx {
    // Создание
public:
    CFourUpDlg(CWnd* pParent = nullptr);  // стандартный конструктор

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_FOURUP_DIALOG };
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

private:
    HICON m_Club;
    HICON m_Diamond;
    HICON m_Spade;
    HICON m_Heart;

    double m_Amt_Remaining;
    int m_Cards[5];

public:
    void CalculateWinnings();
    HICON& PickRandomCard();
    void DealCards();
    void OnDealcards();
    afx_msg void OnCancel();

    CStatic m_Card1;
    CStatic m_Card2;
    CStatic m_Card3;
    CStatic m_Card4;
    CStatic m_Amt_Left;
};
