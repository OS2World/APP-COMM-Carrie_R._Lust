/***
 thth_settings - a custom settings class with INI file handling
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

 Author: Thorsten Thielen <thth@gmx.net>
 Documentation for this class wouldn't hurt. See my programs (Minta,
 Carrie R. Lust, Gotcha!, etc.) for some usage examples
 ***/

#include "thth_settings.h"

#ifndef NO_ERROR
#define NO_ERROR 0
#endif

// ** Settings ************************************************************ /*FOLD00*/

THTH_SETTINGS :: ththSettings (PTHTH_SE *ppse, PSZ pszInifile, ULONG ulVersion)
{
    // what's this?!? well, just forget about doing inits ...
    if (! ppse)
        return;
    this->ppse = ppse;

    // reset - everything should already be on defaults, but just in case ...
    Reset ();

    // shall we use the pro-file?
    if (! pszInifile)
        return;
    psz = pszInifile;  // FIXME maybe do a strdup instead ...

    ulError = 0;

    // check if a pro-file does exist; if not we need not complain
    // about wrong version
    if (access(pszInifile, 0) != NO_ERROR) {
        ulVersion = 0;
        ulError = 3; // "select language" needed
    }

    // open the pro-file
    CHAR   ach[_MAX_PATH];
    strcpy (ach, psz);
    if (! (hini = PrfOpenProfile (GETHAB, ach)))
    {
        ulError = 1;
        return;
    }

    // shall we check the version number?
    if (ulVersion) {
        if ((this->ulVersion =
             PrfQueryProfileInt (hini, "Profile", "Version", 0L))) {
            if (this->ulVersion != ulVersion) {
                ulError = 2;
                return;
            }
        } else
            ulError = 4; // INI file corrupted or wrong ini file
    }

    // awright baby, load the stuff! ;-)
    Load ();
}

// ** Save ****************************************************************

BOOL THTH_SETTINGS :: Save (VOID)
{
    if (!hini || !ppse)
        return FALSE;

    if (ulVersion)
    {
        CHAR   ach[11];
        sprintf (ach, "%lu", ulVersion);
        PrfWriteProfileString (hini, "Profile", "Version", ach);
    }

    // awright baby, save the stuff! ;-)
    for (LONG i = 0; ppse[i]; i++)
        ppse[i]->Save (hini);

    return TRUE;
}

// ** ~Settings *********************************************************** /*FOLD00*/

THTH_SETTINGS :: ~ththSettings (VOID)
{
    // the only thing we might need to do is save the stuff to the pro-file
    Save ();

    // goodbye pro-file!
    if (hini) { PrfCloseProfile (hini); }
    hini = NULL;

    // FIXME if we copied the filename, delete it now
}

// ************************************************************************
