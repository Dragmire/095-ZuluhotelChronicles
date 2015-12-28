@echo off

doskey
set POLROOT=C:\UL095Ow
set PATH=%PATH%;%POLROOT%\scripts
set ECOMPILE_PATH_EM=%POLROOT%\scripts
set ECOMPILE_PATH_INC=%POLROOT%\scripts

echo POL development environment set to %POLROOT%

.\scripts\ecompile -b -r *.src -r