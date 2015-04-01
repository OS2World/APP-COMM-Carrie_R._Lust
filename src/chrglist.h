/***
 chrglist.h
 ***/

#ifndef _CHRGLIST_H_
#define _CHRGLIST_H_

// ** includes ************************************************************ /*FOLD00*/

#include "clust.h"

#define SECONIZE(h,m,s)   ((h)*3600L+(m)*60L+(s))

#define MAX_CHARGESINLIST 16L
#define IDX_HOUR 0
#define IDX_MIN  1
#define IDX_SEC  2

// ** classdef ************************************************************ /*FOLD00*/

class ChargesList
{
public:
    PCHARGE   QueryCharge (USHORT usHour, USHORT usMin, USHORT usSec);

protected:
    ChargesList (VOID);

    BOOL   AddCharge (PCHARGE pcharge, USHORT usHour, USHORT usMin,
                      USHORT usSec);

private:
    USHORT    c, aus[MAX_CHARGESINLIST][3];
    PCHARGE   apcharge[MAX_CHARGESINLIST];
};

// ** inline funcs ******************************************************** /*FOLD00*/


// ************************************************************************
#endif
