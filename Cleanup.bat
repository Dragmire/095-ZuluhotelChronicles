@ECHO OFF

GOTO :MENU()

REM -- MENU FUNCTION
:MENU()
CLS
ECHO #########################
ECHO #                       #
ECHO # Cleanup.bat by Austin #
ECHO #                       #
ECHO #########################
ECHO Command        Purpose
ECHO  [ A ] - Remove *.ecl files. (Will need to recompile scripts)
ECHO  [ B ] - Remove *.bak files
ECHO  [ C ] - Remove *.dep files
ECHO  [ D ] - Remove *.log files
ECHO  [ E ] - Remove *.lst files
ECHO  [ F ] - Remove *.dbg files
ECHO  [ G ] - Remove *.dbg.txt
ECHO  [ H ] - Remove other
ECHO.
ECHO  [ X ] - Back

SET /p CMD=Command:

SET REMOVE_TYPE=
IF /i "%CMD%" == "A" SET REMOVE_TYPE=*.ecl
IF /i "%CMD%" == "B" SET REMOVE_TYPE=*.bak
IF /i "%CMD%" == "C" SET REMOVE_TYPE=*.dep
IF /i "%CMD%" == "D" SET REMOVE_TYPE=*.log
IF /i "%CMD%" == "E" SET REMOVE_TYPE=*.lst
IF /i "%CMD%" == "F" SET REMOVE_TYPE=*.dbg
IF /i "%CMD%" == "G" SET REMOVE_TYPE=*.dbg.txt
IF /i "%CMD%" == "H" GOTO DELETE_CUSTOM()
IF /i "%CMD%" == "X" GOTO :QUIT()

IF NOT "%REMOVE_TYPE%"=="" GOTO REMOVE()

ECHO.
ECHO Invalid command.
GOTO :RETURN_TO_MENU()

REM -- RETURN_TO_MENU() FUNCTION
:RETURN_TO_MENU()
PAUSE
GOTO :MENU()

REM -- REMOVE FUNCTION()
:REMOVE()
IF NOT "%REMOVE_TYPE%"=="" DEL /S %REMOVE_TYPE%
GOTO RETURN_TO_MENU()

REM -- DELETE_CUSTOM FUNCTION()
:DELETE_CUSTOM()
SET /p REMOVE_TYPE=File type to remove (e.g. *.bak or orphans.txt):
GOTO REMOVE()

REM -- QUIT() FUNCTION
:QUIT()