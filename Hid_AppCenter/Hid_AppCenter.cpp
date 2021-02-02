#include <stdio.h>
#include <Windows.h>
#include <fstream>

DWORD WINAPI Init(LPVOID);
DWORD WINAPI HACK(LPVOID);

typedef char (* Fun_acAppCenterInit) ();
typedef char (* Fun_acAppRegister) (void *a1);
typedef char (* Fun_acAppRequest) (char a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9);
typedef char (* Fun_acAppSearch) (char a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8);
typedef char (* Fun_acAppSearchByAction) (void *a1, char a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9);
typedef char (* Fun_acGetAppInfo) (char a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8, DWORD *a9, int a10, int a11, int a12, DWORD *a13);
typedef int (* Fun_acGetAppListCount) (char a1);
typedef int (* Fun_acQueryAppMetaList) (void *a1, void *Src, int a3, int a4);

Fun_acAppCenterInit _acAppCenterInit;
Fun_acAppRegister _acAppRegister;
Fun_acAppRequest _acAppRequest;
Fun_acAppSearch _acAppSearch;
Fun_acAppSearchByAction _acAppSearchByAction;
Fun_acGetAppInfo _acGetAppInfo;
Fun_acGetAppListCount _acGetAppListCount;
Fun_acQueryAppMetaList _acQueryAppMetaList;

char buf[1024] = { 0 };

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        {
            CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)Init, NULL, NULL, NULL);
            CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)HACK, NULL, NULL, NULL);
        }

    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

DWORD WINAPI Init(LPVOID)
{
    HMODULE dll = LoadLibraryA("AppCenterr.dll");

    _acAppCenterInit = (Fun_acAppCenterInit)GetProcAddress(dll, "acAppCenterInit");
    _acAppRegister = (Fun_acAppRegister)GetProcAddress(dll, "acAppRegister");
    _acAppRequest = (Fun_acAppRequest)GetProcAddress(dll, "acAppRequest");
    _acAppSearch = (Fun_acAppSearch)GetProcAddress(dll, "acAppSearch");
    _acAppSearchByAction = (Fun_acAppSearchByAction)GetProcAddress(dll, "acAppSearchByAction");
    _acGetAppInfo = (Fun_acGetAppInfo)GetProcAddress(dll, "acGetAppInfo");
    _acGetAppListCount = (Fun_acGetAppListCount)GetProcAddress(dll, "acGetAppListCount");
    _acQueryAppMetaList = (Fun_acQueryAppMetaList)GetProcAddress(dll, "acQueryAppMetaList");

    sprintf(buf, "dll_hmodule: %p\n_acAppCenterInit=%p\n_acAppRegister=%p\n_acAppRequest=%p\n_acAppSearch=%p\n_acAppSearchByAction=%p\n_acGetAppInfo=%p\n_acGetAppListCount=%p\n_acQueryAppMetaList=%p\n", dll, _acAppCenterInit, _acAppRegister, _acAppRequest, _acAppSearch, _acAppSearchByAction, _acGetAppInfo, _acGetAppListCount, _acQueryAppMetaList);
    OutputDebugStringA(buf);

    return 0;
}

DWORD WINAPI HACK(LPVOID)
{
    MessageBoxA(NULL, "TEXT", "QQ", MB_OK);

    return 0;
}

extern "C" __declspec(dllexport) char acAppCenterInit()
{

    return _acAppCenterInit ();
}

extern "C" __declspec(dllexport) char acAppRegister (void *a1)
{
    return _acAppRegister (a1);
}

extern "C" __declspec(dllexport) char acAppRequest (char a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9)
{
    return _acAppRequest (a1, a2, a3, a4, a5, a6, a7, a8, a9);
}

extern "C" __declspec(dllexport) char acAppSearch (char a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8)
{
    return _acAppSearch (a1, a2, a3, a4, a5, a6, a7, a8);
}

extern "C" __declspec(dllexport) char acAppSearchByAction (void *a1, char a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9)
{
    return acAppSearchByAction (a1, a2, a3, a4, a5, a6, a7, a8, a9);
}

extern "C" __declspec(dllexport) char acGetAppInfo (char a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8, DWORD *a9, int a10, int a11, int a12, DWORD *a13)
{
    return _acGetAppInfo (a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13);
}

extern "C" __declspec(dllexport) int acGetAppListCount (char a1)
{
    return _acGetAppListCount(a1);
}

extern "C" __declspec(dllexport) int acQueryAppMetaList (void *a1, void *Src, int a3, int a4)
{
    return _acQueryAppMetaList(a1, Src, a3, a4);
}