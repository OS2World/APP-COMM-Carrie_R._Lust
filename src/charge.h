/***
 charge.h
 ***/

#ifndef _CHARGE_H_
#define _CHARGE_H_

// ** includes ************************************************************ /*FOLD00*/

#include "clust.h"

// ** classdef ************************************************************ /*FOLD00*/

class Charge
{
    friend class ChargesDatabase;

public:
    PSZ        QueryName (VOID);
    MONEY_T    QueryMoney (VOID);
    LENGTH_T   QueryLength (VOID);

protected:
    Charge (PSZ pszID, PSZ psz, MONEY_T money, LENGTH length);
    ~Charge (VOID);

    PSZ   QueryID (VOID);

private:
    PSZ        psz, pszID;
    MONEY_T    money;
    LENGTH_T   length;
};

// ** inline funcs ******************************************************** /*FOLD00*/

PSZ CHARGE :: QueryName (VOID)         { return (psz);    }
MONEY_T CHARGE :: QueryMoney (VOID)    { return (money);  }
LENGTH_T CHARGE :: QueryLength (VOID)  { return (length); }

PSZ CHARGE :: QueryID (VOID)  { return (pszID); }

CHARGE :: Charge (PSZ pszID, PSZ psz, MONEY_T money, LENGTH length)
{
    this->pszID = strdup (pszID);
    this->psz = strdup (psz);
    this->money = money;
    this->length = length;
}

CHARGE :: ~Charge (VOID)
{
    if (psz)
        free (psz);
    if (pszID)
        free (pszID);
}

// ************************************************************************
#endif
