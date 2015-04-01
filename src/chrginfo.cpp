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
 
#include "chrginfo.h"
#include "string.h"

// ** ChargesInfo ********************************************************* /*FOLD00*/

CHRGINFO :: ChargesInfo (PSZ psz)
{
    Reload (psz);
    cdCharge = 1;
    fDontWarn = TRUE;
    UpdateSecond ();
}

// ** Update ************************************************************** /*FOLD00*/

VOID CHRGINFO :: UpdateSecond (VOID)
{
    time_t   secs = time (NULL);
    tm       *ptm;
    ULONG    ulNow, ulThen = 0L;
    USHORT   i;

    ptm = localtime (&secs);
    ulNow = ptm->tm_hour*3600L+ptm->tm_min*60L+ptm->tm_sec;

    for (i = 0; i < c-1; i++)
    {
        ulThen =
            data[i+1].usHour*3600L+
            data[i+1].usMin*60L+
            data[i+1].usSecs;

        if (ulThen > ulNow)
            break;
    }

    ulMoneyPerUnit = MONEY_T (data[i].usMoney);
    ulUnitLength = ULONG (data[i].usLength);

    cdCharge --;
    if (! cdCharge)
    {
        if (ulThen > ulNow)
            cdCharge = ulThen - ulNow;
        else
        {
            ulThen =
                data[0].usHour*3600L+
                data[0].usMin*60L+
                data[0].usSecs;
            cdCharge = ulThen + (24L*3600L-ulNow);
        }
        if (fDontWarn)
            fDontWarn = FALSE;
        else
            NotifyCharge ();
    }

/*    if ((ptm->tm_hour >= 0) && (ptm->tm_hour < 2))
        ulUnitLength = 60L*CLUST_TICKS_PER_SEC;
    else if ((ptm->tm_hour >= 2) && (ptm->tm_hour < 5))
        ulUnitLength = 90*CLUST_TICKS_PER_SEC;
    else if ((ptm->tm_hour >= 5) && (ptm->tm_hour < 9))
        ulUnitLength = 45*CLUST_TICKS_PER_SEC;
    else if ((ptm->tm_hour >= 9) && (ptm->tm_hour < 12))
        ulUnitLength = 255;   // FIXME
    else if ((ptm->tm_hour >= 12) && (ptm->tm_hour < 18))
        ulUnitLength = 295L;  // FIXME
    else if ((ptm->tm_hour >= 18) && (ptm->tm_hour < 21))
        ulUnitLength = 45L*CLUST_TICKS_PER_SEC;
    else
        ulUnitLength = 60L*CLUST_TICKS_PER_SEC; */
    
/*    if ((ptm->tm_hour >= 0) && (ptm->tm_hour < 2))
        ulUnitLength = 4L*60L*CLUST_TICKS_PER_SEC;
    else if ((ptm->tm_hour >= 2) && (ptm->tm_hour < 5))
        ulUnitLength = 4L*60L*CLUST_TICKS_PER_SEC;
    else if ((ptm->tm_hour >= 5) && (ptm->tm_hour < 9))
        ulUnitLength = 150L*CLUST_TICKS_PER_SEC;
    else if ((ptm->tm_hour >= 9) && (ptm->tm_hour < 12))
        ulUnitLength = 90L*CLUST_TICKS_PER_SEC;
    else if ((ptm->tm_hour >= 12) && (ptm->tm_hour < 18))
        ulUnitLength = 90L*CLUST_TICKS_PER_SEC;
    else if ((ptm->tm_hour >= 18) && (ptm->tm_hour < 21))
        ulUnitLength = 150L*CLUST_TICKS_PER_SEC;
    else
        ulUnitLength = 4*60L*CLUST_TICKS_PER_SEC;

    ulUnitLength = 10L*CLUST_TICKS_PER_SEC;  */
}

// ************************************************************************

BOOL CHRGINFO :: Reload (PSZ pszFile)
{
    static PSZ pszDays[7] =
    {
        "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday",
        "Friday", "Saturday"
    };
    static PSZ pszMonths[12] =
    {
        "Jan", "Feb", "Mar", "Apr", "May", "Jun",
        "Jul", "Aug", "Sep", "Okt", "Nov", "Dez",
    };

    FILE *pfile;

    c = 0;

    if (! (pfile = fopen (pszFile, "r")))
        return FALSE;

    CHAR    ach[257];
    BOOL    fUseNext = FALSE;
    USHORT  cLines = 0, usLevel = 0;

    while (c < MAX_CHARGES)
    {
        fgets (ach, sizeof (ach), pfile);
        if (feof (pfile))
        {
//            DisplayError ("DEBUG", "c = %d", c);
            break;
        }

//        DisplayError ("DEBUG", "c = %d, <%s>", c, ach);
        cLines ++;

        PSZ  psz3 = ach+strspn (ach, " \t");

        if (! (psz3[0] == '#') && ! (psz3[0] == '\n') && ! (psz3[0] == '\r'))
        {
            PSZ  psz;

            if (! (psz = strtok (psz3, ":")))
                DisplayError ("SYNTAX ERROR", "Error in '%s', line %d", psz, cLines);

            // We found a "Weekday" entry; check if it fits the current date
            if (stricmp (psz, "Day") == 0)
            {
                if (c)
                    fUseNext = FALSE;

                if (! (psz = strtok (NULL, " \n\r")))
                    DisplayError ("SYNTAX ERROR", "Error in '%s', line %d", psz, cLines);

                time_t   secs = time (NULL);
                tm       *ptm;

                // get current time
                ptm = localtime (&secs);

                // is it the current weekday or the current date?
                if ((stricmp (pszDays[ptm->tm_wday], psz) == 0) &&
                    (usLevel <= 1))
                {
                    usLevel = 1;
                    c = 0;
                    fUseNext = TRUE;
/*                    DisplayError ("DEBUG", "<%s> == <%s>",
                                  pszDays[ptm->tm_wday], psz); */
                }
                else
                {
                    PSZ  psz2 = strtok (NULL, " \n\r");
                    if (psz2)
                    {
                        if ((stricmp (pszMonths[ptm->tm_mon], psz) == 0) &&
                            (atol (psz2) == ptm->tm_mday) && (usLevel <= 2))
                        {
                            usLevel = 2;
                            c = 0;
                            fUseNext = TRUE;
                            /*                        DisplayError ("DEBUG", "<%s><%d> == <%s><%d>",
                             pszMonths[ptm->tm_mon], ptm->tm_mday,
                             psz, atol (psz2)); */
                        }
                    }
                }
            }
            // We found a "Charge" entry; check if it can be used
            else if (stricmp (psz, "Charge") == 0)
            {
                if (fUseNext)
                {
                    if (! (psz = strtok (NULL, " :")))
                        DisplayError ("SYNTAX ERROR", "Error in '%s', line %d", psz, cLines);
                    data[c].usHour   = atoi (psz);

                    if (! (psz = strtok (NULL, " :")))
                        DisplayError ("SYNTAX ERROR", "Error in '%s', line %d", psz, cLines);
                    data[c].usMin    = atoi (psz);

                    if (! (psz = strtok (NULL, " ,")))
                        DisplayError ("SYNTAX ERROR", "Error in '%s', line %d", psz, cLines);
                    data[c].usSecs   = atoi (psz);

                    if (! (psz = strtok (NULL, " ,")))
                        DisplayError ("SYNTAX ERROR", "Error in '%s', line %d", psz, cLines);
                    data[c].usLength = atoi (psz);

                    if (! (psz = strtok (NULL, " ,")))
                        DisplayError ("SYNTAX ERROR", "Error in '%s', line %d", psz, cLines);
                    data[c].usMoney  = atof (psz);

/*                    DisplayError ("ADDED", "%d: %02d:%02d:%02d, %d, %d", c,
                                  data[c].usHour, data[c].usMin,
                                  data[c].usSecs, data[c].usLength,
                                  data[c].usMoney); */
                    c ++;
                }
            }
            else
                DisplayError ("SYNTAX ERROR", "Error in '%s', line %d", psz, cLines);
/*
            ach[2] = ach[5] = ach[8] = ach[17] = ach[26] = '\0';
            data[c].usHour   = atoi (ach);
            data[c].usMin    = atoi (ach+3);
            data[c].usSecs   = atoi (ach+6);
            data[c].usLength = atoi (ach+9);
            data[c].usMoney  = atoi  (ach+18); */
        }
    }
    fclose (pfile);

    return TRUE;
}

// ************************************************************************
