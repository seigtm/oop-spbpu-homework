
// Hello.h: главный файл заголовка для приложения PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
#error "включить pch.h до включения этого файла в PCH"
#endif

#include "resource.h"  // основные символы


// CHelloApp:
// Сведения о реализации этого класса: Hello.cpp
//

class CHelloApp : public CWinApp {
public:
    CHelloApp();

    // Переопределение
public:
    virtual BOOL InitInstance();

    // Реализация

    DECLARE_MESSAGE_MAP()
};

extern CHelloApp theApp;
