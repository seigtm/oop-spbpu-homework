
// Draw.h: главный файл заголовка для приложения PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
#error "включить pch.h до включения этого файла в PCH"
#endif

#include "resource.h"  // основные символы


// CDrawApp:
// Сведения о реализации этого класса: Draw.cpp
//

class CDrawApp : public CWinApp {
public:
    CDrawApp();

    // Переопределение
public:
    virtual BOOL InitInstance();

    // Реализация

    DECLARE_MESSAGE_MAP()
};

extern CDrawApp theApp;
