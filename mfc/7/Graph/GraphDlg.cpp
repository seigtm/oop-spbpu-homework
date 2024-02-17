
// GraphDlg.cpp: файл реализации
//

#include "pch.h"
#include "framework.h"
#include "Graph.h"
#include "GraphDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Диалоговое окно CGraphDlg


CGraphDlg::CGraphDlg(CWnd* pParent /*=nullptr*/)
    : CDialogEx(IDD_GRAPH_DIALOG, pParent) {
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGraphDlg::DoDataExchange(CDataExchange* pDX) {
    CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CGraphDlg, CDialogEx)
ON_WM_PAINT()
ON_WM_QUERYDRAGICON()
ON_BN_CLICKED(IDC_EXIT_BUTTON, &CGraphDlg::OnExitButton)
ON_WM_DESTROY()
ON_WM_TIMER()
ON_BN_CLICKED(IDC_DRAWGRAPHICS_BUTTON, &CGraphDlg::OnDrawgraphicsButton)
END_MESSAGE_MAP()


// Обработчики сообщений CGraphDlg

BOOL CGraphDlg::OnInitDialog() {
    CDialogEx::OnInitDialog();

    // Задает значок для этого диалогового окна.  Среда делает это автоматически,
    //  если главное окно приложения не является диалоговым
    SetIcon(m_hIcon, TRUE);   // Крупный значок
    SetIcon(m_hIcon, FALSE);  // Мелкий значок

    if(!SetTimer(1, 50, nullptr)) {
        MessageBox(L"Cannot install timer",
                   L"Error message",
                   MB_OK + MB_ICONERROR);
    }

    // Выбрать радиокнопку RED.
    m_dlg.m_RedRadio = 0;

    m_Radius = 50;
    m_Direction = 1;

    return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок.  Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void CGraphDlg::OnPaint() {
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
        // Создать объект контекста устройства(DC).
        CPaintDC dc(this);

        // Создать новое перо красного цвета, толщиной линии 10 пикселов,
        // и стилем заливки PS_SOLID - сплошная заливка.
        CPen MyNewPen;

        switch(m_dlg.m_RedRadio) {
            case 0:
                MyNewPen.CreatePen(PS_SOLID, 10, RGB(255, 0, 0));
                break;
            case 1:
                MyNewPen.CreatePen(PS_SOLID, 10, RGB(0, 255, 0));
                break;
            case 2:
                MyNewPen.CreatePen(PS_SOLID, 10, RGB(0, 0, 255));
                break;
        }

        // Выбрать перо.
        CPen* pOriginalPen;
        pOriginalPen = dc.SelectObject(&MyNewPen);

        CRect MyRectangle(20, 10, 20 + m_Radius * 2, 10 + m_Radius * 2);

        // Нарисовать круг.
        dc.Ellipse(&MyRectangle);

        // Выбрать первоначальное перо.
        dc.SelectObject(pOriginalPen);
    }
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR CGraphDlg::OnQueryDragIcon() {
    return m_hIcon;
}


void CGraphDlg::OnExitButton() {
    OnOK();
}


void CGraphDlg::OnDestroy() {
    KillTimer(1);

    CDialogEx::OnDestroy();
}


void CGraphDlg::OnTimer(UINT_PTR nIDEvent) {
    m_Radius = m_Radius + m_Direction;
    if(m_Radius >= 100) {
        m_Direction = -1;
    }
    if(m_Radius <= 10) {
        m_Direction = 1;
    }
    Invalidate();

    CDialogEx::OnTimer(nIDEvent);
}


void CGraphDlg::OnDrawgraphicsButton() {
    m_dlg.DoModal();

    CDialog::OnPaint();
}
