/***
 warner.h
 ***/

#ifndef _WARNER_H_
#define _WARNER_H_

#include "clust.h"

class Warner
{
public:
    PSZ    QueryWarnDescription (WARN_T warnt);

    VOID   UpdateUnit (VOID);
    VOID   UpdateCharge (VOID);
    VOID   UpdateCosts (VOID);
    VOID   UpdateLimit (VOID);
    VOID   UpdateCostsLimit (VOID);

#ifdef _TOTALVALUES_
    VOID UpdateCostsLimitTotal (VOID);
    VOID UpdateLimitTotal (VOID);
#endif

protected:
    VOID   Warn (WARN_T warnt, PSZ pszTitle = NULL, PSZ pszText = NULL);
};

#include "settings.h"

inline VOID WARNER :: UpdateUnit (VOID)
{
    Warn (pset->QueryWarntUnit (), "CARRIE R. LUST",
          "A unit has passed.");
}

inline VOID WARNER :: UpdateCharge (VOID)
{
    Warn (pset->QueryWarntCharge (), "CARRIE R. LUST",
          "We have switched to another charge.");
}

inline VOID WARNER :: UpdateLimit (VOID)
{
    Warn (pset->QueryWarntLimit (), "CARRIE R. LUST",
          "The time-limit has been reached.");
}

inline VOID WARNER :: UpdateCostsLimit (VOID)
{
    Warn (pset->QueryWarntCosts (), "CARRIE R. LUST",
          "The costs-limit has been reached.");
}

#ifdef _TOTALVALUES_
inline VOID WARNER :: UpdateCostsLimitTotal (VOID)
{
    Warn (pset->QueryWarntLimit (), "CARRIE R. LUST",
          "The total costs-limit has been reached.");
}

inline VOID WARNER :: UpdateLimitTotal (VOID)
{
    Warn (pset->QueryWarntLimit (), "CARRIE R. LUST",
          "The total time-limit has been reached.");
}
#endif

#endif
