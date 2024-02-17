
// BmpOpenDlg.cpp: файл реализации
//

#include "pch.h"
#include "framework.h"
#include "BmpOpen.h"
#include "BmpOpenDlg.h"
#include "afxdialogex.h"

#include "Showdib.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Диалоговое окно CBmpOpenDlg


CBmpOpenDlg::CBmpOpenDlg(CWnd* pParent /*=nullptr*/)
    : CDialogEx(IDD_BMPOPEN_DIALOG, pParent) {
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CBmpOpenDlg::DoDataExchange(CDataExchange* pDX) {
    CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CBmpOpenDlg, CDialogEx)
ON_WM_PAINT()
ON_WM_QUERYDRAGICON()
ON_COMMAND(ID_FILE_EXIT, &CBmpOpenDlg::OnFileExit)
ON_COMMAND(ID_FILE_OPEN, &CBmpOpenDlg::OnFileOpen)
END_MESSAGE_MAP()


// Обработчики сообщений CBmpOpenDlg

BOOL CBmpOpenDlg::OnInitDialog() {
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

void CBmpOpenDlg::OnPaint() {
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
        // Если открыт bmp файл
        if(hbm) {
            CClientDC dc(this);

            // Получить указатель на DC.
            HDC hdc = ::GetDC(m_hWnd);
            HDC hdcBits = ::CreateCompatibleDC(hdc);

            // Выбрать объект
            SelectObject(hdcBits, hbm);

            // Закрасить клиентскую облаcть черным цветом
            CRect wdRect;
            GetClientRect(&wdRect);
            CBrush brush;
            brush.CreateSolidBrush(RGB(0, 0, 0));
            dc.FillRect(&wdRect, &brush);

            // Вывести изображение
            BitBlt(hdc, 0, 0, bm.bmWidth, bm.bmHeight, hdcBits, 0, 0, SRCCOPY);

            // Удалить DC
            DeleteDC(hdcBits);
            ::ReleaseDC(m_hWnd, hdc);
        }

        CDialogEx::OnPaint();
    }
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR CBmpOpenDlg::OnQueryDragIcon() {
    return m_hIcon;
}


void CBmpOpenDlg::OnFileExit() {
    OnOK();
}


void CBmpOpenDlg::OnFileOpen() {
    // Заголовок и путь к файлу
    CString FileName;
    CString FileTitle;

    // Создать объект диалогового окна
    CFileDialog file(TRUE);
    // Уставновить аттрибуты диалогового окна
    file.m_ofn.lpstrFilter = TEXT("Bitmap picture files *.bmp\0*.bmp\0All Files *.*\0*.*\0\0");
    file.m_ofn.lpstrFileTitle = FileTitle.GetBuffer(_MAX_FNAME);
    file.m_ofn.lpstrFile = FileName.GetBuffer(_MAX_PATH);
    file.m_ofn.lpstrTitle = TEXT("Open BMP File");
    // Вывести диалоговое окно
    file.DoModal();

    FileName.ReleaseBuffer();
    FileTitle.ReleaseBuffer();

    // Если ничего не выбранно, то вернуться
    if(FileName.IsEmpty()) return;
    // Изменить заголовок окна на имя файла
    SetWindowText(FileTitle);

    // Получить указатель на объект в памяти
    CStringA FileNameA(FileName);
    HANDLE hdibCurrent1 = OpenDIB(FileNameA.GetBuffer());
    FileName.ReleaseBuffer();
    if(hdibCurrent1 == nullptr) {
        MessageBox(L"Что-то пошло не так при вызове OpenDIB().");
        return;
    }

    hbm = nullptr;
    // Получить указатель на изображение
    hbm = BitmapFromDib(hdibCurrent1, nullptr);

    // Записать параметры изображения
    GetObject(hbm, sizeof(BITMAP), (LPSTR)&bm);

    // Получить координаты окна
    CRect wdRect;
    GetClientRect(&wdRect);
    ClientToScreen(&wdRect);

    // Изменить размеры окна
    SetWindowPos(nullptr,
                 wdRect.left - 4,
                 wdRect.top - 42,
                 bm.bmWidth + wdRect.left,
                 bm.bmHeight + wdRect.top,
                 0);

    // Вывести картинку
    OnPaint();
}
