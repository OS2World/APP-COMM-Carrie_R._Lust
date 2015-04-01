/***
 display.h
 ***/

#ifndef _DISPLAY_H_
#define _DISPLAY_H_

// ** includes ************************************************************ /*fold00*/

#include "memory.h"
#include "string.h"
#include "clust.h"
#include "helper.h"

// ** defines ************************************************************* /*FOLD00*/

#define UM_TOGGLE_FRAME      UM_START+0
#define PSZ_WINNAME          "winclass.Display"
#define DISPLAY_XS           QueryWidth ()

// ** classdef ************************************************************ /*FOLD00*/

class Display
{
    friend class Item;
    friend class Coordinator;
    friend class Settings;
    
public:
    Display (BOOL fUseHelp = TRUE);
    ~Display (VOID);

    VOID   Repaint (VOID);
    VOID   Settings (VOID);

    VOID   ShowItem (IID iid);
    VOID   HideItem (IID iid);
    BOOL   IsShownItem (IID iid);
    PITEM  QueryItem (IID iid);

    VOID   HideExitButton (VOID);
    VOID   ShowExitButton (VOID);
    BOOL   IsShownExitButton (VOID);

    VOID   HideSuspendButton (VOID);
    VOID   ShowSuspendButton (VOID);
    BOOL   IsShownSuspendButton (VOID);

    VOID   HideResetButton (VOID);
    VOID   ShowResetButton (VOID);
    BOOL   IsShownResetButton (VOID);
    
    BOOL   FrameHidden (VOID);
    VOID   ShowFrame (VOID);
    VOID   HideFrame (VOID);

    // FIXME make protected
    HWND   QueryHWNDFrame (VOID)   { return (hwndFrame);  }

    VOID   Show (BOOL f = TRUE) { WinShowWindow (QueryHWNDFrame (), f); }
    VOID   Hide (VOID) { Show (FALSE); }

protected:
    VOID   Drag (VOID);
    VOID   Resize (VOID);

    VOID   UpdateSecond (VOID);
    VOID   UpdateDuration (VOID);
    VOID   UpdateLimit (VOID);
    VOID   UpdateUnit (VOID);
    VOID   UpdateCharge (VOID);
    VOID   UpdateCostsLimit (VOID);

#ifdef _TOTALVALUES_
    VOID UpdateLimitTotal (VOID) {
        if (RefreshEnabled ())
            WinInvalidateRect (QueryHWNDClient (), NULL, TRUE); }
    VOID UpdateCostsLimitTotal (VOID) {
        if (RefreshEnabled ())
            WinInvalidateRect (QueryHWNDClient (), NULL, TRUE); }
#endif

    VOID   Reformat (VOID);
    VOID   UpdateButtons (VOID);

    VOID   EnableRefresh (VOID);
    VOID   DisableRefresh (VOID);
    BOOL   RefreshEnabled (VOID);

    HWND   QueryHWNDClient (VOID);

    PCHRGINFO     QueryChargesInfo (VOID);
    PCONNECTION   QueryConnection (VOID);

    VOID   ToggleFrame (VOID);
    VOID   HideFrame (BOOL fHide);

    USHORT   QueryHeight (VOID);
    USHORT   QueryWidth (VOID);

    USHORT   QueryFontSizeX (VOID);
    USHORT   QueryFontSizeY (VOID);

    static MRESULT EXPENTRY
        WindowProcedure (HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2);

    static VOID   HandlePipe (PVOID);
    static VOID   AutodetectConnection (PVOID);

private:
    HWND   hwndFrame, hwndClient, hwndSysMenu, hwndTitleBar, hwndMinMax;
    BOOL   fFrameHidden, fRefreshEnabled;

    BOOL   fShowExitButton, fShowSuspendButton, fShowResetButton;
    HWND   hwndExitButton, hwndSuspendButton, hwndResetButton;
    HWND   hwndMenu;

    USHORT        cxFont, cyFont;

    PITEM         apitem[MAX_ITEMS];

    PHELPER       phelp;

    static BOOL   fClassRegistered;
};

// ** inline funcs ******************************************************** /*FOLD00*/

#include "crdntr.h"
#include "connectn.h"

// ------------------------------------------------------------------------

inline PCHRGINFO DISPLAY :: QueryChargesInfo (VOID)
{
    return (pcrdntr->QueryChargesInfo (this));
}

inline PCONNECTION DISPLAY :: QueryConnection (VOID)
{
    return (pcrdntr->QueryConnection (this));
}

// ------------------------------------------------------------------------

#include "items.h"

// ------------------------------------------------------------------------

inline BOOL DISPLAY :: IsShownSuspendButton (VOID) {
    return (fShowSuspendButton); }

inline BOOL DISPLAY :: IsShownResetButton (VOID) {
    return (fShowResetButton); }

inline BOOL DISPLAY :: IsShownExitButton (VOID) {
    return (fShowExitButton); }

inline BOOL DISPLAY :: FrameHidden (VOID)  { return (fFrameHidden); }
inline VOID DISPLAY :: ShowFrame (VOID)    { HideFrame (FALSE);     }
inline VOID DISPLAY :: HideFrame (VOID)    { HideFrame (TRUE);      }

inline VOID DISPLAY :: EnableRefresh (VOID)  { fRefreshEnabled = TRUE; }
inline VOID DISPLAY :: DisableRefresh (VOID) { fRefreshEnabled = FALSE; }
inline BOOL DISPLAY :: RefreshEnabled (VOID) { return (fRefreshEnabled); }

inline HWND DISPLAY :: QueryHWNDClient (VOID)  { return (hwndClient); }

// ------------------------------------------------------------------------

inline VOID DISPLAY :: UpdateDuration (VOID)
{
    if (RefreshEnabled ())
        WinInvalidateRect (QueryHWNDClient (), NULL, TRUE);
}

inline VOID DISPLAY :: UpdateLimit (VOID)
{
    if (RefreshEnabled ())
        WinInvalidateRect (QueryHWNDClient (), NULL, TRUE);
}

inline VOID DISPLAY :: UpdateUnit (VOID)
{
    if (RefreshEnabled ())
        WinInvalidateRect (QueryHWNDClient (), NULL, TRUE);
}

inline VOID DISPLAY :: UpdateCharge (VOID)
{
    if (RefreshEnabled ())
        WinInvalidateRect (QueryHWNDClient (), NULL, TRUE);
}

inline VOID DISPLAY :: UpdateCostsLimit (VOID)
{
    if (RefreshEnabled ())
        WinInvalidateRect (QueryHWNDClient (), NULL, TRUE);
}

// ------------------------------------------------------------------------

inline VOID DISPLAY :: ToggleFrame (VOID)
{
    if (this->FrameHidden ())
        this->ShowFrame ();
    else
        this->HideFrame ();
}

inline PITEM DISPLAY :: QueryItem (IID iid) { return (apitem[iid]); }

inline USHORT DISPLAY :: QueryFontSizeX (VOID) { return (cxFont); }
inline USHORT DISPLAY :: QueryFontSizeY (VOID) { return (cyFont); }

inline VOID DISPLAY :: Reformat (VOID)
{
    Resize ();
    UpdateButtons ();
}

// ------------------------------------------------------------------------

inline VOID DISPLAY :: HideSuspendButton (VOID)
{
    fShowSuspendButton = FALSE;
    Reformat ();
}

inline VOID DISPLAY :: ShowSuspendButton (VOID)
{
    fShowSuspendButton = TRUE;
    Reformat ();
}

inline VOID DISPLAY :: HideResetButton (VOID)
{
    fShowResetButton = FALSE;
    Reformat ();
}

inline VOID DISPLAY :: ShowResetButton (VOID)
{
    fShowResetButton = TRUE;
    Reformat ();
}

inline VOID DISPLAY :: HideExitButton (VOID)
{
    fShowExitButton = FALSE;
    UpdateButtons ();
}

inline VOID DISPLAY :: ShowExitButton (VOID)
{
    fShowExitButton = TRUE;
    UpdateButtons ();
}

// ------------------------------------------------------------------------

inline VOID DISPLAY :: ShowItem (IID iid)
{
    QueryItem (iid)->Show ();
    Reformat ();
}

inline VOID DISPLAY :: HideItem (IID iid)
{
    QueryItem (iid)->Hide ();
    Reformat ();
}

inline BOOL DISPLAY :: IsShownItem (IID iid) {
    return (QueryItem (iid)->IsShown ()); }

// ************************************************************************
#endif
