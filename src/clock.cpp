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

#include "clock.h"

// ************************************************************************ /*FOLD00*/

PCLOCK CLOCK :: pclock  = NULL;
BOOL   CLOCK :: fTickOn = FALSE;

// ** Tick **************************************************************** /*FOLD00*/

VOID CLOCK :: Tick (PVOID)
{
    // ATTENTION: Update-stuff should *never* take longer than 1 second!
    
    static time_t    secsOld = time (NULL);

    HMQ   hmq = WinCreateMsgQueue (hab, 0);

    while (fTickOn)
    {
        _sleep2 (950);
        for (; secsOld < time (NULL); secsOld++)
            if (pclock)  // Must be checked, when clock just got deleted
                pclock->NotifySecond ();
    }

    WinDestroyMsgQueue (hmq);
}

// ** Clock *************************************************************** /*FOLD00*/

CLOCK :: Clock (VOID)
{
    pclock = this;
    fTickOn = TRUE;
    _beginthread (Tick, NULL, 1024L*32L, NULL);
}

// ************************************************************************
