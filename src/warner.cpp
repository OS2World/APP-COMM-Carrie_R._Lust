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

#include "warner.h"

VOID WARNER :: Warn (WARN_T warnt, PSZ pszTitle, PSZ pszText)
{
    switch (warnt)
    {
    case WARNT_BEEP:
        DosBeep (1000, 100);
        break;

    case WARNT_BEEPTWICE:
        DosBeep (1000, 100);
        DosBeep (2000, 100);
        break;

    case WARNT_BEEPTHREE:
        DosBeep (1000, 100);
        DosBeep (2000, 100);
        DosBeep (3000, 100);
        break;

    case WARNT_MSGBOX:
        WinMessageBox (HWND_DESKTOP, HWND_DESKTOP, pszText, pszTitle, 0,
                       MB_OK | MB_INFORMATION | MB_APPLMODAL);
        break;

    case WARNT_MSGBOXBEEP:
        DosBeep (1000, 100);
        WinMessageBox (HWND_DESKTOP, HWND_DESKTOP, pszText, pszTitle, 0,
                       MB_OK | MB_INFORMATION | MB_APPLMODAL);
        break;

    default:
        break;
    }
}


PSZ WARNER :: QueryWarnDescription (WARN_T warnt)
{
    switch (warnt)
    {
    case WARNT_BEEP:         return ("Beep");
    case WARNT_BEEPTWICE:    return ("Beep 2x");
    case WARNT_BEEPTHREE:    return ("Beep 3x");
    case WARNT_MSGBOX:       return ("Show messagebox");
    case WARNT_MSGBOXBEEP:   return ("Beep & show msgbox");
    default:                 return ("Don't warn");
    }
}
