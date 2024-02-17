
// TasksView.cpp: реализация класса CTasksView
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS можно определить в обработчиках фильтров просмотра реализации проекта ATL, эскизов
// и поиска; позволяет совместно использовать код документа в данным проекте.
#ifndef SHARED_HANDLERS
#include "Tasks.h"
#endif

#include "TasksDoc.h"
#include "TasksView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTasksView

IMPLEMENT_DYNCREATE(CTasksView, CFormView)

BEGIN_MESSAGE_MAP(CTasksView, CFormView)
END_MESSAGE_MAP()

// Создание или уничтожение CTasksView

CTasksView::CTasksView() noexcept
    : CFormView(IDD_TASKS_FORM)
    , m_EnableTask1Check(FALSE)
    , m_EnableTask2Check(FALSE)
    , m_EnableTask3Check(FALSE)
    , m_Task1Edit(0)
    , m_Task2Edit(0)
    , m_Task3Edit(0) {}

CTasksView::~CTasksView() {
}

void CTasksView::DoDataExchange(CDataExchange* pDX) {
    CFormView::DoDataExchange(pDX);
    DDX_Check(pDX, IDC_ENABLE_TASK1_CHECK, m_EnableTask1Check);
    DDX_Check(pDX, IDC_ENABLE_TASK2_CHECK, m_EnableTask2Check);
    DDX_Check(pDX, IDC_ENABLE_TASK3_CHECK, m_EnableTask3Check);
    DDX_Text(pDX, IDC_TASK1_EDIT, m_Task1Edit);
    DDX_Text(pDX, IDC_TASK2_EDIT, m_Task2Edit);
    DDX_Text(pDX, IDC_TASK3_EDIT, m_Task3Edit);
}

BOOL CTasksView::PreCreateWindow(CREATESTRUCT& cs) {
    return CFormView::PreCreateWindow(cs);
}

void CTasksView::OnInitialUpdate() {
    CFormView::OnInitialUpdate();
    GetParentFrame()->RecalcLayout();
    ResizeParentToFit();

    m_EnableTask1Check = TRUE;
    m_EnableTask2Check = TRUE;
    m_EnableTask3Check = TRUE;
    UpdateData(FALSE);
}


// Диагностика CTasksView

#ifdef _DEBUG
void CTasksView::AssertValid() const {
    CFormView::AssertValid();
}

void CTasksView::Dump(CDumpContext& dc) const {
    CFormView::Dump(dc);
}

CTasksDoc* CTasksView::GetDocument() const  // встроена неотлаженная версия
{
    ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTasksDoc)));
    return (CTasksDoc*)m_pDocument;
}
#endif  //_DEBUG


// Обработчики сообщений CTasksView
