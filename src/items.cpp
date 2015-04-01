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

// ************************************************************************

#define ITEM_DRAW_LABEL \
    GpiSetColor (hps, pset->QueryBackgroundColor ());  \
    GpiMove (hps, PPOINTL (&(rcl->xLeft))); \
    GpiBox (hps, DRO_FILL, PPOINTL (&(rcl->xRight)), 0, 0); \
    WinDrawText (hps, -1, QueryLabel (), rcl, \
    QueryFGColor (), 0, DT_LEFT | DT_TOP)

#define ITEM_DRAW_VALUE    WinDrawText (hps, -1, psz, rcl, \
    QueryFGColor (), 0, DT_RIGHT | DT_TOP)

#include "items.h"

CHAR Item :: psz[Item::CB_BUFFER];

// ** ItemDuration ******************************************************** /*fold00*/

VOID ItemDuration :: Repaint (HPS hps, RECTL *rcl)
{
    ITEM_DRAW_LABEL;
    sprintf (psz, "%lu%c%02lu%c%02lu",
             QueryConnection ()->QueryHours (),
             pset->QueryTimeSeperator (),
             QueryConnection ()->QueryMinutes ()%60L,
             pset->QueryTimeSeperator (),
             QueryConnection ()->QuerySeconds ()%60L);
    ITEM_DRAW_VALUE;
}

// ** ItemUnits *********************************************************** /*fold00*/

VOID ItemUnits :: Repaint (HPS hps, RECTL *rcl)
{
    ITEM_DRAW_LABEL;
    sprintf (psz, "%lu", QueryConnection ()->QueryUnits ());
    ITEM_DRAW_VALUE;
}

// ** ItemMoney *********************************************************** /*fold00*/

VOID ItemMoney :: Repaint (HPS hps, RECTL *rcl)
{
    ITEM_DRAW_LABEL;
    FORMAT_MONEY_STRING (psz, QueryConnection ()->QueryMoney ());
    ITEM_DRAW_VALUE;
}

// ** ItemUnitLeft ******************************************************** /*fold00*/

VOID ItemUnitLeft :: Repaint (HPS hps, RECTL *rcl)
{
    ITEM_DRAW_LABEL;
    sprintf (psz, "%lu%c%02lu,%1lu",
             QueryConnection ()->QueryUnitLeftMinutes (),
             pset->QueryTimeSeperator (),
             QueryConnection ()->QueryUnitLeftSeconds ()%60L,
             QueryConnection ()->QueryUnitLeft10thSecs ()%10L);
    ITEM_DRAW_VALUE;
}

// ** ItemLimitLeft ******************************************************* /*fold00*/

VOID ItemLimitLeft :: Repaint (HPS hps, RECTL *rcl)
{
    ITEM_DRAW_LABEL;
    if (QueryConnection ()->QueryLimitType () == LIMITT_UNITS)
    {
        if (! QueryConnection ()->LimitEnabled ())
            strcpy (psz, "-");
        else
            sprintf (psz, "%5ld", QueryConnection ()->QueryLimitLeft ());
    }
    else
    {
        if (! QueryConnection ()->LimitEnabled ())
            strcpy (psz, "-");
        else
        {
            if (! QueryConnection ()->LimitExceeded ())
                sprintf (psz, "%ld%c%02ld%c%02ld",
                         QueryConnection ()->QueryLimitLeftHours (),
                         pset->QueryTimeSeperator (),
                         QueryConnection ()->QueryLimitLeftMinutes ()%60L,
                         pset->QueryTimeSeperator (),
                         QueryConnection ()->QueryLimitLeftSeconds ()%60L);
            else
                sprintf (psz, "-%ld%c%02ld%c%02ld",
                         -QueryConnection ()->QueryLimitLeftHours (),
                         pset->QueryTimeSeperator (),
                         -QueryConnection ()->QueryLimitLeftMinutes ()%60L,
                         pset->QueryTimeSeperator (),
                         -QueryConnection ()->QueryLimitLeftSeconds ()%60L);
        }
    }
    ITEM_DRAW_VALUE;
}

// ** ItemUnitLength ****************************************************** /*fold00*/

VOID ItemUnitLength :: Repaint (HPS hps, RECTL *rcl)
{
    ITEM_DRAW_LABEL;
    sprintf (psz, "%lu%c%02lu,%1lu",
             QueryChargesInfo ()->QueryUnitLengthMinutes (),
             pset->QueryTimeSeperator (),
             QueryChargesInfo ()->QueryUnitLengthSeconds ()%60L,
             QueryChargesInfo ()->QueryUnitLength10thSecs ()%10L);
    ITEM_DRAW_VALUE;
}

// ** ItemMoneyPerUnit **************************************************** /*fold00*/

VOID ItemMoneyPerUnit :: Repaint (HPS hps, RECTL *rcl)
{
    ITEM_DRAW_LABEL;
    FORMAT_MONEY_STRING (psz, QueryChargesInfo ()->QueryMoneyPerUnit ());
    ITEM_DRAW_VALUE;
}
// ** ItemMoneyPerMinute ************************************************** /*fold00*/

VOID ItemMoneyPerMinute :: Repaint (HPS hps, RECTL *rcl)
{
    ITEM_DRAW_LABEL;
    FORMAT_MONEY_STRING (psz, QueryChargesInfo ()->QueryMoneyPerMinute ());
    ITEM_DRAW_VALUE;
}
// ** ItemMoneyPerHour **************************************************** /*fold00*/

VOID ItemMoneyPerHour :: Repaint (HPS hps, RECTL *rcl)
{
    ITEM_DRAW_LABEL;
    FORMAT_MONEY_STRING (psz, QueryChargesInfo ()->QueryMoneyPerHour ());
    ITEM_DRAW_VALUE;
}
// ** ItemSecsTillCharge ************************************************** /*fold00*/

VOID ItemSecsTillCharge :: Repaint (HPS hps, RECTL *rcl)
{
    ITEM_DRAW_LABEL;
    sprintf (psz, "%lu%c%02lu%c%02lu",
             QueryChargesInfo ()->QuerySecsTillCharge ()/(3600L),
             pset->QueryTimeSeperator (),
             (QueryChargesInfo ()->QuerySecsTillCharge ()/60L)%60L,
             pset->QueryTimeSeperator (),
             QueryChargesInfo ()->QuerySecsTillCharge ()%60L);
    ITEM_DRAW_VALUE;
}

// ** ItemTotalConTime **************************************************** /*fold00*/

VOID ItemTotalConTime :: Repaint (HPS hps, RECTL *rcl)
{
    ITEM_DRAW_LABEL;
    ULONG  ul = QueryConnection ()->QueryTotalConTime ();
    sprintf (psz, "%lu%c%02lu%c%02lu",
             HOURSFROMTICKS (ul), pset->QueryTimeSeperator (),
             MINSFROMTICKS (ul), pset->QueryTimeSeperator (),
             SECSFROMTICKS (ul));
    ITEM_DRAW_VALUE;
}

#ifdef _TOTALVALUES_
// ** ItemTotalUnits ****************************************************** /*fold00*/

VOID ItemTotalUnits :: Repaint (HPS hps, RECTL *rcl)
{
    ITEM_DRAW_LABEL;
    sprintf (psz, "%lu", QueryConnection ()->QueryTotalUnits ());
    ITEM_DRAW_VALUE;
}

// ** ItemTotalMoney ****************************************************** /*fold00*/

VOID ItemTotalMoney :: Repaint (HPS hps, RECTL *rcl)
{
    ITEM_DRAW_LABEL;
    FORMAT_MONEY_STRING (psz, QueryConnection ()->QueryTotalMoney ());
    ITEM_DRAW_VALUE;
}

// ** ItemTotalLimitLeft ************************************************** /*fold00*/

VOID ItemTotalLimitLeft :: Repaint (HPS hps, RECTL *rcl)
{
    ITEM_DRAW_LABEL;
    if (QueryConnection ()->QueryLimitTypeTotal () == LIMITT_UNITS)
    {
        if (! QueryConnection ()->LimitEnabledTotal ())
            strcpy (psz, "-");
        else
            sprintf (psz, "%5ld", QueryConnection ()->QueryLimitLeftTotal ());
    }
    else
    {
        if (! QueryConnection ()->LimitEnabledTotal ())
            strcpy (psz, "-");
        else
        {
            if (! QueryConnection ()->LimitExceededTotal ())
                sprintf (psz, "%ld%c%02ld%c%02ld",
                         QueryConnection ()->QueryLimitLeftHoursTotal (),
                         pset->QueryTimeSeperator (),
                         QueryConnection ()->QueryLimitLeftMinutesTotal ()%60L,
                         pset->QueryTimeSeperator (),
                         QueryConnection ()->QueryLimitLeftSecondsTotal ()%60L);
            else
                sprintf (psz, "-%ld%c%02ld%c%02ld",
                         -QueryConnection ()->QueryLimitLeftHoursTotal (),
                         pset->QueryTimeSeperator (),
                         -QueryConnection ()->QueryLimitLeftMinutesTotal ()%60L,
                         pset->QueryTimeSeperator (),
                         -QueryConnection ()->QueryLimitLeftSecondsTotal ()%60L);
        }
    }
    ITEM_DRAW_VALUE;
}

// ************************************************************************
#endif
