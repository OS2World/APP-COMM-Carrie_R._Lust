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

#include "display.h"

BOOL DISPLAY :: fClassRegistered = FALSE;

// ** WindowProcedure ***************************************************** /*fold00*/

MRESULT EXPENTRY DISPLAY ::
    WindowProcedure (HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
{
    // get pointer to display object assoc. with this window (hwnd)
    PDISPLAY   pdisplay = (PDISPLAY)WinQueryWindowPtr (hwnd, 0);

    switch (msg)
    {
    case WM_PAINT:           pdisplay->Repaint ();         return (MRESULT)0;
    case WM_BUTTON1DBLCLK:   pdisplay->ToggleFrame ();     return (MRESULT)0;
    case WM_BEGINSELECT:
    case WM_BEGINDRAG:       pdisplay->Drag ();            return (MRESULT)0;

    case WM_COMMAND:
        switch (SHORT1FROMMP (mp1))
        {
        case WID_PB_EXIT:
            WinSendMsg (hwnd, WM_CLOSE, 0, 0);
            break;

        case WID_PB_SUSPEND:
            {
                HWND   hwndButton = WinWindowFromID (hwnd, WID_PB_SUSPEND);

                if (pdisplay->QueryConnection ()->IsSuspended ())
                {
                    WinSetWindowText (hwndButton, PSZ_PAUSE);
                    pdisplay->QueryConnection ()->Continue ();
                }
                else
                {
                    WinSetWindowText (hwndButton, PSZ_CONTINUE);
                    pdisplay->QueryConnection ()->Suspend ();
                }
            }
            break;

        case WID_PB_RESET:
            pcrdntr->Log (pdisplay->QueryConnection ());
            pdisplay->QueryConnection ()->Reset ();
            pdisplay->UpdateSecond ();  // FIXME
            break;

        case WID_PB_ABOUT:
            AboutBox (hwnd);
            break;

        case WID_PB_SETTINGS:
            pdisplay->Settings ();
            break;
        }
        return (MRESULT (0));

    case WM_CLOSE:
        if (pdisplay->QueryConnection ()->WasReset ())
            pcrdntr->Log (pdisplay->QueryConnection ());
        break;

    case WM_PRESPARAMCHANGED:
        switch (LONGFROMMP (mp1))
        {
        case PP_FONTNAMESIZE:
            {
                ULONG   ppid;
                CHAR    psz[LEN_FONTNAMESIZE];
                
                if (WinQueryPresParam (hwnd, PP_FONTNAMESIZE, 0, &ppid,
                                       sizeof (psz), &psz, 0))
                    pset->SetFontNameSize (PSZ (psz));
                pdisplay->Reformat ();
            }
            break;

        case PP_BACKGROUNDCOLOR:
            {
                ULONG   ppid;
                COLOR   color;

                if (WinQueryPresParam (hwnd, PP_BACKGROUNDCOLOR, 0, &ppid,
                                       sizeof (color), &color, 0))
                    pset->SetBackgroundColor (color);
            }
            break;
        }
        WinInvalidateRect (hwnd, NULL, TRUE);
        break;

    case WM_CONTEXTMENU:
        {
/*            WinSetPresParam (pdisplay->hwndMenu, PP_FONTNAMESIZE,
                             Data->IniData.fFontNameSize ? strlen(Data->IniData.FontNameSize)+1 : 0,
                             Data->IniData.fFontNameSize ? PSZ(Data->IniData.FontNameSize) : PSZ("") ) ; */

            WinPopupMenu (hwnd, hwnd, pdisplay->hwndMenu, 150,150, WID_PB_SUSPEND,
                          PU_HCONSTRAIN | PU_VCONSTRAIN | PU_POSITIONONITEM |
                          PU_KEYBOARD | PU_MOUSEBUTTON1);
        }
        return MRESULT (0);

    case HM_QUERY_KEYS_HELP:
        return MRESULT (FALSE);
    }

    return WinDefWindowProc (hwnd, msg, mp1, mp2);
}

// ** Settings ************************************************************ /*fold00*/

VOID DISPLAY :: Settings (VOID)
{
    pset->Dialog ();
}

// ** Display ************************************************************* /*fold00*/

DISPLAY :: Display (BOOL fUseHelp)
{
    /* Register our window class. */
    if (! fClassRegistered)
    {
        WinRegisterClass (GETHAB, PSZ_WINNAME, WindowProcedure, 0L, 4L);
        fClassRegistered = TRUE;
    }

    /* Our window has a lot of frame flags set. */
    ULONG flFrameFlags = (FCF_TITLEBAR      | FCF_SYSMENU |
                          FCF_BORDER        | FCF_MINBUTTON  |
                          FCF_SHELLPOSITION | FCF_ICON    |
                          FCF_TASKLIST      | FCF_NOBYTEALIGN |
                          FCF_ACCELTABLE);

    FRAMECDATA   fcd;
    memset (&fcd, 0, sizeof (fcd));
    fcd.cb = sizeof (fcd);
    fcd.flCreateFlags = flFrameFlags;
    fcd.idResources = ID_CLUST;

    // create frame window
    hwndFrame = WinCreateWindow (HWND_DESKTOP, WC_FRAME, "Carrie R. Lust", 0,
                                 0,0,0,0, HWND_DESKTOP, HWND_TOP, ID_CLUST,
                                 &fcd, NULL);

    COLOR   color = pset->QueryBackgroundColor ();
    PBYTE   pb;
    ULONG   ul = sizeof (ULONG);

    ul += sizeof (ULONG)*2L+sizeof (COLOR);
    ul += sizeof (ULONG)*2L+strlen (pset->QueryFontNameSize ())+1;

    PPRESPARAMS   ppp = (PPRESPARAMS) malloc (ul);

    ppp->cb = ul - sizeof (ppp->cb);

    PPARAM   param = ppp->aparam;

    param->id = PP_BACKGROUNDCOLOR;
    param->cb = sizeof (COLOR);

    memcpy (param->ab, &color, sizeof (color));
    
    pb = PBYTE (param);
    pb += sizeof (param->id) + sizeof (param->cb) + sizeof (COLOR);
    param = PPARAM (pb);

    param->id = PP_FONTNAMESIZE;
    param->cb = strlen (pset->QueryFontNameSize ())+1;

    memcpy (param->ab, pset->QueryFontNameSize (),
            strlen (pset->QueryFontNameSize ())+1);

    // create client window
    hwndClient = WinCreateWindow (hwndFrame, PSZ_WINNAME, "", 0, 0,0,0,0,
                                  hwndFrame, HWND_BOTTOM, FID_CLIENT, NULL,
                                  ppp);
    WinSetWindowPtr (hwndClient, 0, this);

    // We have to save this stuff for HideFrame ()
    hwndSysMenu = WinWindowFromID (hwndFrame, FID_SYSMENU);
    hwndTitleBar = WinWindowFromID (hwndFrame, FID_TITLEBAR);
    hwndMinMax = WinWindowFromID (hwndFrame, FID_MINMAX);

    fFrameHidden = FALSE;
    fRefreshEnabled = TRUE;

    fShowExitButton = pset->ShowExitButton ();
    fShowSuspendButton = pset->ShowSuspendButton ();
    fShowResetButton = pset->ShowResetButton ();

    hwndExitButton = hwndSuspendButton = hwndResetButton = NULLHANDLE;

    // create all items
    apitem[IID_DURATION]         = new ItemDuration (this);
    apitem[IID_UNITS]            = new ItemUnits (this);
    apitem[IID_MONEY]            = new ItemMoney (this);
    apitem[IID_UNIT_LEFT]        = new ItemUnitLeft (this);
    apitem[IID_UNIT_LENGTH]      = new ItemUnitLength (this);
    apitem[IID_LIMIT_LEFT]       = new ItemLimitLeft (this);
    apitem[IID_MONEY_PER_UNIT]   = new ItemMoneyPerUnit (this);
    apitem[IID_MONEY_PER_MINUTE] = new ItemMoneyPerMinute (this);
    apitem[IID_MONEY_PER_HOUR]   = new ItemMoneyPerHour (this);
    apitem[IID_SECS_TILL_CHARGE] = new ItemSecsTillCharge (this);
    apitem[IID_TOTAL_CON_TIME]   = new ItemTotalConTime (this);
#ifdef _TOTALVALUES_
    apitem[IID_TOTALUNITS]       = new ItemTotalUnits (this);
    apitem[IID_TOTALMONEY]       = new ItemTotalMoney (this);
    apitem[IID_TOTALLIMIT_LEFT]  = new ItemTotalLimitLeft (this);
#endif

    for (USHORT i = 0; i < MAX_ITEMS; i++)
        if (pset->ShowItem (IID (i)))
            ShowItem (IID (i));
        else
            HideItem (IID (i));

    SWP      swp;
    USHORT   us[7];

    pset->QueryWindowData (&swp, us);

    /* size, activate & show window */
    WinSetWindowPos (hwndFrame, HWND_DESKTOP, swp.x,swp.y, swp.cx,swp.cy,
                     SWP_SHOW | SWP_SIZE | SWP_MOVE);
    WinSetWindowUShort (hwndFrame, QWS_XRESTORE, us[0]);
    WinSetWindowUShort (hwndFrame, QWS_YRESTORE, us[1]);
    WinSetWindowUShort (hwndFrame, QWS_CXRESTORE, us[2]);
    WinSetWindowUShort (hwndFrame, QWS_CYRESTORE, us[3]);
    WinSetWindowUShort (hwndFrame, QWS_XMINIMIZE, us[4]);
    WinSetWindowUShort (hwndFrame, QWS_YMINIMIZE, us[5]);

    if (! pset->ShowFrame ())
        HideFrame ();

    // attach the menu
    hwndMenu = WinLoadMenu (HWND_DESKTOP, NULLHANDLE, IDM_POPUP);

    // init online help
    if (fUseHelp)
        phelp = new HELPER (hwndFrame);
    else
        phelp = NULL;

    // start the pipe handling thread
    _beginthread (HandlePipe, NULL, 1024L*32L, NULL);

    if (g_usComport)
    {
        // start the autodetect thread
        _beginthread (AutodetectConnection, NULL, 1024L*32L, NULL);
    }

    WinSetWindowPos (hwndFrame, NULLHANDLE, 0,0, 0,0, SWP_ACTIVATE);
    Reformat ();
}

// ** HandlePipe ********************************************************** /*fold00*/

VOID DISPLAY :: HandlePipe (PVOID)
{
    // FIXME I guess this whole function should be redesigned ...
    HMQ hmq = WinCreateMsgQueue (GETHAB, 0);

    APIRET       rc;
    static CHAR  ach[256];
    ULONG        ul;
    HPIPE        hpipe;
    BOOL         f = FALSE;

    // init our named pipe for remote control
    if ((rc = DosCreateNPipe (PSZ_RCPIPENAME, &hpipe,
                              NP_NOWRITEBEHIND | NP_NOINHERIT | NP_ACCESS_INBOUND,
                              NP_WAIT | NP_TYPE_MESSAGE | NP_READMODE_MESSAGE |
                              1, 32L, 2048L, 10000L)))
    {
        DisplayError ("ERROR", "Could not create pipe (rc=%d); Probably another "
                      "instance of me is already running. Exiting ...", rc);
        exit(1);
    }

    do
    {
        if ((rc = DosConnectNPipe (hpipe))) {
            if (! f) {
                DisplayError ("ERROR", "Could not connect to pipe (rc=%d) "
                              "(but will keep trying ...)", rc);
                f = TRUE;
            }
        }

        if (DosRead (hpipe, ach, sizeof (ach), &ul) == 0)
        {
            // FIXME yukk, puke, spit! Get connection a different way!
            if (strnicmp (ach, "start", strlen  ("start")) == 0)
                pcrdntr->pconnect->Continue ();
            else if (strnicmp (ach, "stop", strlen  ("stop")) == 0)
                pcrdntr->pconnect->Suspend ();
            else if (strnicmp (ach, "reset", strlen  ("reset")) == 0)
                pcrdntr->pconnect->Reset ();
            else if (strnicmp (ach, "exit", strlen  ("exit")) == 0)
                WinSendMsg (pcrdntr->pdisplay->QueryHWNDFrame (),
                            WM_CLOSE, 0,0);  // FIXME
            else if (strnicmp (ach, "show", strlen  ("show")) == 0)
                pcrdntr->pdisplay->Show ();
            else if (strnicmp (ach, "hide", strlen  ("hide")) == 0)
                pcrdntr->pdisplay->Hide ();
        }

        DosDisConnectNPipe (hpipe);
        if (f) { sleep(1); }
    }
    while (19);  // FIXME we should end the thread someday, shouldn't we?

    WinDestroyMsgQueue (hmq);
}

// ** ~Display ************************************************************ /*fold00*/

DISPLAY :: ~Display (VOID)
{
    SWP      swp;
    USHORT   us[7];

    WinQueryWindowPos (QueryHWNDFrame (), &swp);
    us[0] = WinQueryWindowUShort (QueryHWNDFrame (), QWS_XRESTORE);
    us[1] = WinQueryWindowUShort (QueryHWNDFrame (), QWS_YRESTORE);
    us[2] = WinQueryWindowUShort (QueryHWNDFrame (), QWS_CXRESTORE);
    us[3] = WinQueryWindowUShort (QueryHWNDFrame (), QWS_CYRESTORE);
    us[4] = WinQueryWindowUShort (QueryHWNDFrame (), QWS_XMINIMIZE);
    us[5] = WinQueryWindowUShort (QueryHWNDFrame (), QWS_YMINIMIZE);

    pset->SetWindowData (&swp, us);

    if (FrameHidden ())
        pset->ShowFrame (FALSE);
    else
        pset->ShowFrame (TRUE);

    if (phelp)
        delete phelp;

    WinDestroyWindow (hwndFrame);
}

// ** Repaint ************************************************************* /*fold00*/

VOID DISPLAY :: Repaint (VOID)
{
    RECTL   rcl;
    SHORT   i;
    HWND    hwnd = QueryHWNDClient ();
    HPS     hps = WinBeginPaint (hwnd, NULLHANDLE, NULL);

    GpiCreateLogColorTable (hps, LCOL_RESET, LCOLF_RGB, 0, 0, 0);

    WinQueryWindowRect (hwnd, &rcl);
    GpiMove (hps, (PPOINTL) &rcl.xLeft);
/*    GpiSetColor (hps, pset->QueryBackgroundColor ());
    GpiBox (hps, DRO_FILL, (PPOINTL)&rcl.xRight, 0, 0); */

    GpiSetColor (hps, CLR_BLACK);

    rcl.xLeft = 0;
    rcl.xRight = DISPLAY_XS-2;
    rcl.yBottom = rcl.yTop - QueryFontSizeY () + 1;

    for (i = 0; i < MAX_ITEMS; i++)
        if (apitem[i]->IsShown ())
        {
            if (apitem[i]->HasChanged ())
                apitem[i]->Repaint (hps, &rcl);
            rcl.yTop -= QueryFontSizeY ();
            rcl.yBottom = rcl.yTop - QueryFontSizeY () + 1;
        }

    WinEndPaint (hps);
}

// ** HideFrame *********************************************************** /*fold00*/

VOID DISPLAY :: HideFrame (BOOL fHide)
{
    HWND   hwnd = QueryHWNDFrame ();
    BOOL   fWasVisible = WinIsWindowVisible (hwnd);

    fFrameHidden = fHide;

    // get original window position and state
    SWP   swpOld;
    WinQueryWindowPos (hwnd, &swpOld);

    // restore and hide the window
    WinSetWindowPos (hwnd, 0, 0, 0, 0, 0, SWP_RESTORE | SWP_HIDE);

    // determine client window and location
    SWP   swp;
    WinQueryWindowPos (hwnd, &swp);

    RECTL   rcl;
    rcl.xLeft   = swp.x;
    rcl.xRight  = swp.x + swp.cx;
    rcl.yBottom = swp.y;
    rcl.yTop    = swp.y + swp.cy;

    WinCalcFrameRect (hwnd, &rcl, TRUE);

    // hide or reveal the controls windows by changing their parentage
    if (fHide)
    {
        WinSetParent (hwndSysMenu,  HWND_OBJECT, FALSE);
        WinSetParent (hwndTitleBar, HWND_OBJECT, FALSE);
        WinSetParent (hwndMinMax,   HWND_OBJECT, FALSE);
    } else {
        WinSetParent (hwndSysMenu,  hwnd, TRUE);
        WinSetParent (hwndTitleBar, hwnd, TRUE);
        WinSetParent (hwndMinMax,   hwnd, TRUE);
        if (WinQueryActiveWindow (WinQueryWindow (hwnd, QW_PARENT)) == hwnd)
            WinSendMsg (WinWindowFromID (hwnd, FID_TITLEBAR), TBM_SETHILITE,
                        MPFROMLONG (TRUE), 0);
    }

    // tell the frame that things have changed. let it update the window
    WinSendMsg (hwnd, WM_UPDATEFRAME,
                MPFROMSHORT (FCF_TITLEBAR | FCF_SYSMENU | FCF_MINBUTTON), 0);

    // reposition the frame around the client window, which is left be
    WinCalcFrameRect (hwnd, &rcl, FALSE);

    WinSetWindowPos (hwnd, 0, rcl.xLeft, rcl.yBottom, rcl.xRight - rcl.xLeft,
                     rcl.yTop - rcl.yBottom, SWP_SIZE | SWP_MOVE);
    
    // if window was maximized, put it back that way
    if (swpOld.fl & SWP_MAXIMIZE)
    {
        WinSetWindowPos (hwnd, 0, rcl.xLeft,  rcl.yBottom,
                         rcl.xRight - rcl.xLeft, rcl.yTop - rcl.yBottom,
                         SWP_SIZE | SWP_MOVE | (swpOld.fl & SWP_MAXIMIZE));
    }
    
    // if the window was visible in the first place, show it
    if (fWasVisible)
        WinShowWindow (hwnd, TRUE);
}

// ** Drag **************************************************************** /*fold00*/

VOID DISPLAY :: Drag (VOID)
{
    HWND   hwnd = QueryHWNDFrame ();
    
    // determine the new window position
    TRACKINFO   trackinfo ;
    memset (&trackinfo, 0, sizeof (trackinfo));

    trackinfo.cxBorder = 1;
    trackinfo.cyBorder = 1;
    trackinfo.cxGrid = 1;
    trackinfo.cyGrid = 1;
    trackinfo.cxKeyboard = 8;
    trackinfo.cyKeyboard = 8;
 
    SWP   swp;
    WinQueryWindowPos (hwnd, &swp);
    trackinfo.rclTrack.xLeft   = swp.x;
    trackinfo.rclTrack.xRight  = swp.x + swp.cx;
    trackinfo.rclTrack.yBottom = swp.y;
    trackinfo.rclTrack.yTop    = swp.y + swp.cy;

    WinQueryWindowPos (HWND_DESKTOP, &swp);
    trackinfo.rclBoundary.xLeft   = swp.x;
    trackinfo.rclBoundary.xRight  = swp.x + swp.cx;
    trackinfo.rclBoundary.yBottom = swp.y;
    trackinfo.rclBoundary.yTop    = swp.y + swp.cy;

    trackinfo.ptlMinTrackSize.x = 0;
    trackinfo.ptlMinTrackSize.y = 0;
    trackinfo.ptlMaxTrackSize.x = swp.cx;
    trackinfo.ptlMaxTrackSize.y = swp.cy;

    trackinfo.fs = TF_MOVE | TF_STANDARD | TF_ALLINBOUNDARY;

    if (WinTrackRect (HWND_DESKTOP, 0, &trackinfo))
        WinSetWindowPos (hwnd, 0, trackinfo.rclTrack.xLeft,
                         trackinfo.rclTrack.yBottom, 0, 0, SWP_MOVE);
}

// ** UpdateButtons ******************************************************* /*fold00*/

#define XOFFSET  0
#define XDIST 0

VOID DISPLAY :: UpdateButtons (VOID)
{
    // FIXME this is all not the best performing code ...
    
    USHORT   cx = DISPLAY_XS-XOFFSET, c = 0, x = XOFFSET;

    if (IsShownExitButton ())
        c++;
    if (IsShownSuspendButton ())
        c++;
    if (IsShownResetButton ())
        c++;

    switch (c)
    {
    case 2:   cx = (DISPLAY_XS-XOFFSET-XDIST)/2;      break;
    case 3:   cx = (DISPLAY_XS-XOFFSET-2*XDIST)/3;    break;
    }

    if (hwndExitButton)
    {
        WinDestroyWindow (hwndExitButton);
        hwndExitButton = NULL;
    }
    if (hwndSuspendButton)
    {
        WinDestroyWindow (hwndSuspendButton);
        hwndSuspendButton = NULL;
    }
    if (hwndResetButton)
    {
        WinDestroyWindow (hwndResetButton);
        hwndResetButton = NULL;
    }

    Resize ();

    if (IsShownExitButton ())
    {
        hwndExitButton =
            WinCreateWindow (QueryHWNDClient (), WC_BUTTON, "E~xit",
                             WS_VISIBLE | WS_SYNCPAINT | BS_PUSHBUTTON,
                             x, 0, cx, QueryFontSizeY ()+13,
                             QueryHWNDClient (), HWND_TOP,
                             WID_PB_EXIT, NULL, NULL);
        x += cx+XDIST;
    }

    if (IsShownSuspendButton ())
    {
        PSZ   psz;

        if (pcrdntr->QueryConnection (this)->IsSuspended ())
            psz = PSZ_CONTINUE;
        else
            psz = PSZ_PAUSE;
        
        hwndSuspendButton =
                WinCreateWindow (QueryHWNDClient (), WC_BUTTON, psz,
                             WS_VISIBLE | WS_SYNCPAINT | BS_PUSHBUTTON,
                             x, 0, cx, QueryFontSizeY ()+13,
                             QueryHWNDClient (), HWND_TOP,
                             WID_PB_SUSPEND, NULL, NULL);
        x += cx+XDIST;
    }

    if (IsShownResetButton ())
    {
        hwndResetButton =
            WinCreateWindow (QueryHWNDClient (), WC_BUTTON, "~Reset",
                             WS_VISIBLE | WS_SYNCPAINT | BS_PUSHBUTTON,
                             x, 0, cx, QueryFontSizeY ()+13,
                             QueryHWNDClient (), HWND_TOP,
                             WID_PB_RESET, NULL, NULL);
        x += cx+XDIST;
    }
}

// ** Resize ************************************************************** /*fold00*/

VOID DISPLAY :: Resize (VOID)
{
    LONG l = 2;

    if (! FrameHidden ())
    {
        SWP  swp;
        WinQueryWindowPos (hwndTitleBar, &swp);
        l += swp.cy;
    }

    /* resize window */
    WinSetWindowPos (QueryHWNDFrame (), HWND_DESKTOP, 0, 0, DISPLAY_XS,
                     QueryHeight ()+l, SWP_SIZE);
    UpdateSecond ();
}
// ** QueryHeight ********************************************************* /*FOLD00*/

USHORT DISPLAY :: QueryHeight (VOID)
{
    USHORT   i, s = 0;

    if (IsShownExitButton () ||
        IsShownSuspendButton () ||
        IsShownResetButton ())
        s += QueryFontSizeY ()+12;

    HPS   hPS = WinGetPS (QueryHWNDClient ());
    RECTL rcl;
    WinQueryWindowRect (HWND_DESKTOP, &rcl);
    WinDrawText (hPS, 1, PSZ (" "), &rcl, 0,0,
                 DT_LEFT | DT_BOTTOM | DT_QUERYEXTENT);
    cxFont = rcl.xRight - rcl.xLeft;
    cyFont = rcl.yTop - rcl.yBottom;
    WinReleasePS (hPS);

    for (i = 0; i < MAX_ITEMS; i++)
        if (QueryItem (IID (i))->IsShown ())
            s += QueryFontSizeY ();
    return (s-1);
}

// ** QueryWidth ********************************************************** /*FOLD00*/

USHORT DISPLAY :: QueryWidth (VOID)
{
    HPS   hPS = WinGetPS (QueryHWNDClient ());
    RECTL rcl;
    PSZ   psz = "Costs/Minute      00:00:0000";
    
    WinQueryWindowRect (HWND_DESKTOP, &rcl);
    WinDrawText (hPS, strlen (psz), psz, &rcl, 0,0,
                 DT_LEFT | DT_BOTTOM | DT_QUERYEXTENT);
    WinReleasePS (hPS);

    return (rcl.xRight - rcl.xLeft);
}

// ** UpdateSecond ******************************************************** /*fold00*/

VOID DISPLAY :: UpdateSecond (VOID)
{
    if (RefreshEnabled ())
        WinInvalidateRect (QueryHWNDClient (), NULL, FALSE);
}

// ** AutodetectConnection ************************************************ /*fold00*/

VOID DISPLAY :: AutodetectConnection (PVOID)
{
    HMQ hmq = WinCreateMsgQueue (GETHAB, 0);

    HFILE   hf;           /* File handle for the device         */
    UCHAR   ucStatus;     /* The COM port status byte           */
    ULONG   ulStatusLen;  /* Length of status (the data packet) */
    ULONG   ulAction;     /* Action taken by DosOpen            */
    APIRET  rc;           /* Return code                        */
    CHAR    ach[21];
    BOOL    fCarrier = FALSE;

    sprintf (ach, "COM%1d", g_usComport); // FIXME global variable? :-(

    if (g_fReset)
        pcrdntr->pdisplay->Hide ();

    do
    {
        rc = DosOpen (ach, &hf, &ulAction, 0, FILE_NORMAL, FILE_OPEN,
                      OPEN_ACCESS_READWRITE | OPEN_SHARE_DENYNONE,
                      (PEAOP2) NULL);
        rc = DosDevIOCtl(hf,                  /* Device handle                    */
                         IOCTL_ASYNC,         /* Serial-device control            */
                         ASYNC_GETMODEMINPUT, /* Get the COM status byte          */
                         NULL,                /* No parameter packet              */
                         0,                   /* Maximum size of parameter packet */
                         NULL,                /* Length of parameter packet       */
                         (PULONG) &ucStatus,  /* Data packet                      */
                         sizeof(ucStatus),    /* Maximum size of data packet      */
                         &ulStatusLen);       /* Length of data packet            */
#define BITSET(c,n)  (((c)&(1<<(n)))!=0)
        if (! g_fQuitting)
        {
            if (fCarrier & !BITSET (ucStatus,7))
            {
                pcrdntr->pconnect->Suspend ();
                if (g_fReset)
                {
                    pcrdntr->pdisplay->Hide ();
                    pcrdntr->pconnect->Reset ();
                }
            }
            else if (!fCarrier & BITSET (ucStatus,7))
            {
                if (g_fReset)
                    pcrdntr->pdisplay->Show ();
                pcrdntr->pconnect->Continue ();
            }
        }

        fCarrier = BITSET (ucStatus,7);
        rc = DosClose(hf);
        _sleep2 (1000);
    }
    while (! g_fQuitting);

    WinDestroyMsgQueue (hmq);
}

// ************************************************************************
