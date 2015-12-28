use uo;
use os;
use util;
use basic;

include "include/dismount";
include "include/client";
include "include/spelldata";
include "include/classes";
include "include/random";


function AddToPersistedMods( byref allmods, byref mmod )

	set_critical(1);
	var i;
	for( i := 1; i <= len(allmods); i := i + 1 )
		if ( allmods[i][1] == mmod[1] )
			return 0;
		endif
	endfor

	allmods.append( mmod );
	set_critical(0);

	return i;

endfunction


function AddToPoisonMod( byref currentmod, byref mmod )

	set_critical(1);
	if( mmod[1] > currentmod[1] )
		currentmod[1] := mmod[1];
	endif

	if( mmod[2] > currentmod[2] )
		currentmod[2] := mmod[2];
	endif
	set_critical(0);

endfunction


function AddToStatMods( byref allmods, byref mmod )

	set_critical(1);
	var i;
	for( i := 1; i <= len(allmods); i := i + 1 )
		if ( allmods[i][1] == mmod[1] )
			return 0;
		endif
	endfor

	allmods.append( mmod );
	set_critical(0);

	return i;

endfunction


function BaseRegenRate( who )

	var baseregen := GetObjProperty(who,"baseregen");

	if (!baseregen)
		return 100;
	endif

	return baseregen;

endfunction


function CanMod( who, stat, persistedprop := 0 )

	var modarray := "#mods";
	if( persistedprop )
		modarray := "mods";
	endif

	var currentmods := GetObjProperty( who, modarray );
	if (!currentmods)
		return 1;
	endif

	foreach mmod in currentmods
		if ( mmod[1] == stat )
			return 0;
		endif
	endforeach
	
	return 1;

endfunction


function CurePoison( who, sound := 0, msg := 0 )

	set_critical( 1 );

	var currentmod := GetObjProperty( who, "poison" );
	if( !currentmod )
		set_critical( 0 );
		return;
	endif

	EraseObjProperty(who, "poison_level");
	EraseObjProperty( who, "poison" );
	SetHpRegenRate(who , ( BaseRegenRate(who)) * 12);
	who.SetPoisoned( 0 );

	set_critical( 0 );

	if( sound )
		PlaySoundEffectPrivate( who, sound, who );
	endif

	if( msg )
		PrintTextAbovePrivate( who, msg, who );
	endif

endfunction


//for name, graphic and color changes!
function DoPersistedMod( who, prop, newvalue, oldvalue, duration )

	var parms := {};
	parms[1] := who;
	parms[2] := prop;
	parms[3] := newvalue;
	parms[4] := oldvalue;
	parms[5] := duration;

	start_script( ":summoning:processpersistedmod", parms );
	sleepms(250);

endfunction


//for nonpersistedmods
function DoTempMod( who, stat, amt, duration )

	var parms := {};
	parms[1] := who;
	parms[2] := stat;
	parms[3] := amt;
	parms[4] := duration;

	start_script( ":summoning:processtempmod", parms );
	sleepms(250);

endfunction


function GetModAmount( who )

	var magery := GetEffectiveSkill( who, SKILLID_MAGERY );
	var amount := RandomInt(10) + CInt(magery/10) + 5;
	amount := ModifyWithMagicEfficiency( who, amount );
	if( !amount )
		amount := 1;
	endif

	return CInt(amount);

endfunction


function GetModDuration( who )

	var magery := GetEffectiveSkill( who, SKILLID_MAGERY );
	var duration := magery * 4;
	duration := ModifyWithMagicEfficiency( who, duration );
	if( !duration )
		duration := 1;
	endif

	return CInt(duration);

endfunction


function GetPoisonRegenMod( plvl )

	case (plvl)
		0: return 100;
		1: return -500;
		2: return -750;
		3: return -1500;
		4: return -2500;
		5: return -3500;
		6: return -5000;
	endcase

/*	
		0: return 0;
		1: return -500;
		2: return -1000;
		3: return -2000;
		4: return -4000;
		5: return -8000;
		6: return -16000;
*/

endfunction


function PoisonLevel( who )

	var currentmod := GetObjProperty( who, "poison" );
	if( !currentmod )
		currentmod := {};
	endif

	if( !len(currentmod) )
		return 0;
	else
		return CInt( currentmod[1] );
	endif

endfunction


function PoisonProtected( cast_on, plvl )

	var prot := "PoisonImmunity";
	var protserial := GetObjProperty( cast_on, "PoisonImmunity" );
	var protlvl := GetObjProperty( cast_on, "PermPoisonImmunity" );
	if( !protlvl )
		protlvl := 0;
	endif

	var cmi := 0 - protlvl;
	var item;
	var charges;
	var cursed;

	if( protserial )
		foreach thing in ListEquippedItems( cast_on )
			if ( thing.serial == protserial )
				item := thing;
				charges := GetObjProperty( item, "PoisonImmunity" );
				cursed := GetObjProperty( item, "Cursed" );
				if (!charges)
					EraseObjProperty( cast_on, "PoisonImmunity" );
					EraseObjProperty( item, "PoisonImmunity" );
					PrintTextAbovePrivate(item, item.desc + " is out of charges!", cast_on );
					CheckForAnotherProtItem( cast_on, item, "PoisonImmunity" );
				endif
				break;
			endif
		endforeach
	endif

	if( charges >= plvl )
		charges := charges - plvl;
		SetObjProperty( item, "PoisonImmunity", charges );
		if( !cursed )
			PrintTextAbovePrivate( cast_on, "Your " + item.desc + " protected you from the poison!", cast_on );
			return IMMUNED;
		else
			return CURSED;
		endif
	
	elseif( cmi >= plvl )
		return CURSED;
	
	elseif( protlvl >= plvl )
		PrintTextAbovePrivate( cast_on, "Your poison immunity protect you from the poison", cast_on );
		return IMMUNED;
	endif
	
	return 0;


endfunction


function RandomHairColor()

	return Random(46)+1102;

endfunction


function SetPoison( who, plvl, msg := 0 )

	if( NoPKArea(who) )
		return 0;
	endif


	if( !who.isA(POLCLASS_NPC) )
		plvl := plvl - 1;
	endif

	if( plvl < 1 )
		plvl := 1;
	elseif( plvl > 9)
		plvl := 9;
	endif

	var parms := {};
	parms[1] := who;
	parms[2] := plvl;
	parms[3] := CStr( msg );

	start_script( ":summoning:processpoisonmod", parms );
	sleepms(250);

endfunction


function UndoTheMod( who, prop, amt )

	var 	msg,
		sound;
	
	var 	oldvalue := amt;
 
	case (prop)
		"cstr":
		"str" :
  SetStrengthMod(who, GetStrengthMod( who ) - amt);
	
		"cdex":
		"dex" :
  SetDexterityMod(who, GetDexterityMod( who ) - amt);
	
		"cint":
		"int" :
  SetIntelligenceMod(who, GetIntelligenceMod( who ) - amt);
	
		"car":
		"ar"  :		who.ar_mod := who.ar_mod - amt;
				msg := "Armor is now " + who.ar;
				sound := 0x01e3;
			
		"p"   :		who.setParalyzed( 0 );
		"call":
		"all" :		SetStrengthMod(who, GetStrengthMod( who ) - amt );
				SetDexterityMod(who, GetDexterityMod( who ) - amt );
				SetIntelligenceMod(who, GetIntelligenceMod( who ) - amt );
			
		"cpoly":
		"poly":		who.ar_mod := who.ar_mod - CInt( amt / 3 );
				msg := "Armor is now " + who.ar;
				sound := 0x01e3;
				SetStrengthMod(who, GetStrengthMod( who ) - amt);
				SetDexterityMod(who, GetDexterityMod( who ) - amt);
				SetIntelligenceMod(who, GetIntelligenceMod( who ) - amt);
			
        	"name"    : 	who.name := oldvalue;
				msg := "Your name is now " + who.name;
				sound := 0x01e3;
			
		"graphic" : 	who.graphic := oldvalue;
	
		"color"   : 	who.color := oldvalue;
	
		"spiritspeak":	if (!amt)
					RevokePrivilege( who, "hearghosts" );
				endif
			
        	"title_prefix": who.title_prefix := oldvalue;
        
        	"title_suffix": who.title_suffix := oldvalue;
        
		"gender":	who.gender := oldvalue;
	
		"hair":
			DestroyItem( GetEquipmentByLayer( who, LAYER_HAIR ));
			if (oldvalue)
				var newhair := CreateItemAtLocation(5288, 1176, 0, oldvalue, 1);
				newhair.color := GetObjProperty(who,"haircolor");
				EquipItem(who,newhair);
			endif
		"beard":
			DestroyItem(GetEquipmentByLayer(who,LAYER_BEARD));
			if (oldvalue)
				var newhair := CreateItemAtLocation(5288, 1176, 0, oldvalue, 1);
				newhair.color := GetObjProperty(who,"haircolor");
				EquipItem(who,newhair);
			endif
		"poison":
			SetHpRegenRate(who , ( BaseRegenRate(who)) * 12);
			who.SetPoisoned( 0 );
	endcase

	if( sound )
		PlaySoundEffectPrivate(who, sound, who);
	endif

	if( msg )
		PrintTextAbovePrivate(who,msg,who);
	endif

endfunction


function WipeMods( who )

	set_critical( 1 );

	var had_mods := 0;
	var modarray := GetObjProperty( who, "#mods" );
	if( !modarray )
		modarray := {};
	else
		had_mods := 1;
	endif

	foreach mmod in modarray
		UndoTheMod( who, mmod[1], mmod[2] );
	endforeach
	EraseObjProperty( who, "#mods" );


	var persitedmodarray := GetObjProperty( who, "mods" );
	var newmods := {};
	if( !persitedmodarray )
		persitedmodarray := {};
	else
		had_mods := 1;
	endif

	foreach mmod in persitedmodarray
		if( mmod[1] != "poison" )
			UndoTheMod( who, mmod[1], mmod[2] );
		else
			newmods.append( mmod );
		endif
	endforeach

	if( len(newmods) )
		SetObjProperty( who, "mods", newmods );
	else
		EraseObjProperty( who, "mods" );
	endif

	set_critical(0);

	return had_mods;

endfunction
