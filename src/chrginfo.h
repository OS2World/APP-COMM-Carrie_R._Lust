/***
 chrginfo.h
 ***/

#ifndef _CHRGINFO_H_
#define _CHRGINFO_H_

// ** includes ************************************************************ /*FOLD00*/

#include "clust.h"

#define MAX_CHARGES   32

// ** classdef ************************************************************ /*FOLD00*/

class ChargesInfo
{
    friend class Coordinator;

public:
    ChargesInfo (PSZ psz);

    ULONG   QueryUnitLength (VOID);
    ULONG   QueryUnitLengthMinutes (VOID);
    ULONG   QueryUnitLengthSeconds (VOID);
    ULONG   QueryUnitLength10thSecs (VOID);

    MONEY_T  QueryMoneyPerUnit (VOID);

    MONEY_T  QueryMoneyPerMinute (VOID);
    MONEY_T  QueryMoneyPerHour (VOID);
    ULONG   QuerySecsTillCharge (VOID);

    BOOL    Reload (VOID);

protected:
    VOID    UpdateSecond (VOID);
    VOID    NotifyCharge (VOID);

    BOOL    Reload (PSZ psz);

private:
    ULONG    ulUnitLength;
    MONEY_T   ulMoneyPerUnit;
    ULONG    cdCharge;
    USHORT   c;

    CHAR     ach[_MAX_PATH];
    BOOL     fDontWarn;

struct
{
    USHORT  usHour, usMin, usSecs;
    USHORT  usLength;
    MONEY_T  usMoney;
} data[MAX_CHARGES];
};

// ** inline funcs ******************************************************** /*FOLD00*/

inline ULONG CHRGINFO :: QueryUnitLength (VOID) {
    return ((ulUnitLength == 0L) ? 1L : ulUnitLength); }

inline ULONG CHRGINFO :: QueryUnitLengthMinutes (VOID) {
    return (QueryUnitLength ()/(CLUST_TICKS_PER_SEC*60L)); }
inline ULONG CHRGINFO :: QueryUnitLengthSeconds (VOID) {
    return (QueryUnitLength ()/CLUST_TICKS_PER_SEC); }
inline ULONG CHRGINFO :: QueryUnitLength10thSecs (VOID) {
    return (QueryUnitLength ()); }

inline MONEY_T CHRGINFO :: QueryMoneyPerUnit (VOID)  { return (ulMoneyPerUnit); }

inline MONEY_T CHRGINFO :: QueryMoneyPerMinute (VOID) {
    return (MONEY_T ((QueryMoneyPerUnit ()*60.0*double(CLUST_TICKS_PER_SEC))
                     /double(QueryUnitLength ()))); }

inline MONEY_T CHRGINFO :: QueryMoneyPerHour (VOID) {
    return (MONEY_T ((QueryMoneyPerUnit ()*3600.0*double(CLUST_TICKS_PER_SEC))
                     /double(QueryUnitLength ()))); }

inline ULONG CHRGINFO :: QuerySecsTillCharge (VOID) { return (cdCharge); }

// ------------------------------------------------------------------------

#include "crdntr.h"

// ------------------------------------------------------------------------

inline VOID CHRGINFO :: NotifyCharge (VOID)
{
    pcrdntr->UpdateCharge (this);
}

inline BOOL CHRGINFO :: Reload (VOID)  { return Reload (ach); }

// ************************************************************************
#endif
