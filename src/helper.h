/***
 helper.h
 ***/

#ifndef _HELPER_H_
#define _HELPER_H_

typedef class Helper HELPER;
typedef HELPER *PHELPER;

#include "clust.h"

class Helper
{
public:
    Helper (HWND hwnd);
    ~Helper (VOID);

    VOID   DisplayPanel (SHORT idPanel);
    BOOL   IsAvailable (VOID);

    VOID   DisplayContents (VOID);
    VOID   DisplayIndex (VOID);
    VOID   DisplayKeysHelp (VOID);

private:
    HWND   hwndHelpInstance;
    BOOL   fHelpEnabled;
};

inline BOOL HELPER :: IsAvailable (VOID)
{
    return (fHelpEnabled);
}

inline VOID HELPER :: DisplayContents (VOID)
{
    WinSendMsg (hwndHelpInstance, HM_HELP_CONTENTS, 0,0);
}

inline VOID HELPER :: DisplayIndex (VOID)
{
    WinSendMsg (hwndHelpInstance, HM_HELP_INDEX, 0,0);
}

inline VOID HELPER :: DisplayKeysHelp (VOID)
{
    WinSendMsg (hwndHelpInstance, HM_KEYS_HELP, 0,0);
}

#endif
