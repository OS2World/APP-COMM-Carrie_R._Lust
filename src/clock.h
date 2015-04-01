/***
 clock.h
 ***/

#ifndef _CLOCK_H_
#define _CLOCK_H_

// ** includes ************************************************************ /*FOLD00*/

#include <time.h>

#include "clust.h"

// ** classdef ************************************************************ /*FOLD00*/

class Clock
{
public:
    Clock (VOID);
    ~Clock (VOID);

    ULONG   QueryHours (VOID);
    ULONG   QueryMinutes (VOID);
    ULONG   QuerySeconds (VOID);

protected:
    VOID    NotifySecond (VOID);

    static VOID Tick (PVOID);

private:
    static class Clock   *pclock;
    static BOOL          fTickOn;
};

// ** inline funcs ******************************************************** /*FOLD00*/

#include "crdntr.h"

// ------------------------------------------------------------------------

inline VOID CLOCK :: NotifySecond (VOID)
{
    if (! g_fQuitting)
        pcrdntr->UpdateSecond (this);
}

inline CLOCK :: ~Clock (VOID)
{
    // Tell Tick () thread to exit
    fTickOn = FALSE;
}

// ************************************************************************
#endif
