
#ifndef _CLUST_H_
#define _CLUST_H_

#define OS2EMX_PLAIN_CHAR
#define INCL_PM
#define INCL_DOS
#define __MT__

#define INCL_DOSFILEMGR    /* File System values */
#define INCL_DOSDEVIOCTL   /* DosDevIOCtl values */

#include <os2.h>

#include <stdio.h>
#include <stdlib.h>

// *** some private includes **********************************************

#include "config.h"
#include "id.h"
#include "version.h"

// *** some defines *******************************************************

#define GETHAB               hab
#define GETMODULE            NULLHANDLE

#define CLUST_TICKS_PER_SEC  10
#define PSZ_HELPFILENAME     "clust.hlp"
#define PSZ_RCPIPENAME       "\\PIPE\\CarrieRLust"
#define CID_DETAILS          1
#define LEN_FONTNAMESIZE     80

#define PSZ_PAUSE       "~Stop"
#define PSZ_CONTINUE    "~Go"

#define HOURSFROMTICKS(ul)   (ul/CLUST_TICKS_PER_SEC/3600L)
#define MINSFROMTICKS(ul)    (ul/CLUST_TICKS_PER_SEC/60L)%60L
#define SECSFROMTICKS(ul)    ((ul/CLUST_TICKS_PER_SEC)%60L)

#define WinLboxIsSelectedItem(hwndLbox,i) \
    ((LONG)WinSendMsg (hwndLbox, LM_QUERYSELECTION, MPFROMLONG ((i)-1), \
		       (MPARAM)NULL)==(i))

#define FORMAT_MONEY_STRING(psz,l)   FormatMoneyString (psz, l, 41)

enum IID
{
    IID_DURATION,
    IID_UNITS,
    IID_MONEY,
    IID_UNIT_LEFT,
    IID_UNIT_LENGTH,

    IID_LIMIT_LEFT,
    IID_MONEY_PER_UNIT,
    IID_MONEY_PER_MINUTE,
    IID_MONEY_PER_HOUR,
    IID_SECS_TILL_CHARGE,

    IID_TOTAL_CON_TIME,
#ifdef _TOTALVALUES_
    IID_TOTALUNITS,
    IID_TOTALMONEY,
    IID_TOTALLIMIT_LEFT,
#endif

    MAX_ITEMS,
};

enum WARN_T
{
    WARNT_DONTWARN,
    WARNT_BEEP,
    WARNT_BEEPTWICE,
    WARNT_BEEPTHREE,
    WARNT_MSGBOX,
    WARNT_MSGBOXBEEP,
    MAX_WARNT,
};

enum LIMIT_T
{
    LIMITT_SECONDS,
    LIMITT_MINUTES,
    LIMITT_HOURS,
    LIMITT_UNITS,
};

// *** some typedefs ******************************************************

typedef double MONEY_T;

typedef class Clock CLOCK;
typedef CLOCK *PCLOCK;

typedef class Connection CONNECTION;
typedef CONNECTION *PCONNECTION;

typedef class ChargesInfo CHRGINFO;
typedef CHRGINFO *PCHRGINFO;

typedef class Display DISPLAY;
typedef DISPLAY *PDISPLAY;

typedef class Item ITEM;
typedef ITEM *PITEM;

typedef class Settings SETTINGS;
typedef SETTINGS *PSETTINGS;

typedef class Warner WARNER;
typedef WARNER *PWARNER;

typedef class Coordinator COORDINATOR;
typedef COORDINATOR *PCOORDINATOR;

// *** something else :-) *************************************************

#include "extern.h"

// ** function prototypes *************************************************

VOID   DisplayError (PSZ pszTitle, PSZ psz, ...);
VOID   AboutBox (HWND hwnd);
VOID   FormatMoneyString (PSZ psz, MONEY_T money, USHORT cb);

#ifdef _TOTALVALUES_
ULONG  LoadLimit (PSZ psz, PULONG pulUnits, MONEY_T *pulMoney);
VOID   SaveLimit (PSZ psz, ULONG ul, ULONG ulUnits, MONEY_T ulMoney);
#else
ULONG  LoadLimit (PSZ psz);
VOID   SaveLimit (PSZ psz, ULONG ul);
#endif

#endif
