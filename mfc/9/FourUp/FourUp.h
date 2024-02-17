
// FourUp.h: главный файл заголовка для приложения PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
#error "включить pch.h до включения этого файла в PCH"
#endif

#include "resource.h"  // основные символы


// CFourUpApp:
// Сведения о реализации этого класса: FourUp.cpp
//

class CFourUpApp : public CWinApp {
public:
    CFourUpApp();

    // Переопределение
public:
    virtual BOOL InitInstance();

    // Реализация

    DECLARE_MESSAGE_MAP()
};

extern CFourUpApp theApp;
