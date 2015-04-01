/***
 Carrie R. Lust - phone cost/online time tracking tool
 Copyright (C) 1997-2000 Thorsten Thielen <thth@gmx.net>

 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation; either version 2 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

 Carrie R. Lust homepage (as of Feb 20, 2000):
 http://www.informatik.uni-trier.de/CIP/thielen/clust/
 ***/

#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#include "clust.h"
#include "display.h"
#include "helper.h"

// ** all kinds of yukki global variables :-) *****************************

HAB           hab;
PCOORDINATOR  pcrdntr;
PSETTINGS     pset;
USHORT        g_usComport = 0, g_usDetectAdjust = 0, g_DecimalShift  = 0;
BOOL          g_fReset = FALSE, g_fQuitting = FALSE;
#ifdef _TOTALHACK_
BOOL          g_fTotalLimit = FALSE;
#endif

/*************************************************************************/

VOID DisplayError (PSZ pszTitle, PSZ psz, ...)
{
    CHAR      dstring[401];
    va_list   valst;

    va_start (valst, psz);
    vsnprintf (dstring, 401, psz, valst);
    va_end (valst);

    WinMessageBox (HWND_DESKTOP, HWND_DESKTOP, dstring, pszTitle, 0,
                   MB_OK | MB_ERROR | MB_APPLMODAL);
}
// ************************************************************************

int main (int argc, char *argv[])
{
    HMQ    hmq;
    QMSG   qmsg;
    CHAR   psz[_MAX_PATH];
    USHORT i;

    hab = WinInitialize (0);
    hmq = WinCreateMsgQueue (hab, 0);

    // parse the arguments for charges.dat file
    strcpy (psz, "charges.dat");
    for (i = 1; i < argc; i++)
        if ((strcmp (argv[i], "-f") == 0) && (i < argc-1))
        {
            strcpy (psz, argv[i+1]);
            break;
        }

    pset = new SETTINGS;
    pcrdntr = new COORDINATOR;

    PCLOCK        pclock = new CLOCK;
    pcrdntr->pclock = pclock;

    PWARNER       pwarner = new WARNER;
    pcrdntr->pwarner = pwarner;

    PCHRGINFO     pchrginfo = new CHRGINFO (psz);
    pcrdntr->pchrginfo = pchrginfo;

    // parse the arguments for autostart option
    BOOL  f = FALSE;
    LONG  c = 0L;
    for (i = 1; i < argc; i++)
        if (strcmp (argv[i], "-a") == 0)
        {
            f = TRUE;
            if (i < argc-1)
                c = atol (argv[i+1]);
            break;
        }

    // parse the arguments for currency decimal shift
    for (i = 1; i < argc; i++)
        if (strcmp (argv[i], "-c") == 0)
        {
            if (i < argc-1)
                g_DecimalShift = atoi (argv[i+1]);
            if (g_DecimalShift > 10)
                g_DecimalShift = 10;
            break;
        }

    // parse the arguments for autodetect option
    for (i = 1; i < argc; i++)
        if ((strcmp (argv[i], "-d") == 0) ||
            (strcmp (argv[i], "-D") == 0))
        {
            if (i < argc-1)
                g_usComport = atoi (argv[i+1]);
            else
                g_usComport = 1;
            if (g_usComport > 4)
                g_usComport = 0;
            if (g_usComport)
            {
                // disable the autostart
                f = FALSE;
                c = 0;
                // check if "extended" autodetect actions requested
                if (strcmp (argv[i], "-D") == 0)
                    g_fReset = TRUE;
                if (i < argc-2)
                    g_usDetectAdjust = atoi (argv[i+2]);
            }
            break;
        }

    // parse the arguments for limit save file
    ULONG ulTotal = 0L;
    for (i = 1; i < argc; i++)
        if ((strcmp (argv[i], "-s") == 0) && (i < argc-1))
        {
            pset->SetString (SEI_SAVEFILENAME, argv[i+1]);
            pset->SetFlag (SEI_SAVEFILEUSE);
            break;
        }

#ifdef _TOTALHACK_
    // parse the arguments for "don't use help"
    for (i = 1; i < argc; i++)
        if (strcmp (argv[i], "-t") == 0)
        {
            g_fTotalLimit = TRUE;
            break;
        }
#endif

#ifdef _TOTALVALUES_
    ULONG  ulUnits;
    MONEY_T ulMoney;
#endif

    if (pset->QueryFlag (SEI_SAVEFILEUSE))
#ifdef _TOTALVALUES_
        ulTotal = LoadLimit (pset->QueryString (SEI_SAVEFILENAME),
                             &ulUnits, &ulMoney);
    PCONNECTION   pconnect = new CONNECTION (ulTotal, ulUnits, ulMoney, !f, c);
#else
        ulTotal = LoadLimit (pset->QueryString (SEI_SAVEFILENAME));
    PCONNECTION   pconnect = new CONNECTION (ulTotal, !f, c);
#endif
    pcrdntr->pconnect = pconnect;

    // parse the arguments for "don't use help"
    f = TRUE;
    for (i = 1; i < argc; i++)
        if (strcmp (argv[i], "-h") == 0)
        {
            f = FALSE;
            break;
        }

    PDISPLAY      pdisplay = new DISPLAY (f);
    pcrdntr->pdisplay = pdisplay;

    while (WinGetMsg (hab, &qmsg, 0L, 0, 0))
        WinDispatchMsg (hab, &qmsg);

    // prevents the autodetect-thread to crash the program by accessing
    // no longer existing variables ... (well, should do so ;-)
    g_fQuitting = TRUE;

    if (pconnect->WasActive ())
    {
        if (pset->QueryString (SEI_SAVEFILEUSE))
#ifdef _TOTALVALUES_
            SaveLimit (pset->QueryString (SEI_SAVEFILENAME),
                       pconnect->QueryTotalConTime (),
                       pconnect->QueryTotalUnits (),
                       pconnect->QueryTotalMoney ());
#else
            SaveLimit (pset->QueryString (SEI_SAVEFILENAME),
                       pconnect->QueryTotalConTime ());
#endif
    }

    delete pdisplay;
    delete pconnect;
    delete pchrginfo;
    delete pclock;
    delete pwarner;
    delete pset;
    delete pcrdntr;

//    sleep (3);

    WinDestroyMsgQueue (hmq);
    WinTerminate (hab);

    return 0;
}
// ************************************************************************

#ifdef _TOTALVALUES_
ULONG LoadLimit (PSZ psz, PULONG pulUnits, MONEY_T *pulMoney)
#else
ULONG LoadLimit (PSZ psz)
#endif
{
    FILE    *file;
    ULONG   ulTotal;

    if (! (file = fopen (psz, "rb")))
    {
#ifdef _TOTALVALUES_
        *pulUnits = 1;
        *pulMoney = 0.0;
#endif
        return 0;
    }

#ifdef _TOTALVALUES_
    fscanf (file, "%ld %ld %lf", &ulTotal, pulUnits, pulMoney);
#else
    fscanf (file, "%ld", &ulTotal);
#endif

/*    pcrdntr->pconnect->cLimitCurrent =
 pcrdntr->pconnect->cLimitCurrentOld = ulTotal; */
    fclose (file);
    return ulTotal;
}

// ************************************************************************

#ifdef _TOTALVALUES_
VOID SaveLimit (PSZ psz, ULONG ul, ULONG ulUnits, MONEY_T ulMoney)
#else
VOID SaveLimit (PSZ psz, ULONG ul)
#endif
{
    FILE    *file;

    if (! (file = fopen (psz, "wb")))
        return;

#ifdef _TOTALVALUES_
    fprintf (file, "%ld %ld %lf", ul, ulUnits, ulMoney);
#else
    fprintf (file, "%ld", ul);
#endif

    fclose (file);
}

// ** FormatMoneyString ***************************************************

#define BITSET(c,n)  (((c)&(1<<(n)))!=0)

VOID FormatMoneyString (PSZ psz, MONEY_T money, USHORT cb)
{
    PCOUNTRYINFO  pci = pset->QueryCountryInfo ();

    // e.g. #Pfennig come in, #(Pfennig/100) is needed
    // money = "0.0749999995" e.g. => ~0.075 Pfennig/sec
    // g_DecimalShift = 3 => l needs to be = 75
    ULONG  ulFactor2 = 1;
    for (USHORT i = 0; i < g_DecimalShift; i++)
        ulFactor2 *= 10;
    ULONG  l = ULONG(money*ulFactor2);

    psz[0] = 0;
    if (! pci)
        return;

    // 1 currency unit / ulFactor is what we need
    ULONG  ulFactor = ulFactor2;
    for (USHORT i = 0; i < pci->cDecimalPlace; i++)
        ulFactor *= 10;

    // print currency symbol before value?
    if (! BITSET (pci->fsCurrencyFmt, 0)) {
        strcat (psz, pci->szCurrency);
        // seperate value and symbol with a space?
        if (BITSET (pci->fsCurrencyFmt, 1))
            strcat (psz, " ");
    }

    // do we have a decimal point?
    if (pci->cDecimalPlace) {
        if (BITSET (pci->fsCurrencyFmt, 2)) {
            sprintf (psz+strlen (psz), "%lu%s%0*lu",
                     l/ulFactor, pci->szCurrency,
                     pci->cDecimalPlace+g_DecimalShift, l%ulFactor);
        } else {
            sprintf (psz+strlen (psz), "%lu%c%0*lu",
                     l/ulFactor, pci->szDecimal[0],
                     pci->cDecimalPlace+g_DecimalShift, l%ulFactor);
        }
    } else {
        if (g_DecimalShift) {
            sprintf (psz+strlen (psz), "%lu.%0*lu", l/ulFactor,
                     g_DecimalShift, l%ulFactor);
        } else {
            sprintf (psz+strlen (psz), "%lu", l);
        }
    }

    // print currency symbol after value?
    if (BITSET (pci->fsCurrencyFmt, 0))
    {
        // seperate value and symbol with a space?
        if (BITSET (pci->fsCurrencyFmt, 1))
            strcat (psz, " ");
        strcat (psz, pci->szCurrency);
    }
}

// ************************************************************************
