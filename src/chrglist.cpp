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

#include "chrglist.h"

// ** ChargesList ********************************************************* /*FOLD00*/

CHARGESLIST :: ChargesList (VOID)
{
    for (c = 0; c < MAX_CHARGESINLIST; c++)
    {
        aus[c][IDX_HOUR] = aus[c][IDX_MIN] = aus[c][IDX_SEC] = 0;
        apcharge[c] = NULL;
    }
    c = 0;
}

// ** QueryCharge ********************************************************* /*FOLD00*/

PCHARGE CHARGESLIST :: QueryCharge (USHORT usHour, USHORT usMin, USHORT usSec)
{
    USHORT   i;

    for (i = 0; i < c; i++)
        if (SECONIZE (usHour, usMin, usSec) >=
            SECONIZE (aus[i][IDX_HOUR], aus[i][IDX_MIN], aus[i][IDX_SEC]))
            return (apcharge[i]);

    return (NULL);
}

// ** AddCharge *********************************************************** /*FOLD00*/

BOOL CHARGESLIST :: AddCharge (PCHARGE pcharge, USHORT usHour, USHORT usMin,
                               USHORT usSec)
{
    USHORT   i, j;

    if (c >= MAX_CHARGESINLIST)
        return (FALSE);

    for (i = 0; i < c; i++)
        if (SECONIZE (usHour, usMin, usSec) <=   // FIXME "==" !?
            SECONIZE (aus[i][IDX_HOUR], aus[i][IDX_MIN], aus[i][IDX_SEC]))
        {
            for (j = c; j > i; j--)
            {
                aus[j][IDX_HOUR] = aus[j-1][IDX_HOUR];
                aus[j][IDX_MIN]  = aus[j-1][IDX_MIN];
                aus[j][IDX_SEC]  = aus[j-1][IDX_SEC];
            }
            break;
        }

    aus[i][IDX_HOUR] = usHour;
    aus[i][IDX_MIN]  = usMin;
    aus[i][IDX_SEC]  = usSec;

    c ++;
    return (TRUE);
}

// ************************************************************************
