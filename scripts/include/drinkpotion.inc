use cfgfile;

include "include/client";
//include "include/attributes";
include "include/objtype";
include "include/dotempmods";
include "include/random";

const DRINK_SOUND	:= 0x0032;
const DELAY_BETWEEN_DRINK	:= 10;
const DURATION_MULTIPLIER	:= 120;

function CheckIfCanDrink( character )

	if( GetObjProperty( character, "#potion" ) && GetObjProperty( character, "#potion" ) > ReadGameClock() )
		SendSysMessage( character, "You must wait until you can drink another potion!" );
		return 0;
	else
		SetObjProperty( character, "#potion", ReadGameClock() + DELAY_BETWEEN_DRINK );
		return 1;
	endif
	
endfunction


function CanDrink( character )

	EraseObjProperty( character, "#potion" );
	
endfunction


function EmptyBottle( character, potion )

	ReserveItem( potion );
	PlaySoundEffect( character, DRINK_SOUND );
	CreateItemInBackpack( character, UOBJ_EMPTY_BOTTLE, 1 );
	SubtractAmount( potion, 1 );
	ReleaseItem( potion );

endfunction


function GetPotionStrength( potion )

	var itemcfg := ReadConfigFile( ":alchemy:itemdesc" );

	if( potion.objtype == 0x7059 )
		return GetObjProperty( potion,"strength" );
	else
		var power := CInt( itemcfg[potion.objtype].strength );
		if( !power )
			return 0;
		endif
	
		if( GetObjProperty( potion, "ByTrueMage" ) )
			power := power + CInt(GetObjProperty( potion, "ByTrueMage" ));
		endif
	
		return power;
	endif

endfunction


function IsPoison( potion )

	return GetObjProperty( potion, "Poisoned" );
	
endfunction


function DoPoison( character, potion )

	var plvl := IsPoison( potion );

	if( CheckSkill( character, CInt(SKILLID_TASTEID), CInt(plvl*15),  CInt(plvl*15*10) ) )
		SendSysMessage( character, "That potion is poisonous!" );
		return;
	endif

	EmptyBottle( character, potion );

	SetPoison( character, plvl, "You've been poisoned!" );

endfunction
