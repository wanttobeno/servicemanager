#include <windows.h>
#include <commctrl.h>
#include <stdio.h>
#include "resource.h"
#include "ServiceTools.h"

HINSTANCE hInst;

static void Error(HWND hwndDlg)
{
    LPTSTR errorText=NULL;
    FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM|FORMAT_MESSAGE_ALLOCATE_BUFFER|FORMAT_MESSAGE_IGNORE_INSERTS, NULL, GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&errorText, 0, NULL);
    if(errorText)
    {
        MessageBoxA(hwndDlg, errorText, "Error...", MB_ICONERROR);
        LocalFree(errorText);
    }
}

BOOL CALLBACK DlgMain(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {
    case WM_INITDIALOG:
    {
        SendMessageA(hwndDlg, WM_SETICON, ICON_BIG, (LPARAM)LoadIconA(hInst, MAKEINTRESOURCEA(IDI_ICON1)));
    }
    return TRUE;

    case WM_CLOSE:
    {
        EndDialog(hwndDlg, 0);
    }
    return TRUE;

    case WM_COMMAND:
    {
        switch(LOWORD(wParam))
        {
        case IDC_BTN_CREATE:
        {
            SetFocus(GetDlgItem(hwndDlg, IDC_EDT_PATH));
            char path[MAX_PATH]="";
            if(!GetDlgItemTextA(hwndDlg, IDC_EDT_PATH, path, MAX_PATH))
            {
                MessageBoxA(hwndDlg, "No path specified!", "Error...", MB_ICONERROR);
                return TRUE;
            }
            char name[256]="";
            if(!GetDlgItemTextA(hwndDlg, IDC_EDT_NAME, name, 256))
            {
                MessageBoxA(hwndDlg, "No name specified!", "Error...", MB_ICONERROR);
                return TRUE;
            }
            if(!createService(name, path))
                Error(hwndDlg);
            else
                MessageBoxA(hwndDlg, "Service created!", "Success!", MB_ICONINFORMATION);
        }
        return TRUE;

        case IDC_BTN_START:
        {
            SetFocus(GetDlgItem(hwndDlg, IDC_EDT_PATH));
            char name[256]="";
            if(!GetDlgItemTextA(hwndDlg, IDC_EDT_NAME, name, 256))
            {
                MessageBoxA(hwndDlg, "No name specified!", "Error...", MB_ICONERROR);
                return TRUE;
            }
            if(!startService(name))
                Error(hwndDlg);
            else
                MessageBoxA(hwndDlg, "Service started!", "Success!", MB_ICONINFORMATION);
        }
        return TRUE;

        case IDC_BTN_STOP:
        {
            SetFocus(GetDlgItem(hwndDlg, IDC_EDT_PATH));
            char name[256]="";
            if(!GetDlgItemTextA(hwndDlg, IDC_EDT_NAME, name, 256))
            {
                MessageBoxA(hwndDlg, "No name specified!", "Error...", MB_ICONERROR);
                return TRUE;
            }
            if(!stopService(name))
                Error(hwndDlg);
            else
                MessageBoxA(hwndDlg, "Service stopped!", "Success!", MB_ICONINFORMATION);
        }
        return TRUE;

        case IDC_BTN_DELETE:
        {
            SetFocus(GetDlgItem(hwndDlg, IDC_EDT_PATH));
            char name[256]="";
            if(!GetDlgItemTextA(hwndDlg, IDC_EDT_NAME, name, 256))
            {
                MessageBoxA(hwndDlg, "No name specified!", "Error...", MB_ICONERROR);
                return TRUE;
            }
            if(!deleteService(name))
                Error(hwndDlg);
            else
                MessageBoxA(hwndDlg, "Service deleted!", "Success!", MB_ICONINFORMATION);
        }
        return TRUE;

        case IDC_BTN_ABOUT:
        {
            SetFocus(GetDlgItem(hwndDlg, IDC_EDT_PATH));
            MessageBoxA(hwndDlg, "Created by: Mr. eXoDia\nIcon by: http://victorerixon.com/", "About", MB_ICONINFORMATION);
        }
        return TRUE;
        }
    }
    return TRUE;
    }
    return FALSE;
}


int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    hInst=hInstance;
    InitCommonControls();
    return DialogBox(hInst, MAKEINTRESOURCE(DLG_MAIN), NULL, (DLGPROC)DlgMain);
}
