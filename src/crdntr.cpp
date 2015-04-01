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

#include "crdntr.h"

COORDINATOR :: Coordinator (VOID)
{
    pclock = NULL;
    pchrginfo = NULL;
    pwarner = NULL;
    pconnect = NULL;
    pdisplay = NULL;

    if (pset->UseLogfile ())
        pfile = fopen (pset->QueryLogfileName (), "a");
    else
        pfile = NULL;
}

COORDINATOR :: ~Coordinator (VOID)
{
    if (pfile)
        fclose (pfile);
}

BOOL COORDINATOR :: Log (PCONNECTION pconnect)
{
    if (! pfile)
        return (FALSE);
    if (! pconnect->WasActive ())
        return FALSE;

    CHAR  psz[41];
    FORMAT_MONEY_STRING (psz, pconnect->QueryMoney ());

    fprintf (pfile,
             "%02u.%02u.%04u, %02u:%02u:%02u  "
             "%2lu:%02lu:%02lu  "
             "%5lu  "
             "%s"
             "\n",
             pconnect->QueryStartMDay (),
             pconnect->QueryStartMonth (),
             pconnect->QueryStartYear (),
             pconnect->QueryStartHours (),
             pconnect->QueryStartMinutes (),
             pconnect->QueryStartSeconds (),
             pconnect->QueryHours (),
             pconnect->QueryMinutes ()%60L,
             pconnect->QuerySeconds ()%60L,
             pconnect->QueryUnits (), psz);
    fflush (pfile);
    return (TRUE);
}

VOID COORDINATOR :: UpdateDuration (PCONNECTION pconnect)
{
    if (pdisplay)
        pdisplay->UpdateDuration ();
}

VOID COORDINATOR :: UpdateSecond (PCLOCK pclock)
{
    if (pchrginfo)
        pchrginfo->UpdateSecond ();
    if (pconnect)
        pconnect->UpdateSecond ();
    if (pdisplay)
        pdisplay->UpdateSecond ();
}

VOID COORDINATOR :: UpdateLimit (PCONNECTION pconnect)
{
    if (pdisplay)
        pdisplay->UpdateLimit ();
    if (pwarner)
        pwarner->UpdateLimit ();
}

VOID COORDINATOR :: UpdateCostsLimit (PCONNECTION pconnect)
{
    if (pdisplay)
        pdisplay->UpdateCostsLimit ();
    if (pwarner)
        pwarner->UpdateCostsLimit ();
}

#ifdef _TOTALVALUES_
VOID COORDINATOR :: UpdateLimitTotal (PCONNECTION pconnect)
{
    if (pdisplay)
        pdisplay->UpdateLimitTotal ();
    if (pwarner)
        pwarner->UpdateLimitTotal ();
}

VOID COORDINATOR :: UpdateCostsLimitTotal (PCONNECTION pconnect)
{
    if (pdisplay)
        pdisplay->UpdateCostsLimitTotal ();
    if (pwarner)
        pwarner->UpdateCostsLimitTotal ();
}
#endif

VOID COORDINATOR :: UpdateUnit (PCONNECTION pconnect)
{
    if (pdisplay)
        pdisplay->UpdateUnit ();
    if (pwarner)
        pwarner->UpdateUnit ();
}

VOID COORDINATOR :: UpdateCharge (PCHRGINFO pchrginfo)
{
    if (pdisplay)
        pdisplay->UpdateCharge ();
    if (pwarner)
        pwarner->UpdateCharge ();
}

PCHRGINFO COORDINATOR :: QueryChargesInfo (PCONNECTION pconnect)
{
    return (pchrginfo);
}

PCHRGINFO COORDINATOR :: QueryChargesInfo (PDISPLAY pdisplay)
{
    return (pchrginfo);
}

PCONNECTION COORDINATOR :: QueryConnection (PDISPLAY pdisplay)
{
    return (pconnect);
}

PDISPLAY COORDINATOR :: QueryDisplay (PSETTINGS pset)
{
    return (pdisplay);
}

PWARNER COORDINATOR :: QueryWarner (PSETTINGS pset)
{
    return (pwarner);
}

PCONNECTION COORDINATOR :: QueryConnection (PSETTINGS pset)
{
    return (pconnect);
}
