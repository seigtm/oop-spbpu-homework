
// TasksDoc.cpp: реализация класса CTasksDoc
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS можно определить в обработчиках фильтров просмотра реализации проекта ATL, эскизов
// и поиска; позволяет совместно использовать код документа в данным проекте.
#ifndef SHARED_HANDLERS
#include "Tasks.h"
#endif

#include "TasksDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CTasksDoc

IMPLEMENT_DYNCREATE(CTasksDoc, CDocument)

BEGIN_MESSAGE_MAP(CTasksDoc, CDocument)
END_MESSAGE_MAP()


// Создание или уничтожение CTasksDoc

CTasksDoc::CTasksDoc() noexcept {
    // TODO: добавьте код для одноразового вызова конструктора
}

CTasksDoc::~CTasksDoc() {
}

BOOL CTasksDoc::OnNewDocument() {
    if(!CDocument::OnNewDocument())
        return FALSE;

    // TODO: добавьте код повторной инициализации
    // (Документы SDI будут повторно использовать этот документ)

    return TRUE;
}


// Сериализация CTasksDoc

void CTasksDoc::Serialize(CArchive& ar) {
    if(ar.IsStoring()) {
        // TODO: добавьте код сохранения
    } else {
        // TODO: добавьте код загрузки
    }
}

#ifdef SHARED_HANDLERS

// Поддержка для эскизов
void CTasksDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds) {
    // Измените этот код для отображения данных документа
    dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

    CString strText = _T("TODO: implement thumbnail drawing here");
    LOGFONT lf;

    CFont* pDefaultGUIFont = CFont::FromHandle((HFONT)GetStockObject(DEFAULT_GUI_FONT));
    pDefaultGUIFont->GetLogFont(&lf);
    lf.lfHeight = 36;

    CFont fontDraw;
    fontDraw.CreateFontIndirect(&lf);

    CFont* pOldFont = dc.SelectObject(&fontDraw);
    dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
    dc.SelectObject(pOldFont);
}

// Поддержка обработчиков поиска
void CTasksDoc::InitializeSearchContent() {
    CString strSearchContent;
    // Задание содержимого поиска из данных документа.
    // Части содержимого должны разделяться точкой с запятой ";"

    // Например:  strSearchContent = _T("точка;прямоугольник;круг;объект ole;");
    SetSearchContent(strSearchContent);
}

void CTasksDoc::SetSearchContent(const CString& value) {
    if(value.IsEmpty()) {
        RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
    } else {
        CMFCFilterChunkValueImpl* pChunk = nullptr;
        ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
        if(pChunk != nullptr) {
            pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
            SetChunkValue(pChunk);
        }
    }
}

#endif  // SHARED_HANDLERS

// Диагностика CTasksDoc

#ifdef _DEBUG
void CTasksDoc::AssertValid() const {
    CDocument::AssertValid();
}

void CTasksDoc::Dump(CDumpContext& dc) const {
    CDocument::Dump(dc);
}
#endif  //_DEBUG


// Команды CTasksDoc
