// CSetDlg.cpp: файл реализации
//

#include "pch.h"
#include "Graph.h"
#include "afxdialogex.h"
#include "CSetDlg.h"


// Диалоговое окно CSetDlg

IMPLEMENT_DYNAMIC(CSetDlg, CDialog)

CSetDlg::CSetDlg(CWnd* pParent /*=nullptr*/)
    : CDialog(IDD_CSetDlg, pParent)
    , m_RedRadio{ -1 } {
}

CSetDlg::~CSetDlg() {
}

void CSetDlg::DoDataExchange(CDataExchange* pDX) {
    CDialog::DoDataExchange(pDX);
    DDX_Radio(pDX, IDC_RED_RADIO, m_RedRadio);
}


BEGIN_MESSAGE_MAP(CSetDlg, CDialog)
ON_BN_CLICKED(IDC_RED_RADIO, OnRedRadio)
ON_BN_CLICKED(IDC_BLUE_RADIO, OnBlueRadio)
ON_BN_CLICKED(IDC_GREEN_RADIO, OnGreenRadio)
END_MESSAGE_MAP()


// Обработчики сообщений CSetDlg
void CSetDlg::OnRedRadio() {
    UpdateData(TRUE);
}


void CSetDlg::OnBlueRadio() {
    UpdateData(TRUE);
}


void CSetDlg::OnGreenRadio() {
    UpdateData(TRUE);
}
