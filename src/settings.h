/***
 settings.h
 ***/

#ifndef _SETTINGS_H_
#define _SETTINGS_H_

#define INCL_DOSNLS

#include "thth/thth_settings.h"

// ************************************************************************

#include "clust.h"

#define PSZ_PROFILENAME           "clust.ini"

// this should be increased every time the format of the proFile changes
#ifdef _TOTALVALUES_
#define L_PROFILEVERSION          3
#else
#define L_PROFILEVERSION          2
#endif

// ** Classdef ************************************************************ /*FOLD00*/

class Settings : public ththSettings
{
public:
    Settings (VOID);
    ~Settings (VOID);

    BOOL   Dialog (VOID);

    VOID ShowItem (IID iid, BOOL f) {
        if (iid >= MAX_ITEMS)
            return;
        ((BOOL *) QueryBinary (SEI_SHOWITEMS))[iid] = f; }

    BOOL ShowItem (IID iid) {
        if (iid >= MAX_ITEMS)
            return FALSE;
        return ((BOOL *) QueryBinary (SEI_SHOWITEMS))[iid];
    }

    VOID   ShowExitButton (BOOL f) { SetFlag (SEI_SHOWEXITBUTTON, f); }
    VOID   ShowSuspendButton (BOOL f) { SetFlag (SEI_SHOWSUSPENDBUTTON, f); }
    VOID   ShowResetButton (BOOL f) { SetFlag (SEI_SHOWRESETBUTTON, f); }

    BOOL   ShowExitButton (VOID) { return QueryFlag (SEI_SHOWEXITBUTTON); }
    BOOL   ShowSuspendButton (VOID) { return QueryFlag (SEI_SHOWSUSPENDBUTTON); }
    BOOL   ShowResetButton (VOID) { return QueryFlag (SEI_SHOWRESETBUTTON); }

    WARN_T   QueryWarntUnit (VOID) {
        return WARN_T (QueryLong (SEI_WARNTUNIT)); }
    WARN_T   QueryWarntCharge (VOID) {
        return WARN_T (QueryLong (SEI_WARNTCHARGE)); }
    WARN_T   QueryWarntCosts (VOID) {
        return WARN_T (QueryLong (SEI_WARNTCOSTS)); }
    WARN_T   QueryWarntLimit (VOID) {
        return WARN_T (QueryLong (SEI_WARNTLIMIT)); }

    VOID   SetWarntUnit (WARN_T warnt) { SetLong (SEI_WARNTUNIT, warnt); }
    VOID   SetWarntCharge (WARN_T warnt) { SetLong (SEI_WARNTCHARGE, warnt); }
    VOID   SetWarntCosts (WARN_T warnt) { SetLong (SEI_WARNTCOSTS, warnt); }
    VOID   SetWarntLimit (WARN_T warnt) { SetLong (SEI_WARNTLIMIT, warnt); }

    VOID      SetLimitType (LIMIT_T limitt) { SetLong (SEI_LIMITTYPE, limitt); }
    LIMIT_T   QueryLimitType (VOID) {
        return LIMIT_T (QueryLong (SEI_LIMITTYPE)); }

    VOID   SetLimit (ULONG ul) { SetLong (SEI_LIMITVALUE, ul); }

    ULONG QueryLimit (VOID) {
        if (QueryWarntLimit () != WARNT_DONTWARN)
            return QueryLong (SEI_LIMITVALUE);
        return 0; }

    VOID   SetCostsLimit (ULONG ul) { SetLong (SEI_LIMITCOSTS, ul); }
    ULONG  QueryCostsLimit (VOID) { return QueryLong (SEI_LIMITCOSTS); }

    VOID SetWindowData (SWP *pswp, USHORT us[7]) {
        SetBinary (SEI_SWP, pswp, sizeof (*pswp));
        SetBinary (SEI_US, us, sizeof (us[0])*7); }

    VOID   QueryWindowData (SWP *pswp, USHORT us[7]);

    VOID   AdjustSettings (VOID);

    VOID   ShowFrame (BOOL f) { SetFlag (SEI_WINDOWSHOWFRAME, f); }
    BOOL   ShowFrame (VOID) { return QueryFlag (SEI_WINDOWSHOWFRAME); }

    VOID   UseLogfile (BOOL f) { SetFlag (SEI_LOGFILEUSE, f); }
    BOOL   UseLogfile (VOID) { return QueryFlag (SEI_LOGFILEUSE); }

    PSZ    QueryLogfileName (VOID) { return QueryString (SEI_LOGFILENAME); }
    VOID   SetLogfileName (PSZ psz) { SetString (SEI_LOGFILENAME, psz); }

    COLOR  QueryBackgroundColor (VOID) {
        return *((COLOR *)QueryBinary (SEI_BACKGROUNDCOLOR)); }
    VOID   SetBackgroundColor (COLOR color) {
        SetBinary (SEI_BACKGROUNDCOLOR, &color, sizeof (color)); }

    VOID   SetFontNameSize (PSZ psz) { SetString (SEI_FONTNAMESIZE, psz); }
    PSZ    QueryFontNameSize (VOID) { return QueryString (SEI_FONTNAMESIZE); }

    VOID   DoUnitCountdown (BOOL f) { SetFlag (SEI_WARNCOUNTDOWN, f); }
    BOOL   DoUnitCountdown (VOID) { return QueryFlag (SEI_WARNCOUNTDOWN); }

    CHAR   QueryTimeSeperator (VOID) { return ci.szTimeSeparator[0]; }
    PCOUNTRYINFO   QueryCountryInfo (VOID) { return &ci; }

protected:
    static MRESULT EXPENTRY
        DialogProcedure (HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2);
    static MRESULT EXPENTRY
        Page1Procedure (HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2);
    static MRESULT EXPENTRY
        Page2Procedure (HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2);
    static MRESULT EXPENTRY
        Page3Procedure (HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2);

    USHORT   FileNotOpenError (VOID);
    USHORT   VersionError (VOID);

private:
    SWP           swp;
    USHORT        us[7];
    COUNTRYINFO   ci;

    PDISPLAY      pdisplay;
    static HWND   hwndPage[3];
};

#include "crdntr.h"
#include "display.h"

// ************************************************************************
#endif
