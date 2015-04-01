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

#include "helper.h"

// ** Helper ************************************************************** /*FOLD00*/

HELPER :: Helper (HWND hwnd)
{
    HELPINIT   helpInit;

    // if we return because of an error, Help will be disabled
    fHelpEnabled = TRUE;

    // inititalize help init structure
    helpInit.cb                  = sizeof (HELPINIT);
    helpInit.ulReturnCode        = 0L;
    helpInit.pszTutorialName     = PSZ (NULL);
    helpInit.phtHelpTable        = PHELPTABLE (MAKELONG (MAIN_HELP_TABLE,
                                                         0xFFFF));
    helpInit.hmodHelpTableModule = GETMODULE;
    helpInit.hmodAccelActionBarModule = GETMODULE;
    helpInit.idAccelTable        = 0;
    helpInit.idActionBar         = 0;
    helpInit.pszHelpWindowTitle  = PSZ ("Carrie R. Lust");
    helpInit.fShowPanelId        = CMIC_HIDE_PANEL_ID;
    helpInit.pszHelpLibraryName  = PSZ_HELPFILENAME;

    // create the help instance
    hwndHelpInstance = WinCreateHelpInstance (GETHAB, &helpInit);
    if (!hwndHelpInstance || helpInit.ulReturnCode)
    {
        DisplayError ("ERROR",
                      "Could not initialize online help. Please check if "
                      "helpfile '%s' exists in Carrie's directory.\n\n"
                      "Note: Either copy '%s' to the directory where Carrie "
                      "is started from, to one of the directories in the HELP-"
                      "path or use the parameter '-h' at program start to "
                      "disable the online help.",
                      PSZ_HELPFILENAME, PSZ_HELPFILENAME);
        fHelpEnabled = FALSE;
    }

    // associate help instance with main frame
    if (! WinAssociateHelpInstance (hwndHelpInstance, hwnd))
    {
        DisplayError ("ERROR", "Could not initialize online help.");
        fHelpEnabled = FALSE;
    }
}

// ** ~Helper ************************************************************* /*FOLD00*/

HELPER :: ~Helper (VOID)
{
    if (hwndHelpInstance)
        WinDestroyHelpInstance (hwndHelpInstance);
}

// ** DisplayPanel ******************************************************** /*FOLD00*/

VOID HELPER :: DisplayPanel (SHORT idPanel)
{
    if (fHelpEnabled)
    {
        WinSendMsg (hwndHelpInstance, HM_DISPLAY_HELP,
                    MPFROM2SHORT (idPanel, NULL), MPFROMSHORT (HM_RESOURCEID));
    }
}

// ************************************************************************
