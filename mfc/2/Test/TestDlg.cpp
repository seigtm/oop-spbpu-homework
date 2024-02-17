
// TestDlg.cpp: файл реализации
//

#include "pch.h"
#include "framework.h"
#include "Test.h"
#include "TestDlg.h"
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
    void DoDataExchange(CDataExchange* pDX) final;  // поддержка DDX/DDV

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


// Диалоговое окно CTestDlg


CTestDlg::CTestDlg(CWnd* pParent /*=nullptr*/)
    : CDialogEx(IDD_TEST_DIALOG, pParent), m_EnableCheck(FALSE), m_VisibleCheck(FALSE) {
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTestDlg::DoDataExchange(CDataExchange* pDX) {
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_TEST_EDIT, m_TestEdit);
    DDX_Check(pDX, IDC_ENABLED_CHECK, m_EnableCheck);
    DDX_Check(pDX, IDC_VISIBLE_CHECK, m_VisibleCheck);
}

BEGIN_MESSAGE_MAP(CTestDlg, CDialogEx)
ON_WM_SYSCOMMAND()
ON_WM_PAINT()
ON_WM_QUERYDRAGICON()
ON_BN_CLICKED(IDC_EXIT_BUTTON, &CTestDlg::OnExitButton)
ON_BN_CLICKED(IDC_TEST_BUTTON, &CTestDlg::OnTestButton)
ON_BN_CLICKED(IDC_CLEAR_BUTTON, &CTestDlg::OnClearButton)
ON_BN_CLICKED(IDC_VISIBLE_CHECK, &CTestDlg::OnVisibleCheck)
ON_EN_CHANGE(IDC_TEST_EDIT, &CTestDlg::OnChangeTestEdit)
ON_BN_CLICKED(IDC_ENABLED_CHECK, &CTestDlg::OnEnabledCheck)
END_MESSAGE_MAP()


// Обработчики сообщений CTestDlg

BOOL CTestDlg::OnInitDialog() {
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

    // Устаноить переменную флажка VisibleCheck и EnabledCheck в состояние
    // TRUE
    m_VisibleCheck = TRUE;
    m_EnableCheck = TRUE;
    // Обновить экран
    UpdateData(FALSE);

    return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

void CTestDlg::OnSysCommand(UINT nID, LPARAM lParam) {
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

void CTestDlg::OnPaint() {
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
HCURSOR CTestDlg::OnQueryDragIcon() {
    return m_hIcon;
}


void CTestDlg::OnExitButton() {
    OnOK();
}


void CTestDlg::OnTestButton() {
    m_TestEdit.SetWindowText(_T("This is a Test"));
    UpdateData(FALSE);
}


void CTestDlg::OnClearButton() {
    m_TestEdit.SetWindowText(_T(""));
    UpdateData(FALSE);
}


void CTestDlg::OnVisibleCheck() {
    UpdateData(TRUE);
    GetDlgItem(IDC_TEST_EDIT)->ShowWindow(m_VisibleCheck ? SW_SHOW : SW_HIDE);
}


void CTestDlg::OnChangeTestEdit() {
    UpdateData(TRUE);

    CString UpperValue{};
    m_TestEdit.GetWindowText(UpperValue);
    UpperValue.MakeUpper();

    bool shouldClearText{ false };

    if(UpperValue == _T("PAINT")) {
        ::ShellExecute(nullptr, _T("open"), _T("pbrush.exe"), nullptr, nullptr, SW_SHOWNORMAL);
        shouldClearText = true;
    } else if(UpperValue == _T("CALCULATOR")) {
        ::ShellExecute(nullptr, _T("open"), _T("calc.exe"), nullptr, nullptr, SW_SHOWNORMAL);
        shouldClearText = true;
    } else if(UpperValue == _T("BEEP")) {
        ::MessageBeep(static_cast<UINT>(-2));
        shouldClearText = true;
    }

    if(shouldClearText) {
        m_TestEdit.SetWindowText(_T(""));
        UpdateData(FALSE);
    }
}


void CTestDlg::OnEnabledCheck() {
    UpdateData(TRUE);
    GetDlgItem(IDC_TEST_EDIT)->EnableWindow(m_EnableCheck ? SW_SHOW : SW_HIDE);
}
