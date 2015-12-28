//////////////////////////////////////////////////////////////////////////////////
//										//
//	spelldata.inc : 							//
//										//
//	This file include all the constant related to existing spells, as	//
//	well as useful fuction about spells. The first line of each spell	//
//	is the spellid, then his SFX anf finally his FX				//
//										//
//////////////////////////////////////////////////////////////////////////////////
use uo;
use os;
use util;
use basic;
use cfgfile;

include "include/client";
include "include/attributes";
include "include/random";
include "include/eventid";
include "include/classes";
include "include/damages";
include "include/areas";
include "include/skillpoints";
include "include/damages";

////////////////////////////////
// Spell functions' constants //
////////////////////////////////


// TryToCast return values
const IN_ANTIMAGIC_AREA := 1;
const INTERRUPTED       := 2;
const INVALID_EQUIPMENT := 3;
const NO_REGS           := 4;
const NO_MANA           := 5;
const NO_SKILL          := 6;
const SUCCESS           := 7;


// Casting options
const CASTINGOPT_PROP_NAME      := "CastingOpts";
const PERM_CASTINGOPT_PROP_NAME := "PermCastingOpts";
const CASTINGOPT_ANY_EQUIPMENT  := "ANYEQUIP";
const CASTINGOPT_NO_WORDS       := "NOWORDS";
const CASTINGOPT_NO_DELAY       := "NODELAY";
const CASTINGOPT_NO_REAGENTS    := "NOREGS";
const CASTINGOPT_NO_MANA        := "NOMANA";
const CASTINGOPT_NO_SKILL_CHECK := "NOSKILL";


// CalcSpellDamage options
const SINGLE_TARGET_SPELL := 0;
const AREA_EFFECT_SPELL   := 1;

const SPELL_DAMAGES_MAGERY_DIVIDER    := 5;
const SPELL_DAMAGES_ON_PLAYER_DIVIDER := 3;
const SPELL_DAMAGES_CIRCLE_MULTIPLIER := 3; // number of dices to throw per circle
const SPELL_DAMAGES_DICE_TYPE         := 5; // type of dices to throw



// Immunities constants
const IMMUNED	:= 1;
const CURSED	:= 2;


// Elements contants
const FIRE	:= 0x01;
const AIR	:= 0x02;
const EARTH	:= 0x04;
const WATER	:= 0x08;
const NECRO	:= 0x10;
const HOLY	:= 0x20;


// Error messages
const ERROR_MSG_ANTI_MAGIC_AREA		:= "Spells cannot be cast here.";
const ERROR_MSG_FIZZLE			:= "The spell fizzles";
const ERROR_MSG_INTERRUPTED		:= "You were interrupted during the casting";
const ERROR_MSG_LOST_CONCENTRATION	:= "You've lost your concentration!";
const ERROR_MSG_NOT_ENOUGH_REAGENTS	:= "Insufficient Reagents.";
const ERROR_MSG_NOT_ENOUGH_MANA		:= "Insufficient Mana.";
const ERROR_MSG_NOT_ENOUGH_SKILL	:= "This spell is above yours magical capacities.";
const ERROR_MSG_NOT_IN_SIGHT		:= "You can't see that.";
const ERROR_MSG_WRONG_EQUIPMENT		:= "Your hands must be free to cast spells.";


//////////////////////////////////////////////////////////////////////////////////////////////////
// Spell functions :										//
//	This include all functions from spellrestrictions.inc, plus some more.			//
//	Don't erase the spellrestrictions however, unless you are certain that you changed	//
//	include "include/spellrestrictions" from ALL pkgs that used it.	Some parameters of	//
//	the functions changed however.								//
//////////////////////////////////////////////////////////////////////////////////////////////////


function ApplyElementalDamage( caster, cast_on, circle, dmg, element )

	If (!GetObjProperty( caster, "PeaceKeeper") )
		if( NoPKArea(cast_on) )
			return 0;
		endif
	endif

	if(caster.dead) return; endif
	if(cast_on.dead) return; endif
	if(cast_on.hidden) return; endif

	var resultprot := GetResultingElementalProt( cast_on, element );

	if( resultprot <= 4 )
		dmg := dmg - CInt(dmg * resultprot * 25 / 100);
		ApplyTheDamage( cast_on, caster, Resisted( caster, cast_on, circle, dmg ), DMGID_MAGIC + element );
	else
		HealTheDamage( cast_on, CInt(dmg * (resultprot - 4) * 0.25) );
	endif

endfunction


function ApplyElementalDamageNoResist( on_who, by_who, dmg, element )

	if(by_who.dead) return; endif
	if(on_who.dead) return; endif
	if(on_who.hidden) return; endif

	var resultprot := GetResultingElementalProt( on_who, element );

	if( resultprot <= 4 )
		dmg := dmg - CInt(dmg * resultprot * 25 / 100);
		ApplyTheDamage( on_who, by_who, dmg, element );
	else
		HealTheDamage( on_who, CInt(dmg * (resultprot - 4) * 0.25) );
	endif

endfunction


function ApplyPlanarDamage( caster, cast_on, circle, dmg, plane )

	If (!GetObjProperty( caster, "PeaceKeeper") )
		if( NoPKArea(cast_on) )
			return 0;
		endif
	endif

	if(caster.dead) return; endif
	if(cast_on.dead) return; endif
	if(cast_on.hidden) return; endif

	var resultprot := GetResultingPlaneProtection( cast_on, plane );

	if( resultprot <= 4 )
		dmg := dmg - CInt(dmg * resultprot * 25 / 100);
		ApplyTheDamage( cast_on, caster, Resisted( caster, cast_on, circle, dmg ), DMGID_MAGIC + plane );
	else
		HealTheDamage( cast_on, CInt(dmg * (resultprot - 4) * 25 / 100) );
	endif

endfunction


function BurnSelf( caster, circle )

	if(caster.dead) return; endif

	var dmg;
	var cast_on := caster;
        dmg := CalcSpellDamage( caster, cast_on, circle );
        if( GetObjProperty( caster, CLASSEID_MAGE ) )
        	dmg := CInt( dmg / ClasseBonus( caster, CLASSEID_MAGE ) );
        elseif( GetObjProperty( caster, CLASSEID_WARRIOR ) )
        	dmg := CInt( dmg * ClasseBonus( caster, CLASSEID_WARRIOR ) );
        endif

	ApplyRawDamage( caster, Resisted( caster, circle, cast_on, CInt(dmg / 2) ) );

endfunction


function CalcSpellDamage( caster, cast_on, circle, area_spell := SINGLE_TARGET_SPELL )

	If (!GetObjProperty( caster, "PeaceKeeper") )
		if( NoPKArea(cast_on) )
			return 0;
		endif
	endif

	if(caster.dead) return 0; endif
	if(cast_on.dead) return 0; endif
	if(cast_on.hidden) return 0; endif

	if( area_spell ) circle := circle-3; endif

	if( circle < 1 ) circle := 1; endif

	var dmg := RandomDiceRoll(
		 circle * SPELL_DAMAGES_CIRCLE_MULTIPLIER+"d"+
		 SPELL_DAMAGES_DICE_TYPE+"+"+
		 CInt( GetAttribute(caster, ATTRIBUTEID_MAGERY) / SPELL_DAMAGES_MAGERY_DIVIDER )
	);

	if( dmg > CInt(circle * (13 + circle)) ) dmg := CInt(circle * (13 + circle)); endif

	dmg := ModifyWithMagicEfficiency( caster, dmg );

	if( !cast_on.isA(POLCLASS_NPC) ) dmg := CInt(dmg / SPELL_DAMAGES_ON_PLAYER_DIVIDER); endif

	if( cast_on.IsA(POLCLASS_NPC) )
		dmg := dmg * 1.75;
	endif

	if (GetObjProperty(caster,"#ctftech") =="quadUSED")
	  dmg:=dmg*3;
	  PlaySoundEffect(caster,262);
	endif

	if (GetObjProperty(caster,"#ctftech") =="haste")
	  dmg:=dmg*1.5;
	  PlaySoundEffect(caster,259);
	endif

	var teamcolor:=33,fixit:=0;

	if (GetObjProperty(cast_on,"#ctftech") =="disrupt")
	  if (random(4)>=2)
	    if(GetObjProperty(cast_on,"team")=="BLUE") teamcolor:=4; endif
	    fixit:=1;
	    colorstuff(cast_on,70);
	    dmg:=dmg/2;
	    PlaySoundEffect(cast_on,305);
	    sleepms(500);
	  endif
	endif

	if (fixit) colorstuff(cast_on,teamcolor); endif

	return dmg;

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


function can_cast( me, circle )


	if(me.dead) return 0; endif

	var max_circle := GetMaxCircle( me );
	if( max_circle )
		if( circle > max_circle )
			PlayObjectCenteredEffect( me, FX_SPELL_FIZZLE, SPEED_SPELL_FIZZLE, LOOP_SPELL_FIZZLE );
			PlaySoundEffect( me, SFX_SPELL_FIZZLE );
			SendSysMessage( me, ERROR_MSG_NOT_ENOUGH_SKILL );
			return 0;
		endif
	endif

	return 1;

endfunction


function CanTargetArea( caster, circle := 1 )


	if (!can_cast(caster, circle))
        	return 0;
	endif

	var cx := caster.x;
	var cy := caster.y;
	var shp := GetHp(caster);

	var cast_loc := TargetCoordinates( caster );
	if( !cast_loc.x )
		return 0;
	endif

	if( !caster.cmdlevel )
		if ( caster.x>=2555 && caster.y>=478 && caster.x <= 2615 && caster.y <= 3886 )
			SendSysMessage( caster, "Spell disabled in this area");
			return 0;
		endif
	endif

	if( (cx != caster.x) || (cy != caster.y) || (shp > GetHp(caster)) )
		SendSysMessage( caster, ERROR_MSG_LOST_CONCENTRATION );
		return 0;
	endif

	if( !CheckLosAt( caster, cast_loc.x, cast_loc.y, cast_loc.z ) )
        	SendSysMessage( caster, ERROR_MSG_NOT_IN_SIGHT );
		return 0;
	endif

	return cast_loc;

endfunction


function CanTargetSpell( caster, circle := 1, targopt := TGTOPT_CHECK_LOS )


	if (!can_cast(caster, circle))
        	return 0;
	endif


	var cx := caster.x;
	var cy := caster.y;
	var shp := GetHp(caster);

	var cast_on := Target( caster, targopt );
	if(!cast_on  || !GetStrength(cast_on))
		return 0;
	endif

	if( !caster.cmdlevel )
		if ( caster.x>=2555 && caster.y>=478 && caster.x <= 2615 && caster.y <= 3886 )
			SendSysMessage( caster, "Spell disabled in this area");
			return 0;
		endif
	endif

	if ( (cx != caster.x) || (cy != caster.y) || (shp > GetHp(caster)) )
		SendSysMessage( caster, ERROR_MSG_LOST_CONCENTRATION );
		return 0;
	endif
 
        If( cast_on.hidden > 0 )
        SendSysMessage( caster, "You can't see that" );
        Return 0;
        Endif

	return cast_on;

endfunction


function CanTargetThing( caster, circle := 1, targopt := TGTOPT_CHECK_LOS )


	var cx := caster.x;
	var cy := caster.y;
	var shp := GetHp(caster);

	if(!can_cast(caster, circle))
        	return 0;
	endif

	var cast_on := Target( caster, targopt );

	if(!cast_on)
		return 0;
	endif
	if( !caster.cmdlevel )
		if ( caster.x>=2555 && caster.y>=478 && caster.x <= 2615 && caster.y <= 3886 )
			SendSysMessage( caster, "Spell disabled in this area");
			return 0;
		endif
	endif
        If( cast_on.hidden > 0 )
        SendSysMessage( caster, "You can't see that" );
        Return 0;
        Endif
	if ( (cx != caster.x) || (cy != caster.y) || (shp > GetHp(caster)) )
		SendSysMessage( caster, ERROR_MSG_LOST_CONCENTRATION );
		return 0;
	endif

	return cast_on;

endfunction


function CheckForAnotherProtItem( who, item, prot )

	var prots := { "PoisonImmunity",
			 "MagicImmunity",
			 "SpellReflect" };

	if( !(prot in prots) )
		return 0;
	endif

	EraseObjProperty( who, prot );
	foreach thing in ListEquippedItems( who )
		if( GetObjProperty( thing, prot ) )
			SetObjProperty( who, prot, thing.serial );
			break;
		endif
	endforeach

	return 1;

endfunction


function ExtractName( name )

	var words := SplitWords( name );

	//Trunc the articles
	if( (words[1] == "A") || (words[1] == "a") || (words[1] == "An") || (words[1] == "an") )
		name := words[2];
		var i := 3;
		for( i; i <= len(words); i := i + 1 )
			name := name + " " + words[i];
		endfor
	endif


	//Remove the "corpse of" from the name
	words := SplitWords( name );
	if( (words[1] == "corpse") && (words[2] == "of") )
		name := words[3];
		var i := 4;
		if( words[3] == "a" )
			name := words[4];
			i := 5;
		endif

		for( i; i <= len(words); i := i + 1)
			name := name + " " + words[i];
		endfor
	endif


	//Remove the "Reanimated" or "conjured" from the name
	words := SplitWords( name );
	if( (words[1] == "Reanimated") || (words[1] == "conjured") )
		name := words[2];
		var i := 3;
		for( i; i <= len(words); i := i + 1 )
			name := name + " " + words[i];
		endfor
	endif

	if( !name )
		name := "creature";
	endif

	return name;

endfunction


function FindOption( options, wanted )

	if( options[wanted] )
		return 1;
	else
		return 0;
	endif

endfunction


function GetCircle( spell )

	var conf   	:= ReadConfigFile(":*:spells");
	var elem   	:= FindConfigElem(conf, spell);
	var circ 	:= GetConfigString(elem, "Circle");
	conf		:= ReadConfigFile(":*:circles");
	var circle	:= conf[circ].UseCircle;
	if (!circle)
		circle 	:= circ;
	endif
	return CInt(circle);

endfunction


function GetMagicEfficiencyPenalty( who )

	var penalty := 0;

	if(who.dead) return 0; endif

	if( who.isA(POLCLASS_NPC) ) return 0; endif

	foreach item in ListEquippedItems( who )
		if( GetObjProperty( item, "MagicPenalty" ) )
			penalty := penalty + GetObjProperty( item, "MagicPenalty" );
		endif
	endforeach

	if( penalty > 100 )
		penalty := 100;
	endif

	return CInt(penalty);

endfunction


function GetProtLevel( cast_on, element )

	var prot;

	case( element )

		FIRE:	prot := GetObjProperty( cast_on, "FireProtection" );
			break;

		AIR:	prot := GetObjProperty( cast_on, "AirProtection" );
			break;

		EARTH:	prot := GetObjProperty( cast_on, "EarthProtection" );
			break;

		WATER:	prot := GetObjProperty( cast_on, "WaterProtection" );
			break;

		NECRO:	prot := GetObjProperty( cast_on, "NecroProtection" );
			break;

		HOLY:	prot := 0;
			break;

		default:

	endcase

	if( !prot )
		prot := 0;
	endif

	return prot;

endfunction


function GetResultingElementalProt( cast_on, element )

	var complementary;
	var opposed;
	case( element )
		FIRE:	complementary 	:= WATER;
			opposed		:= AIR;
			break;

		AIR:	complementary 	:= FIRE;
			opposed		:= EARTH;
			break;

		EARTH:	complementary 	:= AIR;
			opposed		:= WATER;
			break;

		WATER:	complementary 	:= EARTH;
			opposed		:= FIRE;
			break;
	endcase

	var eprot := GetProtLevel( cast_on, element );
	var cprot := GetProtLevel( cast_on, complementary );
	var oprot := GetProtLevel( cast_on, opposed );

	if( oprot < 0 )
		oprot := 6 - oprot;
	endif

	var resultprot := eprot + CInt(cprot / 2) -  CInt(oprot / 2);

	return resultprot;

endfunction


function GetResultingPlaneProtection( cast_on, plane )

	var opposed;
	if( plane == NECRO )
		opposed := HOLY;
	elseif( plane == HOLY )
		opposed := NECRO;
	else
		return 0;
	endif

	var planeprot := GetProtLevel( cast_on, plane );
	var opposedprot := GetProtLevel( cast_on, opposed );

	if( opposedprot < 0 )
		opposedprot := 6 - opposedprot;
	endif

	var resultingprot := planeprot - opposedprot;

	return resultingprot;

endfunction


function GetScript( spellid )

	var spellcfg := ReadConfigFile( ":*:spells" );
	var script := spellcfg[spellid].script;
	if( spellid <= MAX_NORMAL_SPELL )
		script := ":spells:" + script;
	elseif( spellid <= MAX_NECRO_SPELL )
		script := ":necro:" + script;
	elseif( spellid <= MAX_EARTH_SPELL )
		script := ":earth:" + script;
	elseif( spellid <= MAX_RITUAL_SPELL )
		script := ":artificier:" + script;
	endif

	return script;

endfunction


function IsProtected( caster, cast_on, circle )

	var protserial := GetObjProperty( cast_on, "MagicImmunity" );
	var protlvl	 := Cint(GetObjProperty( cast_on, "PermMagicImmunity" ));
	if( !protlvl )
		protlvl := 0;
	endif

	circle := circle * ClasseBonus( cast_on, CLASSEID_WARRIOR );

	var cmi := 0 - protlvl;
	var item;
	var charges;
	var cursed;

	if( protserial )
		foreach thing in ListEquippedItems( cast_on )
			if( thing.serial == protserial )
				item := thing;
				charges := CInt( GetObjProperty( item, "MagicImmunity" ) );
				cursed := GetObjProperty( item, "Cursed" );
				if( !charges )
					EraseObjProperty( cast_on, "MagicImmunity" );
					EraseObjProperty( item, "MagicImmunity" );
					PrintTextAbovePrivate(item, CStr(item.desc + " is out of charges!"), cast_on );
					CheckForAnotherProtItem( cast_on, item, "MagicImmunity" );
				endif
				break;
			endif
		endforeach
	endif

	if( charges >= circle )
		charges := charges - circle;
		SetObjProperty( item, "MagicImmunity", charges );
		if( !cursed )
			PrintTextAbovePrivate( cast_on, CStr("Your " + item.desc + " protected you from the spell!"), cast_on );
			return IMMUNED;
		else
			return CURSED;
		endif

	elseif( cmi >= circle )
		return CURSED;

	elseif( protlvl >= circle )
		PrintTextAbovePrivate( cast_on, CStr(caster.name + "'s spell is absorbed by your magical protection!"), cast_on );
		PrintTextAbovePrivate( cast_on, CStr("The spell dissipates upon contact with " + cast_on.name + "'s magical barrier!"), caster );
		return IMMUNED;
	endif

	return 0;

endfunction


function ModifyWithMagicEfficiency( who, val )

	if( GetObjProperty( who, CLASSEID_MAGE ) )
		val := CInt(val * ClasseBonus( who, CLASSEID_MAGE ));
	elseif( GetObjProperty( who, CLASSEID_WARRIOR ) )
		val := CInt(val / ClasseBonus( who, CLASSEID_WARRIOR ));
	endif

	var penalty := CInt( GetMagicEfficiencyPenalty( who ) );
	if( penalty >= 100 )
		return 0;
	endif

	return CInt( val * ( 100 - penalty ) / 100 );

endfunction


function PolymorphMobile( cast_on, new_form, new_color, duration, mod := 0 )

	var parms := {};

	parms[1] := cast_on;
	parms[2] := CInt( new_form );
	parms[3] := CInt( new_color );
	parms[4] := CInt( duration );
	if( mod )
		parms[5] := mod;
	endif

	start_script( ":summoning:polymorphing", parms );

endfunction


function Reflect( source, targ )

	if(source.dead) return; endif
	if(targ.dead) return; endif

	PlaySoundEffect( source, SFX_SPELL_MAGIC_REFLECTION );
	PlayObjectCenteredEffect( source, FX_SPELL_MAGIC_REFLECTION, SPEED_SPELL_MAGIC_REFLECTION, LOOP_SPELL_MAGIC_REFLECTION );
	SendSysMessage( source, "Your magic reflect spell saved you!" );
        if( SPELL_EFFECT_TYPE_MOVING == 1 )
        	sleep( 1 );
        	PlayMovingEffect(source,
				 targ,
				 SPELL_EFFECT_ID,
				 SPELL_EFFECT_SPEED,
				 SPELL_EFFECT_LOOP,
				 explode := 0);
	endif

endfunction


function Reflected( caster, cast_on, circle )

	var source	:= caster;
	var targ	:= cast_on;
	var wasreflected;

        if( SPELL_EFFECT_TYPE_MOVING == 1 )
        	PlayMovingEffect(source,
				 targ,
				 SPELL_EFFECT_ID,
				 SPELL_EFFECT_SPEED,
				 SPELL_EFFECT_LOOP,
				 explode := 0);
	endif

	if( source == targ )
		if( !SPELL_EFFECT_TYPE_MOVING && SPELL_EFFECT_ID )
			PlayObjectCenteredEffect(targ,
						 SPELL_EFFECT_ID,
						 SPELL_EFFECT_SPEED,
						 SPELL_EFFECT_LOOP);

		elseif( SPELL_EFFECT_TYPE_MOVING == 2 )
			PlayLightningBoltEffect( targ );
			PlaySoundEffect( targ, SFX_SPELL_LIGHTNING );

		elseif( SPELL_EFFECT_TYPE_MOVING == 3 )
			PlayLightningBoltEffect( targ );
			PlaySoundEffect( targ, SFX_SPELL_CALL_LIGHTNING );
			PlayLightningBoltEffect( targ );
			PlaySoundEffect( targ, SFX_SPELL_CALL_LIGHTNING );

		elseif( SPELL_EFFECT_TYPE_MOVING == 4 )
			PlayStationaryEffect( targ.x, targ.y, targ.z, SPELL_EFFECT_ID, SPELL_EFFECT_SPEED, SPELL_EFFECT_LOOP );

		endif

		return targ;
	endif

	var permmr   := CInt( GetObjProperty( targ, "Permmr" ) );
	var corrupmr := CInt( 0 - permmr );
	var protserial := CInt( GetObjProperty( targ, "SpellReflect") );
	var item;
	var cursed;
	var charges;
	if( protserial )
		set_critical(1);
		foreach thing in ListEquippedItems( targ )
			if( thing.serial == protserial )
				item := thing;
				cursed  := GetObjProperty( item, "Cursed" );
				charges := CInt( GetObjProperty( item, "SpellReflect" ) );
				if( !charges )
					EraseObjProperty( item, "SpellReflect" );
					EraseObjProperty( targ, "SpellReflect" );
					PrintTextAbovePrivate( item, CStr(item.desc + " is out of charges!"), targ );
					CheckForAnotherProtItem( targ, item, "SpellReflect" );
				endif
				break;
			endif
		endforeach
		set_critical(0);
	endif


	if( charges && charges >= circle )
		charges := CInt(charges - circle);
		SetObjProperty( item, "SpellReflect", charges );
		if( !cursed )
			PrintTextAbovePrivate( targ, CStr("Your " + item.desc + " reflected the spell!"), targ );
			source := cast_on;
			targ := caster;
			Reflect( source, targ );
			//ReflectBack( caster, cast_on, source, targ, circle );
		else
			PrintTextAbovePrivate( targ, CStr("Your " + item.desc + " prevent all reflections!"), targ );
		endif

	elseif( corrupmr >= circle )
		PrintTextAbovePrivate( targ, CStr("One of your item prevent all reflections!"), targ );

	elseif( CInt(GetObjProperty( targ, "mr" )) >= circle )
		EraseObjProperty(targ, "mr");
		source := cast_on;
		targ := caster;
		Reflect( source, targ );
		//ReflectBack( caster, cast_on, source, targ, circle );

	elseif( permmr >= circle )
		source := cast_on;
		targ := caster;
		Reflect( source, targ );
		//ReflectBack( caster, cast_on, source, targ, circle );
	endif


	if( targ == caster )
		SendSysMessage( caster, "The spell is reflected back to you!" );
	endif

	if( !SPELL_EFFECT_TYPE_MOVING && SPELL_EFFECT_ID )
		PlayObjectCenteredEffect(targ,
					 SPELL_EFFECT_ID,
					 SPELL_EFFECT_SPEED,
					 SPELL_EFFECT_LOOP);

        elseif( SPELL_EFFECT_TYPE_MOVING == 2 )
		PlayLightningBoltEffect( targ );
		PlaySoundEffect( targ, SFX_SPELL_LIGHTNING );

	elseif( SPELL_EFFECT_TYPE_MOVING == 3 )
		PlayLightningBoltEffect( targ );
		PlaySoundEffect( targ, SFX_SPELL_CALL_LIGHTNING );
		PlayLightningBoltEffect( targ );
		PlaySoundEffect( targ, SFX_SPELL_CALL_LIGHTNING );

	elseif( SPELL_EFFECT_TYPE_MOVING == 4 )
		PlayStationaryEffect( targ.x, targ.y, targ.z, SPELL_EFFECT_ID, SPELL_EFFECT_SPEED, SPELL_EFFECT_LOOP );

	endif

	return targ;

endfunction


function Resisted( caster, cast_on, circle, dmg )

	if( cast_on.dead ) return 0; endif
	if(caster.dead) return 0; endif

	var multiplier;
	var points 	:= circle * 40;
	var magery 	:= GetAttribute( caster, ATTRIBUTEID_MAGERY );
	var evalint 	:= GetAttribute( caster, ATTRIBUTEID_EVALINT );
	var resist 	:= GetAttribute( cast_on, ATTRIBUTEID_MAGICRESISTANCE );
	var chance 	:= CInt( resist / 6);
	var chance2 	:= CInt( resist - ((magery / 4) + (circle * 6)) );

	if( chance2 > chance )
		chance := chance2;
	endif

	if( GetObjProperty( cast_on, CLASSEID_MAGE ) )
		chance := CInt( chance * ClasseBonus( cast_on, CLASSEID_MAGE ) );
	elseif( GetObjProperty( cast_on, CLASSEID_WARRIOR ) )
		var bonus := ClasseBonus( cast_on, CLASSEID_WARRIOR );
		chance := CInt( chance / bonus / 2 );
		resist := CInt( resist / bonus );
	endif

	if( GetObjProperty( caster, CLASSEID_MAGE ) )
		chance := CInt( chance / ClasseBonus( caster, CLASSEID_MAGE ) );
	elseif( GetObjProperty( caster, CLASSEID_WARRIOR ) )
		var bonus := ClasseBonus( caster, CLASSEID_WARRIOR );
		chance := CInt( chance * bonus * 2 );
		resist := CInt( resist * bonus );
	endif

	if( resist < 25 )
		AwardPoints( cast_on, SKILLID_MAGICRESISTANCE, CInt( points / 3 ) );
	endif

	if( random(100)+1 <= chance )
		SendSysMessage( cast_on, "You feel yourself resisting magical energy!" );
		PlaySoundEffect( cast_on, SFX_SPELL_WEAKEN );
		PlayObjectCenteredEffect( cast_on, FX_SPELL_CURSE, 5, 5 );
		dmg := CInt( dmg / 2 );
		if( dmg < 1 )
			dmg := 1;
		endif
	
		if( !caster.multi && !cast_on.multi )
			AwardPoints( cast_on, SKILLID_MAGICRESISTANCE, points );
		endif
	endif

	dmg := CInt( dmg * (1 + (evalint - resist) / 200) );

	if( GetObjProperty( cast_on, CLASSEID_MAGE ) )
		dmg := CInt( dmg / ClasseBonus( cast_on, CLASSEID_MAGE ) );
	elseif( GetObjProperty( cast_on, CLASSEID_WARRIOR ) )
		dmg := CInt( dmg * ClasseBonus( cast_on, CLASSEID_WARRIOR ) );
	endif

	if( dmg < 0 )
		dmg := 0;
	endif

	return dmg;

endfunction


function ResistedDefinedSkillGain( caster, cast_on, dmg, diff, points := 0 )

	if( cast_on.dead ) return 0; endif
	if(caster.dead) return 0; endif

	var evalint;
	if( caster )
		evalint := GetAttribute( caster, ATTRIBUTEID_EVALINT );
	endif

	if( !evalint )
		evalint := 0;
	endif

	var resist	:= GetAttribute( cast_on, ATTRIBUTEID_MAGICRESISTANCE );

	if( CheckSkill( cast_on, SKILLID_MAGICRESISTANCE, diff, points ) )
		dmg := CInt( dmg / 2 );
		if( dmg < 1 )
			dmg := 1;
		endif
	endif

	dmg := CInt( dmg * (1 + (evalint - resist) / 200) );

	if( GetObjProperty( cast_on, CLASSEID_MAGE ) )
		dmg := CInt( dmg / ClasseBonus( cast_on, CLASSEID_MAGE ) );
	elseif( GetObjProperty( cast_on, CLASSEID_WARRIOR ) )
		dmg := CInt( dmg * ClasseBonus( cast_on, CLASSEID_WARRIOR ) );
	endif

	if( dmg < 0 )
		dmg := 0;
	endif

	return dmg;

endfunction


function Send_Attack( ttarget, source, spellid := 0 )

	var ev := array;
	ev.+type;
	ev.+source;

	ev.type := SYSEVENT_ENGAGED;
	ev.source := source;
	SendEvent( ttarget, ev );

 	if (spellid)
         	ev.+spell;
         	ev.type := 0x0800; //spell attack
         	ev.spell := spellid;
         	SendEvent(ttarget, ev);
 	endif

endfunction


function SummonCreature( caster, npctemplate, cast_loc, sfx := 0x0218, delay := 0 )

	If (!GetObjProperty( caster, "PeaceKeeper") )
		if( NoPKArea(caster) )
			return 0;
		endif
	endif

	var parms := {};

	parms[1] := caster;
	parms[2] := npctemplate;
	parms[3] := cast_loc;
	parms[4] := sfx;
	parms[5] := delay;

	start_script( ":summoning:summoning", parms );

endfunction


function TruncPkgName( name )

	if( name[1] == ":" )
		var i;
		for( i := 2; i <= len(name); i := i + 1 )
			if( name[i] == ":" )
				break;
			endif
		endfor

		return name[i+1,len(name)];

	else
		return name;
	endif

endfunction


function TryToCast( caster, spell, anim := ANIM_CAST_DIR )


	if( !caster.cmdlevel )
		if( IsInAntiMagicArea( caster ) )
			SendSysMessage( caster, ERROR_MSG_ANTI_MAGIC_AREA );
			return IN_ANTIMAGIC_AREA;
		endif
	endif



	//Variables declaration and initialisation
	var conf	 := ReadConfigFile( ":*:spells" );
	var elem	 := FindConfigElem( conf, spell );
	var circ	 := GetConfigInt( elem, "Circle" );
	conf	 	 := ReadConfigFile( ":*:circles" );
	var spelldelay := CInt( conf[circ].Delay );
	var value	 := CInt( conf[circ].PointValue );
	var manacost	 := CInt( conf[circ].mana );
	var difficulty := CInt( conf[circ].Difficulty );

	//Casting Options management
	var options := GetObjProperty( caster, CASTINGOPT_PROP_NAME );
	if( !options )
		options := GetObjProperty( caster, PERM_CASTINGOPT_PROP_NAME );
		if( !options )
			options := "";
		endif
	else
		EraseObjProperty( caster, CASTINGOPT_PROP_NAME );
	endif

	//Try to cast the spell
	PerformAction( caster, anim );

	//Speak the power words
	if ( !FindOption( options, CASTINGOPT_NO_WORDS ) )
                SpeakPowerWords( caster, spell );
	endif

	//Check for the equipment in hands
	if( !FindOption( options, CASTINGOPT_ANY_EQUIPMENT ) )

		var hand1	:= GetEquipmentByLayer( caster, LAYER_HAND1 );
		var hand2	:= GetEquipmentByLayer( caster, LAYER_HAND2 );

		if( hand1 || hand2 )
			var weapcfg := ReadConfigFile( ":*:itemdesc" );

			if( hand1 && weapcfg[hand1.objtype].BlocksCastingIfInHand != 0 )
				SendSysMessage( caster, ERROR_MSG_WRONG_EQUIPMENT );
				PlayObjectCenteredEffect( caster, FX_SPELL_FIZZLE, SPEED_SPELL_FIZZLE, LOOP_SPELL_FIZZLE );
				PlaySoundEffect( caster, SFX_SPELL_FIZZLE );
				return INVALID_EQUIPMENT;
			endif

			if( hand2 && weapcfg[hand2.objtype].BlocksCastingIfInHand != 0)
				SendSysMessage( caster, ERROR_MSG_WRONG_EQUIPMENT );
				PlayObjectCenteredEffect( caster, FX_SPELL_FIZZLE, SPEED_SPELL_FIZZLE, LOOP_SPELL_FIZZLE );
				PlaySoundEffect( caster, SFX_SPELL_FIZZLE );
				return INVALID_EQUIPMENT;
			endif
		endif
	endif

	//Delay and interruption management
	if( !FindOption( options, CASTINGOPT_NO_DELAY ) )
		var shp := GetHp(caster);
		var sx := caster.x;
		var sy := caster.y;
		var sz := caster.z;

		//True mages cast faster
		if( GetObjProperty( caster, CLASSEID_MAGE ) )
			spelldelay := CInt( spelldelay / ClasseBonus( caster, CLASSEID_MAGE ) );
		elseif( GetObjProperty( caster, CLASSEID_WARRIOR ) )
			spelldelay := CInt( spelldelay * ClasseBonus( caster, CLASSEID_WARRIOR ) );
		endif

		while( spelldelay >= 500 )
			sleepms( 500 );
			spelldelay := spelldelay - 500;
			if( GetHp(caster) < shp )
				SendSysMessage( caster, ERROR_MSG_INTERRUPTED );
				PlayObjectCenteredEffect(caster, FX_SPELL_FIZZLE, SPEED_SPELL_FIZZLE, LOOP_SPELL_FIZZLE );
				PlaySoundEffect(caster, SFX_SPELL_FIZZLE);
				return INTERRUPTED;
			endif

			if( caster.x != sx || caster.y != sy || caster.z != sz )
				SendSysMessage( caster, ERROR_MSG_LOST_CONCENTRATION );
				PlayObjectCenteredEffect(caster, FX_SPELL_FIZZLE, SPEED_SPELL_FIZZLE, LOOP_SPELL_FIZZLE );
				PlaySoundEffect(caster, SFX_SPELL_FIZZLE);
				return INTERRUPTED;
			endif
		endwhile

		sleepms( spelldelay );

		if( GetHp(caster) < shp )
			SendSysMessage( caster, ERROR_MSG_INTERRUPTED );
			PlayObjectCenteredEffect(caster, FX_SPELL_FIZZLE, SPEED_SPELL_FIZZLE, LOOP_SPELL_FIZZLE );
			PlaySoundEffect(caster, SFX_SPELL_FIZZLE);
			return INTERRUPTED;
		endif

		if( caster.x != sx || caster.y != sy || caster.z != sz )
			SendSysMessage( caster, ERROR_MSG_LOST_CONCENTRATION );
			PlayObjectCenteredEffect(caster, FX_SPELL_FIZZLE, SPEED_SPELL_FIZZLE, LOOP_SPELL_FIZZLE );
			PlaySoundEffect(caster, SFX_SPELL_FIZZLE);
			return INTERRUPTED;
		endif
	endif

	//Consume the reagents
	if( !FindOption( options, CASTINGOPT_NO_REAGENTS ) )
                if( !ConsumeReagents( caster, spell ) )
			PlayObjectCenteredEffect(caster, FX_SPELL_FIZZLE, SPEED_SPELL_FIZZLE, LOOP_SPELL_FIZZLE );
			PlaySoundEffect(caster, SFX_SPELL_FIZZLE);
			SendSysMessage( caster, ERROR_MSG_NOT_ENOUGH_REAGENTS );
			return NO_REGS;
		endif
	endif

	//Consume the mana
	if( !FindOption( options, CASTINGOPT_NO_MANA ) )
                if( !ConsumeMana( caster, spell ) )
			PlayObjectCenteredEffect(caster, FX_SPELL_FIZZLE, SPEED_SPELL_FIZZLE, LOOP_SPELL_FIZZLE);
			PlaySoundEffect(caster, SFX_SPELL_FIZZLE);
			SendSysMessage( caster, ERROR_MSG_NOT_ENOUGH_MANA );
			return NO_MANA;
		endif
	endif

	//Do the skill check and return mana if failure occur
	if( !FindOption( options, CASTINGOPT_NO_SKILL_CHECK ) )
        	if( !CheckSkill( caster, SKILLID_MAGERY, difficulty, value ) )
			SetMana(caster, GetMana(caster) + manacost);
			if( GetMana(caster) > GetMaxMana(caster) )
				SetMana(caster, GetMaxMana(caster));
			endif
			PlayObjectCenteredEffect(caster, FX_SPELL_FIZZLE, SPEED_SPELL_FIZZLE, LOOP_SPELL_FIZZLE );
			PlaySoundEffect( caster, SFX_SPELL_FIZZLE );
			SendSysMessage( caster, ERROR_MSG_FIZZLE );
			return NO_SKILL;
		endif
	endif

	return SUCCESS;

endfunction
