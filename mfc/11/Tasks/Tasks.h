
// Tasks.h: основной файл заголовка для приложения Tasks
//
#pragma once

#ifndef __AFXWIN_H__
#error "включить pch.h до включения этого файла в PCH"
#endif

#include "resource.h"  // основные символы


// CTasksApp:
// Сведения о реализации этого класса: Tasks.cpp
//

class CTasksApp : public CWinApp {
public:
    CTasksApp() noexcept;


    // Переопределение
public:
    virtual BOOL InitInstance();

    // Реализация
    afx_msg void OnAppAbout();
    DECLARE_MESSAGE_MAP()
    virtual BOOL OnIdle(LONG lCount);
};

extern CTasksApp theApp;
