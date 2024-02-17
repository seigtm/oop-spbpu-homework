
// PaintORamaDlg.h: файл заголовка
//

#pragma once


// Диалоговое окно CPaintORamaDlg
class CPaintORamaDlg : public CDialogEx {
    // Создание
public:
    void PaintBrushPreview();
    void DrawShape(bool stretch = false);
    CPaintORamaDlg(CWnd* pParent = nullptr);  // стандартный конструктор

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_PAINTORAMA_DIALOG };
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
    afx_msg void OnClearbtn();
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    afx_msg void OnPencolor();
    afx_msg void OnSelchangeBrushstyle();
    afx_msg void OnBrushcolor();
    afx_msg void OnDestroy();

    DECLARE_MESSAGE_MAP()
private:
    CMetaFileDC* m_pMF;
    CPoint m_LineEnd;
    CRect m_PenColorSwatch;
    CPen m_Pen;
    bool m_IsDrawing;
    CPoint m_LineStart;
    CRect m_Canvas;
    COLORREF m_PenColor;

    CBrush m_Brush;              // Объект кисти
    COLORREF m_BrushColor;       // Цвет заливки
    CRect m_BrushColorSwatch;    // Координаты индикатора цвета
    CRect m_BrushPreviewSwatch;  // Координаты просмотра
    int m_BrushStyle;            // Стиль закраски

    int m_PenWidth;
    int m_PenStyle;
    CComboBox m_ShapesCombo;
    CListBox m_BrushStyleList;
};
