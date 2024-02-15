
// HelloDlg.cpp: файл реализации
//

#include "pch.h"
#include "framework.h"
#include "Hello.h"
#include "HelloDlg.h"
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


// Диалоговое окно CHelloDlg


CHelloDlg::CHelloDlg(CWnd* pParent /*=nullptr*/)
    : CDialogEx(IDD_HELLO_DIALOG, pParent) {
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CHelloDlg::DoDataExchange(CDataExchange* pDX) {
    CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CHelloDlg, CDialogEx)
ON_WM_SYSCOMMAND()
ON_WM_PAINT()
ON_WM_QUERYDRAGICON()
ON_BN_CLICKED(IDC_EXIT_BUTTON, &CHelloDlg::OnExitButton)
ON_BN_CLICKED(IDC_SAYHELLO_BUTTON, &CHelloDlg::OnSayhelloButton)
ON_BN_CLICKED(IDC_BEEP_BUTTON, &CHelloDlg::OnBeepButton)
END_MESSAGE_MAP()


// Обработчики сообщений CHelloDlg

BOOL CHelloDlg::OnInitDialog() {
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

void CHelloDlg::OnSysCommand(UINT nID, LPARAM lParam) {
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

void CHelloDlg::OnPaint() {
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
HCURSOR CHelloDlg::OnQueryDragIcon() {
    return static_cast<HCURSOR>(m_hIcon);
}


void CHelloDlg::OnExitButton() {
    OnOK();
}


void CHelloDlg::OnSayhelloButton() {
    MessageBox(L"Say Hello");
}


void CHelloDlg::OnBeepButton() {
    // Note: On Windows Server 2022, the Microsoft\Windows\Multimedia\SystemSoundsService task in
    // Task Scheduler is disabled. This task will need to be enabled for MessageBeep to function.
    // Source: https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-messagebeep
    MessageBeep((WORD)-2);
}
