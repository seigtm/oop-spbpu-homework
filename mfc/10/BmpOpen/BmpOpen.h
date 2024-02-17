
// BmpOpen.h: главный файл заголовка для приложения PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
#error "включить pch.h до включения этого файла в PCH"
#endif

#include "resource.h"  // основные символы


// CBmpOpenApp:
// Сведения о реализации этого класса: BmpOpen.cpp
//

class CBmpOpenApp : public CWinApp {
public:
    CBmpOpenApp();

    // Переопределение
public:
    virtual BOOL InitInstance();

    // Реализация

    DECLARE_MESSAGE_MAP()
};

extern CBmpOpenApp theApp;
