// HitScript Include

use uo;
use util;

include "include/client";
include "include/dotempmods";
include "include/classes";
include "include/damages";
include "include/areas";
include "include/bitwise";
include "include/random";
include "include/attributes";


function RecalcDmg( attacker, defender, weapon, armor, byref basedamage, piercing := 0 )

	if( attacker == defender )

		var times := CInt( GetObjProperty( attacker , "#AttackedSelf" ) );

		if( times > 3 )
			SendSysMessage( attacker , "The god won't tolerate such a foolishness..." );
			PlayLightningBoltEffect( attacker );
			ApplyRawDamage( attacker , GetHp(attacker) );
			return 0;
		elseif( times )
			times := times+1;
			SetObjProperty( attacker , "#AttackedSelf" , times);
			SendSysMessage( attacker , "The god won't tolerate such a foolishness..." );
			PlayLightningBoltEffect( attacker );
		else
			SetObjProperty( attacker , "#AttackedSelf" , 1 );
			SendSysMessage( attacker , "The god won't tolerate such a foolishness..." );
			PlayLightningBoltEffect( attacker );
		endif

	endif

	If (!GetObjProperty( attacker, "PeaceKeeper") )
		if( NoPKArea(defender) )
			return 0;
		endif
	endif
	if( !GetObjProperty( weapon, "Astral" ) )
		return RecalcPhysicalDmg( attacker , defender , weapon , armor , basedamage , piercing );
	else
		return RecalcAstralDmg( attacker , defender , weapon , armor , basedamage , piercing );
	endif

endfunction


function RecalcPhysicalDmg( attacker, defender, weapon, armor, byref basedamage, piercing := 0 )

	var rawdamage;
	var absorbed;
	var ar := CInt(armor.ar) + CInt(defender.ar_mod);
	var anatomy := GetEffectiveskill( attacker , ATTRIBUTEID_ANATOMY );

	If (!GetObjProperty( attacker, "PeaceKeeper") )
		if( NoPKArea(defender) )
			return 0;
		endif
	endif

	if( defender.npctemplate )
		if( !attacker.npctemplate )
			basedamage := basedamage * 1.5;
		endif
	endif

	basedamage := ModByDist( attacker , defender , weapon , basedamage );
	basedamage := basedamage * ( 1 + anatomy * 0.002 );

	if( !piercing )
		rawdamage := GetShieldAbsorption( attacker , defender , weapon , basedamage );
		absorbed  := ar * (Random(51) + 50) * 0.01;
	else
		rawdamage := basedamage;
		absorbed  := 0;
	endif

	rawdamage := rawdamage - absorbed;
	rawdamage := rawdamage * 0.5;
	rawdamage := ModByProt( defender , rawdamage );

	if( rawdamage < 0 )
		rawdamage := 0;
	endif

	MaceHit( attacker , defender , weapon , armor , absorbed );
//	CheckForTheSkillGain( attacker , defender , weapon );

	return CInt( rawdamage );

endfunction


function RecalcAstralDmg( attacker, defender, weapon, armor, byref basedamage, piercing := 0 )

	var rawdamage;
	var absorbed := 0;


	If (!GetObjProperty( attacker, "PeaceKeeper") )
		if( NoPKArea(defender) )
			return 0;
		endif
	endif

	var ar := CInt( GetObjProperty( armor , "Astral" ) ) * 25 * CInt( armor.ar );

	basedamage := basedamage
		* ((GetEffectiveSkill( attacker , ATTRIBUTEID_SPIRITSPEAK ) + 50.0 + (GetIntelligence(attacker)* 0.2)) * 0.01)
		/ ((GetEffectiveSkill( attacker , ATTRIBUTEID_TACTICS ) + 50.0 + (GetStrength(attacker) * 0.2)) * 0.01);

	AwardRawSkillPoints( attacker, ATTRIBUTEID_EVALINT, 30 );
	AwardRawSkillPoints( attacker, ATTRIBUTEID_SPIRITSPEAK, 30 );

	if( defender.npctemplate )
		basedamage := basedamage * ClasseBonus( attacker , CLASSEID_MAGE );
	else
		var level := GetObjProperty( attacker , CLASSEID_MAGE );
		if( level )
			level := level - 2;
			if( level >= 1 )
				basedamage := basedamage * ClasseBonusByLevel( level );
			endif
		endif
	endif

	if( GetObjProperty( attacker , CLASSEID_WARRIOR ) )
		if( !GetObjProperty( attacker , CLASSEID_MAGE ) )
			basedamage := basedamage / ClasseBonus( attacker , CLASSEID_WARRIOR );
		endif
	endif

	if( GetObjProperty( defender , CLASSEID_WARRIOR ) )
		if( !GetObjProperty( defender , CLASSEID_MAGE ) )
			basedamage := basedamage * ClasseBonus( defender , CLASSEID_WARRIOR );
		endif
	endif

	basedamage := basedamage * ( 1 + GetEffectiveSkill( attacker , ATTRIBUTEID_EVALINT ) * 0.002 );
	rawdamage  := basedamage;

	if( !piercing )

		var meditation := GetEffectiveSkill( defender , ATTRIBUTEID_MEDITATION );
		meditation := meditation * ClasseBonus( defender , CLASSEID_MAGE );

		if( (Random(100) + 1) <= CInt( meditation * 0.5 ) )

			var resist := GetEffectiveSkill( defender , ATTRIBUTEID_MAGICRESISTANCE );
			var defint := GetIntelligence(defender);

			AwardRawSkillPoints( defender, ATTRIBUTEID_MEDITATION, 30 );
			AwardRawSkillPoints( defender, ATTRIBUTEID_MAGICRESISTANCE, 30 );
			PerformAction(  defender, ANIM_CAST_AREA );
			SendSysmessage( defender, "You successfully block a part of the astral attack." );

			if( GetObjProperty( defender, CLASSEID_MAGE ) )
				rawdamage := rawdamage - (resist + defint) * 0.25 * ClasseBonus( defender , CLASSEID_MAGE );
			elseif( GetObjProperty( defender, CLASSEID_WARRIOR ) )
				rawdamage := rawdamage - (resist + defint) * 0.25 / ClasseBonus( defender , CLASSEID_WARRIOR );
			endif

			if( rawdamage < 0 )
				rawdamage := 0;
			endif

		endif

		if( ar )
			absorbed := CInt( ar * (Random(51) + 50) / 100 );
		endif

	endif

	rawdamage := rawdamage - absorbed;
	rawdamage := rawdamage * 0.5;
	if( rawdamage < 0 )
		rawdamage := 0;
	endif

//	CheckForTheSkillGain( attacker , defender , weapon );

	return CInt(rawdamage);

endfunction


function ModByDist( attacker, defender, weapon, basedamage )


	If (!GetObjProperty( attacker, "PeaceKeeper") )
		if( NoPKArea(defender) )
			return 0;
		endif
	endif

	if( weapon.attribute == ATTRIBUTEID_ARCHERY )
		basedamage := basedamage
			* ((GetDexterity(attacker) + 60.0) * 0.01)
			/ ((GetAttribute( attacker , SKILLID_TACTICS ) + 50.0 + (GetStrength(attacker) / 5.0)) * 0.01);
		basedamage := basedamage * 0.75;
		var dist := Distance( attacker , defender );
		if( (dist <= 1) or (dist > 10) )
			basedamage := basedamage * 0.25;
		endif
		if( !weapon.dmg_mod && defender.npctemplate)
			If(!GetObjProperty( weapon, "IsExceptional") )
				basedamage := basedamage*3;
				basedamage := basedamage * 1.75;
			endif
		endif

		basedamage := basedamage * ClasseBonus( attacker , CLASSEID_RANGER );

	else

		if( defender.npctemplate )
			basedamage := basedamage * ClasseBonus( attacker , CLASSEID_WARRIOR );
		else
			var level := GetObjProperty( attacker , CLASSEID_WARRIOR );
			if( level )
				level := level - 1;
				if( level >= 1 )
					basedamage := basedamage * ClasseBonusByLevel( level );
				endif
			endif
		endif

	endif

	if( GetObjProperty( attacker , CLASSEID_MAGE ) )
		if( !GetObjProperty( attacker , CLASSEID_WARRIOR ) )
			basedamage := basedamage / ClasseBonus( attacker , CLASSEID_MAGE );
		endif
	endif

	if( GetObjProperty( defender , CLASSEID_MAGE ) )
		if( !GetObjProperty( defender , CLASSEID_WARRIOR ) )
			basedamage := basedamage * ClasseBonus( defender , CLASSEID_MAGE );
		endif
	endif

	return basedamage;

endfunction


function MaceHit( attacker, defender, weapon, armor, absorbed )


	If (!GetObjProperty( attacker, "PeaceKeeper") )
		if( NoPKArea(defender) )
			return 0;
		endif
	endif

	var archance := 2;
	var weapchance := 2;

	if( weapon.attribute == ATTRIBUTEID_MACEFIGHTING )

		var loss := Random(2) + 1;
		if(loss > GetStamina(defender))
			SetStamina(defender, 0);
		else
			SetStamina( defender, (GetStamina(defender) - loss));
		endif

		if( armor.hp )
			if( Random(100) < 5 )
				armor.hp := armor.hp - 1;
			endif
		endif

	elseif( Random(100) < archance )

		if( armor.hp )
			armor.hp := armor.hp - 1;
		endif

	endif

	if( Random(100) < weapchance )
		if( weapon.hp )
			weapon.hp := weapon.hp - 1;
		endif
	endif

	if( armor.quality )
		if( (armor.hp > armor.maxhp) or (armor.hp < 1) )
			DestroyEquipment( defender, armor );
		endif
	endif

	if( weapon.quality )
		if( (weapon.hp > weapon.maxhp) or (weapon.hp < 1) )
			DestroyEquipment( attacker , weapon );
		endif
	endif

endfunction


function ModByProt( defender, basedamage )

	var physicalprot := GetObjProperty( defender , "PhysicalProtection" );
	if( !physicalprot )
		return basedamage;
	else
		basedamage := basedamage * ( 1 - physicalprot * 0.05 );
		return basedamage;
	endif

endfunction


function GetShieldAbsorption( attacker, defender, weapon, basedamage )

	var shield := GetEquipmentByLayer( defender , LAYER_HAND2 );
	var shieldar := CInt(shield.ar);
	if( shieldar )
		var parry_skill := GetEffectiveSkill( defender , ATTRIBUTEID_PARRY );
		parry_skill := CInt( parry_skill * ClasseBonus( attacker , CLASSEID_WARRIOR ) );

		if( (Random(100) + 1) <= CInt(parry_skill / 2.5) )
			var absorbed;

			PerformAction( defender , ANIM_ATTACK_XBOW );
			SendSysmessage( defender , "You successfully parry the attack." );

			if( weapon.attribute == ATTRIBUTEID_ARCHERY )
				absorbed := CInt(shieldar/1.2);
			else
				absorbed := CInt(shieldar / 2);
			endif

			basedamage := basedamage - absorbed;
			if( basedamage < 0 )
				basedamage := 0;
			endif

			MaceHit( attacker , defender , weapon , shield , absorbed );
		endif
	endif

	return basedamage;

endfunction


function DealDamage( attacker, defender, weapon, armor, basedamage, rawdamage )

	If (!GetObjProperty( attacker, "PeaceKeeper") )
		if( NoPKArea(defender) )
			return 0;
		endif
	endif

	
	if( attacker == defender )

		var times := CInt( GetObjProperty( attacker , "#AttackedSelf" ) );

		if( times > 3 )
			SendSysMessage( attacker , "The god won't tolerate such a foolishness..." );
			PlayLightningBoltEffect( attacker );
			ApplyRawDamage( attacker , GetHp(attacker) );
			return 0;
		elseif( times )
			times := times+1;
			SetObjProperty( attacker , "#AttackedSelf" , times);
			SendSysMessage( attacker , "The god won't tolerate such a foolishness..." );
			PlayLightningBoltEffect( attacker );
		else
			SetObjProperty( attacker , "#AttackedSelf" , 1 );
			SendSysMessage( attacker , "The god won't tolerate such a foolishness..." );
			PlayLightningBoltEffect( attacker );
		endif

	endif

	if( !GetObjProperty( weapon, "Astral" ) )

		var poisoned := GetObjProperty( weapon   , "SkillPoisoned" );
		var reactive := GetObjProperty( defender , "ReactiveArmor" );
		var onhit    := GetObjProperty( armor    , "OnHitScript" );

		//Check if the item was poisonned by someone
		if( poisoned )

			var plvl := CInt( poisoned / 3 );
			poisoned  := poisoned - 1;
			if( poisoned )
				SetObjProperty( weapon , "SkillPoisoned" , poisoned );
			else
				EraseObjProperty( weapon , "SkillPoisoned" );
			endif

			SetPoison( defender, plvl, "You have been poisoned by " + attacker.name + "." );

		endif

		if( GetObjProperty( defender , CLASSEID_WARRIOR ) )
			if( attacker.npctemplate )
				rawdamage := CInt( rawdamage / ClasseBonus( defender , CLASSEID_WARRIOR ) );
			else
				var level := GetObjProperty( defender , CLASSEID_WARRIOR );
				if( level )
					level := level - 1;
					if( level >= 1 )
						basedamage := CInt( basedamage * ClasseBonusByLevel( level ) );
					endif
				endif
			endif
		endif

		//Check if reactive armor spell is on
		if( reactive )
			start_script( ":combat:reactivearmoronhit" , { attacker, defender, basedamage, rawdamage, reactive} );
		endif

		//Check if the armor have an on hit script and launch it
		if( onhit )
			start_script( onhit , {attacker, defender, weapon, armor, basedamage, rawdamage} );
		else
			ApplyTheDamage( defender , attacker , rawdamage );
		endif

	else

		ApplyTheAstralDamage( defender , attacker , rawdamage );

	endif

endfunction


function DestroyEquipment( who, item )

	var cursed := GetObjProperty( item , "Cursed" );

	if( cursed )
		SetObjProperty( item , "Cursed" , 3 );
	endif

	if( who.backpack )
		MoveItemToContainer( item , who.backpack );
	endif

	if( who.npctemplate )
		if( item.attribute )
			PrintTextAbove( who , who.name + " seem exhausted and can barely hit anyones anymore!" );
		else
			PrintTextAbove( who , who.name + "'s defences has been penetrated making it easy to hit vital parts!" );
		endif
	endif

	DestroyItem( item );

endfunction


function CheckForTheSkillGain( attacker, defender, weapon )

	set_critical(1);

	if( !attacker.npctemplate )
		var weapon_attribute := weapon.attribute;
		var attacker_skills_state := GetObjProperty( attacker , "SkillsState" );
		if( !attacker_skills_state )
			attacker_skills_state := {};
		endif

		var attacker_tactics_state := attacker_skills_state[ATTRIBUTEID_TACTICS+1];
		var attacker_weapon_state := attacker_skills_state[weapon_attribute+1];
		var attacker_wrestling_state := attacker_skills_state[attribute_WRESTLING+1];

		if( attacker_tactics_state = "l" or attacker_tactics_state = "d" )
			RemoveSkillGain( attacker , ATTRIBUTEID_TACTICS , attacker_tactics_state );
		endif

		if( attacker_weapon_state = "l" or attacker_weapon_state = "d" )
			RemoveSkillGain( attacker , weapon_attribute , attacker_weapon_state );
		endif

		if( attacker_wrestling_state = "l" or attacker_wrestling_state = "d" )
			RemoveSkillGain( attacker , attribute_WRESTLING , attacker_wrestling_state );
		endif
	endif

	if( !defender.npctemplate )
		var defender_skills_state := GetObjProperty( defender , "SkillsState" );
		if( !defender_skills_state )
			defender_skills_state := {};
		endif

		var defender_wrestling_state	:= defender_skills_state[attribute_WRESTLING+1];
		var defender_swords_state	:= defender_skills_state[attribute_SWORDSMANSHIP+1];
		var defender_fencing_state	:= defender_skills_state[attribute_FENCING+1];
		var defender_mace_state	:= defender_skills_state[ATTRIBUTEID_MACEFIGHTING+1];
		var defender_archery_state	:= defender_skills_state[ATTRIBUTEID_ARCHERY+1];
		var defender_tactics_state	:= defender_skills_state[ATTRIBUTEID_TACTICS+1];
		var defender_parry_state	:= defender_skills_state[attribute_PARRY+1];

		if( defender_wrestling_state = "l" or defender_wrestling_state = "d" )
			RemoveSkillGain( defender , attribute_WRESTLING , defender_wrestling_state );
		endif

		if( defender_swords_state = "l" or defender_swords_state = "d" )
			RemoveSkillGain( defender , attribute_SWORDSMANSHIP , defender_swords_state );
		endif

		if( defender_fencing_state = "l" or defender_fencing_state = "d" )
			RemoveSkillGain( defender , attribute_FENCING , defender_fencing_state );
		endif

		if( defender_mace_state = "l" or defender_mace_state = "d" )
			RemoveSkillGain( defender , ATTRIBUTEID_MACEFIGHTING , defender_mace_state );
		endif

		if( defender_archery_state = "l" or defender_archery_state = "d" )
			RemoveSkillGain( defender , ATTRIBUTEID_ARCHERY , defender_archery_state );
		endif

		if( defender_tactics_state = "l" or defender_tactics_state = "d" )
			RemoveSkillGain( defender , ATTRIBUTEID_TACTICS , defender_tactics_state );
		endif

		if( defender_parry_state = "l" or defender_parry_state = "d" )
			RemoveSkillGain( defender , attribute_PARRY , defender_parry_state );
		endif
	endif

	set_critical(0);

endfunction


function RemoveSkillGain( who, attribute, state )

	set_critical(1);

	var combat_skills := {
		attribute_PARRY,
		ATTRIBUTEID_TACTICS,
		ATTRIBUTEID_ARCHERY,
		attribute_SWORDSMANSHIP,
		ATTRIBUTEID_MACEFIGHTING,
		attribute_FENCING,
		attribute_WRESTLING
	};

	var i;
	for( i := Len( combat_skills ) ; i > 0 ; i := i - 1 )
		if( combat_skills[i] = attribute )
			break;
		endif
	endfor

	if( i > 0 )
		set_critical(0);
		return;
	endif

	var combat_level := GetObjProperty( who , "CombatSkillsLevel" );
	if( !combat_level )
		combat_level := {};
	endif

	var rawskill := GetRawSkill( who , attribute );
	foreach item in ListEquippedItems( who )
		if( GetObjProperty( item , "skilladv" ) = attribute )
			rawskill := rawskill - CInt( GetObjProperty( who , "advamount" + attribute + "s" + item.serial ) );
		endif
	endforeach

	var old_skill_level	:= CInt( combat_level[i] );
	var current_level	:= CInt( rawskill );

	if( state = "l" )

		if( current_level > old_skill_level )
			SetRawSkill( who , attribute , old_skill_level );
		endif

	elseif( state = "d" )

		var amount := 10000;
		if( amount >= old_skill_level )
			amount := old_skill_level;
			var state_array := GetObjProperty( who , "SkillsState" );
			if( !state_array )
				state_array := {};
			endif
			state_array[attribute+1] := "l";
			SetObjProperty( who , "SkillsState" , state_array );
		endif

		var new_level := CInt( old_skill_level - amount );
		SetRawSkill( who , attribute , new_level );
		combat_level[i] := new_level;
		SetObjProperty( who , "CombatSkillsLevel" , combat_level );

	endif

	set_critical(0);

endfunction