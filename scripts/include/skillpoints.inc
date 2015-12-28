//Edited by Sno 17/1/03. Replaced some RawSkill functions with their base skill counterparts. Also uncommented the skill arrows/locking.
//Currently it's checking if _base_ skill is going over 165. Should it be looking if raw skill is going over raw(165) ?

use uo;
use os;
use util;
use basic;
use cfgfile;

include "include/classes";
//include "include/attributes";


const SKILL_CAP := 130;

function get_default_points(skillid)
        var cfg := ReadConfigFile("skills");

        var default_points := cfg[skillid].default_points;
       
        if (!default_points)
                return 0;
        else
                return default_points;

        endif

endfunction


function AwardSkillPoints( who, skillid, points )

	if( who.IsA(POLCLASS_NPC) )
		return 0;
	elseif( who.cmdlevel )
		return 0;
	endif

	// START MODIFYING 'points'

	var skills_state_array   := GetObjProperty( who, "SkillsState" );
	if( !skills_state_array )
		skills_state_array := array;
	endif
	
	var skill_state := skills_state_array[skillid+1];
	if( skill_state == "d" )
		var baseskill := GetBaseSkill( who, skillid );
		var amount   := 1;
		if( amount > baseskill )
			amount := baseskill;
			skills_state_array[skillid+1] := "l";
			SetObjProperty( who, "SkillsState", skills_state_array );
		endif
		SetBaseSkill( who, skillid, Cint(baseskill - amount) );
		return;
		
	elseif( skill_state == "l" )
		return;
	endif
	
	points := Cint( points * GetSkillPointsMultiplier( who , skillid ) );
	var special_multipliers := GetObjProperty( who, "SkillMultipliers" );
	if( len(special_multipliers) )
		if( special_multipliers[skillid+1] )
			if( Cint(special_multipliers[skillid+1]) == 9999 )
				points := 0;
			else
				var skill_mult := Cdbl( special_multipliers[skillid+1] );
				points := Cint( points * skill_mult );
			endif
		endif
	endif
	
	var global_multipliers := GetGlobalProperty( "SkillPointsMultiplier" );
	if( len(global_multipliers) )
		if( global_multipliers[skillid+1] )
			if( Cint(global_multipliers[skillid+1]) == 9999 )
				points := 0;
			else
				var mult := Cdbl( global_multipliers[skillid+1] );
				points := Cint( points * mult );
			endif
		endif
	endif

	// FINISHED MODIFYING 'points'

	if( points > 0 )
			var current := GetBaseSkill(who, skillid);
			var basepoints := RawSkillToBaseSkill(points); // Edited by Sno 17/1/03
			var skilllevel;

			if( (current+basepoints) <= SKILL_CAP )
				AwardRawSkillPoints(who, skillid, points);
			endif

			skilllevel := GetBaseSkill(who, skillid);
			if( skilllevel > 130)
				SetBaseSkill(who, skillid, 130);
			endif
			


	endif

	/* HERE STARTS OLD VERSION. Just left it commented out in case something goes wrong.
	var skills_state_array   := GetObjProperty( who, "SkillsState" );
	if( !skills_state_array )
		skills_state_array := array;
	endif
	
	var skill_state := skills_state_array[skillid+1];
	if( skill_state = "d" )
		var rawskill := GetRawSkill( who, skillid );
		var amount   := 10000;
		if( amount > rawskill )
			amount := rawskill;
			skills_state_array[skillid+1] := "l";
			SetObjProperty( who, "SkillsState", skills_state_array );
		endif
		SetRawSkill( who, skillid, Cint(rawskill - amount) );
		return;
		
	elseif( skill_state = "l" )
		return;
	endif
	
	points := Cint( points * GetSkillPointsMultiplier( who , skillid ) );
	var special_multipliers := GetObjProperty( who, "SkillMultipliers" );
	if( len(special_multipliers) )
		if( special_multipliers[skillid+1] )
			if( Cint(special_multipliers[skillid+1]) = 9999 )
				points := 0;
			else
				var skill_mult := Cdbl( special_multipliers[skillid+1] );
				points := Cint( points * skill_mult );
			endif
		endif
	endif
	
	var global_multipliers := GetGlobalProperty( "SkillPointsMultiplier" );
	if( len(global_multipliers) )
		if( global_multipliers[skillid+1] )
			if( Cint(global_multipliers[skillid+1]) = 9999 )
				points := 0;
			else
				var mult := Cdbl( global_multipliers[skillid+1] );
				points := Cint( points * mult );
			endif
		endif
	endif
	
	if( points > 0 )
	//	var cfg := ReadConfigFile( ":shilhook:skillcap" );
	//	var cap := Cdbl( cfg[skillid].Cap );
	//	if( !cap or GetObjProperty( who, "CapOff" ) )
	//		AwardRawPoints( who, skillid, points );
	//	else
	//		var raw_cap	:= BaseSkillToRawSkill( Cint(cap * 10.0) );
	//		var raw_skill	:= GetRawSkill( who, skillid );
	//		if( Cint(raw_skill + points) <= raw_cap )
				AwardRawPoints( who, skillid, points );
	//		else
	//			
	//			foreach item in ListEquippedItems( who )
	//				if( GetObjProperty( item , "skilladv" ) = skillid )
	//					raw_cap := raw_cap + Cint(GetObjProperty( who, "advamount" + skillid + "s" + item.serial ));
	//				endif
	//			endforeach
				
	//			if( raw_cap < 0 )
	//				raw_cap := 0;
	//			endif
				
	//			if( Cint(raw_skill + points) < raw_cap )
	//				AwardRawPoints( who, skillid, points );
	//			else
	//				SetRawSkill( who, skillid, Cint(raw_cap) );
	//			endif
	//		endif
	//	endif
	endif
	*/
endfunction


function AwardStatPoints( who, skillid ) //I found out that the core still allow the stat points so this will help the load

	var skill_cfg	:= ReadConfigFile( ":*:skills" );
	var str_adv	:= skill_cfg[skillid].StrAdv;
	var dex_adv	:= skill_cfg[skillid].DexAdv;
	var int_adv	:= skill_cfg[skillid].IntAdv;
	var base_str	:= GetStrength(who) - GetStrengthMod(who);
	var base_dex	:= GetDexterity(who) - GetDexterityMod(who);
	var base_int	:= GetIntelligence(who) - GetIntelligenceMod(who);
	var raw_str;
	var raw_dex;
	var raw_int;

	var stat_array := GetObjProperty( who, "StatsState" );
	if( !stat_array )
		raw_str	:= BaseSkillToRawSkill( CInt(base_str * 10) );
		raw_dex	:= BaseSkillToRawSkill( CInt(base_dex * 10) );
		raw_int	:= BaseSkillToRawSkill( CInt(base_int * 10) );
	else
		raw_str := CInt( stat_array[1] );
		if( !raw_str )
			raw_str	:= BaseSkillToRawSkill( CInt(base_str * 10) );
		endif
	
		raw_dex := CInt( stat_array[2] );
		if( !raw_dex )
			raw_dex	:= BaseSkillToRawSkill( CInt(base_dex * 10) );
		endif
	
		raw_int := CInt( stat_array[3] );
		if( !raw_int )
			raw_int	:= BaseSkillToRawSkill( CInt(base_int * 10) );
		endif
	endif

	if( str_adv )
		AwardStrengthPoints( who, str_adv, base_str, raw_str );
	endif

	if( dex_adv )
		AwardDexterityPoints( who, dex_adv, base_dex, raw_dex );
	endif

	if( int_adv )
		AwardIntelligencePoints( who, int_adv, base_int, raw_int );
	endif

	stat_array := array( CInt(raw_str), CInt(raw_dex), CInt(raw_int) );
	SetObjProperty( who, "StatsState", stat_array );

endfunction


function AwardStrengthPoints( who, str_adv, base_str, byref raw_str )

	if( raw_str >= 1073741825 )
		if( !GetObjProperty( who, "CapOff" ) )
			raw_str := 33554433;
			if( base_str > 130 )
				SetBaseStrength(who,130);
			endif
			return;
		endif
	endif

	var str_split  := SplitWords( str_adv );
	var str_chance := CInt( str_split[1] );
	
	if( RandomInt(100) < str_chance )
		var str_amount	:= RandomDiceRoll( str_split[2] );
		raw_str		:= raw_str + str_amount;
		var new_strength := CInt(RawSkillToBaseSkill( raw_str ) / 10 );
		if( new_strength > base_str )
			SetBaseStrength(who, new_strength );
		endif
	endif

endfunction


function AwardDexterityPoints( who, dex_adv, base_dex, byref raw_dex )

	if( raw_dex >= 1073741825 )
		if( !GetObjProperty( who, "CapOff" ) )
			raw_dex := 33554433;
			if( base_dex > 130 )
				SetBaseDexterity(who,130);
			endif
			return;
		endif
	endif

	var dex_split  := SplitWords( dex_adv );
	var dex_chance := CInt( dex_split[1] );

	if( RandomInt(100) < dex_chance )
		var dex_amount := RandomDiceStr( dex_split[2] ) ;
		raw_dex := raw_dex + dex_amount;
		var new_dexterity := CInt(RawSkillToBaseSkill( raw_dex ) / 10);
		if( new_dexterity > base_dex )
			SetBaseDexterity(who, new_dexterity );
		endif
	endif

endfunction


function AwardIntelligencePoints( who, int_adv, base_int, byref raw_int )

	if( raw_int >= 1073741825 )
		if( !GetObjProperty( who, "CapOff" ) )
			raw_int := 33554433;
			if( base_int > 130 )
				SetBaseIntelligence(who,130);
			endif
			return;
		endif
	endif

	var int_split  := SplitWords( int_adv );
	var int_chance := CInt( int_split[1] );

	if( RandomInt(100) < int_chance )
		var int_amount := RandomDiceStr( int_split[2] );
		raw_int := raw_int + int_amount;
		var new_intelligence := CInt(RawSkillToBaseSkill( raw_int ) / 10 );
		if( new_intelligence > base_int )
			SetBaseIntelligence(who, new_intelligence );
		endif
	endif

endfunction
