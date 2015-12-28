//include "include/attributes";
function topclass(who)

var class:=GetObjProperty(who,"ctfclass");

var newwand:={0x6116,0x6114,0x6121,0x6123,0x612b,0x612d,0x6130,0x6135,0x6136,0x6139,0x613a,0x613b,0x6140,0x6142,0x6146,0x6150,0x6151};
var item,i,regs:={0xf7a,0xf7b,0xf84,0xf85,0xf86,0xf88,0xf8c,0xf8d};

if (class=="cleric")
DestroyItem(GetEquipmentByLayer(who,1));

item:=CreateItemInBackpack(who,newwand[Random(17)+1],1);
SetObjProperty(item,"X6",1);
EquipItem(who,item);
SetObjProperty(item,"charges",25);
item.name:=GetObjProperty(item,"tname");
item.movable:=0;

endif
if (class=="bow")
CreateItemInBackpack(who,0xf3f,300);
endif
if (class=="mage")
for (i:=1;i<=8;i:=i+1)
CreateItemInContainer(who.backpack,regs[i],30);
endfor
endif

CreateItemInBackpack(who, 0x0e21, 10);
CreateItemInBackpack(who, 0xdc01, Random(2)+1);

endfunction

function messagectf(message,msgcolor,msgsnd:=0)

  var i,who,ctfplyr:=GetGlobalProperty("#ctfplyr");
  var ctfloc,ctfsize:=ctfplyr.size();

  if (ctfplyr[1]=="NONE") return; endif

  for(i:=1;i<=ctfsize;i:=i+1)
    who:=SystemFindObjectBySerial(CInt(ctfplyr[i]));
    ctfloc:=GetObjProperty(who,"ctfloc");
    if (ctfloc==1 || ctfloc==2) SendSysMessage(who,message,3,msgcolor);
       if (msgsnd!=0) PlaySoundEffect(who,msgsnd); endif
       start_script(":zuluctf:hud",who);
    endif
  endfor

endfunction

function topstats(who)

    SetHp(who, who.maxhp);
    SetMana(who, who.maxmana);
    SetStamina(who, who.maxstamina);

endfunction

function howmany()
return CInt(GetGlobalProperty("ctfredteam")+GetGlobalProperty("ctfblueteam"));
endfunction

function quitctf(who)
set_critical(1);

  var i,ctfplyr:=GetGlobalProperty("#ctfplyr"),csize:=ctfplyr.size();

    for (i:=1;i<=csize;i:=i+1)
      if (ctfplyr[i]==who.serial)
          ctfplyr.erase(i);
          if (ctfplyr.size()==0) ctfplyr:={"NONE"}; endif
          break;
      endif
    endfor

SetGlobalProperty("#ctfplyr",ctfplyr);
set_critical(0);

DestroyItem(GetEquipmentByLayer(who,LAYER_HAND2));

var team:=GetObjProperty(who,"team");

if (GetObjProperty(who,"ctfloc")!=0)
if (team=="BLUE")
SetGlobalProperty("ctfblueteam",GetGlobalProperty("ctfblueteam")-1);
else
SetGlobalProperty("ctfredteam",GetGlobalProperty("ctfredteam")-1);
endif
endif

removetech(who);
EraseObjProperty(who,"team");
SetObjProperty(who,"ctfloc",0);
MoveCharacterToLocation(who,6083,450,-22);

endfunction


function colorstuff(who,ncolor)

var item,i,armor:={0x03,0x04,0x05,0x06,0x07,0x0a,0x0c,0x0d,0x0e,0x11,0x13,0x14,0x16,0x17,0x18};

for(i:=1;i<=15;i:=i+1)
item:=GetEquipmentByLayer(who,armor[i]);

if (ncolor>=0)
item.color:=ncolor;
SetObjProperty(item,"X6",1);
else
DestroyItem(item);
endif

endfor

endfunction

function removetech(who)

var tech,techchr:=GetObjProperty(who,"#ctftech");

if (techchr!="")

  if (techchr=="armor")
    tech:=SystemFindObjectBySerial(CInt(GetGlobalProperty("#tech1")));
  elseif (techchr=="disrupt")
    tech:=SystemFindObjectBySerial(CInt(GetGlobalProperty("#tech2")));
  elseif (techchr=="haste")
    tech:=SystemFindObjectBySerial(CInt(GetGlobalProperty("#tech3")));
  elseif (techchr=="inviso")
    tech:=SystemFindObjectBySerial(CInt(GetGlobalProperty("#tech4")));
  elseif (techchr=="strength")
    tech:=SystemFindObjectBySerial(CInt(GetGlobalProperty("#tech5")));
  elseif (techchr=="magic")
    tech:=SystemFindObjectBySerial(CInt(GetGlobalProperty("#tech6")));
  elseif (techchr=="quad")
    tech:=SystemFindObjectBySerial(CInt(GetGlobalProperty("#tech7")));
  elseif (techchr=="regen")
    tech:=SystemFindObjectBySerial(CInt(GetGlobalProperty("#tech8")));
  endif
  EraseObjProperty(who,"#ctftech");
  EraseObjProperty(tech,"user");
  DestroyItem(tech);
  start_script(":zuluctf:hud",who);
endif

endfunction

function putinplayer(who)
var redstart:={6037,275,0};
var bluestart:={6114,275,22};

if (GetObjProperty(who,"ctfloc")!=3)
SetObjProperty(who,"ctfkills",0);
SetObjProperty(who,"ctfdeaths",0);
SetObjProperty(who,"ctfcaps",0);
SetObjProperty(who,"ctfscore",0);
SetObjProperty(who,"ctfddd",0);
SetObjProperty(who,"ctfooo",0);
else
SetObjProperty(who,"ctfloc",1);
endif

topclass(who);
topstats(who);

SendSysMessage(who,"Starting...",70);
PlaySoundEffect(who,0x135);

if(GetObjProperty(who,"team")=="BLUE")
colorstuff(who,4);
MoveCharacterToLocation(who,(Random(9)+bluestart[1]),(Random(9)+bluestart[2]),bluestart[3]);
else
colorstuff(who,33);
MoveCharacterToLocation(who,(Random(9)+redstart[1]),(Random(9)+redstart[2]),redstart[3]);
endif

endfunction