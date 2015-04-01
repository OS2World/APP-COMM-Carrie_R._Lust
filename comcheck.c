
#include <stdlib.h>
#include <stdio.h>
#include <sys/kbdscan.h>

#define INCL_DOSFILEMGR    /* File System values */
#define INCL_DOSDEVIOCTL   /* DosDevIOCtl values */

#include <os2.h>

#define BITSET(c,n)  (((c)&(1<<(n)))!=0)

//#define X3

int main (VOID)
{
    HFILE   hf;           /* File handle for the device         */
    UCHAR   ucStatus, uc;     /* The COM port status byte           */
    ULONG   ulStatusLen;  /* Length of status (the data packet) */
    ULONG   ulAction;     /* Action taken by DosOpen            */
    APIRET  rc;           /* Return code                        */
    USHORT uw;

/*    rc = DosOpen ("COM1", &hf, &ulAction, 0, FILE_NORMAL, FILE_OPEN,
                  OPEN_ACCESS_READWRITE | OPEN_SHARE_DENYNONE,
                  (PEAOP2) NULL);*/

    while (_read_kbd (1,0,1) != ' ')
    {
        rc = DosOpen ("COM1", &hf, &ulAction, 0, FILE_NORMAL, FILE_OPEN,
                      OPEN_ACCESS_READWRITE | OPEN_SHARE_DENYNONE,
                      (PEAOP2) NULL);
//        rc = DosDevIOCtl(hf,                  /* Device handle                    */
//                         IOCTL_ASYNC,         /* Serial-device control            */
//                         ASYNC_GETCOMMSTATUS, /* Get the COM status byte          */
//                         NULL,                /* No parameter packet              */
//                         0,                   /* Maximum size of parameter packet */
//                         NULL,                /* Length of parameter packet       */
//                         (PULONG) &ucStatus,  /* Data packet                      */
//                         sizeof(ucStatus),    /* Maximum size of data packet      */
//                         &ulStatusLen);       /* Length of data packet            */
#ifdef X1
        printf ("CTS %d - DSR %d - DCD %d - XOFFr %d - "
                "XOFFt %d - BRKt %d - ChaRt %d - R-DSR %d\r",
                ucStatus&0x01, ucStatus&0x02, ucStatus&0x04, ucStatus&0x08,
                ucStatus&0x10, ucStatus&0x20, ucStatus&0x40, ucStatus&0x80);
        rc = DosDevIOCtl(hf,                  /* Device handle                    */
                         IOCTL_ASYNC,         /* Serial-device control            */
                         ASYNC_GETCOMMSTATUS, /* Get the COM status byte          */
                         NULL,                /* No parameter packet              */
                         0,                   /* Maximum size of parameter packet */
                         NULL,                /* Length of parameter packet       */
                         (PULONG) &ucStatus,  /* Data packet                      */
                         sizeof(ucStatus),    /* Maximum size of data packet      */
                         &ulStatusLen);       /* Length of data packet            */
#endif
        uc = 0;
        rc = DosDevIOCtl(hf,                  /* Device handle                    */
                         IOCTL_ASYNC,         /* Serial-device control            */
                         ASYNC_GETMODEMOUTPUT, /* Get the COM status byte          */
                         NULL,                /* No parameter packet              */
                         0,                   /* Maximum size of parameter packet */
                         NULL,                /* Length of parameter packet       */
                         (PULONG) &ucStatus,  /* Data packet                      */
                         sizeof(ucStatus),    /* Maximum size of data packet      */
                         &ulStatusLen);       /* Length of data packet            */
        uc = uc | ucStatus;
        rc = DosDevIOCtl(hf,                  /* Device handle                    */
                         IOCTL_ASYNC,         /* Serial-device control            */
                         ASYNC_GETMODEMINPUT, /* Get the COM status byte          */
                         NULL,                /* No parameter packet              */
                         0,                   /* Maximum size of parameter packet */
                         NULL,                /* Length of parameter packet       */
                         (PULONG) &ucStatus,  /* Data packet                      */
                         sizeof(ucStatus),    /* Maximum size of data packet      */
                         &ulStatusLen);       /* Length of data packet            */
        uc = uc | ucStatus;
        printf ("%s %s %s %s %s %s %s %s\n",
                BITSET (uc,0) ? "DTR" : "---",
                BITSET (uc,1) ? "RTS" : "---",
                BITSET (uc,2) ? "???" : "---",
                BITSET (uc,3) ? "???" : "---",
                BITSET (uc,4) ? "CTS" : "---",
                BITSET (uc,5) ? "DSR" : "---",
                BITSET (uc,6) ? "RI " : "---",
                BITSET (uc,7) ? "DCD" : "---");
        fprintf (stderr, "%s %s %s %s %s %s %s %s\r\n",
                 BITSET (uc,0) ? "DTR" : "---",
                 BITSET (uc,1) ? "RTS" : "---",
                 BITSET (uc,2) ? "???" : "---",
                 BITSET (uc,3) ? "???" : "---",
                 BITSET (uc,4) ? "CTS" : "---",
                 BITSET (uc,5) ? "DSR" : "---",
                 BITSET (uc,6) ? "RI " : "---",
                 BITSET (uc,7) ? "DCD" : "---");
#ifdef X3
        rc = DosDevIOCtl(hf,                  /* Device handle                    */
                         IOCTL_ASYNC,         /* Serial-device control            */
                         ASYNC_GETCOMMEVENT, /* Get the COM status byte          */
                         NULL,                /* No parameter packet              */
                         0,                   /* Maximum size of parameter packet */
                         NULL,                /* Length of parameter packet       */
                         (PULONG) &uw,  /* Data packet                      */
                         sizeof(uw),    /* Maximum size of data packet      */
                         &ulStatusLen);       /* Length of data packet            */
        printf ("0x%04x\n", uw);
        fprintf (stderr, "0x%04x\n", uw);
#endif

        rc = DosClose(hf);
        _sleep2 (1000);
    }
//    rc = DosClose(hf);

    printf ("Changing ...\n");
    fprintf (stderr, "Changing ...\n");

    rc = DosOpen ("COM1", &hf, &ulAction, 0, FILE_NORMAL, FILE_OPEN,
                  OPEN_ACCESS_READWRITE | OPEN_SHARE_DENYNONE, (PEAOP2) NULL);
    while (_read_kbd (1,0,1) != ' ')
    {
        rc = DosDevIOCtl(hf,                  /* Device handle                    */
                         IOCTL_ASYNC,         /* Serial-device control            */
                         ASYNC_GETCOMMSTATUS, /* Get the COM status byte          */
                         NULL,                /* No parameter packet              */
                         0,                   /* Maximum size of parameter packet */
                         NULL,                /* Length of parameter packet       */
                         (PULONG) &ucStatus,  /* Data packet                      */
                         sizeof(ucStatus),    /* Maximum size of data packet      */
                         &ulStatusLen);       /* Length of data packet            */
#ifdef X1
        printf ("CTS %d - DSR %d - DCD %d - XOFFr %d - "
                "XOFFt %d - BRKt %d - ChaRt %d - R-DSR %d\r",
                ucStatus&0x01, ucStatus&0x02, ucStatus&0x04, ucStatus&0x08,
                ucStatus&0x10, ucStatus&0x20, ucStatus&0x40, ucStatus&0x80);
        rc = DosDevIOCtl(hf,                  /* Device handle                    */
                         IOCTL_ASYNC,         /* Serial-device control            */
                         ASYNC_GETCOMMSTATUS, /* Get the COM status byte          */
                         NULL,                /* No parameter packet              */
                         0,                   /* Maximum size of parameter packet */
                         NULL,                /* Length of parameter packet       */
                         (PULONG) &ucStatus,  /* Data packet                      */
                         sizeof(ucStatus),    /* Maximum size of data packet      */
                         &ulStatusLen);       /* Length of data packet            */
#endif
        uc = 0;
        rc = DosDevIOCtl(hf,                  /* Device handle                    */
                         IOCTL_ASYNC,         /* Serial-device control            */
                         ASYNC_GETMODEMOUTPUT, /* Get the COM status byte          */
                         NULL,                /* No parameter packet              */
                         0,                   /* Maximum size of parameter packet */
                         NULL,                /* Length of parameter packet       */
                         (PULONG) &ucStatus,  /* Data packet                      */
                         sizeof(ucStatus),    /* Maximum size of data packet      */
                         &ulStatusLen);       /* Length of data packet            */
        uc = uc | ucStatus;
        rc = DosDevIOCtl(hf,                  /* Device handle                    */
                         IOCTL_ASYNC,         /* Serial-device control            */
                         ASYNC_GETMODEMINPUT, /* Get the COM status byte          */
                         NULL,                /* No parameter packet              */
                         0,                   /* Maximum size of parameter packet */
                         NULL,                /* Length of parameter packet       */
                         (PULONG) &ucStatus,  /* Data packet                      */
                         sizeof(ucStatus),    /* Maximum size of data packet      */
                         &ulStatusLen);       /* Length of data packet            */
        uc = uc | ucStatus;
        printf ("%s %s %s %s %s %s %s %s\n",
                BITSET (uc,0) ? "DTR" : "---",
                BITSET (uc,1) ? "RTS" : "---",
                BITSET (uc,2) ? "???" : "---",
                BITSET (uc,3) ? "???" : "---",
                BITSET (uc,4) ? "CTS" : "---",
                BITSET (uc,5) ? "DSR" : "---",
                BITSET (uc,6) ? "RI " : "---",
                BITSET (uc,7) ? "DCD" : "---");
        fprintf (stderr, "%s %s %s %s %s %s %s %s\r\n",
                 BITSET (uc,0) ? "DTR" : "---",
                 BITSET (uc,1) ? "RTS" : "---",
                 BITSET (uc,2) ? "???" : "---",
                 BITSET (uc,3) ? "???" : "---",
                 BITSET (uc,4) ? "CTS" : "---",
                 BITSET (uc,5) ? "DSR" : "---",
                 BITSET (uc,6) ? "RI " : "---",
                 BITSET (uc,7) ? "DCD" : "---");
#ifdef X3
        rc = DosDevIOCtl(hf,                  /* Device handle                    */
                         IOCTL_ASYNC,         /* Serial-device control            */
                         ASYNC_GETCOMMEVENT, /* Get the COM status byte          */
                         NULL,                /* No parameter packet              */
                         0,                   /* Maximum size of parameter packet */
                         NULL,                /* Length of parameter packet       */
                         (PULONG) &uw,  /* Data packet                      */
                         sizeof(uw),    /* Maximum size of data packet      */
                         &ulStatusLen);       /* Length of data packet            */
        printf ("0x%04x\n", uw);
        fprintf (stderr, "0x%04x\n", uw);
#endif

        _sleep2 (1000);
    }
    rc = DosClose(hf);
}
