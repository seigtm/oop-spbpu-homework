
// FourUpDlg.cpp: файл реализации
//

#include "pch.h"
#include "framework.h"
#include "FourUp.h"
#include "FourUpDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Диалоговое окно CFourUpDlg


CFourUpDlg::CFourUpDlg(CWnd* pParent /*=nullptr*/)
    : CDialogEx(IDD_FOURUP_DIALOG, pParent) {
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
    m_Club = AfxGetApp()->LoadIcon(IDI_CLUB);
    m_Diamond = AfxGetApp()->LoadIcon(IDI_DIAMOND);
    m_Heart = AfxGetApp()->LoadIcon(IDI_HEART);
    m_Spade = AfxGetApp()->LoadIcon(IDI_SPADE);
    m_Amt_Remaining = 100.0;
}

void CFourUpDlg::DoDataExchange(CDataExchange* pDX) {
    CDialogEx::DoDataExchange(pDX);

    DDX_Control(pDX, IDC_CARD1, m_Card1);
    DDX_Control(pDX, IDC_CARD2, m_Card2);
    DDX_Control(pDX, IDC_CARD3, m_Card3);
    DDX_Control(pDX, IDC_CARD4, m_Card4);
    DDX_Control(pDX, IDC_AMT_LEFT, m_Amt_Left);
}

BEGIN_MESSAGE_MAP(CFourUpDlg, CDialogEx)
ON_WM_PAINT()
ON_WM_QUERYDRAGICON()
ON_BN_CLICKED(IDC_DEALCARDS, &CFourUpDlg::OnDealcards)
ON_BN_CLICKED(IDCANCEL, &CFourUpDlg::OnCancel)
END_MESSAGE_MAP()


// Обработчики сообщений CFourUpDlg

BOOL CFourUpDlg::OnInitDialog() {
    CDialogEx::OnInitDialog();

    // Задает значок для этого диалогового окна.  Среда делает это автоматически,
    //  если главное окно приложения не является диалоговым
    SetIcon(m_hIcon, TRUE);   // Крупный значок
    SetIcon(m_hIcon, FALSE);  // Мелкий значок

    return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок.  Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void CFourUpDlg::OnPaint() {
    if(IsIconic()) {
        CPaintDC dc(this);  // контекст устройства для рисования

        SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

        // Выравнивание значка по центру клиентского прямоугольника
        int cxIcon = GetSystemMetrics(SM_CXICON);
        int cyIcon = GetSystemMetrics(SM_CYICON);
        CRect rect;
        GetClientRect(&rect);
        int x = (rect.Width() - cxIcon + 1) / 2;
        int y = (rect.Height() - cyIcon + 1) / 2;

        // Нарисуйте значок
        dc.DrawIcon(x, y, m_hIcon);
    } else {
        CDialogEx::OnPaint();
    }
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR CFourUpDlg::OnQueryDragIcon() {
    return m_hIcon;
}


void CFourUpDlg::CalculateWinnings() {
    int pairs = 0;
    for(int i = 0; i < 4; i++) {
        if(m_Cards[i] == 2) {
            if(pairs > 0) {
                m_Amt_Remaining += 3.00;
                break;
            } else {
                pairs++;
            }
        } else if(m_Cards[i] == 3) {
            m_Amt_Remaining += 6.00;
            break;

        } else if(m_Cards[i] == 4) {
            m_Amt_Remaining += 9.00;
            break;
        }
    }
}

HICON& CFourUpDlg::PickRandomCard() {
    // Выбрать номер карты случайным образом
    static std::default_random_engine gen{ std::random_device{}() };
    static std::uniform_int_distribution<int> int_dist{ 0, 3 };
    const auto num{ int_dist(gen) };
    // Проссумировать кол-во выпавших карт одной масти
    m_Cards[num]++;

    // В зависимости от выпавшего номера вернуть адрес иконки
    switch(num) {
        case 0: return m_Club;
        case 1: return m_Diamond;
        case 2: return m_Heart;
    }

    return m_Spade;
}

void CFourUpDlg::DealCards() {
    // Обнуляем заначение выпавших карт одной масти
    for(int i = 0; i < 4; i++) m_Cards[i] = 0;

    // Меняем иконку в элементах управления иконками
    m_Card1.SetIcon(PickRandomCard());
    m_Card2.SetIcon(PickRandomCard());
    m_Card3.SetIcon(PickRandomCard());
    m_Card4.SetIcon(PickRandomCard());
}

void CFourUpDlg::OnDealcards() {
    // Отнять два доллара при сдаче карт
    m_Amt_Remaining -= 2.00;

    // Сдать карты
    DealCards();

    // Подсчитать выигрыш
    CalculateWinnings();

    // Изменить заголовок элемента Group Box
    CString s;
    s.Format(L"Amount Remaining $ %.2f", m_Amt_Remaining);
    m_Amt_Left.SetWindowText(s);
}

void CFourUpDlg::OnCancel() {
    CString s;
    // Добавить в строку размер выигрыша
    s.Format(L"Good game! I have $ %.2f.", m_Amt_Remaining);
    // Выдать окно сообщения
    MessageBox(s, L"Thank you for game in FourUp!");

    CDialogEx::OnCancel();
}
