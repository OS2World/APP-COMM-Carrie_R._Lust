/***
 connectn.h
 ***/

#ifndef _CONNECTN_H_
#define _CONNECTN_H_

// ** includes ************************************************************ /*FOLD00*/

#include <memory.h>
#include <time.h>

#include "clust.h"

// ** classdef ************************************************************ /*FOLD00*/

class Connection
{
    friend class Coordinator;
    
public:
#ifdef _TOTALVALUES_
    Connection (ULONG ul, ULONG ulUnits, MONEY_T ulMoney, BOOL f = TRUE,
                LONG c = 0L);
#else
    Connection (ULONG ul, BOOL f = TRUE, LONG c = 0L);
#endif

    VOID    Reset (VOID);
    BOOL    WasActive (VOID) { return fWasActive; }

    ULONG   QueryHours (VOID);
    ULONG   QueryMinutes (VOID);
    ULONG   QuerySeconds (VOID);

    ULONG   QueryDuration (VOID);
    ULONG   QueryTotalConTime (VOID);

#ifdef _TOTALVALUES_
    ULONG   QueryTotalUnits (VOID) { return cUnitsTotal; }
    MONEY_T   QueryTotalMoney (VOID) { return cMoneyTotal; }
#endif
    ULONG   QueryUnits (VOID);
    MONEY_T   QueryMoney (VOID);

    ULONG   QueryUnitLeftMinutes (VOID);
    ULONG   QueryUnitLeftSeconds (VOID);
    ULONG   QueryUnitLeft10thSecs (VOID);

    LONG    QueryLimitLeftHours (VOID);
    LONG    QueryLimitLeftMinutes (VOID);
    LONG    QueryLimitLeftSeconds (VOID);
    LONG    QueryLimitLeft (VOID);
#ifdef _TOTALVALUES_
    LONG    QueryLimitLeftHoursTotal (VOID) {
        return (LONG (QueryLimitLeftTotal ()/(CLUST_TICKS_PER_SEC*60L*60L))); }
    LONG    QueryLimitLeftMinutesTotal (VOID) {
        return (LONG (QueryLimitLeftTotal ()/(CLUST_TICKS_PER_SEC*60L))); }
    LONG    QueryLimitLeftSecondsTotal (VOID) {
        return (LONG (QueryLimitLeftTotal ()/CLUST_TICKS_PER_SEC)); }
    LONG    QueryLimitLeftTotal (VOID) {
        return (LONG (cLimitTotal-cLimitCurrentTotal)); }
#endif

    ULONG   QueryLimit (VOID);
    VOID    SetLimit (ULONG ul);

#ifdef _TOTALVALUES_
    ULONG   QueryLimitTotal (VOID) { return (cLimitTotal); }
    VOID    SetLimitTotal (ULONG ul);

    VOID    SetLimitTypeTotal (LIMIT_T limitt, BOOL f = FALSE);
    LIMIT_T QueryLimitTypeTotal (VOID) { return limittTotal; }
#endif

    LIMIT_T QueryLimitType (VOID);
    VOID    SetLimitType (LIMIT_T limitt, BOOL f = FALSE);
    // FIXME f default should be TRUE but doesn't work right yet

    BOOL    LimitExceeded (VOID);
    BOOL    LimitEnabled (VOID);

#ifdef _TOTALVALUES_
    BOOL    LimitExceededTotal (VOID) { return (BOOL(cLimitCurrentTotal > cLimitTotal)); }
    BOOL    LimitEnabledTotal (VOID) { return (BOOL (QueryLimitTotal () != 0)); }
#endif

    VOID    Suspend (VOID);
    VOID    Continue (VOID);
    BOOL    IsSuspended (VOID);

    BOOL    WasReset (VOID);

    USHORT  QueryStartSeconds (VOID);
    USHORT  QueryStartMinutes (VOID);
    USHORT  QueryStartHours (VOID);
    USHORT  QueryStartMDay (VOID);
    USHORT  QueryStartMonth (VOID);
    USHORT  QueryStartYear (VOID);

protected:
    VOID    UpdateSecond (VOID);

    VOID    NotifyDuration (VOID);
    VOID    NotifyUnit (VOID);
    VOID    NotifyLimit (VOID);
    VOID    NotifyCostsLimit (VOID);
#ifdef _TOTALVALUES_
    VOID    NotifyCostsLimitTotal (VOID);
    VOID    NotifyLimitTotal (VOID);
#endif

private:
    ULONG   cTicks;     // duration of connection in clust-ticks
    ULONG   cUnits;     // duration of connection in units
    MONEY_T   cMoney;     // total costs
    LONG    cdUnit;     // ticks left till end of unit
    LONG    cLimit;     // con.time-limit in ticks
    LIMIT_T limitt;
    BOOL    fCostsWarned, fWasReset, fWasActive;
#ifdef _TOTALVALUES_
    MONEY_T   cMoneyTotal;     // total costs
    ULONG   cUnitsTotal;     // duration of connection in units
    LONG    cLimitTotal;     // con.time-limit in ticks
    LIMIT_T limittTotal;
    LONG    cLimitCurrentTotal;
    BOOL    fCostsWarnedTotal;
#endif

    tm      tmStart;

    BOOL    fSuspended;
    LONG    cCountdown;

    LONG    cLimitCurrent;
    LONG    cTotal;       // saved total connection time
};

// ** inline funcs ******************************************************** /*FOLD00*/

inline VOID CONNECTION :: Suspend (VOID)     { fSuspended = TRUE; }
inline VOID CONNECTION :: Continue (VOID)    { fWasActive = TRUE; fSuspended = FALSE; }

#include "chrginfo.h"
#include "crdntr.h"

// ------------------------------------------------------------------------

#ifdef _TOTALVALUES_
inline VOID CONNECTION :: NotifyCostsLimitTotal (VOID) { pcrdntr->UpdateCostsLimitTotal (this); }
inline VOID CONNECTION :: NotifyLimitTotal (VOID) { pcrdntr->UpdateLimitTotal (this); }
#endif

inline VOID CONNECTION :: NotifyDuration (VOID) { pcrdntr->UpdateDuration (this); }
inline VOID CONNECTION :: NotifyUnit (VOID)   { pcrdntr->UpdateUnit (this);   }
inline VOID CONNECTION :: NotifyLimit (VOID)  { pcrdntr->UpdateLimit (this);  }
inline VOID CONNECTION :: NotifyCostsLimit (VOID)  { pcrdntr->UpdateCostsLimit (this);  }

inline ULONG CONNECTION :: QueryDuration (VOID)     { return cTicks; }
inline ULONG CONNECTION :: QueryTotalConTime (VOID) { return cTicks+cTotal; }

inline ULONG CONNECTION :: QueryHours (VOID) {
    return (ULONG (QueryDuration ()/(CLUST_TICKS_PER_SEC*60L*60L))); }
inline ULONG CONNECTION :: QueryMinutes (VOID)   {
    return (ULONG (QueryDuration ()/(CLUST_TICKS_PER_SEC*60L))); }
inline ULONG CONNECTION :: QuerySeconds (VOID) {
    return (ULONG (QueryDuration ()/CLUST_TICKS_PER_SEC)); }

inline ULONG CONNECTION :: QueryUnits (VOID)     { return (cUnits); }
inline MONEY_T CONNECTION :: QueryMoney (VOID)     { return (cMoney); }

inline ULONG CONNECTION :: QueryUnitLeftMinutes (VOID) {
    return (cdUnit/(CLUST_TICKS_PER_SEC*60L)); }
inline ULONG CONNECTION :: QueryUnitLeftSeconds (VOID) {
    return (cdUnit/CLUST_TICKS_PER_SEC); }
inline ULONG CONNECTION :: QueryUnitLeft10thSecs (VOID) {
    return (cdUnit); }

inline LONG  CONNECTION :: QueryLimitLeftHours (VOID) {
    return (LONG ((cLimit-cLimitCurrent)/(CLUST_TICKS_PER_SEC*60L*60L))); }
inline LONG  CONNECTION :: QueryLimitLeftMinutes (VOID) {
    return (LONG ((cLimit-cLimitCurrent)/(CLUST_TICKS_PER_SEC*60L))); }
inline LONG  CONNECTION :: QueryLimitLeftSeconds (VOID) {
    return (LONG ((cLimit-cLimitCurrent)/CLUST_TICKS_PER_SEC)); }
inline LONG  CONNECTION :: QueryLimitLeft (VOID) {
    return (LONG (cLimit-cLimitCurrent)); }

inline ULONG CONNECTION :: QueryLimit (VOID)  { return (cLimit); }

inline LIMIT_T CONNECTION :: QueryLimitType (VOID) { return (limitt); }

inline BOOL CONNECTION :: LimitExceeded (VOID) {
    return (BOOL(cLimitCurrent > cLimit)); }
inline BOOL CONNECTION :: LimitEnabled (VOID) {
    return (BOOL (QueryLimit () != 0)); }

inline BOOL CONNECTION :: WasReset (VOID)
{
    if (! fWasReset)
        return (FALSE);

    fWasReset = FALSE;
    return (TRUE);
}

inline USHORT CONNECTION :: QueryStartSeconds (VOID) { return (tmStart.tm_sec); }
inline USHORT CONNECTION :: QueryStartMinutes (VOID) { return (tmStart.tm_min); }
inline USHORT CONNECTION :: QueryStartHours (VOID)   { return (tmStart.tm_hour); }
inline USHORT CONNECTION :: QueryStartMDay (VOID)    { return (tmStart.tm_mday); }
inline USHORT CONNECTION :: QueryStartMonth (VOID)   { return (tmStart.tm_mon+1); }
inline USHORT CONNECTION :: QueryStartYear (VOID)    { return (tmStart.tm_year+1900); }

// ------------------------------------------------------------------------

inline BOOL CONNECTION :: IsSuspended (VOID) {
    return (BOOL(fSuspended == TRUE)); }

// ************************************************************************
#endif
