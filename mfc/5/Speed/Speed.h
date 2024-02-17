
// Speed.h: главный файл заголовка для приложения PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
#error "включить pch.h до включения этого файла в PCH"
#endif

#include "resource.h"  // основные символы


// CSpeedApp:
// Сведения о реализации этого класса: Speed.cpp
//

class CSpeedApp : public CWinApp {
public:
    CSpeedApp();

    // Переопределение
public:
    virtual BOOL InitInstance();

    // Реализация

    DECLARE_MESSAGE_MAP()
};

extern CSpeedApp theApp;
