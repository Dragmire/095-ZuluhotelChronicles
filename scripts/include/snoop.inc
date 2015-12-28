///////   DPW snooping include file
///
///  The snooping source was getting crowded, so I've added this include file to shorten it up.
///	
//////Dex (rgaffey@earthlink.net)

//this function checks to make sure the player isn't holding anything, or wearing heavy armor
//ripped directly from the armor check on spell casting

function cansteal(character)

if(GetEquipmentByLayer( character, LAYER_HAND1))
	SendSysmessage(character, "You'll need you're hands empty for that!");
	return 1;
endif
if(GetEquipmentByLayer( character, LAYER_HAND2))
	SendSysmessage(character, "You'll need you're hands empty for that!");
	return 1;
endif

var cfg := readconfigfile(":combat:itemdesc");
var item;

foreach item in ListEquippedItems(character)
	if ((cfg[item.objtype].blockcircle) && 
	(cfg[item.objtype].blockcircle <= 6 ) 
	&& !cfg[item.objtype].errortext) 
	SendSysmessage(character, "Only a fool would snoop in so much armor!");
	return 1;
	endif
endforeach
endfunction

function isamark(character, mark)

//This function makes sure the mark is a moble, and not the player

if (!mark.intelligence)
sendsysmessage(character, "Perhaps you should find a more lively mark!");
return;
endif
if (mark.serial = character.serial)
SendSysmessage(character, "You notice yourself acting foolish!");
return;
endif
endfunction

//This function gets the players skill to determine how long the snooping delay should be

function seeskill(character)
var skill;

skill := GetEffectiveSkill( character, 28 );
if ((skill >= 0) and (skill <= 10))	
return 10;
elseif ((skill >= 11) and (skill <= 20))	
return 9;
elseif ((skill >= 21) and (skill <= 30))	
return 8;
elseif ((skill >= 31) and (skill <= 40))	
return 7;
elseif ((skill >= 41) and (skill <= 50))	
return 6;
elseif ((skill >= 51) and (skill <= 60))	
return 5;
elseif ((skill >= 61) and (skill <= 70))	
return 4;
elseif ((skill >= 71) and (skill <= 80))	
return 3;
elseif ((skill >= 81) and (skill <= 90))	
return 2;
elseif ((skill >= 91) and (skill <= 99))	
return 1;
elseif (skill >= 100)
return 0;
endif
endfunction

//This checks if a item is a container or not, probably won't be used in final script

function iscontainer(itemt, thingie)
if (((itemt >= 0x1f2d) and (itemt <= 0x1f72)) or ((itemt >= 0x0e43) and (itemt <= 0x0e3c)) or ((itemt >= 0x0e75) and (itemt <= 0x0e77)) or ((itemt >= 0x0e43) and (itemt <= 0x0e3c)) or ((itemt >= 0x0e80) and (itemt <= 0x0e79)))
data.insert( 1, thingie.serial );
return 1;
endif
endfunction

//This checks the marks intelligence against the players skill to determin difficulty

function snoopindifficulty(character, mark)
var marksi;
var skill;

skill := GetEffectiveSkill( character, 28 );
marksi := GetIntelligence(mark) - (GetDexterity(character)* 0.3);
if (GetIntelligence(mark) > 100)
marksi := cint(100 - (GetDexterity(character) * 0.3));
endif
if (marksi < 0)
marksi := 0;
endif

return marksi;
endfunction