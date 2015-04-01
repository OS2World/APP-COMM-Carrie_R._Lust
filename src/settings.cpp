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

#include "settings.h"

/* This includes the code for a "settings" class that I've written.
 I plan to someday create a library with all the stuff that I use often,
 and this library would of course be a better place for this. But until
 then I'll just choose this way though it's a bit ugly.
 */
#include "thth/thth_settings.cpp"

HWND SETTINGS :: hwndPage[3];

// ** VersionError ******************************************************** /*fold00*/

USHORT SETTINGS :: VersionError (VOID)
{
    DisplayError ("INI-FILE VERSION ERROR",
                  "The INI-file's (\"%s\") version does not match the current "
                  "version of Carrie. Defaults will be used.",
                  QueryProfileName ());
    return 0;
}

// ** FileNotOpenError **************************************************** /*fold00*/

USHORT SETTINGS :: FileNotOpenError (VOID)
{
    DisplayError ("INI-FILE OPENING ERROR",
                  "The INI-file (\"%s\") could not be opened! "
                  "Defaults will be used.",
                  QueryProfileName ());
    return 0;
}

// ** Settings ************************************************************ /*fold00*/

SWP swpDef;
USHORT ausDef[7];

COLOR colorBGDef = 0x00e0c080;

BOOL fShowItemsDef[MAX_ITEMS] =
{
    TRUE, TRUE, TRUE, TRUE, TRUE,    TRUE, TRUE, TRUE, TRUE, TRUE,
    TRUE,
#ifdef _TOTALVALUES_
    TRUE, TRUE, TRUE,
#endif
};

PTHTH_SE apse[] =
{
    new THTH_SEB (SEI_SHOWITEMS, "Show", "Items", &fShowItemsDef, sizeof (BOOL)*MAX_ITEMS),
    new THTH_SEF (SEI_SHOWEXITBUTTON, "Show", "ShowExitButton", TRUE),
    new THTH_SEF (SEI_SHOWSUSPENDBUTTON, "Show", "ShowSuspendButton", TRUE),
    new THTH_SEF (SEI_SHOWRESETBUTTON, "Show", "ShowResetButton", TRUE),

    new THTH_SEL (SEI_WARNTUNIT,   "Warn", "TypeUnit", WARNT_DONTWARN),
    new THTH_SEL (SEI_WARNTCHARGE, "Warn", "TypeCharge", WARNT_DONTWARN),
    new THTH_SEL (SEI_WARNTCOSTS,  "Warn", "TypeCosts", WARNT_DONTWARN),
    new THTH_SEL (SEI_WARNTLIMIT,  "Warn", "TypeLimit", WARNT_DONTWARN),
#ifdef _TOTALVALUES_
    new THTH_SEL (SEI_WARNTCOSTSTOTAL,  "Warn", "TypeTotalCosts", WARNT_DONTWARN),
    new THTH_SEL (SEI_WARNTLIMITTOTAL,  "Warn", "TypeTotalLimit", WARNT_DONTWARN),
#endif
    new THTH_SEF (SEI_WARNCOUNTDOWN, "Warn", "Countdown", TRUE),

    new THTH_SEL (SEI_LIMITTYPE,  "Limit", "Type", LIMITT_SECONDS),
    new THTH_SEL (SEI_LIMITVALUE, "Limit", "Value", 0),
    new THTH_SEL (SEI_LIMITCOSTS, "Limit", "Costs", 0),
#ifdef _TOTALVALUES_
    new THTH_SEL (SEI_LIMITTYPETOTAL,  "Limit", "TypeTotal", LIMITT_SECONDS),
    new THTH_SEL (SEI_LIMITVALUETOTAL, "Limit", "ValueTotal", 0),
    new THTH_SEL (SEI_LIMITCOSTSTOTAL, "Limit", "CostsTotal", 0),
#endif

    new THTH_SEB (SEI_BACKGROUNDCOLOR, "Window", "BackgroundColor", &colorBGDef, sizeof (colorBGDef)),
    new THTH_SES (SEI_FONTNAMESIZE, "Window", "FontNameSize", "8.Helv"),
    new THTH_SEF (SEI_WINDOWSHOWFRAME, "Window", "ShowFrame", TRUE),
    new THTH_SEB (SEI_SWP, "Window", "SWP", &swpDef, sizeof (swpDef)),
    new THTH_SEB (SEI_US, "Window", "US", &ausDef, sizeof (ausDef)),

    new THTH_SEF (SEI_LOGFILEUSE, "Logfile", "Use", TRUE),
    new THTH_SES (SEI_LOGFILENAME, "Logfile", "Name", "clust.log"),

    new THTH_SEF (SEI_SAVEFILEUSE, "Savefile", "Use", TRUE),
    new THTH_SES (SEI_SAVEFILENAME, "Savefile", "Name", "clust.sav"),

    NULL,
};

SETTINGS :: Settings (VOID)
: ththSettings (apse, PSZ_PROFILENAME, L_PROFILEVERSION)
{
    COUNTRYCODE cc = {0};
    ULONG       ul = 0;

    if (DosQueryCtryInfo (sizeof (ci), &cc, &ci, &ul) != 0)
        ; // FIXME
}

// ** ~Settings *********************************************************** /*fold00*/

SETTINGS :: ~Settings (VOID)
{
    this->ththSettings::~ththSettings ();
}

// ** DialogProcedure ***************************************************** /*fold00*/

MRESULT EXPENTRY SETTINGS ::
    DialogProcedure (HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
{
    switch (msg)
    {
    case WM_FORMATFRAME:
        {
            MRESULT   mresult = WinDefDlgProc (hwnd, msg, mp1, mp2);

            SWP   swp;
            WinQueryWindowPos (hwnd, &swp);

            SWP   swpNB;
            WinQueryWindowPos (WinWindowFromID (hwnd, WID_NB_SETTINGS), &swpNB);

            LONG   cyBorder = WinQuerySysValue (HWND_DESKTOP, SV_CYSIZEBORDER);
            LONG   cyTitle = WinQuerySysValue (HWND_DESKTOP, SV_CYTITLEBAR);

            swpNB.cx = swp.cx - swpNB.x*2;
            swpNB.cy = swp.cy - swpNB.y - cyBorder*2 - cyTitle;

            WinSetWindowPos (WinWindowFromID (hwnd, WID_NB_SETTINGS), 0, 0, 0,
                             swpNB.cx, swpNB.cy, SWP_SIZE);
            return (mresult);
        }

    case WM_CLOSE:
        pset->AdjustSettings ();
        break;
    }

    return WinDefDlgProc (hwnd, msg, mp1, mp2);
}

// ** Page1Procedure ****************************************************** /*fold00*/

MRESULT EXPENTRY SETTINGS ::
    Page1Procedure (HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
{
    static BOOL   f;

    switch (msg)
    {
    case WM_INITDLG:
        {
            PDISPLAY   pdisplay = pcrdntr->QueryDisplay (pset);
            
            f = FALSE;

            // init details listbox
            WinSendDlgItemMsg (hwnd, WID_LB_ITEMS, LM_DELETEALL, NULL,NULL);

            // insert text into listbox
            for (USHORT i = 0; i < MAX_ITEMS; i++)
            {
                WinSendDlgItemMsg (hwnd, WID_LB_ITEMS, LM_INSERTITEM,
                                   MPFROMLONG (i), pdisplay->
                                   QueryItem (IID (i))->QueryDescription ());
                if (pdisplay->IsShownItem (IID (i)))
                    WinSendDlgItemMsg (hwnd, WID_LB_ITEMS, LM_SELECTITEM,
                                       MPFROMLONG (i), MPFROM2SHORT (TRUE,0));
            }

            // set state of checkbuttons
            WinSendDlgItemMsg (hwnd, WID_CB_SHOWEXITBUTTON, BM_SETCHECK,
                               MPFROMLONG (pdisplay->IsShownExitButton ()),
                               MPFROMLONG (0));
            WinSendDlgItemMsg (hwnd, WID_CB_SHOWSUSPENDBUTTON, BM_SETCHECK,
                               MPFROMLONG (pdisplay->IsShownSuspendButton ()),
                               MPFROMLONG (0));
            WinSendDlgItemMsg (hwnd, WID_CB_SHOWRESETBUTTON, BM_SETCHECK,
                               MPFROMLONG (pdisplay->IsShownResetButton ()),
                               MPFROMLONG (0));
            f = TRUE;
        }
        break;

    case WM_CONTROL:
        {
            PDISPLAY   pdisplay = pcrdntr->QueryDisplay (pset);

            switch (SHORT1FROMMP (mp1))
            {
            case WID_CB_SHOWEXITBUTTON:
                if (pdisplay->IsShownExitButton ())
                    pdisplay->HideExitButton ();
                else
                    pdisplay->ShowExitButton ();
                break;

            case WID_CB_SHOWSUSPENDBUTTON:
                if (pdisplay->IsShownSuspendButton ())
                    pdisplay->HideSuspendButton ();
                else
                    pdisplay->ShowSuspendButton ();
                break;

            case WID_CB_SHOWZONELISTBOX:
                DosBeep (1000, 10);
                break;

            case WID_CB_SHOWRESETBUTTON:
                if (pdisplay->IsShownResetButton ())
                    pdisplay->HideResetButton ();
                else
                    pdisplay->ShowResetButton ();
                break;

            case WID_LB_ITEMS:
                switch (SHORT2FROMMP (mp1))
                {
                case LN_ENTER:
                    return (MRESULT)0;

                case LN_SELECT:
                    {
                        PDISPLAY   pdisplay = pcrdntr->QueryDisplay (pset);

                        if (! f)
                            return (MRESULT)0;

                        USHORT   i;

                        for (i = 0; i < MAX_ITEMS; i++)
                        {
                            if (WinLboxIsSelectedItem (WinWindowFromID
                                                       (hwnd, WID_LB_ITEMS), i))
                            {
                                if (! pdisplay->IsShownItem (IID (i)))
                                    pdisplay->ShowItem (IID (i));
                            }
                            else
                            {
                                if (pdisplay->IsShownItem (IID (i)))
                                    pdisplay->HideItem (IID (i));
                            }
                        }
                    }
                    return (MRESULT)0;
                }
            }
        }
        break;
    }

    return WinDefDlgProc (hwnd, msg, mp1, mp2);
}

// ** Page2Procedure ****************************************************** /*fold00*/

MRESULT EXPENTRY SETTINGS :: Page2Procedure (HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
{
    switch (msg)
    {
    case WM_INITDLG:
        {
            PWARNER   pwarner = pcrdntr->QueryWarner (pset);

            // init listboxes
            WinSendDlgItemMsg (hwnd, WID_LB_WARNTUNIT, LM_DELETEALL, NULL,NULL);
            WinSendDlgItemMsg (hwnd, WID_LB_WARNTCHARGE, LM_DELETEALL, NULL,NULL);
            WinSendDlgItemMsg (hwnd, WID_LB_WARNTCOSTS, LM_DELETEALL, NULL,NULL);
            WinSendDlgItemMsg (hwnd, WID_LB_WARNTLIMIT, LM_DELETEALL, NULL,NULL);

#ifdef _TOTALVALUES_
            WinSendDlgItemMsg (hwnd, WID_LB_WARNTCOSTSTOTAL, LM_DELETEALL, NULL,NULL);
            WinSendDlgItemMsg (hwnd, WID_LB_WARNTLIMITTOTAL, LM_DELETEALL, NULL,NULL);
#endif
            // insert text into listbox
            for (USHORT i = 0; i < MAX_WARNT; i++)
            {
                WinSendDlgItemMsg (hwnd, WID_LB_WARNTUNIT, LM_INSERTITEM,
                                   MPFROMLONG (i),
                                   pwarner->QueryWarnDescription (WARN_T (i)));
                WinSendDlgItemMsg (hwnd, WID_LB_WARNTCHARGE, LM_INSERTITEM,
                                   MPFROMLONG (i),
                                   pwarner->QueryWarnDescription (WARN_T (i)));
                WinSendDlgItemMsg (hwnd, WID_LB_WARNTCOSTS, LM_INSERTITEM,
                                   MPFROMLONG (i),
                                   pwarner->QueryWarnDescription (WARN_T (i)));
                WinSendDlgItemMsg (hwnd, WID_LB_WARNTLIMIT, LM_INSERTITEM,
                                   MPFROMLONG (i),
                                   pwarner->QueryWarnDescription (WARN_T (i)));
#ifdef _TOTALVALUES_
                WinSendDlgItemMsg (hwnd, WID_LB_WARNTCOSTSTOTAL, LM_INSERTITEM,
                                   MPFROMLONG (i),
                                   pwarner->QueryWarnDescription (WARN_T (i)));
                WinSendDlgItemMsg (hwnd, WID_LB_WARNTLIMITTOTAL, LM_INSERTITEM,
                                   MPFROMLONG (i),
                                   pwarner->QueryWarnDescription (WARN_T (i)));
#endif
            }

            WinSendDlgItemMsg (hwnd, WID_LB_WARNTUNIT, LM_SELECTITEM,
                               MPFROMLONG (pset->QueryWarntUnit ()),
                               MPFROMLONG (TRUE));
            WinSendDlgItemMsg (hwnd, WID_LB_WARNTUNIT, CBM_SHOWLIST,
                               FALSE, 0);
            WinSendDlgItemMsg (hwnd, WID_LB_WARNTCHARGE, LM_SELECTITEM,
                               MPFROMLONG (pset->QueryWarntCharge ()),
                               MPFROMLONG (TRUE));
            WinSendDlgItemMsg (hwnd, WID_LB_WARNTCHARGE, CBM_SHOWLIST,
                               FALSE, 0);
            WinSendDlgItemMsg (hwnd, WID_LB_WARNTCOSTS, LM_SELECTITEM,
                               MPFROMLONG (pset->QueryWarntCosts ()),
                               MPFROMLONG (TRUE));
            WinSendDlgItemMsg (hwnd, WID_LB_WARNTCOSTS, CBM_SHOWLIST,
                               FALSE, 0);
            WinSendDlgItemMsg (hwnd, WID_LB_WARNTLIMIT, LM_SELECTITEM,
                               MPFROMLONG (pset->QueryWarntLimit ()),
                               MPFROMLONG (TRUE));
            WinSendDlgItemMsg (hwnd, WID_LB_WARNTLIMIT, CBM_SHOWLIST,
                               FALSE, 0);
#ifdef _TOTALVALUES_
            WinSendDlgItemMsg (hwnd, WID_LB_WARNTCOSTSTOTAL, LM_SELECTITEM,
                               MPFROMLONG (pset->QueryLong (SEI_WARNTCOSTSTOTAL)),
                               MPFROMLONG (TRUE));
            WinSendDlgItemMsg (hwnd, WID_LB_WARNTCOSTSTOTAL, CBM_SHOWLIST,
                               FALSE, 0);
            WinSendDlgItemMsg (hwnd, WID_LB_WARNTLIMITTOTAL, LM_SELECTITEM,
                               MPFROMLONG (pset->QueryLong (SEI_WARNTLIMITTOTAL)),
                               MPFROMLONG (TRUE));
            WinSendDlgItemMsg (hwnd, WID_LB_WARNTLIMITTOTAL, CBM_SHOWLIST,
                               FALSE, 0);
#endif
            // init limit type cb
            WinSendDlgItemMsg (hwnd, WID_CB_LIMITTYPE, LM_INSERTITEM,
                               MPFROMLONG (LONG (LIMITT_SECONDS)),
                               PSZ ("seconds"));
            WinSendDlgItemMsg (hwnd, WID_CB_LIMITTYPE, LM_INSERTITEM,
                               MPFROMLONG (LONG (LIMITT_MINUTES)),
                               PSZ ("minutes"));
            WinSendDlgItemMsg (hwnd, WID_CB_LIMITTYPE, LM_INSERTITEM,
                               MPFROMLONG (LONG (LIMITT_HOURS)),
                               PSZ ("hours"));
            WinSendDlgItemMsg (hwnd, WID_CB_LIMITTYPE, LM_INSERTITEM,
                               MPFROMLONG (LONG (LIMITT_UNITS)),
                               PSZ ("units"));

            WinSendDlgItemMsg (hwnd, WID_CB_LIMITTYPE, LM_SELECTITEM,
                               MPFROMLONG (pset->QueryLimitType ()),
                               MPFROMLONG (TRUE));
            WinSendDlgItemMsg (hwnd, WID_CB_LIMITTYPE, CBM_SHOWLIST,
                               FALSE, 0);

            // init limit count sb
            WinSendDlgItemMsg (hwnd, WID_SB_LIMIT, SPBM_SETLIMITS,
                               MPFROMLONG (65536), MPFROMLONG (1));
            WinSendDlgItemMsg (hwnd, WID_SB_LIMIT, SPBM_SETCURRENTVALUE,
                               MPFROMLONG (pset->QueryLimit ()), 0);

            // init costs count sb
            WinSendDlgItemMsg (hwnd, WID_SB_COSTS, SPBM_SETLIMITS,
                               MPFROMLONG (65536), MPFROMLONG (1));
            WinSendDlgItemMsg (hwnd, WID_SB_COSTS, SPBM_SETCURRENTVALUE,
                               MPFROMLONG (pset->QueryCostsLimit ()), 0);

#ifdef _TOTALVALUES_
            // init limit type cb
            WinSendDlgItemMsg (hwnd, WID_CB_LIMITTYPETOTAL, LM_INSERTITEM,
                               MPFROMLONG (LONG (LIMITT_SECONDS)),
                               PSZ ("seconds"));
            WinSendDlgItemMsg (hwnd, WID_CB_LIMITTYPETOTAL, LM_INSERTITEM,
                               MPFROMLONG (LONG (LIMITT_MINUTES)),
                               PSZ ("minutes"));
            WinSendDlgItemMsg (hwnd, WID_CB_LIMITTYPETOTAL, LM_INSERTITEM,
                               MPFROMLONG (LONG (LIMITT_HOURS)),
                               PSZ ("hours"));
            WinSendDlgItemMsg (hwnd, WID_CB_LIMITTYPETOTAL, LM_INSERTITEM,
                               MPFROMLONG (LONG (LIMITT_UNITS)),
                               PSZ ("units"));

            WinSendDlgItemMsg (hwnd, WID_CB_LIMITTYPETOTAL, LM_SELECTITEM,
                               MPFROMLONG (pset->QueryLong (SEI_LIMITTYPETOTAL)),
                               MPFROMLONG (TRUE));
            WinSendDlgItemMsg (hwnd, WID_CB_LIMITTYPETOTAL, CBM_SHOWLIST,
                               FALSE, 0);

            // init limit count sb
            WinSendDlgItemMsg (hwnd, WID_SB_LIMITTOTAL, SPBM_SETLIMITS,
                               MPFROMLONG (65536), MPFROMLONG (1));
            WinSendDlgItemMsg (hwnd, WID_SB_LIMITTOTAL, SPBM_SETCURRENTVALUE,
                               MPFROMLONG (pset->QueryLong (SEI_LIMITVALUETOTAL)), 0);

            // init costs count sb
            WinSendDlgItemMsg (hwnd, WID_SB_COSTSTOTAL, SPBM_SETLIMITS,
                               MPFROMLONG (65536), MPFROMLONG (1));
            WinSendDlgItemMsg (hwnd, WID_SB_COSTSTOTAL, SPBM_SETCURRENTVALUE,
                               MPFROMLONG (pset->QueryLong (SEI_LIMITCOSTSTOTAL)), 0);
#endif
            // set state of checkbutton
            WinSendDlgItemMsg (hwnd, WID_CB_UNITCOUNTDOWN, BM_SETCHECK,
                               MPFROMLONG (pset->DoUnitCountdown ()),
                               MPFROMLONG (0));
        }
        return MRESULT (0);

    case WM_COMMAND:
        return 0;
    }

    return WinDefDlgProc (hwnd, msg, mp1, mp2);
}

// ** Page3Procedure ****************************************************** /*fold00*/

MRESULT EXPENTRY SETTINGS :: Page3Procedure (HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
{
    switch (msg)
    {
    case WM_INITDLG:
        // set state of checkbuttons
        WinSendDlgItemMsg (hwnd, WID_CB_USELOGFILE, BM_SETCHECK,
                           MPFROMLONG (pset->UseLogfile ()),
                           MPFROMLONG (0));

        WinSendDlgItemMsg (hwnd, WID_E_LOGFILENAME, EM_SETTEXTLIMIT,
                           MPARAM (_MAX_PATH-1), (MPARAM)0);
        WinSetDlgItemText (hwnd, WID_E_LOGFILENAME, pset->QueryLogfileName ());
        WinSendDlgItemMsg (hwnd, WID_E_LOGFILENAME, EM_SETSEL,
                           MPFROM2SHORT (0, _MAX_PATH), (MPARAM)0);

        WinSendDlgItemMsg (hwnd, WID_CB_USESAVEFILE, BM_SETCHECK,
                           MPFROMLONG (pset->QueryFlag (SEI_SAVEFILEUSE)),
                           MPFROMLONG (0));

        WinSendDlgItemMsg (hwnd, WID_E_SAVEFILENAME, EM_SETTEXTLIMIT,
                           MPARAM (_MAX_PATH-1), (MPARAM)0);
        WinSetDlgItemText (hwnd, WID_E_SAVEFILENAME,
                           pset->QueryString (SEI_SAVEFILENAME));
        WinSendDlgItemMsg (hwnd, WID_E_SAVEFILENAME, EM_SETSEL,
                           MPFROM2SHORT (0, _MAX_PATH), (MPARAM)0);
        // set state of checkbuttons
/*        WinSendDlgItemMsg (hwnd, WID_CB_SHOWEXITBUTTON, BM_SETCHECK,
                           MPFROMLONG (FALSE),  // FIXME
                           MPFROMLONG (0));*/
        return 0;

    case WM_COMMAND:
        return 0;
    }

    return WinDefDlgProc (hwnd, msg, mp1, mp2);
}
// ** Dialog ************************************************************** /*fold00*/

BOOL SETTINGS :: Dialog (VOID)
{
    static PSZ   pszPageStatus[3] = { "Page 1", "Page 2", "Page 3" };
    static PSZ   pszPageTab[3] = { "Details", "Warn", "Logfile" };

    HWND   hwnd =
        WinLoadDlg (HWND_DESKTOP, pcrdntr->QueryDisplay (this)->QueryHWNDClient (),
                    PFNWP (DialogProcedure), NULLHANDLE, ID_DLG_SETTINGS,
                    this);

    HWND   hwndNB = WinWindowFromID (hwnd, WID_NB_SETTINGS);

    // set notebook background color
    WinSendMsg (hwndNB, BKM_SETNOTEBOOKCOLORS,
                MPFROMLONG (SYSCLR_FIELDBACKGROUND),
                MPFROMSHORT (BKA_BACKGROUNDPAGECOLORINDEX));

    // set tab dimensions
    WinSendMsg (hwndNB, BKM_SETDIMENSIONS,
                MPFROM2SHORT (65, 25), MPFROMSHORT (BKA_MAJORTAB));

    ULONG   idPage[3];
    USHORT  i;
    
    // insert 3 empty pages
    for (i = 0; i < 3; i++)
    {
        idPage[i] = (ULONG)
            WinSendMsg (hwndNB, BKM_INSERTPAGE, 0L,
                        MPFROM2SHORT (BKA_MAJOR | BKA_AUTOPAGESIZE, BKA_LAST));
        WinSendMsg (hwndNB, BKM_SETSTATUSLINETEXT, MPFROMLONG (idPage[i]),
                    MPFROMP (pszPageStatus[i]));
        WinSendMsg (hwndNB, BKM_SETTABTEXT,
                    MPFROMLONG (idPage[i]), MPFROMP (pszPageTab[i]));
    }

    // open and assign dialogs to pages
    hwndPage[0] = WinLoadDlg (hwndNB, hwndNB, (PFNWP) Page1Procedure,
                              NULLHANDLE, ID_DLG_SETTINGSPAGE1, this);
    hwndPage[1] = WinLoadDlg (hwndNB, hwndNB, (PFNWP) Page2Procedure,
                              NULLHANDLE, ID_DLG_SETTINGSPAGE2, this);
    hwndPage[2] = WinLoadDlg (hwndNB, hwndNB, (PFNWP) Page3Procedure,
                              NULLHANDLE, ID_DLG_SETTINGSPAGE3, this);

    // combine dlg-handle and page ids
    for (i = 0; i < 3; i++)
        WinSendMsg (hwndNB, BKM_SETPAGEWINDOWHWND,
                    MPFROMLONG (idPage[i]), MPFROMHWND (hwndPage[i]));

    WinProcessDlg (hwnd);
    WinDestroyWindow (hwnd);

    for (i = 0; i < 3; i++)
        hwndPage[i] = NULL;
    
    return (TRUE);  // FIXME
}

// ** AdjustSettings ****************************************************** /*fold00*/

VOID SETTINGS :: AdjustSettings (VOID)
{
    HWND   hwnd;

    if (! hwndPage[0])
        return;

    //  get settings from page 1
    hwnd = hwndPage[0];
    for (USHORT i = 0; i < MAX_ITEMS; i++)
        if (WinLboxIsSelectedItem (WinWindowFromID (hwnd, WID_LB_ITEMS), i))
            ShowItem (IID (i), TRUE);
        else
            ShowItem (IID (i), FALSE);

    ShowExitButton (BOOL (WinSendDlgItemMsg (hwnd, WID_CB_SHOWEXITBUTTON,
                                             BM_QUERYCHECK, 0, 0)));
    ShowSuspendButton (BOOL (WinSendDlgItemMsg (hwnd, WID_CB_SHOWSUSPENDBUTTON,
                                                BM_QUERYCHECK, 0, 0)));
    ShowResetButton (BOOL (WinSendDlgItemMsg (hwnd, WID_CB_SHOWRESETBUTTON,
                                              BM_QUERYCHECK, 0, 0)));

    // get settings from page 2
    hwnd = hwndPage[1];
    SetWarntUnit (WARN_T (WinSendDlgItemMsg (hwnd, WID_LB_WARNTUNIT,
                                             LM_QUERYSELECTION,
                                             MPFROMLONG (LIT_FIRST),
                                             MPARAM (NULL))));
    SetWarntCharge (WARN_T (WinSendDlgItemMsg (hwnd, WID_LB_WARNTCHARGE,
                                               LM_QUERYSELECTION,
                                               MPFROMLONG (LIT_FIRST),
                                               MPARAM (NULL))));
    SetWarntCosts (WARN_T (WinSendDlgItemMsg (hwnd, WID_LB_WARNTCOSTS,
                                              LM_QUERYSELECTION,
                                              MPFROMLONG (LIT_FIRST),
                                              MPARAM (NULL))));
    SetWarntLimit (WARN_T (WinSendDlgItemMsg (hwnd, WID_LB_WARNTLIMIT,
                                              LM_QUERYSELECTION,
                                              MPFROMLONG (LIT_FIRST),
                                              MPARAM (NULL))));
#ifdef _TOTALVALUES_
    SetLong (SEI_WARNTCOSTSTOTAL,
             WARN_T (WinSendDlgItemMsg (hwnd, WID_LB_WARNTCOSTSTOTAL,
                                        LM_QUERYSELECTION,
                                        MPFROMLONG (LIT_FIRST),
                                        MPARAM (NULL))));
    SetLong (SEI_WARNTLIMITTOTAL,
             WARN_T (WinSendDlgItemMsg (hwnd, WID_LB_WARNTLIMITTOTAL,
                                        LM_QUERYSELECTION,
                                        MPFROMLONG (LIT_FIRST),
                                        MPARAM (NULL))));
#endif
    ULONG   ul;

    // costs value
    if (! BOOL (WinSendDlgItemMsg (hwnd, WID_SB_COSTS, SPBM_QUERYVALUE,
                                   MPFROMP (&ul), MPFROM2SHORT (0, 0))))
        ul = 1L;
    SetCostsLimit (ul);

//    pcrdntr->QueryConnection (this)->SetLimit (ul);

    // user limit type
    LIMIT_T   limitt = LIMIT_T (WinSendDlgItemMsg (hwnd, WID_CB_LIMITTYPE,
                                                   LM_QUERYSELECTION,
                                                   MPFROMLONG (LIT_FIRST),
                                                   MPARAM (NULL)));
    SetLimitType (limitt);
    pcrdntr->QueryConnection (this)->SetLimitType (limitt);

    // user limit value
    if (! BOOL (WinSendDlgItemMsg (hwnd, WID_SB_LIMIT, SPBM_QUERYVALUE,
                                   MPFROMP (&ul), MPFROM2SHORT (0, 0))))
        ul = 1L;
    SetLimit (ul);

    pcrdntr->QueryConnection (this)->SetLimit (QueryLimit ());

#ifdef _TOTALVALUES_
    // costs value
    if (! BOOL (WinSendDlgItemMsg (hwnd, WID_SB_COSTSTOTAL, SPBM_QUERYVALUE,
                                   MPFROMP (&ul), MPFROM2SHORT (0, 0))))
        ul = 1L;
    SetLong (SEI_LIMITCOSTSTOTAL, ul);

//    cLimitTotal = pset->QueryLong (SEI_LIMITVALUETOTAL);

//    pcrdntr->QueryConnection (this)->SetLimitTotal (ul);

    // user limit type
    limitt = LIMIT_T (WinSendDlgItemMsg (hwnd, WID_CB_LIMITTYPETOTAL,
                                         LM_QUERYSELECTION,
                                         MPFROMLONG (LIT_FIRST),
                                         MPARAM (NULL)));
    SetLong (SEI_LIMITTYPETOTAL, limitt);
    pcrdntr->QueryConnection (this)->SetLimitTypeTotal (limitt);

    // user limit value
    if (! BOOL (WinSendDlgItemMsg (hwnd, WID_SB_LIMITTOTAL, SPBM_QUERYVALUE,
                                   MPFROMP (&ul), MPFROM2SHORT (0, 0))))
        ul = 1L;
    SetLong (SEI_LIMITVALUETOTAL, ul);

    pcrdntr->QueryConnection (this)->
        SetLimitTotal (QueryLong (SEI_LIMITVALUETOTAL));
#endif

    DoUnitCountdown (BOOL (WinSendDlgItemMsg (hwnd, WID_CB_UNITCOUNTDOWN,
                                              BM_QUERYCHECK, 0, 0)));

    //  get settings from page 3
    hwnd = hwndPage[2];
    UseLogfile (BOOL (WinSendDlgItemMsg (hwnd, WID_CB_USELOGFILE,
                                         BM_QUERYCHECK, 0, 0)));
    SetFlag (SEI_SAVEFILEUSE, BOOL
             (WinSendDlgItemMsg (hwnd, WID_CB_USESAVEFILE,
                                 BM_QUERYCHECK, 0, 0)));
    CHAR   psz[_MAX_PATH];

    WinQueryDlgItemText (hwnd, WID_E_LOGFILENAME, _MAX_PATH, psz);
    SetLogfileName (psz);
    WinQueryDlgItemText (hwnd, WID_E_SAVEFILENAME, _MAX_PATH, psz);
    SetString (SEI_SAVEFILENAME, psz);
}

// ** QueryWindowData ***************************************************** /*fold00*/

VOID SETTINGS :: QueryWindowData (SWP *pswp, USHORT us[7])
{
    memcpy (pswp, QueryBinary (SEI_SWP), sizeof (*pswp));

    LONG  cx, cy;
    cx = WinQuerySysValue (HWND_DESKTOP, SV_CXSCREEN);
    cy = WinQuerySysValue (HWND_DESKTOP, SV_CYSCREEN);

    // partly outside of screen?
    if (pswp->x+pswp->cx >= cx)
        pswp->x = cx-pswp->cx;
    // partly outside of screen?
    if (pswp->y+pswp->cy >= cy)
        pswp->y = cy-pswp->cy;

    // partly outside of screen?
    if (pswp->x < 0)
        pswp->x = 0;
    // partly outside of screen?
    if (pswp->y < 0)
        pswp->y = 0;

    memcpy (us, QueryBinary (SEI_US), sizeof (us[0])*7);
}

// ************************************************************************
