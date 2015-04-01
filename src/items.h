/***
 items.h
 ***/

#ifndef _ITEMS_H_
#define _ITEMS_H_

// ** includes ************************************************************ /*FOLD00*/

#include "clust.h"

// ** Item (Base class) *************************************************** /*FOLD00*/

class Item
{
    friend class Display;
    friend  class Settings;

    const USHORT CB_BUFFER = 41;

protected:
    Item (PDISPLAY pdisplay);

    virtual VOID    Repaint (HPS hps, RECTL *rcl) = 0;
    virtual PSZ     QueryLabel (VOID) = 0;
    virtual PSZ     QueryDescription (VOID) = 0;

    virtual BOOL    HasChanged (VOID) = 0;

    VOID   Show (VOID);
    VOID   Hide (VOID);
    BOOL   IsShown (VOID);

    COLOR         QueryBGColor (VOID);
    COLOR         QueryFGColor (VOID);

    PDISPLAY      QueryDisplay (VOID);
    VOID          SetDisplay (PDISPLAY pdisplay);

    PCHRGINFO     QueryChargesInfo (VOID);
    PCONNECTION   QueryConnection (VOID);

    static CHAR   psz[CB_BUFFER];

private:
    PDISPLAY   pdisplay;
    BOOL       fIsShown;
};
// ------------------------------------------------------------------------

inline VOID Item :: Show (VOID) { fIsShown = TRUE; }
inline VOID Item :: Hide (VOID) { fIsShown = FALSE; }
inline BOOL Item :: IsShown (VOID) { return (fIsShown); }

// ------------------------------------------------------------------------

#include "display.h"
#include "chrginfo.h"
#include "connectn.h"

// ------------------------------------------------------------------------

inline COLOR Item :: QueryBGColor (VOID)  {
    return (pset->QueryBackgroundColor ()); }
inline COLOR Item :: QueryFGColor (VOID)  {
    return (CLR_BLACK); }

inline PDISPLAY Item :: QueryDisplay (VOID) {
    return (pdisplay); }

inline VOID Item :: SetDisplay (PDISPLAY pdisplay) {
    this->pdisplay = pdisplay; }

inline PCHRGINFO Item :: QueryChargesInfo (VOID) {
    return (QueryDisplay ()->QueryChargesInfo ()); }

inline PCONNECTION Item :: QueryConnection (VOID) {
    return (QueryDisplay ()->QueryConnection ()); }

inline Item :: Item (PDISPLAY pdisplay)
{
    Show ();
    SetDisplay (pdisplay);
}

// ** ItemDuration ******************************************************** /*FOLD00*/

class ItemDuration : public Item
{
    friend class Display;

protected:
    ItemDuration (PDISPLAY pdisplay);

    VOID   Repaint (HPS hps, RECTL *rcl);
    PSZ    QueryLabel (VOID);
    PSZ    QueryDescription (VOID);
    BOOL   HasChanged (VOID);
};
// ------------------------------------------------------------------------

inline ItemDuration :: ItemDuration (PDISPLAY pdisplay) : Item (pdisplay) { }
inline PSZ ItemDuration :: QueryLabel (VOID)   { return ("Connect.time"); }
inline PSZ ItemDuration :: QueryDescription (VOID)   { return ("Session connection time"); }
inline BOOL ItemDuration :: HasChanged (VOID)  { return (TRUE); }

// ** ItemUnits *********************************************************** /*FOLD00*/

class ItemUnits : public Item
{
    friend class Display;

protected:
    ItemUnits (PDISPLAY pdisplay);

    VOID   Repaint (HPS hps, RECTL *rcl);
    PSZ    QueryLabel (VOID);
    PSZ    QueryDescription (VOID);
    BOOL   HasChanged (VOID);
};
// ------------------------------------------------------------------------

inline ItemUnits :: ItemUnits (PDISPLAY pdisplay) : Item (pdisplay) { }
inline PSZ ItemUnits :: QueryLabel (VOID)   { return ("# Units"); }
inline PSZ ItemUnits :: QueryDescription (VOID)   { return ("Number of units passed in this session"); }
inline BOOL ItemUnits :: HasChanged (VOID)  { return (TRUE); }

// ** ItemMoney *********************************************************** /*FOLD00*/

class ItemMoney : public Item
{
    friend class Display;

protected:
    ItemMoney (PDISPLAY pdisplay);

    VOID   Repaint (HPS hps, RECTL *rcl);
    PSZ    QueryLabel (VOID);
    PSZ    QueryDescription (VOID);
    BOOL   HasChanged (VOID);
};
// ------------------------------------------------------------------------

inline ItemMoney :: ItemMoney (PDISPLAY pdisplay) : Item (pdisplay) { }
inline PSZ ItemMoney :: QueryLabel (VOID)   { return ("Costs"); }
inline PSZ ItemMoney :: QueryDescription (VOID)   { return ("Total costs of this session"); }
inline BOOL ItemMoney :: HasChanged (VOID)  { return (TRUE); }

// ** ItemUnitLeft ******************************************************** /*FOLD00*/

class ItemUnitLeft : public Item
{
    friend class Display;

protected:
    ItemUnitLeft (PDISPLAY pdisplay);

    VOID   Repaint (HPS hps, RECTL *rcl);
    PSZ    QueryLabel (VOID);
    PSZ    QueryDescription (VOID);
    BOOL   HasChanged (VOID);
};
// ------------------------------------------------------------------------

inline ItemUnitLeft :: ItemUnitLeft (PDISPLAY pdisplay) : Item (pdisplay) { }
inline PSZ ItemUnitLeft :: QueryLabel (VOID)   { return ("Unit left"); }
inline PSZ ItemUnitLeft :: QueryDescription (VOID)   { return ("Time left of current unit"); }
inline BOOL ItemUnitLeft :: HasChanged (VOID)  { return (TRUE); }

// ** ItemLimitLeft ******************************************************* /*FOLD00*/

class ItemLimitLeft : public Item
{
    friend class Display;

protected:
    ItemLimitLeft (PDISPLAY pdisplay);

    VOID   Repaint (HPS hps, RECTL *rcl);
    PSZ    QueryLabel (VOID);
    PSZ    QueryDescription (VOID);
    BOOL   HasChanged (VOID);
};
// ------------------------------------------------------------------------

inline ItemLimitLeft :: ItemLimitLeft (PDISPLAY pdisplay) : Item (pdisplay) { }
inline PSZ ItemLimitLeft :: QueryLabel (VOID)   { return ("Limit left"); }
inline PSZ ItemLimitLeft :: QueryDescription (VOID)   { return ("Time left until session limit reached"); }
inline BOOL ItemLimitLeft :: HasChanged (VOID)  { return (TRUE); }

// ** ItemUnitLength ****************************************************** /*FOLD00*/

class ItemUnitLength : public Item
{
    friend class Display;

protected:
    ItemUnitLength (PDISPLAY pdisplay);

    VOID   Repaint (HPS hps, RECTL *rcl);
    PSZ    QueryLabel (VOID);
    PSZ    QueryDescription (VOID);
    BOOL   HasChanged (VOID);
};
// ------------------------------------------------------------------------

inline ItemUnitLength :: ItemUnitLength (PDISPLAY pdisplay) : Item (pdisplay) { }
inline PSZ ItemUnitLength :: QueryLabel (VOID)   { return ("Unit length"); }
inline PSZ ItemUnitLength :: QueryDescription (VOID)   { return ("Length of a unit"); }
inline BOOL ItemUnitLength :: HasChanged (VOID)  { return (TRUE); }

// ** ItemMoneyPerUnit **************************************************** /*FOLD00*/

class ItemMoneyPerUnit : public Item
{
    friend class Display;

protected:
    ItemMoneyPerUnit (PDISPLAY pdisplay);

    VOID   Repaint (HPS hps, RECTL *rcl);
    PSZ    QueryLabel (VOID);
    PSZ    QueryDescription (VOID);
    BOOL   HasChanged (VOID);
};
// ------------------------------------------------------------------------

inline ItemMoneyPerUnit :: ItemMoneyPerUnit (PDISPLAY pdisplay) : Item (pdisplay) { }
inline PSZ ItemMoneyPerUnit :: QueryLabel (VOID)   { return ("Costs/Unit"); }
inline PSZ ItemMoneyPerUnit :: QueryDescription (VOID)   { return ("Costs per unit"); }
inline BOOL ItemMoneyPerUnit :: HasChanged (VOID)  { return (TRUE); }

// ** ItemMoneyPerMinute ****************************************************

class ItemMoneyPerMinute : public Item
{
    friend class Display;

protected:
    ItemMoneyPerMinute (PDISPLAY pdisplay);

    VOID   Repaint (HPS hps, RECTL *rcl);
    PSZ    QueryLabel (VOID);
    PSZ    QueryDescription (VOID);
    BOOL   HasChanged (VOID);
};
// ------------------------------------------------------------------------

inline ItemMoneyPerMinute :: ItemMoneyPerMinute (PDISPLAY pdisplay) : Item (pdisplay) { }
inline PSZ ItemMoneyPerMinute :: QueryLabel (VOID)   { return ("Costs/Minute"); }
inline PSZ ItemMoneyPerMinute :: QueryDescription (VOID)   { return ("Costs per minute"); }
inline BOOL ItemMoneyPerMinute :: HasChanged (VOID)  { return (TRUE); }

// ** ItemMoneyPerHour **************************************************** /*FOLD00*/

class ItemMoneyPerHour : public Item
{
    friend class Display;

protected:
    ItemMoneyPerHour (PDISPLAY pdisplay);

    VOID   Repaint (HPS hps, RECTL *rcl);
    PSZ    QueryLabel (VOID);
    PSZ    QueryDescription (VOID);
    BOOL   HasChanged (VOID);
};
// ------------------------------------------------------------------------

inline ItemMoneyPerHour :: ItemMoneyPerHour (PDISPLAY pdisplay) : Item (pdisplay) { }
inline PSZ ItemMoneyPerHour :: QueryLabel (VOID)   { return ("Costs/Hour"); }
inline PSZ ItemMoneyPerHour :: QueryDescription (VOID)   { return ("Costs per hour"); }
inline BOOL ItemMoneyPerHour :: HasChanged (VOID)  { return (TRUE); }

// ** ItemSecsTillCharge ************************************************** /*FOLD00*/

class ItemSecsTillCharge : public Item
{
    friend class Display;

protected:
    ItemSecsTillCharge (PDISPLAY pdisplay);

    VOID   Repaint (HPS hps, RECTL *rcl);
    PSZ    QueryLabel (VOID);
    PSZ    QueryDescription (VOID);
    BOOL   HasChanged (VOID);
};
// ------------------------------------------------------------------------

inline ItemSecsTillCharge :: ItemSecsTillCharge (PDISPLAY pdisplay) : Item (pdisplay) { }
inline PSZ ItemSecsTillCharge :: QueryLabel (VOID)   { return ("Next Charge"); }
inline PSZ ItemSecsTillCharge :: QueryDescription (VOID)   { return ("Time until next charge"); }
inline BOOL ItemSecsTillCharge :: HasChanged (VOID)  { return (TRUE); }

// ** ItemTotalConTime **************************************************** /*FOLD00*/

class ItemTotalConTime : public Item
{
    friend class Display;

protected:
    ItemTotalConTime (PDISPLAY pdisplay);

    VOID   Repaint (HPS hps, RECTL *rcl);
    PSZ    QueryLabel (VOID);
    PSZ    QueryDescription (VOID);
    BOOL   HasChanged (VOID);
};
// ------------------------------------------------------------------------

inline ItemTotalConTime :: ItemTotalConTime (PDISPLAY pdisplay) : Item (pdisplay) { }
inline PSZ ItemTotalConTime :: QueryLabel (VOID)   { return ("Total con.time"); }
inline PSZ ItemTotalConTime :: QueryDescription (VOID)   { return ("Total connection time"); }
inline BOOL ItemTotalConTime :: HasChanged (VOID)  { return (TRUE); }

#ifdef _TOTALVALUES_
// ** ItemTotalUnits ****************************************************** /*FOLD00*/

class ItemTotalUnits : public Item
{
    friend class Display;

protected:
    ItemTotalUnits (PDISPLAY pdisplay) : Item (pdisplay) { }

    VOID   Repaint (HPS hps, RECTL *rcl);
    PSZ    QueryLabel (VOID) { return ("# Units total"); }
    PSZ    QueryDescription (VOID) { return ("Total number of units passed"); }
    BOOL   HasChanged (VOID) { return (TRUE); }
};

// ** ItemTotalMoney ****************************************************** /*FOLD00*/

class ItemTotalMoney : public Item
{
    friend class Display;

protected:
    ItemTotalMoney (PDISPLAY pdisplay) : Item (pdisplay) { }

    VOID   Repaint (HPS hps, RECTL *rcl);
    PSZ    QueryLabel (VOID) { return ("Costs total"); }
    PSZ    QueryDescription (VOID) { return ("Total costs"); }
    BOOL   HasChanged (VOID) { return (TRUE); }
};

// ** ItemTotalLimitLeft ************************************************** /*FOLD00*/

class ItemTotalLimitLeft : public Item
{
    friend class Display;

protected:
    ItemTotalLimitLeft (PDISPLAY pdisplay) : Item (pdisplay) { }

    VOID   Repaint (HPS hps, RECTL *rcl);
    PSZ    QueryLabel (VOID) { return ("Lim. left total"); }
    PSZ    QueryDescription (VOID) { return ("Time until total limit reached"); }
    BOOL   HasChanged (VOID) { return (TRUE); }
};
#endif
// ************************************************************************
#endif
