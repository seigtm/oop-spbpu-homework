
// MyKey.h: главный файл заголовка для приложения PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
#error "включить pch.h до включения этого файла в PCH"
#endif

#include "resource.h"  // основные символы


// CMyKeyApp:
// Сведения о реализации этого класса: MyKey.cpp
//

class CMyKeyApp : public CWinApp {
public:
    CMyKeyApp();

    // Переопределение
public:
    virtual BOOL InitInstance();

    // Реализация

    DECLARE_MESSAGE_MAP()
};

extern CMyKeyApp theApp;
