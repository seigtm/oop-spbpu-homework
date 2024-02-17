
// Graph.h: главный файл заголовка для приложения PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
#error "включить pch.h до включения этого файла в PCH"
#endif

#include "resource.h"  // основные символы


// CGraphApp:
// Сведения о реализации этого класса: Graph.cpp
//

class CGraphApp : public CWinApp {
public:
    CGraphApp();

    // Переопределение
public:
    virtual BOOL InitInstance();

    // Реализация

    DECLARE_MESSAGE_MAP()
};

extern CGraphApp theApp;
