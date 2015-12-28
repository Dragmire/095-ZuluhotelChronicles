@ECHO OFF

REM -- If a special path is needed to ecompile.exe set it here
REM -- Path is considered to be run from the root if started by starthere.bat
SET ECOMPILE_PATH=scripts\ecompile.exe
REM ----------

GOTO :MENU()

REM -- MENU FUNCTION
:MENU()
CLS
ECHO #########################
ECHO #                       #
ECHO # Compile.bat by Austin #
ECHO #                       #
ECHO #########################
ECHO Command        Purpose
ECHO  [ A ] - Compile a specific script.
ECHO  [ B ] - Compile a directory.
ECHO  [ C ] - Compile all .src scripts.
ECHO  [ D ] - Compile all scripts and output to POL\ecompile.log
ECHO.
ECHO  [ X ] - Back

SET /p CMD=Command:

IF /i "%CMD%" == "A" GOTO :COMPILE_SCRIPT()
IF /i "%CMD%" == "B" GOTO :COMPILE_DIRECTORY()
IF /i "%CMD%" == "C" GOTO :COMPILE_ALL_SCRIPTS()
IF /i "%CMD%" == "D" GOTO :COMPILE_ALL_SCRIPTS_OPTXT()
IF /i "%CMD%" == "X" GOTO :QUIT()

ECHO.
ECHO Invalid command.
GOTO :RETURN_TO_MENU()

REM -- RETURN_TO_MENU() FUNCTION
:RETURN_TO_MENU()
PAUSE
GOTO :MENU()

REM -- COMPILE_SCRIPT() FUNCTION
:COMPILE_SCRIPT()
SET /p CMD="Path to script to compile:"
%ECOMPILE_PATH% %CMD%
GOTO RETURN_TO_MENU()

REM -- COMPILE_DIRECTORY() FUNCTION
:COMPILE_DIRECTORY()
SET /p CMD="Path to DIRECTORY:"
%ECOMPILE_PATH% -b -r %CMD%
GOTO RETURN_TO_MENU()

REM -- COMPILE_ALL_SCRIPTS() FUNCTION
:COMPILE_ALL_SCRIPTS()
%ECOMPILE_PATH% -b -r
GOTO RETURN_TO_MENU()

REM -- COMPILE_ALL_SCRIPTS_OPTXT() FUNCTION
:COMPILE_ALL_SCRIPTS_OPTXT()
%ECOMPILE_PATH% -b -r >ecompile.log
GOTO RETURN_TO_MENU()

REM -- QUIT FUNCTION
:QUIT()