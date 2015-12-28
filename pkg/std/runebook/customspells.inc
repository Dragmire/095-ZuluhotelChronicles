/////////////////////////////////////////////////////
// customspells.inc -- Simplified gate and recall code
//                     for use with runebook.src
//
// Author(s): Racalac
// Revisions: 1.0, 11/13/99: Gate, Recall
//                           Mana, Reagent consumption
//                           Normal Spell Restrictions
//
// Notes: (rev1.0) - None
//
// Dependencies: (rev1.0) - client.inc
//                          objtype.inc
//                          spellrestrictions.inc
//
/////////////////////////////////////////////////////

use uo;
use os;

const ANIM_WALK_UNARMED         :=  0x0000; // Walk unarmed.
const ANIM_WALK_ARMED           :=  0x0001; // Walk armed.
const ANIM_RUN_UNARMED          :=  0x0002; // Run unarmed.
const ANIM_RUN_ARMED            :=  0x0003; // Run armed.
const ANIM_STAND                :=  0x0004; // Stand.
const ANIM_FIDGET_1             :=  0x0005; // Twist a little (look around?).
const ANIM_FIDGET_2             :=  0x0006; // Look down.
const ANIM_STAND_1HAND          :=  0x0007; // Stand 1 handed attack.
const ANIM_STAND_2HAND          :=  0x0008; // Stand 2 handed attack.
const ANIM_ATTACK_1HAND_WIDE    :=  0x0009; // Attack 1 handed wide (sword/any).
const ANIM_ATTACK_1HAND_JAB     :=  0x000a; // Attack 1 handed jab (fencing).
const ANIM_ATTACK_1HAND_DOWN    :=  0x000b; // Attack 1 handed down (mace).
const ANIM_ATTACK_2HAND_DOWN    :=  0x000c; // Attack 2 handed jab (mace).
const ANIM_ATTACK_2HAND_WIDE    :=  0x000d; // Attack 2 handed wide.
const ANIM_ATTACK_2HAND_JAB     :=  0x000e; // Attack 2 handed jab (spear).
const ANIM_ATTACK_BOW           :=  0x0012; // Attack bow.
const ANIM_ATTACK_XBOW          :=  0x0013; // Attack xbow.
const ANIM_WALK_WARMODE         :=  0x000f; // Walk in warmode.
const ANIM_CAST_DIR             :=  0x0010; // Spellcasting direction.
const ANIM_CAST_AREA            :=  0x0011; // Spellcasting area.
const ANIM_HIT                  :=  0x0014; // Get hit.
const ANIM_DIE_BACK             :=  0x0015; // Die backward.
const ANIM_DIE_FOR              :=  0x0016; // Die forward.
const ANIM_BOW                  :=  0x0020; // Bow.
const ANIM_SALUTE               :=  0x0021; // Salute.



const RECALL_DELAY_MS	:= 2500;
const GATE_DELAY_MS	:= 4000;


function CustomRecall( caster, x, y, z, from_charge := 0 )

	var shp	:= caster.hp;
	var sx	:= caster.x;
	var sy	:= caster.y;
	var sz	:= caster.z;
	var smana	:= caster.mana;
	var circle	:= 4;
	var spelldelay := RECALL_DELAY_MS;

	caster.hidden := 0;
	PerformAction( caster , ANIM_CAST_DIR );
        SpeakPowerWords( caster , SPELLID_RECALL );

	if( !CanUseBook( caster ) )
		return 0;
	endif

	while( spelldelay >= 500 )
		Sleepms( 500 );
		spelldelay := spelldelay - 500;
		if( caster.hp < shp )
			SendSysmessage( caster , "You were interrupted during the casting" );
			PlayObjectCenteredEffect(caster, FX_SPELL_FIZZLE, SPEED_SPELL_FIZZLE,LOOP_SPELL_FIZZLE );
			PlaySoundEffect(caster, SFX_SPELL_FIZZLE);
			return 0;
		endif

		if( caster.x != sx or caster.y != sy or caster.z != sz )
			SendSysmessage( caster , "You've lost your concentration!" );
			PlayObjectCenteredEffect(caster, FX_SPELL_FIZZLE, SPEED_SPELL_FIZZLE, LOOP_SPELL_FIZZLE );
			PlaySoundEffect(caster, SFX_SPELL_FIZZLE);
			return 0;
		endif
	endwhile

	Sleepms( spelldelay );

	if( caster.hp < shp )
		SendSysmessage( caster , "You were interrupted during the casting" );
		PlayObjectCenteredEffect(caster, FX_SPELL_FIZZLE, SPEED_SPELL_FIZZLE, LOOP_SPELL_FIZZLE );
		PlaySoundEffect(caster, SFX_SPELL_FIZZLE);
		return 0;
	endif

	if( caster.x != sx or caster.y != sy or caster.z != sz )
		SendSysmessage( caster , "You've lost your concentration!" );
		PlayObjectCenteredEffect(caster, FX_SPELL_FIZZLE, SPEED_SPELL_FIZZLE, LOOP_SPELL_FIZZLE );
		PlaySoundEffect(caster, SFX_SPELL_FIZZLE);
		return 0;
	endif

	if( !from_charge )
        	if(!ConsumeReagents( caster, SPELLID_RECALL ))
		   	PrintTextAbovePrivate(caster,"*No reagents*", caster);
			PlayObjectCenteredEffect(caster, FX_SPELL_FIZZLE, SPEED_SPELL_FIZZLE,LOOP_SPELL_FIZZLE );
			PlaySoundEffect(caster, SFX_SPELL_FIZZLE);
           		return 0;
        	endif

        	if(!ConsumeMana( caster , SPELLID_RECALL ))
		   	PrintTextAbovePrivate(caster,"*No mana*", caster);
			PlayObjectCenteredEffect(caster, FX_SPELL_FIZZLE, SPEED_SPELL_FIZZLE,LOOP_SPELL_FIZZLE );
			PlaySoundEffect(caster, SFX_SPELL_FIZZLE);
           		return 0;
        	endif

	        if(!CheckSkill( caster , SKILLID_MAGERY , GetSpellDifficulty(SPELLID_RECALL), 50 ) )
        		caster.mana := smana;
			PrintTextAbovePrivate(caster,"*The spell fizzle*", caster);
			PlayObjectCenteredEffect(caster, FX_SPELL_FIZZLE, SPEED_SPELL_FIZZLE,LOOP_SPELL_FIZZLE );
			PlaySoundEffect(caster, SFX_SPELL_FIZZLE);
           		return 0;
        	endif
        endif

	if( !can_cast( caster , circle ) )
		return 0;
	endif

	if( IsForbiddenAreaToRecallFrom( caster ) )
		SendSysMessage( caster, "You can't gate from there." );
		return 0;
	endif

	var tox := x;
	var toy := y;
	var toz := z;

	if( !Checkpoz(tox,toy) )
		SendSysMessage( caster , "The destination is a magic place with protection." );
		return 0;
	endif

	if( IsForbiddenAreaToRecallTo( caster , tox , toy ) )
		SendsysMessage( caster , "The destination is a magic place with protection." );
		return 0;
	endif


//---- by Greven ----//
	//DONATOR basic area
	var x1 := 5894;
	var x2 := 6016;
	var y1 := 1416;
	var y2 := 1533;

        if(tox >= x1 and tox <= x2 and toy >= y1 and toy <= y2)
           sendsysmessage(caster,"You can't recall to this place.",3,33);
	   return;
	endif

	//DONATOR elite area
	var elitex1 := 5375;
	var elitex2 := 5427;
	var elitey1 := 1080;
	var elitey2 := 1142;

	if(tox >= elitex1 and tox <= elitex2 and toy >= elitey1 and toy <= elitey2)
            sendsysmessage(caster,"You can't recall to this place.",3,33);
	    return;
	endif

	//DONATOR pro area
	var prox1 := 6033;
	var prox2 := 6138;
	var proy1 := 1284;
	var proy2 := 1388;

	if(tox >= prox1 and tox <= prox2 and toy >= proy1 and toy <= proy2)
            sendsysmessage(caster,"You can't recall to this place.",3,33);
	    return;
	endif
//---- end ----//

	var owner;
	var lamp;
	var Near_Items := ListItemsNearLocation(tox, toy, toz,10);
	foreach thing in Near_Items
		if (thing.objtype == 0xf156)
			lamp := thing;
			owner := GetObjProperty(lamp,"Owner");
		endif
	endforeach
	if (lamp and owner)
		if (caster.serial != owner)
			SendSysMessage( caster, "You can't recall to this house." );
			return;
		endif
	endif
	var multi := GetStandingHeight( tox, toy, toz ).multi;
	if( multi )
		if( GetObjProperty( multi,"ownerserial") != caster.serial )
			var co_owners := {};
			var friends := {};
			var i,j;
			for( i := 1; i <= 5; i := i + 1 )
				if( GetObjProperty( multi, "Co-owner" + i ) )
					co_owners.append( GetObjProperty( multi, "Co-owner" + i ));
				endif
			endfor
			
			for( j := 1; j <= 20; j := j + 1 )
				if( GetObjProperty( multi, "friend" + j ) )
					friends.append( GetObjProperty( multi, "friend" + j ));
				endif
			endfor

			if( !( caster.serial in co_owners )  )
				if( !( caster.serial in friends ) )
					SendSysMessage( caster, "You can't recall to this house." );
					return 0;
				endif
			endif

//			for( i := 1; i <= 20; i := i + 1 )
//				if( GetObjProperty( multi, "friend" + i ) )
//					friends.append( GetObjProperty( multi, "friend" + i ));
//				endif
//			endfor
			
				
//			if( !( caster.serial in friends ) )
//				SendSysMessage( caster, "You can't recall to this house." );
//				return 0;
//			endif
		endif
	endif

	var multi2 := GetStandingHeight(sx,sy,sz).multi;
	if(multi2)
		if( !IsOwner( caster, multi2 )  )
			if( !IsFriend( caster, multi2 ) )
				SendSysMessage( caster, "You can't recall from this house." );
				return;
			endif
		endif
	endif


	PlaySoundEffect( caster, SFX_SPELL_RECALL1 );
	sleepms(250);

	MoveCharacterToLocation( caster, tox, toy, toz );
	PlaySoundEffect( caster, SFX_SPELL_RECALL2 );

        return 1;

endfunction


function CustomGate( caster, x, y, z )

	var shp	:= GetVital( caster, "life" );
	var sx	:= caster.x;
	var sy	:= caster.y;
	var sz	:= caster.z;
	var smana	:= caster.mana;
	var circle	:= 7;
	var spelldelay := GATE_DELAY_MS;

	caster.hidden := 0;
	PerformAction( caster , ANIM_CAST_DIR );
        SpeakPowerWords( caster , SPELLID_GATE_TRAVEL );

	if( !CanUseBook( caster ) )
		return 0;
	endif

	while( spelldelay >= 500 )
		Sleepms( 500 );
		spelldelay := spelldelay - 500;
		if( GetVital( caster, "life" ) < shp )
			SendSysmessage( caster , "You were interrupted during the casting" );
			PlayObjectCenteredEffect(caster, FX_SPELL_FIZZLE, SPEED_SPELL_FIZZLE,LOOP_SPELL_FIZZLE );
			PlaySoundEffect(caster, SFX_SPELL_FIZZLE);
			return 0;
		endif

		if( caster.x != sx or caster.y != sy or caster.z != sz )
			SendSysmessage( caster , "You've lost your concentration!" );
			PlayObjectCenteredEffect(caster, FX_SPELL_FIZZLE, SPEED_SPELL_FIZZLE,LOOP_SPELL_FIZZLE );
			PlaySoundEffect(caster, SFX_SPELL_FIZZLE);
			return 0;
		endif
	endwhile

	Sleepms( spelldelay );

	if( GetVital( caster, "life" ) < shp )
		SendSysmessage( caster , "You were interrupted during the casting" );
		PlayObjectCenteredEffect(caster, FX_SPELL_FIZZLE, SPEED_SPELL_FIZZLE, LOOP_SPELL_FIZZLE );
		PlaySoundEffect(caster, SFX_SPELL_FIZZLE);
		return 0;
	endif

	if( caster.x != sx or caster.y != sy or caster.z != sz )
		SendSysmessage( caster , "You've lost your concentration!" );
		PlayObjectCenteredEffect(caster, FX_SPELL_FIZZLE, SPEED_SPELL_FIZZLE, LOOP_SPELL_FIZZLE );
		PlaySoundEffect(caster, SFX_SPELL_FIZZLE);
		return 0;
	endif

        if(!ConsumeReagents( caster, SPELLID_GATE_TRAVEL ))
	   	PrintTextAbovePrivate(caster,"*No reagents!*", caster);
		PlayObjectCenteredEffect(caster, FX_SPELL_FIZZLE, SPEED_SPELL_FIZZLE, LOOP_SPELL_FIZZLE );
		PlaySoundEffect(caster, SFX_SPELL_FIZZLE);
        	return 0;
        endif

        if(!ConsumeMana( caster , SPELLID_GATE_TRAVEL ))
	   	PrintTextAbovePrivate(caster,"*No mana!*", caster);
		PlayObjectCenteredEffect(caster, FX_SPELL_FIZZLE, SPEED_SPELL_FIZZLE, LOOP_SPELL_FIZZLE );
		PlaySoundEffect(caster, SFX_SPELL_FIZZLE);
        	return 0;
        endif

        if(!CheckSkill( caster , SKILLID_MAGERY, GetSpellDifficulty(SPELLID_GATE_TRAVEL), 50 ) )
	       	caster.mana := smana;
		PlayObjectCenteredEffect(caster, FX_SPELL_FIZZLE, SPEED_SPELL_FIZZLE, LOOP_SPELL_FIZZLE );
		PlaySoundEffect(caster, SFX_SPELL_FIZZLE);
		SendSysmessage(caster, "The spell fizzles");
        	return 0;
        endif

	if( !can_cast(caster, circle) )
		return 0;
	endif

	if( IsForbiddenAreaToGateFrom( caster ) )
		SendSysMessage( caster, "You can't gate from there." );
		return 0;
	endif
	
 //---- by Greven ----//
	//DONATOR basic area
	var x1 := 5894;
	var x2 := 6016;
	var y1 := 1416;
	var y2 := 1533;

        if(caster.x >= x1 and caster.x <= x2 and caster.y >= y1 and caster.y <= y2)
           sendsysmessage(caster,"You can't gate from there.",3,33);
	   return;
	endif

	//DONATOR elite area
	var elitex1 := 5375;
	var elitex2 := 5427;
	var elitey1 := 1080;
	var elitey2 := 1142;

	if(caster.x >= elitex1 and caster.x <= elitex2 and caster.y >= elitey1 and caster.y <= elitey2)
            sendsysmessage(caster,"You can't gate from there.",3,33);
	    return;
	endif

	//DONATOR pro area
	var prox1 := 6033;
	var prox2 := 6138;
	var proy1 := 1284;
	var proy2 := 1388;

	if(caster.x >= prox1 and caster.x <= prox2 and caster.y >= proy1 and caster.y <= proy2)
            sendsysmessage(caster,"You can't gate from there.",3,33);
	    return;
	endif

//---- end ----//
 
	if( caster.multi and GetObjProperty( caster.multi , "ownerserial" ) != caster.serial )
		var co_owners := {};
		var friends := {};
		var i;
		for( i := 1 ; i <= 5 ; i := i + 1 )
			if( GetObjProperty( caster.multi , "Co-owner" + i ) )
				co_owners.append( GetObjProperty( caster.multi , "Co-owner" + i ));
			endif
		endfor
		
		for( i := 1 ; i <= 20 ; i := i + 1 )
			if( GetObjProperty( caster.multi , "friend" + i ) )
				friends.append( GetObjProperty( caster.multi , "friend" + i ));
			endif
		endfor
			
		if( !( caster.serial in co_owners ) and !( caster.serial in friends ) )
			SendSysMessage( caster , "You can't gate from there!" );
			return;
		endif
	endif
	
	var tox := x;
	var toy := y;
	var toz := z;

	if( IsForbiddenAreaToGateTo( caster, tox, toy ) )
		SendSysMessage(caster, "The destination is a magic place with protection.");
		return 0;
	endif

//---- by Greven ----//
	//DONATOR basic area
        if(tox >= x1 and tox <= x2 and toy >= y1 and toy <= y2)
           sendsysmessage(caster,"The destination is a magic place with protection.",3,33);
	   return;
	endif

	//DONATOR elite area
	if(tox >= elitex1 and tox <= elitex2 and toy >= elitey1 and toy <= elitey2)
            sendsysmessage(caster,"The destination is a magic place with protection.",3,33);
	    return;
	endif

	//DONATOR pro area
	if(tox >= prox1 and tox <= prox2 and toy >= proy1 and toy <= proy2)
            sendsysmessage(caster,"The destination is a magic place with protection.",3,33);
	    return;
	endif
//---- end ----//


	var owner;
	var lamp;
	var Near_Items := ListItemsNearLocation(tox, toy, toz,10);
	foreach thing in Near_Items
		if (thing.objtype == 0xf156)
			lamp := thing;
			owner := GetObjProperty(lamp,"Owner");
		endif
	endforeach
	if (lamp and owner)
		if (caster.serial != owner)
			SendSysMessage( caster, "You can't gate to this house." );
			return;
		endif
	endif
	var multi := GetStandingHeight( tox, toy, toz ).multi;
	if( multi )
		if( GetObjProperty( multi, "ownerserial" ) != caster.serial )
			var co_owners := {};
			var friends := {};
			var i,j;
			for( i := 1 ; i <= 5 ; i := i + 1 )
				if( GetObjProperty( multi , "Co-owner" + i ) )
					co_owners.append( GetObjProperty( multi, "Co-owner" + i ));
				endif
			endfor
			
			for( j := 1 ; j <= 20 ; j := j + 1 )
				if( GetObjProperty( multi , "friend" + j ) )
					friends.append( GetObjProperty( multi, "friend" + j ));
				endif
			endfor

			if( !( caster.serial in co_owners ) and !( caster.serial in friends ) )
				SendSysMessage( caster, "You can't gate to this house." );
				return 0;
			endif
			
//			for( i := 1 ; i <= 20 ; i := i + 1 )
//				if( GetObjProperty( multi , "friend" + i ) )
//					friends.append( GetObjProperty( multi, "friend" + i ));
//				endif
//			endfor
				
//			if( !( caster.serial in friends ) )
//				SendSysMessage( caster , "You can't gate to this house." );
//				return 0;
//			endif
		endif
	endif
	
	set_critical(1);
	var pregate := CreateItemAtLocation( caster.x, caster.y, caster.z, 0x1af3, 1 );
	pregate.facing := 1;
	PlaySoundEffect( caster, SFX_SPELL_GATE_TRAVEL );
	sleepms(1500);

	var gate1 := CreateItemAtLocation( caster.x, caster.y, caster.z, UOBJ_BLUE_MOONGATE, 1 );
	gate1.facing := 1;
	destroyitem(pregate);

	var gate2 := CreateItemAtLocation( tox, toy, toz, UOBJ_BLUE_MOONGATE, 1 );
	gate2.facing := 2;

	if (!gate1 or !gate2)
		DestroyItem(gate1);
		DestroyItem(gate2);
		return 0;
	endif

	SetObjProperty( gate1, "GateDestX", gate2.x );
	SetObjProperty( gate1, "GateDestY", gate2.y );
	SetObjProperty( gate1, "GateDestZ", gate2.z );
	SetObjProperty( gate2, "GateDestX", gate1.x );
	SetObjProperty( gate2, "GateDestY", gate1.y );
	SetObjProperty( gate2, "GateDestZ", gate1.z );

	Detach();

	set_critical(0);

	PlaySoundEffect( caster, SFX_SPELL_GATE_TRAVEL );

	Sleep(30);

	set_critical(1);
	DestroyItem( gate1 );
	DestroyItem( gate2 );
	set_critical(0);

        return 1;

endfunction


function CanUseBook( me )

	var hand1 := GetEquipmentByLayer( me , LAYER_HAND1 );
	var hand2 := GetEquipmentByLayer( me , LAYER_HAND2 );

	if( hand1 or hand2 )
		var weapcfg := ReadConfigFile( ":*:itemdesc" );

		if( hand1 and weapcfg[hand1.objtype].BlocksCastingIfInHand != 0 )
			SendSysmessage( me , "Your hands must be free to use that." );
			PlayObjectCenteredEffect( me , FX_SPELL_FIZZLE , SPEED_SPELL_FIZZLE , LOOP_SPELL_FIZZLE );
			PlaySoundEffect( me , SFX_SPELL_FIZZLE );
			return 0;
		endif

		if( hand2 and weapcfg[hand2.objtype].BlocksCastingIfInHand != 0)
			SendSysmessage( me , "Your hand must be free to use that." );
			PlayObjectCenteredEffect( me , FX_SPELL_FIZZLE , SPEED_SPELL_FIZZLE , LOOP_SPELL_FIZZLE );
			PlaySoundEffect( me , SFX_SPELL_FIZZLE );
			return 0;
		endif
	endif

	return 1;

endfunction

