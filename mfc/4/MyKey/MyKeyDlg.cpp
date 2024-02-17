
// MyKeyDlg.cpp: файл реализации
//

#include "pch.h"
#include "framework.h"
#include "MyKey.h"
#include "MyKeyDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Диалоговое окно CMyKeyDlg


CMyKeyDlg::CMyKeyDlg(CWnd* pParent /*=nullptr*/)
    : CDialogEx(IDD_MYKEY_DIALOG, pParent) {
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMyKeyDlg::DoDataExchange(CDataExchange* pDX) {
    CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMyKeyDlg, CDialogEx)
ON_WM_PAINT()
ON_WM_QUERYDRAGICON()
ON_WM_KEYDOWN()
END_MESSAGE_MAP()


// Обработчики сообщений CMyKeyDlg

BOOL CMyKeyDlg::OnInitDialog() {
    CDialogEx::OnInitDialog();

    // Задает значок для этого диалогового окна.  Среда делает это автоматически,
    //  если главное окно приложения не является диалоговым
    SetIcon(m_hIcon, TRUE);   // Крупный значок
    SetIcon(m_hIcon, FALSE);  // Мелкий значок

    // TODO: добавьте дополнительную инициализацию

    return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок.  Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void CMyKeyDlg::OnPaint() {
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
HCURSOR CMyKeyDlg::OnQueryDragIcon() {
    return m_hIcon;
}


void CMyKeyDlg::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
    CString strKeyPressed;
    strKeyPressed.Format(_T("You pressed the key:\nnChar=%u\nnReptCnt=%u\nnFlags=%u"),
                         nChar, nRepCnt, nFlags);

    MessageBox(strKeyPressed);

    CDialogEx::OnKeyDown(nChar, nRepCnt, nFlags);
}
