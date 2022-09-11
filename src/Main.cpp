#ifdef UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_IA64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='ia64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif

#include <vector>
#include <string>
#include <Windows.h>
#include "resource.h"
#include "FileSearcher.h"

#define TEST

INT_PTR CALLBACK AboutDlgProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
    switch (Message)
    {
    case WM_INITDIALOG:

        return TRUE;
    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case IDC_BUTTONCHOOSE:
            EndDialog(hwnd, IDOK);
            break;
        case IDCANCEL:
            EndDialog(hwnd, IDCANCEL);
            break;
        }
        break;
    default:
        return FALSE;
    }
    return TRUE;
}

int WINAPI wWinMain(HINSTANCE hIhstance, HINSTANCE hPrev, PWSTR lpCmd, int nCmdShow)
{
#if defined(TEST)
    const HWND hConsole = ::GetConsoleWindow();
    BOOL res = ::ShowWindow(hConsole, SW_SHOWNORMAL);

    int nArgs = 0;
    const LPWSTR lpCmdLine = ::GetCommandLineW();
    const LPWSTR* const lpArgs = ::CommandLineToArgvW(lpCmdLine, &nArgs);
    const TCHAR szUsage[] = TEXT("Usage: letss.exe <dir> <part-of-file-name>");

    if (nArgs < 3) {
        DWORD dwTemp;
        WriteConsoleW(GetStdHandle(STD_OUTPUT_HANDLE), szUsage, sizeof(szUsage) / sizeof(szUsage[0]) - 1, &dwTemp, NULL);
    } else {
        const std::wstring dir(lpArgs[1]);
        const std::wstring fileName(lpArgs[2]);
        
        FileSearcher fSearcher;
        fSearcher.SetSearchInFolder(dir);
        fSearcher.SetSearchPattern(fileName);

        std::vector<std::wstring> list;
        if (fSearcher.Letss(list)) {
            list.clear();
        }
    }
#else
	DialogBoxW(hInst, MAKEINTRESOURCE(IDD_DIALOGLETSS), NULL, AboutDlgProc);
#endif

    ExitProcess(0);
}