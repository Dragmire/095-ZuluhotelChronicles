// Bookcase Spawning system  version .1
// created December 7, 2000
// designed by Bishop Ebonhand and Zulu

This is based on syzygy book system.  The requires version .92 of POL.


*** edit book1 and book2 in the zulubooks.cfg ***

** Installing **
1. unzip package \pol\pkg\opt\sysbook\
2. replace items found in \pol\pkg\opt\sysbook\config\itemdesc.txt in
     \config\itemdesc.cfg
3. copy files in \pol\pkg\opt\sysbook\control\ to
     \pol\scripts\control\
4. copy the files in \pol\pkg\opt\sysbook\commands\ to
     \pol\scripts\textcmd\seer\
5. copy the files in \pol\pkg\opt\sysbook\include\ to
     \pol\scripts\include\
6. compile scripts

** To add new books **

1. Load the zulubooks.cfg file
2. go to the bottom of the file
3. add new entry and save the file
4. add book item to itemdesc.cfg
5. add the book to an npc for sale?

** book info **
- books can be up to 16 pages max.
- page 1 can only have 7 lines,
   the rest can have up to 8.
- p#l# = page # line #

book #
{
pages #
title <book title>
author <author name>
p#l# <max 25 chars>
}
