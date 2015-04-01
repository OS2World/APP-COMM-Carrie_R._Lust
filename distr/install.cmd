/*************************************************************************/
/*  Carrie R. Lust installation file - Creates a WPS-object for Carrie   */
/*  To run this file, just type "install" on the OS/2 command line.      */
/*************************************************************************/

PARSE SOURCE operSystem . sourceFile

IF \(operSystem = "OS/2") THEN DO
    SAY "Please use only with IBM-OS/2 Operating system!"
    EXIT
    END

/*************************************************************************/

'@ECHO OFF'

CALL rxfuncadd 'sysloadfuncs', 'rexxutil', 'sysloadfuncs'
CALL sysloadfuncs

/*************************************************************************/

Ver = "1.17"
CLustDir = FILESPEC("drive", sourceFile)FILESPEC("path", sourceFile)

SAY ""

/*************************************************************************/

CALL SysFileTree CLustDir"CLUST.EXE",'file','F'
IF file.0 = 0 THEN DO
    SAY "CLUST.EXE was not found in the same directory as ",
    FILESPEC("name",sourceFile)

    DO UNTIL \(file.0 = 0)
        SAY ""
        SAY "Please give the full path to the file CLUST.EXE."
        SAY "(Press ENTER/RETURN alone to exit)"
        PULL CLustDir
        IF CLustDir = "" THEN
            EXIT
        IF (FILESPEC("drive",CLustDir) = "") | (FILESPEC("path",CLustDir) = "") THEN
            SAY 'You must give a full path in format "d:\path\"'
        ELSE DO
            IF \(SUBSTR(CLustDir,length(CLustDir),1) = "\" ) THEN
                CLustDir = CLustDir"\"
            CALL SysFileTree CLustDir"CLUST.EXE",'file','F'
            IF file.0 = 0 THEN
                SAY "Can not find "CLustDir"CLUST.EXE. Please try again."
            END
        END
    SAY ""
    END

/*************************************************************************/

setup = 'PROGTYPE=PM;EXENAME='CLustDir'CLUST.EXE;STARTUPDIR='CLustDir';'
setup = setup'ICONFILE='CLustDir'CLUST.ICO;OBJECTID=<THTH_CLUST>;'

SAY ""
SAY "* Creating Carrie R. Lust WPS-object ..."
check = SysCreateObject('WPProgram', 'Carrie R. Lust 'Ver, '<WP_DESKTOP>', setup)

IF check = 0 THEN DO
    SAY "* Could not create WPS-object!"
    SAY "  (Does perhaps an object for Carrie R. Lust already exist?)"
    CALL CHAROUT , "* Do you want to replace the existing object [Y/N] ? "
    key = SysGetKey('ECHO')
    PARSE upper var key key
    SAY ""
    IF key <> 'Y' THEN
        EXIT

    SAY "* Replacing old Carrie R. Lust WPS-object ..."
    check = SysCreateObject('WPProgram','Carrie R. Lust 'Ver,'<WP_DESKTOP>',setup,"r")

    IF check = 0 THEN DO
        SAY ""
        SAY "* Sorry, object-creation failed again. Aborting ..."
        EXIT
        END
    ELSE DO
        SAY ""
        SAY "* Old Carrie R. Lust WPS-object replaced successfully!"
        END
    END
ELSE DO
    SAY ""
    SAY "* Carrie R. Lust WPS-object created successfully!"
    END

/*************************************************************************/

SAY ""
SAY "* See the online help for more information about Carrie R. Lust!"

/*************************************************************************/

EXIT
