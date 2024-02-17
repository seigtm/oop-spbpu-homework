
// PaintORamaDlg.cpp: файл реализации
//

#include "pch.h"
#include "framework.h"
#include "PaintORama.h"
#include "PaintORamaDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Диалоговое окно CPaintORamaDlg


CPaintORamaDlg::CPaintORamaDlg(CWnd* pParent /*=nullptr*/)
    : CDialogEx(IDD_PAINTORAMA_DIALOG, pParent), m_PenWidth(0), m_PenStyle(0) {
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
    m_PenColor = RGB(0, 0, 0);
    m_PenWidth = 1;
}

void CPaintORamaDlg::DoDataExchange(CDataExchange* pDX) {
    CDialogEx::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_PENWIDTH, m_PenWidth);
    DDV_MinMaxInt(pDX, m_PenWidth, 1, 32);
    DDX_Radio(pDX, IDC_SOLID_PEN, m_PenStyle);
    DDX_Control(pDX, IDC_SHAPES, m_ShapesCombo);
    DDX_Control(pDX, IDC_BRUSHSTYLE, m_BrushStyleList);
}

BEGIN_MESSAGE_MAP(CPaintORamaDlg, CDialogEx)
ON_WM_PAINT()
ON_WM_QUERYDRAGICON()
ON_BN_CLICKED(IDC_CLEARBTN, &CPaintORamaDlg::OnClearbtn)
ON_WM_LBUTTONDOWN()
ON_WM_MOUSEMOVE()
ON_WM_LBUTTONUP()
ON_STN_CLICKED(IDC_PENCOLOR, &CPaintORamaDlg::OnPencolor)
ON_LBN_SELCHANGE(IDC_BRUSHSTYLE, &CPaintORamaDlg::OnSelchangeBrushstyle)
ON_STN_CLICKED(IDC_BRUSHCOLOR, &CPaintORamaDlg::OnBrushcolor)
ON_WM_DESTROY()
END_MESSAGE_MAP()


// Обработчики сообщений CPaintORamaDlg

BOOL CPaintORamaDlg::OnInitDialog() {
    CDialogEx::OnInitDialog();

    // Задает значок для этого диалогового окна.  Среда делает это автоматически,
    //  если главное окно приложения не является диалоговым
    SetIcon(m_hIcon, TRUE);   // Крупный значок
    SetIcon(m_hIcon, FALSE);  // Мелкий значок

    // Получить указатель на элемент управления Picture
    CWnd const* p_Canvas{ GetDlgItem(IDC_CANVAS) };

    // Записать координаты окна в переменную m_Canvas
    p_Canvas->GetWindowRect(&m_Canvas);

    // Сопоставить координаты для клиентской области
    ScreenToClient(&m_Canvas);

    // Изменить координаты окна
    m_Canvas.DeflateRect(2, 2, 1, 1);

    // Получить указатель на элемент управления
    CWnd const* pPenColor{ GetDlgItem(IDC_PENCOLOR) };

    // Получить координаты элемента управления
    pPenColor->GetWindowRect(&m_PenColorSwatch);

    // Изменить координаты относительно клиентской области
    ScreenToClient(&m_PenColorSwatch);

    // Cузить рамку
    // m_PenColorSwatch.DeflateRect(2,2,1,1);

    // Получить указатель на элемент управления
    CSpinButtonCtrl* pSpin = (CSpinButtonCtrl*)GetDlgItem(IDC_SPIN1);

    // Установить диапазон значений непосредственно для IDC_SPIN1
    pSpin->SetRange(1, 32);

    // Установить начальное значение счетчика в 1;
    pSpin->SetPos(1);

    // Установить начальную позицию курсора
    m_ShapesCombo.SetCurSel(0);

    // Получить указатель на элемент управления
    CWnd* pBrushColor = GetDlgItem(IDC_BRUSHCOLOR);

    // Получить координаты элемента управления
    pBrushColor->GetWindowRect(&m_BrushColorSwatch);

    // Изменить координаты относительно клиентской области
    ScreenToClient(&m_BrushColorSwatch);

    // Cузить рамку
    m_BrushColorSwatch.DeflateRect(2, 2, 1, 1);


    // Получить указатель на элемент управления
    CWnd* pPreviewColor = GetDlgItem(IDC_BRUSHPREVIEW);

    // Получить координаты элемента управления
    pPreviewColor->GetWindowRect(&m_BrushPreviewSwatch);

    // Изменить координаты относительно клиентской области
    ScreenToClient(&m_BrushPreviewSwatch);

    // Cузить рамку
    m_BrushPreviewSwatch.DeflateRect(2, 2, 1, 1);

    // Установить начальный цвет кисти
    m_BrushColor = RGB(0, 0, 0);

    // Создать белую кисть
    m_Brush.CreateStockObject(WHITE_BRUSH);

    // Добавить названия стилей в элемент ListBox
    m_BrushStyleList.AddString(L"(none)");
    m_BrushStyleList.AddString(L"Solid");
    m_BrushStyleList.AddString(L"LL-UR Diagonal");
    m_BrushStyleList.AddString(L"UL-LR Diagonal");
    m_BrushStyleList.AddString(L"Grid");
    m_BrushStyleList.AddString(L"Grid Diagonal");
    m_BrushStyleList.AddString(L"Horizontal");
    m_BrushStyleList.AddString(L"Vertical");
    m_BrushStyleList.AddString(L"White");
    m_BrushStyleList.AddString(L"Light Gray");
    m_BrushStyleList.AddString(L"Medium Gray");
    m_BrushStyleList.AddString(L"Dark Gray");
    m_BrushStyleList.AddString(L"Black");

    // Установить начальную позицию курсора на 8 элементе
    m_BrushStyleList.SetCurSel(8);

    // Разместить в памяти объект метафайла
    m_pMF = new CMetaFileDC;
    // Создать МетаФайл
    m_pMF->Create();

    return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок.  Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void CPaintORamaDlg::OnPaint() {
    CPaintDC dc(this);

    // Закрытие метафайла
    HMETAFILE hmf = m_pMF->Close();
    // Воспроизведение метафайла
    dc.PlayMetaFile(hmf);

    // Присваивание указателя на старый объект переменной temp
    CMetaFileDC* temp = new CMetaFileDC;
    // Закрытие объекта
    temp->Create();
    // Проигрование метафайла
    temp->PlayMetaFile(hmf);

    // Удаление метаструктуры и метафайла
    DeleteMetaFile(hmf);

    // Присваивание временного указателя постоянному
    delete m_pMF;
    m_pMF = temp;

    // Если первый раз была вызвана функия OnPaint, то вызавать очистку экрана
    static BOOL firstTime = TRUE;
    if(firstTime) {
        OnClearbtn();
        firstTime = FALSE;
    }
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR CPaintORamaDlg::OnQueryDragIcon() {
    return m_hIcon;
}

void CPaintORamaDlg::DrawShape(bool stretch) {
    // Получить объект контекста устройства
    CClientDC dc(this);

    // Установить атрибуты DC
    dc.SetAttribDC(dc);
    dc.SelectObject(&m_Brush);
    m_pMF->SetAttribDC(dc);
    dc.IntersectClipRect(m_Canvas);
    m_pMF->IntersectClipRect(m_Canvas);

    // Получить номер позиции из спика названий фигур
    int drawmode = m_ShapesCombo.GetCurSel();

    // Выбрать перо
    dc.SelectObject(&m_Pen);
    dc.SelectObject(&m_Brush);
    // Записать операторы в метафайл
    m_pMF->SelectObject(&m_Pen);
    m_pMF->SelectObject(&m_Brush);

    // Метод резиновой нити
    if(stretch && drawmode != 0) {
        // Установить метод резиновой нити
        dc.SetROP2(R2_NOT);
    }

    // Конструкция выбора фигуры
    switch(drawmode) {
        // Свободное рисование
        case 0:
            dc.MoveTo(m_LineStart);
            dc.LineTo(m_LineEnd);
            // Записать операторы в метафайл
            m_pMF->MoveTo(m_LineStart);
            m_pMF->LineTo(m_LineEnd);
            m_LineStart = m_LineEnd;
            break;

        // Рисование линий
        case 1:
            dc.MoveTo(m_LineStart);
            dc.LineTo(m_LineEnd);
            /*Записать операторы в метафайл, если не выбран режим резиновой нити*/
            if(!stretch) {
                m_pMF->MoveTo(m_LineStart);
                m_pMF->LineTo(m_LineEnd);
            }
            break;

        // Рисование элипсов
        case 2:
            dc.Ellipse(CRect(m_LineStart, m_LineEnd));
            // Записать операторы в метафайл
            if(!stretch) {
                m_pMF->Ellipse(CRect(m_LineStart, m_LineEnd));
            }
            break;

        // Рисование прямоугольника
        case 3:
            dc.Rectangle(CRect(m_LineStart, m_LineEnd));
            // Записать операторы в метафайл
            if(!stretch) {
                m_pMF->Rectangle(CRect(m_LineStart, m_LineEnd));
            }
            break;
    }
}

void CPaintORamaDlg::PaintBrushPreview() {
    CClientDC dc(this);
    dc.FillRect(&m_BrushPreviewSwatch, &m_Brush);
}


void CPaintORamaDlg::OnClearbtn() {
    CClientDC dc(this);
    // Закрыть метафайл
    HMETAFILE hmf = m_pMF->Close();
    // Удалить данные о метафайле
    ::DeleteMetaFile(hmf);

    // Cоздать новый метафайл
    delete m_pMF;
    m_pMF = new CMetaFileDC;
    m_pMF->Create();
    m_pMF->SetAttribDC(dc);
    // Закрасить область рисования белым цветом
    dc.SelectStockObject(NULL_PEN);
    dc.Rectangle(m_Canvas);

    // Записать команды в метафайл
    m_pMF->SelectStockObject(NULL_PEN);
    m_pMF->Rectangle(m_Canvas.left, m_Canvas.top,
                     m_Canvas.right + 1, m_Canvas.bottom + 1);
}


void CPaintORamaDlg::OnLButtonDown(UINT nFlags, CPoint point) {
    // Проверить было ли нажатие внутри области рисования.
    if(m_Canvas.PtInRect(point)) {
        // Присвоить координаты начала двум переменным
        m_LineStart = point;
        m_LineEnd = point;

        m_IsDrawing = true;

        m_Pen.DeleteObject();

        // Обновить переменные значениями в окне прграммы
        UpdateData(TRUE);

        // Создать новую кисть с учетом размера
        m_Pen.CreatePen(m_PenStyle, m_PenWidth, m_PenColor);

        /////-Ваш код заканчивается здесь-/////

        // Захватить мышь
        SetCapture();
    }

    CDialogEx::OnLButtonDown(nFlags, point);
}


void CPaintORamaDlg::OnMouseMove(UINT nFlags, CPoint point) {
    if(m_IsDrawing && (nFlags & MK_LBUTTON) && m_Canvas.PtInRect(point)) {
        // Нарисовать фигуру методом резиновой нити
        DrawShape(true);

        // Поменять координаты конца на текущее положение курсора
        m_LineStart = m_LineEnd;

        // Стереть предыдущую и нарисовать новую фигуру
        DrawShape(true);
    }

    CDialogEx::OnMouseMove(nFlags, point);
}


void CPaintORamaDlg::OnLButtonUp(UINT nFlags, CPoint point) {
    // Отключить режим рисования
    m_IsDrawing = FALSE;

    /*Если мышка отпущена внутри области рисования, то нарисовать фигуру окончательно*/
    if(m_Canvas.PtInRect(point)) {
        m_LineEnd = point;
        DrawShape();
    }
    // Если нет, то стереть
    else {
        DrawShape(true);
    }
    m_LineStart = point;

    // Отпустить мышь
    ReleaseCapture();

    CDialogEx::OnLButtonUp(nFlags, point);
}


void CPaintORamaDlg::OnPencolor() {
    // Создать объект класса диалоговой панели выбора цвета и передать ему
    // в конструкторе текущее значение цвета
    CColorDialog dlg(m_PenColor);

    // Вывод диалогового окна
    if(dlg.DoModal() == IDOK) {
        // Установка цвета
        m_PenColor = dlg.GetColor();

        // Создание кисти
        CBrush swatch;
        swatch.CreateSolidBrush(m_PenColor);

        // Получить объект контекста устройства
        CClientDC dc(this);

        // Закрашивание индикатора выбранным цветом
        dc.FillRect(&m_PenColorSwatch, &swatch);
    }
}


void CPaintORamaDlg::OnSelchangeBrushstyle() {
    // Удалить предыдущий объект
    m_Brush.DeleteObject();

    // Получить номер выбранной позиции
    int style = m_BrushStyleList.GetCurSel();

    // По номеру создать кисть, с выбранным стилем
    switch(style) {
        case 0:
            m_Brush.CreateStockObject(NULL_BRUSH);
            break;

        case 1:
            m_Brush.CreateSolidBrush(m_BrushColor);
            break;

        case 2:
            m_Brush.CreateHatchBrush(HS_BDIAGONAL, m_BrushColor);
            break;

        case 3:
            m_Brush.CreateHatchBrush(HS_FDIAGONAL, m_BrushColor);
            break;

        case 4:
            m_Brush.CreateHatchBrush(HS_CROSS, m_BrushColor);
            break;

        case 5:
            m_Brush.CreateHatchBrush(HS_DIAGCROSS, m_BrushColor);
            break;

        case 6:
            m_Brush.CreateHatchBrush(HS_HORIZONTAL, m_BrushColor);
            break;

        case 7:
            m_Brush.CreateHatchBrush(HS_VERTICAL, m_BrushColor);
            break;

        case 9:
            m_Brush.CreateStockObject(LTGRAY_BRUSH);
            break;


        case 10:
            m_Brush.CreateStockObject(GRAY_BRUSH);
            break;

        case 11:
            m_Brush.CreateStockObject(DKGRAY_BRUSH);
            break;

        case 12:
            m_Brush.CreateStockObject(BLACK_BRUSH);
            break;

        // Создать кисть по умолчанию
        default:
            m_Brush.CreateStockObject(WHITE_BRUSH);
            break;
    }

    // Вызвать функцию зарисовки окна Preview
    PaintBrushPreview();
}


void CPaintORamaDlg::OnBrushcolor() {
    // Создать объект диалогового окна выбор цвета
    CColorDialog dlg(m_BrushColor);

    // Если была нажата кнопка ОК, то закрасить индикатор цвета
    if(dlg.DoModal() == IDOK) {
        m_BrushColor = dlg.GetColor();
        CClientDC dc(this);
        CBrush b(m_BrushColor);

        // Закрашивание индикатора цвета кисти
        dc.FillRect(&m_BrushColorSwatch, &b);
    }

    // Запустить функцию создания кисти, выбранным цветом
    OnSelchangeBrushstyle();
}


void CPaintORamaDlg::OnDestroy() {
    CDialogEx::OnDestroy();

    // Закрыть и удалить метафайл
    m_pMF->Close();
    delete m_pMF;
}
