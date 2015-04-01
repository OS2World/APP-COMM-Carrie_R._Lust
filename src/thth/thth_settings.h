/***
 thth_settings - a custom settings class with INI file handling
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

 Author: Thorsten Thielen <thth@gmx.net>
 Documentation for this class wouldn't hurt. See my programs (Minta,
 Carrie R. Lust, Gotcha!, etc.) for some usage examples
 ***/

#ifndef _THTH_SETTINGS_H_
#define _THTH_SETTINGS_H_

#define OS2EMX_PLAIN_CHAR

#define INCL_PM
#define INCL_GPI

#include "os2.h"
#include "string.h"

typedef USHORT ID;

// ------------------------------------------------------------------------

typedef class ththSettingsEntry
{
    friend class ththSettings;

protected:
    enum { SET_FLAG, SET_LONG, SET_STRING, SET_BINARY };

    ththSettingsEntry (ID id, PSZ pszGroup, PSZ pszKey, USHORT usType);

    ID       QueryID (VOID) { return id; }
    USHORT   QueryType (VOID) { return usType; }
    PSZ      QueryGroup (VOID) { return pszGroup; }
    PSZ      QueryKey (VOID)  { return pszKey; }

    virtual  VOID Reset (VOID) = 0;
    virtual  VOID Load (HINI hini) = 0;
    virtual  VOID Save (HINI hini) = 0;

private:
    ID       id;
    PSZ      pszGroup;
    PSZ      pszKey;
    USHORT   usType;
} THTH_SE;

typedef THTH_SE *PTHTH_SE;

inline THTH_SE :: ththSettingsEntry (ID id, PSZ pszGroup, PSZ pszKey, USHORT usType)
{
    this->id = id;
    this->pszGroup = pszGroup;
    this->pszKey = pszKey;
    this->usType = usType;
}

// ------------------------------------------------------------------------

typedef class ththSettingsEntryFlag : public ththSettingsEntry
{
    friend class ththSettings;

public:
    ththSettingsEntryFlag (ID id, PSZ pszGroup, PSZ pszKey, BOOL f)
        : ththSettingsEntry (id, pszGroup, pszKey, ththSettingsEntry::SET_FLAG) {
            fDefault = f; Reset (); }

    ththSettingsEntryFlag (ID id, PSZ pszGroup, PSZ pszKey, BOOL f, HINI hini)
        : ththSettingsEntry (id, pszGroup, pszKey, ththSettingsEntry::SET_FLAG) {
            fDefault = f; Load (hini); }

    VOID   Set (BOOL f) { this->f = f; }
    BOOL   Query (VOID) { return f; }
    VOID   Reset (VOID) { f = fDefault; }

    VOID Load (HINI hini)
    {
        BOOL  f;
        ULONG ul = sizeof (f);
        if (! PrfQueryProfileData (hini, QueryGroup (), QueryKey (),
                                   PVOID (&f), &ul))
            Reset ();
        else
            Set (f);
    }

    VOID Save (HINI hini)
    {
        BOOL f = Query ();
        PrfWriteProfileData (hini, QueryGroup (), QueryKey (),
                             PVOID (&f), sizeof (f));
    }

private:
    BOOL   f, fDefault;
} THTH_SEF;

typedef THTH_SEF *PTHTH_SEF;

// ------------------------------------------------------------------------

typedef class ththSettingsEntryLong : public ththSettingsEntry
{
    friend class ththSettings;

public:
    ththSettingsEntryLong (ID id, PSZ pszGroup, PSZ pszKey, LONG l)
        : ththSettingsEntry (id, pszGroup, pszKey, ththSettingsEntry::SET_LONG) {
            lDefault = l; Reset (); }

    ththSettingsEntryLong (ID id, PSZ pszGroup, PSZ pszKey, LONG l, HINI hini)
        : ththSettingsEntry (id, pszGroup, pszKey, ththSettingsEntry::SET_LONG) {
            lDefault = l; Load (hini); }

    VOID   Set (LONG l) { this->l = l; }
    LONG   Query (VOID) { return l; }
    VOID   Reset (VOID) { l = lDefault; }

    VOID Load (HINI hini)
    {
        LONG  l;
        ULONG ul = sizeof (l);
        if (! PrfQueryProfileData (hini, QueryGroup (), QueryKey (),
                                   PVOID (&l), &ul))
            Reset ();
        else
                Set (l);
    }

    VOID Save (HINI hini)
    {
        LONG l = Query ();
        PrfWriteProfileData (hini, QueryGroup (), QueryKey (),
                             PVOID (&l), sizeof (l));
    }

private:
    LONG   l, lDefault;
} THTH_SEL;

typedef THTH_SEL *PTHTH_SEL;

// ------------------------------------------------------------------------

typedef class ththSettingsEntryString : public ththSettingsEntry
{
    friend class ththSettings;

public:
    ththSettingsEntryString (ID id, PSZ pszGroup, PSZ pszKey, PSZ psz)
        : ththSettingsEntry (id, pszGroup, pszKey, ththSettingsEntry::SET_STRING) {
            pszDefault = psz; Reset (); }

    ththSettingsEntryString (ID id, PSZ pszGroup, PSZ pszKey, PSZ psz, HINI hini)
        : ththSettingsEntry (id, pszGroup, pszKey, ththSettingsEntry::SET_STRING) {
            pszDefault = psz; Load (hini); }

    VOID Set (PSZ psz)
    {
        if (this->psz)
            delete this->psz;
        this->psz = strdup (psz);
    }

    PSZ Query (VOID)
    {
        if (! psz)
                return "";
        return psz;
    }

    VOID   Reset (VOID) { Set (pszDefault); }

    VOID Load (HINI hini)
    {
        ULONG ul;
        if (PrfQueryProfileSize (hini, QueryGroup (), QueryKey (), &ul))
        {
            CHAR *ach = new char[ul];
            PrfQueryProfileString (hini, QueryGroup (), QueryKey (),
                                   pszDefault, ach, ul);
            Set (ach);
            delete ach;
        }
    }

    VOID Save (HINI hini)
    {
        PrfWriteProfileString (hini, QueryGroup (), QueryKey (), Query ());
    }

private:
    PSZ   psz, pszDefault;
} THTH_SES;

typedef THTH_SES *PTHTH_SES;

// ------------------------------------------------------------------------

typedef class ththSettingsEntryBinary : public ththSettingsEntry
{
    friend class ththSettings;

public:
    ththSettingsEntryBinary (ID id, PSZ pszGroup, PSZ pszKey, PVOID pv, size_t size)
        : ththSettingsEntry (id, pszGroup, pszKey, ththSettingsEntry::SET_BINARY) {
            pvDefault = pv; this->sizeDefault = size; Reset (); }

    ththSettingsEntryBinary (ID id, PSZ pszGroup, PSZ pszKey, PVOID pv, size_t size, HINI hini)
        : ththSettingsEntry (id, pszGroup, pszKey, ththSettingsEntry::SET_BINARY) {
            pvDefault = pv; this->sizeDefault = size; Load (hini); }

    VOID Set (PVOID pv, size_t size)
    {
        if (this->pv)
            delete this->pv;
        this->pv = new BYTE[size];
        memcpy (this->pv, pv, size);
        this->size = size;
    }

    PVOID Query (size_t *psize = NULL)
    {
        if (! pv)
        {
            if (psize)
                *psize = 0L;
            return NULL;
        }
        if (psize)
            *psize = size;
        return pv;
    }

    VOID Reset (VOID) { Set (pvDefault, sizeDefault); }

    VOID Load (HINI hini)
    {
        ULONG ul;
        if (PrfQueryProfileSize (hini, QueryGroup (), QueryKey (), &ul))
        {
            pv = new BYTE[ul];
            if (! PrfQueryProfileData (hini, QueryGroup (), QueryKey (),
                                       pv, &ul))
                Reset ();
        }
    }

    VOID Save (HINI hini)
    {
        PrfWriteProfileData (hini, QueryGroup (), QueryKey (), pv, size);
    }

private:
    PVOID   pv, pvDefault;
    size_t  size, sizeDefault;
} THTH_SEB;

typedef THTH_SEB *PTHTH_SEB;

// ------------------------------------------------------------------------

typedef class ththSettings
{
public:
    ththSettings (PTHTH_SE *ppse, PSZ pszInifile = NULL, ULONG ulVersion = 0L);
    virtual ~ththSettings (VOID);

    VOID Reset (VOID)
    {
        if (ppse)
            for (LONG i = 0; ppse[i]; i++)
                ppse[i]->Reset ();
    }

    VOID Load (VOID)
    {
        if (ppse && hini)
            for (LONG i = 0; ppse[i]; i++)
                ppse[i]->Load (hini);
    }

    BOOL Save (VOID);

    VOID SetFlag (ID id, BOOL f = TRUE)
    {
        if ((pse = ID2Entry (id)))
            if (pse->QueryType () == ththSettingsEntry::SET_FLAG)
                PTHTH_SEF (pse)->Set  (f);
    }

    VOID   ClearFlag (ID id) { SetFlag (id, FALSE); }
    VOID   ToggleFlag (ID id) { SetFlag (id, ! FlagSet (id)); }

    BOOL FlagSet (ID id)
    {
        if ((pse = ID2Entry (id)))
            if (pse->QueryType () == ththSettingsEntry::SET_FLAG)
                return PTHTH_SEF (pse)->Query ();
        return FALSE;
    }

    BOOL   QueryFlag (ID id) { return FlagSet (id); }

    VOID SetLong (ID id, LONG l)
    {
        if ((pse = ID2Entry (id)))
            if (pse->QueryType () == ththSettingsEntry::SET_LONG)
                PTHTH_SEL (pse)->Set (l);
    }

    LONG QueryLong (ID id)
    {
        if ((pse = ID2Entry (id)))
            if (pse->QueryType () == ththSettingsEntry::SET_LONG)
                return PTHTH_SEL (pse)->Query ();
        return 0L;
    }

    VOID SetString (ID id, const PSZ psz)
    {
        if ((pse = ID2Entry (id)))
            if (pse->QueryType () == ththSettingsEntry::SET_STRING)
                PTHTH_SES (pse)->Set  (psz);
    }

    PSZ QueryString (ID id)
    {
        if ((pse = ID2Entry (id)))
            if (pse->QueryType () == ththSettingsEntry::SET_STRING)
                return PTHTH_SES (pse)->Query ();
        return "";
    }

    VOID SetBinary (ID id, PVOID pv, size_t size)
    {
        if ((pse = ID2Entry (id)))
            if (pse->QueryType () == ththSettingsEntry::SET_BINARY)
                PTHTH_SEB (pse)->Set (pv, size);
    }

    PVOID QueryBinary (ID id, size_t *psize = NULL)
    {
        if ((pse = ID2Entry (id)))
            if (pse->QueryType () == ththSettingsEntry::SET_BINARY)
                return PTHTH_SEB (pse)->Query (psize);
        *psize = 0L;
        return NULL;
    }

protected:
    PSZ   QueryProfileName (VOID) { return psz; }
    ULONG Error (VOID) { return ulError; }

    ULONG QueryVersion (VOID) { return ulVersion; }
    VOID  SetVersion (ULONG ul) { ulVersion = ul; }

    HINI  QueryPrfHandle (VOID) { return hini; }

private:
    PTHTH_SE ID2Entry (ID id)
    {
        if (ppse)
            for (LONG i = 0; ppse[i]; i++)
                if (ppse[i]->QueryID () == id)
                    return ppse[i];
        return NULL;
    }

    PSZ    psz;
    HINI   hini;
    PTHTH_SE    *ppse, pse;
    ULONG  ulVersion;
    ULONG  ulError;
} THTH_SETTINGS;

typedef THTH_SETTINGS *PTHTH_SETTINGS;

// ------------------------------------------------------------------------
#endif
