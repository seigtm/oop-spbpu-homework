
// DrawDlg.cpp: файл реализации
//

#include "pch.h"
#include "framework.h"
#include "Draw.h"
#include "DrawDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Диалоговое окно CAboutDlg используется для описания сведений о приложении

class CAboutDlg : public CDialogEx {
public:
    CAboutDlg();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_ABOUTBOX };
#endif

protected:
    virtual void DoDataExchange(CDataExchange* pDX);  // поддержка DDX/DDV

    // Реализация
protected:
    DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg()
    : CDialogEx(IDD_ABOUTBOX) {
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX) {
    CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// Диалоговое окно CDrawDlg


CDrawDlg::CDrawDlg(CWnd* pParent /*=nullptr*/)
    : CDialogEx(IDD_DRAW_DIALOG, pParent) {
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDrawDlg::DoDataExchange(CDataExchange* pDX) {
    CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDrawDlg, CDialogEx)
ON_WM_SYSCOMMAND()
ON_WM_PAINT()
ON_WM_QUERYDRAGICON()
ON_BN_CLICKED(IDC_EXIT_BUTTON, &CDrawDlg::OnExitButton)
ON_WM_MOUSEMOVE()
ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// Обработчики сообщений CDrawDlg

BOOL CDrawDlg::OnInitDialog() {
    CDialogEx::OnInitDialog();

    // Добавление пункта "О программе..." в системное меню.

    // IDM_ABOUTBOX должен быть в пределах системной команды.
    ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
    ASSERT(IDM_ABOUTBOX < 0xF000);

    CMenu* pSysMenu = GetSystemMenu(FALSE);
    if(pSysMenu != nullptr) {
        BOOL bNameValid;
        CString strAboutMenu;
        bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
        ASSERT(bNameValid);
        if(!strAboutMenu.IsEmpty()) {
            pSysMenu->AppendMenu(MF_SEPARATOR);
            pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
        }
    }

    // Задает значок для этого диалогового окна.  Среда делает это автоматически,
    //  если главное окно приложения не является диалоговым
    SetIcon(m_hIcon, TRUE);   // Крупный значок
    SetIcon(m_hIcon, FALSE);  // Мелкий значок

    // TODO: добавьте дополнительную инициализацию

    return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

void CDrawDlg::OnSysCommand(UINT nID, LPARAM lParam) {
    if((nID & 0xFFF0) == IDM_ABOUTBOX) {
        CAboutDlg dlgAbout;
        dlgAbout.DoModal();
    } else {
        CDialogEx::OnSysCommand(nID, lParam);
    }
}

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок.  Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void CDrawDlg::OnPaint() {
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
HCURSOR CDrawDlg::OnQueryDragIcon() {
    return m_hIcon;
}


void CDrawDlg::OnExitButton() {
    OnOK();
}


void CDrawDlg::OnMouseMove(UINT nFlags, CPoint point) {
    if((nFlags & MK_LBUTTON) == MK_LBUTTON) {
        CClientDC dc(this);

        CPen NewPen(PS_SOLID, 5, RGB(255, 0, 0));
        dc.SelectObject(&NewPen);

        dc.MoveTo(m_PrevX, m_PrevY);
        dc.LineTo(point.x, point.y);
        m_PrevX = point.x;
        m_PrevY = point.y;
    }

    CDialogEx::OnMouseMove(nFlags, point);
}


void CDrawDlg::OnLButtonDown(UINT nFlags, CPoint point) {
    m_PrevX = point.x;
    m_PrevY = point.y;

    CDialogEx::OnLButtonDown(nFlags, point);
}
