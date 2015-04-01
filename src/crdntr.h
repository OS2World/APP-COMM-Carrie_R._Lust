/***
 crdntr.h
 ***/

#ifndef _CRDNTR_H_
#define _CRDNTR_H_

#include "clust.h"

class Coordinator
{
public:
    Coordinator (VOID);
    ~Coordinator (VOID);

    BOOL   Log (PCONNECTION pconnect);

    VOID   UpdateSecond (PCLOCK pclock);
    VOID   UpdateDuration (PCONNECTION pconnect);
    VOID   UpdateLimit (PCONNECTION pconnect);
    VOID   UpdateUnit (PCONNECTION pconnect);
    VOID   UpdateCostsLimit (PCONNECTION pconnect);
    VOID   UpdateCharge (PCHRGINFO pchrginfo);
#ifdef _TOTALVALUES_
    VOID   UpdateLimitTotal (PCONNECTION pconnect);
    VOID   UpdateCostsLimitTotal (PCONNECTION pconnect);
#endif

    PCHRGINFO     QueryChargesInfo (PCONNECTION pconnect);

    PCHRGINFO     QueryChargesInfo (PDISPLAY pdisplay);
    PCONNECTION   QueryConnection (PDISPLAY pdisplay);

    PDISPLAY      QueryDisplay (PSETTINGS pset);
    PWARNER       QueryWarner (PSETTINGS pset);
    PCONNECTION   QueryConnection (PSETTINGS pset);

    // FIXME private! make private! ;-)
    PCLOCK        pclock;
    PCHRGINFO     pchrginfo;
    PWARNER       pwarner;
    PCONNECTION   pconnect;
    PDISPLAY      pdisplay;

    FILE   *pfile;
};

#include "clock.h"
#include "chrginfo.h"
#include "warner.h"
#include "connectn.h"
#include "display.h"

#endif
