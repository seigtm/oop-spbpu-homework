
// TasksView.h: интерфейс класса CTasksView
//

#pragma once


class CTasksView : public CFormView {
protected:  // создать только из сериализации
    CTasksView() noexcept;
    DECLARE_DYNCREATE(CTasksView)

public:
#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_TASKS_FORM };
#endif

    // Атрибуты
public:
    CTasksDoc* GetDocument() const;

    // Операции
public:
    // Переопределение
public:
    virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

protected:
    virtual void DoDataExchange(CDataExchange* pDX);  // поддержка DDX/DDV
    virtual void OnInitialUpdate();                   // вызывается в первый раз после конструктора

    // Реализация
public:
    virtual ~CTasksView();
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

protected:
    // Созданные функции схемы сообщений
protected:
    DECLARE_MESSAGE_MAP()
public:
    BOOL m_EnableTask1Check;
    BOOL m_EnableTask2Check;
    BOOL m_EnableTask3Check;
    long m_Task1Edit;
    long m_Task2Edit;
    long m_Task3Edit;
};

#ifndef _DEBUG  // версия отладки в TasksView.cpp
inline CTasksDoc* CTasksView::GetDocument() const { return reinterpret_cast<CTasksDoc*>(m_pDocument); }
#endif
