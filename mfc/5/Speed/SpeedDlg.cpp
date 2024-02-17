
// SpeedDlg.cpp: файл реализации
//

#include "pch.h"
#include "framework.h"
#include "Speed.h"
#include "SpeedDlg.h"
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


// Диалоговое окно CSpeedDlg


CSpeedDlg::CSpeedDlg(CWnd* pParent /*=nullptr*/)
    : CDialogEx(IDD_SPEED_DIALOG, pParent)
    , m_SpeedEdit(0) {
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
    //  m_SpeedEdit = 0;
}

void CSpeedDlg::DoDataExchange(CDataExchange* pDX) {
    CDialogEx::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_SPEED_EDIT, m_SpeedEdit);
}

BEGIN_MESSAGE_MAP(CSpeedDlg, CDialogEx)
ON_WM_SYSCOMMAND()
ON_WM_PAINT()
ON_WM_QUERYDRAGICON()
ON_EN_CHANGE(IDC_SPEED_EDIT, &CSpeedDlg::OnChangeSpeedEdit)
ON_COMMAND(ID_FILE_CURRENTSPEED, &CSpeedDlg::OnFileCurrentspeed)
ON_COMMAND(ID_FILE_EXIT, &CSpeedDlg::OnFileExit)
ON_COMMAND(ID_HELP_ABOUT, &CSpeedDlg::OnHelpAbout)
ON_COMMAND(ID_HELP_SAYHELLO, &CSpeedDlg::OnHelpSayhello)
END_MESSAGE_MAP()


// Обработчики сообщений CSpeedDlg

BOOL CSpeedDlg::OnInitDialog() {
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

void CSpeedDlg::OnSysCommand(UINT nID, LPARAM lParam) {
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

void CSpeedDlg::OnPaint() {
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
HCURSOR CSpeedDlg::OnQueryDragIcon() {
    return m_hIcon;
}


void CSpeedDlg::OnChangeSpeedEdit() {
    UpdateData(TRUE);
}


void CSpeedDlg::OnFileCurrentspeed() {
    CString strSpeed;
    strSpeed.Format(_T("%d"), m_SpeedEdit);  // Convert integer to string.
    MessageBox(strSpeed);
}


void CSpeedDlg::OnFileExit() {
    OnOK();
}


void CSpeedDlg::OnHelpAbout() {
    CAboutDlg dlg;
    dlg.DoModal();
}


void CSpeedDlg::OnHelpSayhello() {
    MessageBox(L"Hello!");
}
