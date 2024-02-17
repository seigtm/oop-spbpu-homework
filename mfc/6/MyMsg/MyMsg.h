
// MyMsg.h: главный файл заголовка для приложения PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
#error "включить pch.h до включения этого файла в PCH"
#endif

#include "resource.h"  // основные символы


// CMyMsgApp:
// Сведения о реализации этого класса: MyMsg.cpp
//

class CMyMsgApp : public CWinApp {
public:
    CMyMsgApp();

    // Переопределение
public:
    virtual BOOL InitInstance();

    // Реализация

    DECLARE_MESSAGE_MAP()
};

extern CMyMsgApp theApp;
