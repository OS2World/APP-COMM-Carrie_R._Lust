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

#include "connectn.h"

// ** Connection ********************************************************** /*fold00*/

#ifdef _TOTALVALUES_
CONNECTION :: Connection (ULONG ul, ULONG ulUnits, MONEY_T ulMoney, BOOL f, LONG c)
#else
CONNECTION :: Connection (ULONG ul, BOOL f, LONG c)
#endif
{
#ifdef _TOTALVALUES_
    cUnitsTotal = ulUnits;
    cMoneyTotal = ulMoney;
    fCostsWarnedTotal = FALSE;

    SetLimitTypeTotal (LIMIT_T (pset->QueryLong (SEI_LIMITTYPETOTAL)));
    switch (limittTotal)
    {
    case LIMITT_SECONDS:
    case LIMITT_MINUTES:
    case LIMITT_HOURS:
        cLimitCurrentTotal = ul;
        break;

    default:
        cLimitCurrentTotal = ulUnits;
    }

    SetLimitTotal (pset->QueryLong (SEI_LIMITVALUETOTAL));
#endif
    cTotal = ul;
    fSuspended = f;
    cCountdown = c;
    fCostsWarned = fWasReset = fWasActive = FALSE;
    Reset ();
}

// ** UpdateSecond ******************************************************** /*fold00*/

VOID CONNECTION :: UpdateSecond (VOID)
{
    // FIXME Values changing after update

    // time to wait till to start counter
    if (cCountdown)
    {
        cCountdown --;
        if (cCountdown)
            return;
        Continue ();
    }

    // Connection suspended? Do nothing.
    if (IsSuspended ())
        return;

    // One second has passed. Tell this to everyone listening
    cTicks += CLUST_TICKS_PER_SEC;
    NotifyDuration ();

    // Seconds left in unit decrease. Has the unit passed already?
    cdUnit -= CLUST_TICKS_PER_SEC;
    if (cdUnit <= 0L)
    {
        cUnits ++;
#ifdef _TOTALVALUES_
        cUnitsTotal ++;
#endif
        cdUnit = pcrdntr->QueryChargesInfo (this)->QueryUnitLength ()+cdUnit;
        cMoney += pcrdntr->QueryChargesInfo (this)->QueryMoneyPerUnit ();
#ifdef _TOTALVALUES_
        cMoneyTotal += pcrdntr->QueryChargesInfo (this)->QueryMoneyPerUnit ();
#endif
        NotifyUnit ();

        if ((cMoney >= pset->QueryCostsLimit () && !fCostsWarned))
        {
            fCostsWarned = TRUE;
            NotifyCostsLimit ();
        }
#ifdef _TOTALVALUES_
        if ((cMoneyTotal >= MONEY_T (pset->QueryLong (SEI_LIMITCOSTSTOTAL)) &&
             !fCostsWarnedTotal))
        {
            fCostsWarnedTotal = TRUE;
            NotifyCostsLimitTotal ();
        }
#endif

        if (limitt == LIMITT_UNITS)
        {
            cLimitCurrent ++;
            if (cLimit && (cLimitCurrent == cLimit))
                NotifyLimit ();
        }
#ifdef _TOTALVALUES_
        if (limittTotal == LIMITT_UNITS)
        {
            cLimitCurrentTotal ++;
            //            DosBeep (10000, 10);
            DisplayError ("DEBUG", "1-cLimitTotal=%ld cLimitCurrentTotal=%ld",
                          cLimitTotal, cLimitCurrentTotal);
            if (cLimitTotal && (cLimitCurrentTotal == cLimitTotal))
                NotifyLimitTotal ();
        }
#endif
    }
    else
        if ((cdUnit <= 10L*CLUST_TICKS_PER_SEC) && pset->DoUnitCountdown ())
            DosBeep (4000L-cdUnit*300L/CLUST_TICKS_PER_SEC, 20);

    // Seconds left to limit decrease. Was limit reached?
    if (limitt != LIMITT_UNITS)
    {
        cLimitCurrent += CLUST_TICKS_PER_SEC;
        if (cLimit && (cLimitCurrent == cLimit))
            NotifyLimit ();
    }
#ifdef _TOTALVALUES_
    if (limittTotal != LIMITT_UNITS)
    {
        cLimitCurrentTotal += CLUST_TICKS_PER_SEC;
/*        DisplayError ("DEBUG", "2-cLimitTotal=%ld cLimitCurrentTotal=%ld",
                      cLimitTotal, cLimitCurrentTotal); */
        if (cLimitTotal && (cLimitCurrentTotal >= cLimitTotal) &&
            (cLimitCurrentTotal-CLUST_TICKS_PER_SEC < cLimitTotal))
            NotifyLimitTotal ();
    }
#endif
}

// ** SetLimit ************************************************************ /*fold00*/

VOID CONNECTION :: SetLimit (ULONG ul)
{
    switch (QueryLimitType ())
    {
    case LIMITT_SECONDS:
        cLimit = ul*CLUST_TICKS_PER_SEC;
        break;

    case LIMITT_MINUTES:
        cLimit = ul*CLUST_TICKS_PER_SEC*60L;
        break;

    case LIMITT_HOURS:
        cLimit = ul*CLUST_TICKS_PER_SEC*60L*60L;
        break;

    default:
        cLimit = ul;
    }
}

// ** SetLimitTotal ******************************************************* /*fold00*/
#ifdef _TOTALVALUES_
VOID CONNECTION :: SetLimitTotal (ULONG ul)
{
    switch (limittTotal)
    {
    case LIMITT_SECONDS:
        cLimitTotal = ul*CLUST_TICKS_PER_SEC;
        break;

    case LIMITT_MINUTES:
        cLimitTotal = ul*CLUST_TICKS_PER_SEC*60L;
        break;

    case LIMITT_HOURS:
        cLimitTotal = ul*CLUST_TICKS_PER_SEC*60L*60L;
        break;

    default:
        cLimitTotal = ul;
    }
}
#endif
// ** SetLimitType ******************************************************** /*fold00*/

VOID CONNECTION :: SetLimitType (LIMIT_T limitt, BOOL)
{
/* FIXME
    // no adjustment of counter wanted?
    if (! f)
    {
        this->limitt = limitt;
        return;
    }

    // adjust counter to fit new type
    switch (QueryLimitType ())
    {
    case LIMITT_SECONDS:
        switch (limitt)
        {
        case LIMITT_MINUTES:      cLimit /= 60L;           break;
        case LIMITT_HOURS:        cLimit /= 3600L;         break;

        case LIMITT_UNITS:
            cLimit /= pcrdntr->QueryChargesInfo (this)->QueryUnitLengthSeconds ();
            break;
        }

    case LIMITT_MINUTES:
        switch (limitt)
        {
        case LIMITT_SECONDS:      cLimit *= 60L;           break;
        case LIMITT_HOURS:        cLimit /= 60L;           break;

        case LIMITT_UNITS:
            cLimit /= pcrdntr->QueryChargesInfo (this)->QueryUnitLengthMinutes ()+1;
            // FIXME this calculation is pretty wrong
            break;
        }

    case LIMITT_HOURS:
        switch (limitt)
        {
        case LIMITT_SECONDS:      cLimit *= 3600L;         break;
        case LIMITT_MINUTES:      cLimit *= 60L;           break;

        case LIMITT_UNITS:
            cLimit /= pcrdntr->QueryChargesInfo (this)->QueryUnitLengthMinutes ()+1;
            // FIXME this calculation is pretty wrong
            break;
        }

    case LIMITT_UNITS:
        switch (limitt)
        {
        case LIMITT_SECONDS:
            cLimit *= pcrdntr->QueryChargesInfo (this)->QueryUnitLengthSeconds ();
            // FIXME this calculation is pretty bad
            break;

        case LIMITT_MINUTES:
            cLimit *= pcrdntr->QueryChargesInfo (this)->QueryUnitLengthMinutes ()+1;
            // FIXME this calculation is pretty wrong
            break;

        case LIMITT_HOURS:
            cLimit *= pcrdntr->QueryChargesInfo (this)->QueryUnitLengthMinutes ()+1;
            // FIXME this calculation is pretty wrong
            break;
        }
    } */
    
    this->limitt = limitt;
}

// ** SetLimitTypeTotal *************************************************** /*fold00*/
#ifdef _TOTALVALUES_
VOID CONNECTION :: SetLimitTypeTotal (LIMIT_T limitt, BOOL)
{
    this->limittTotal = limitt;
}
#endif
// ** Reset *************************************************************** /*FOLD00*/

VOID CONNECTION :: Reset (VOID)
{
    time_t   secs = time (NULL);
    tm       *ptm;

    ptm = localtime (&secs);

    tmStart.tm_sec = ptm->tm_sec;
    tmStart.tm_min = ptm->tm_min;
    tmStart.tm_hour = ptm->tm_hour;
    tmStart.tm_mday = ptm->tm_mday;
    tmStart.tm_mon = ptm->tm_mon;
    tmStart.tm_year = ptm->tm_year;

    fWasReset = TRUE;

    cLimitCurrent =  0;
#ifdef _TOTALHACK_
    if (g_fTotalLimit && (pset->QueryLimitType () != LIMITT_UNITS))
        cLimitCurrent += cTotal;
#endif
    if (g_usComport)
    {
        cTicks = g_usDetectAdjust*CLUST_TICKS_PER_SEC;
        cdUnit = pcrdntr->QueryChargesInfo (this)->QueryUnitLength ()-cTicks;
        if (pset->QueryLimitType () != LIMITT_UNITS)
            cLimitCurrent += cTicks;
    }
    else
    {
        cTicks = 0L;
        cdUnit = pcrdntr->QueryChargesInfo (this)->QueryUnitLength ();
    }

    SetLimitType (pset->QueryLimitType ());
    SetLimit (pset->QueryLimit ());
    cUnits = ((g_usDetectAdjust*CLUST_TICKS_PER_SEC)/
              pcrdntr->QueryChargesInfo (this)->QueryUnitLength ())+1;
    cMoney = cUnits*pcrdntr->QueryChargesInfo (this)->QueryMoneyPerUnit ();
    fCostsWarned = fWasActive = FALSE;
}

// ************************************************************************
