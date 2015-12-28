use uo;

include "include/objtype";
include "include/attributes";


function ConsumeObjType( who, objtype, amount )

	var item := FindItemInContainer( who.backpack, objtype );
	if( !item )
		return 0;
	endif

	if( !ReserveItem( item ) )
		return 0;
	endif

	if( item.amount < amount )
		return 0;
	endif

	if( !SubtractAmount( item, amount ) )
		return 0;
	endif

	return 1;

endfunction


function CreateItemAt( where, objtype, duration := -1, amount := 1, color := 0, movable := 0 )

	var parms := {};
	parms[1] := where;
	parms[2] := objtype;
	parms[3] := duration;
	parms[4] := amount;
	parms[5] := color;
	parms[6] := movable;

	start_script( ":summoning:itemappear", parms );

endfunction


function CreateMagicCircleAround( who, duration := 0, color := 0, sfx := 0 )

	var parms := {};
	parms[1] := who;
	parms[2] := duration;
	parms[3] := color;
	parms[4] := sfx;

	start_script( ":summoning:magiccircleappear", parms );

endfunction


function CreateWaterfall( who, duration := 0, color := 0, sfx := 0 )

	var parms := {};
	parms[1] := who;
	parms[2] := duration;
	parms[3] := color;
	parms[4] := sfx;

	start_script( ":summoning:waterfallappear", parms );

endfunction


function DupeItem( item, newitem )

	newitem.graphic := item.graphic;
	newitem.movable	:= item.decayAt;
	
	if( item.name )		newitem.name 		:= item.name; 		endif
	if( item.maxhp_mod ) 	newitem.maxhp_mod 	:= item.maxhp_mod; 	endif
	if( item.ar_mod ) 	newitem.ar_mod 		:= item.ar_mod; 	endif
	if( item.dmg_mod ) 	newitem.dmg_mod 	:= item.dmg_mod; 	endif
	if( item.hitscript ) 	newitem.hitscript 	:= item.hitscript; 	endif
	if( item.quality ) 	newitem.quality 	:= item.quality; 	endif
	if( item.color ) 	newitem.color 		:= item.color; 		endif
	if( item.newbie ) 	newitem.newbie 		:= item.newbie; 	endif
	if( item.facing )	newitem.facing		:= item.facing;		endif
	if( item.hp ) 		newitem.hp 		:= item.hp; 		endif
	if( item.buyprice )	newitem.buyprice 	:= item.buyprice; 	endif
	if( item.decayAt )	newitem.decayAt		:= item.decayAt;	endif

	foreach prop in GetObjPropertyNames(item)
		SetObjProperty( newitem, prop, GetObjProperty( item, prop ) );
	endforeach

endfunction


function DestroyTheItem( who, item )

	var cursed := GetObjProperty( item, "Cursed" );
	if( cursed )
		SetObjProperty( item, "Cursed", 3 );
	endif

	if( who.backpack )
		MoveItemToContainer( item, who.backpack );
	endif

	DestroyItem( item );

endfunction


function FindItemInContainer( container, objtype )

	var the_item;
	foreach thing in EnumerateItemsInContainer( container );
		if( thing.objtype == objtype )
			the_item := thing;
			break;
		endif
	endforeach

	return the_item;

endfunction


function FindRootItemInContainer( container, objtype )

	var the_item;

	foreach thing in EnumerateItemsInContainer( container );
		if( (thing.container == container) && (thing.objtype == objtype) )
			the_item := thing;
			break;
		endif
	endforeach

	return the_item;

endfunction


function FitRequirements( who, item )

	var required := GetObjProperty( item, "ToUseRequirements" );
	if( !required )
		return 1;
	endif

	foreach condition in required
		var type := condition[1];
		case( type )
			"skill":	if( GetEffectiveSkill( who, CInt(condition[2]) ) < CInt( condition[3] ) )
						return 0;
					endif
					break;
				
			"stat":		case( condition[2] )
						"str":	if( GetStrength(who) < CInt( condition[3] ) )
								return 0;
							endif
							break;
						
						"dex":	if( GetDexterity(who) < CInt( condition[3] ) )
								return 0;
							endif
							break;
						
						"int":	if( GetIntelligence(who) < CInt( condition[3] ) )
								return 0;
							endif
							break;
					endcase
					break;
				
			"spec":		if( CInt( GetObjProperty( who, condition[2] ) ) < CInt( condition[3] ) )
						return 0;
					endif
					break;
				
			"owner":	if( !( who.serial in condition[2] ) )
						return 0;
					endif
					break;
		endcase
	endforeach

	return 1;

endfunction


function GetBoneArmorGraphics()

	return { 0x144e, 0x144f, 0x1450, 0x1451, 0x1452,
		 0x1453, 0x1454, 0x1455, 0x1456, 0x1457 };

endfunction


function GetChainmailArmorGraphics()

	return { 0x13bb, 0x13bc, 0x13bd, 0x13be, 0x13bf,
		 0x13c0, 0x13c1, 0x13c2, 0x13c3, 0x13c4 };

endfunction


function GetLeatherArmorGraphics()

	return { 0x13c5, 0x13c6, 0x13c7, 0x13c8, 0x13c9,
		 0x13ca, 0x13cb, 0x13cc, 0x13cd, 0x13ce,
		 0x13cf, 0x13d0, 0x13d1, 0x13d2, 0x13d3 };

endfunction


function GetPlatemailArmorGraphics()

	return { 0x1408, 0x1409, 0x140a, 0x140b, 0x140c,
		 0x140d, 0x140e, 0x140f, 0x1410, 0x1411,
		 0x1412, 0x1413, 0x1414, 0x1415, 0x1416,
		 0x1417, 0x1418, 0x1419, 0x141a };

endfunction


function GetPossiblePropertyNames()

	return {	"AirProtection",
			"ArBonus",
			"AvailSkills",
			"BaseName",
			"BetweenUses",
			"bookcontent",
			"ByTrueMage",
			"CannotBeUncursed",
			"CastingOpts",
			"CastSpell",
			"ChanceOfEffect",
			"charges",
			"ChoppedBy",
			"Circle1",
			"Circle2",
			"Circle3",
			"Circle4",
			"CircleColor",
			"CircleDurationMs",
			"CircleSfx",
			"ColorMod",
			"ConfirmationMsg",
			"Consecrated",
			"CostPerCharge",
			"CreatureType",
			"Cursed",
			"DefaultDex",
			"DefaultLocation",
			"Delay",
			"DelayBetweenMs",
			"DestroyAfterUse",
			"dex",
			"DontAffectCaster",
			"EarthProtection",
			"EffectCircle",
			"EffectType",
			"ElementalSpell",
			"EnchantColor",
			"Enchanted",
			"EnchantedWith",
			"equipspell",
			"Expire",
			"ExpireNum",
			"FireProtection",
			"FixedDamages",
			"FreeAction",
			"Frequency",
			"GateDestX",
			"GateDestY",
			"GateDestZ",
			"GraphicMod",
			"Greater",
			"HealingIncrease",
			"HitscriptNumber",
			"HitWithSpell",
			"HolyProtection",
			"HpRegen",
			"HrEnd",
			"HrStart",
			"IDed",
			"int",
			"IsExceptional",
			"IsGMItem",
			"ItemAppear",
			"ItemAppearAmount",
			"ItemAppearColor",
			"ItemAppearDurationMs",
			"ItemAppearMovable",
			"keep",
			"KilledBy",
			"Lesser",
			"LootedBy",
			"LumberjackingBonus",
			"MagicImmunity",
			"MagicPenalty",
			"ManaCost",
			"ManaLevel",
			"ManaRegen",
			"Max",
			"maxcharges",
			"MaxStatMod",
			"MiningBonus",
			"name",
			"NameMod",
			"NecroProtection",
			"NoCheckLos",
			"noloot",
			"NormalRange",
			"OfBlackrock",
			"OnHitScript",
			"OnHitscriptNumber",
			"ownername",
			"ownerserial",
			"PermMagicCircle",
			"PermMagicImmunity",
			"Permmr",
			"PermPoisonImmunity",
			"PhysicalProtection",
			"PlanarSpell",
			"PlayAnimation",
			"Poisoned",
			"PoisonImmunity",
			"Poisonlvl",
			"PolymorphColor",
			"PolymorphDuration",
			"PolymorphInto",
			"PolymorphMod",
			"Powerlevel",
			"PowerWords",
			"ProtectedType",
			"Range",
			"ReagentsNeeded",
			"Rechargeable",
			"RequireNoCharges",
			"runedefs",
			"SlayType",
			"ShearingBonus",
			"skilladv",
			"skilladvamount",
			"SkillLevelMod",
			"SkillMultipliersMod",
			"SkillPoisoned",
			"SpecMult",
			"SpellCircle",
			"SpellDifficulty",
			"SpellEffectType",
			"SpellFx",
			"SpellFxLoop",
			"SpellFxSpeed",
			"SpellFxType",
			"SpellHealAmount",
			"SpellId",
			"SpellModAmount",
			"SpellModDuration",
			"SpellModId",
			"SpellPoisonLevel",
			"SpellRadius",
			"SpellReflect",
			"SpellSfx",
			"SpellTargetOption",
			"StamRegen",
			"StaticColor",
			"StaticName",
			"StaticCursedName",
			"StatLevelMod",
			"StayEquipped",
			"str",
			"SummonDelayBeforeMs",
			"SummonDelayBetweenMs",
			"SummonSfx",
			"SummonNpcTemplate",
			"TargetingType",
			"Template",
			"TriggerCircle",
			"Type",
			"WasCursed",
			"WaterProtection",
			"WordOfPower",
			"x",
			"y",
			"z"			};
		
endfunction


function GetRingmailArmorGraphics()

	return { 0x13e5, 0x13e6, 0x13e7, 0x13e8, 0x13e9,
		 0x13ea, 0x13eb, 0x13ec, 0x13ed, 0x13ee,
		 0x13ef, 0x13f0, 0x13f1, 0x13f2 };

endfunction


function GetShieldGraphics()

	return { 0x1b72, 0x1b73, 0x1b74, 0x1b75, 0x1b76,
		 0x1b77, 0x1b78, 0x1b79, 0x1b7a, 0x1b7b };

endfunction


function GetStuddedLeatherArmorGraphics()

	return { 0x13d4, 0x13d5, 0x13d6, 0x13d7, 0x13d8,
		 0x13d9, 0x13da, 0x13db, 0x13dc, 0x13dd,
		 0x13de, 0x13df, 0x13e0, 0x13e1, 0x13e2 };

endfunction

function IsCarpet( item )

	if( item.objtype >= UOBJ_CARPET_START && item.objtype <= UOBJ_CARPET_END )
		return 1;
	else
		return 0;
	endif

endfunction

function IsCloth( item )

	if( item.objtype >= UOBJ_CLOTH_START && item.objtype <= UOBJ_CLOTH_END )
		return 1;
	else
		return 0;
	endif

endfunction


function IsConsommable( item )

	var objtype := item.objtype;

	if( objtype == 0x099b || objtype == 0x099f || objtype == 0x09c7 || objtype == 0x09c8 )
		return 1;
	elseif( objtype >= 0x1f7d && objtype <= 0x1f9e )
		return 1;
	elseif( objtype >= 0x09ee && objtype <= 0x09f0 )
		return 1;
	elseif( objtype >= 0x0c7f && objtype <= 0x0c82 )
		return 1;
	elseif( objtype >= 0x0c77 && objtype <= 0x0c7c )
		return 1;
	elseif( objtype >= 0x171d && objtype <= 0x172d )
		return 1;
	elseif( objtype >= 0x0c64 && objtype <= 0x0c67 )
		return 1;
	elseif( objtype >= 0x0c70 && objtype <= 0x0c75 )
		return 1;
	elseif( objtype >= 0x097b && objtype <= 0x097e )
		return 1;
	elseif( objtype >= 0xc900 && objtype <= 0xc903 )
		return 1;
	elseif( objtype >= 0xc910 && objtype <= 0xc912 )
		return 1;
	elseif( objtype >= 0xc920 && objtype <= 0xc923 )
		return 1;
	elseif( objtype >= 0xc930 && objtype <= 0xc936 )
		return 1;
	elseif( objtype >= 0xc940 && objtype <= 0xc947 )
		return 1;
	elseif( objtype == 0x0978 || objtype == 0x0979 )
		return 1;
	elseif( objtype == 0x09b7 || objtype == 0x09b8 )
		return 1;
	elseif( objtype == 0x09d0 || objtype == 0x0d1a || objtype == 0x0c5c )
		return 1;
	elseif( objtype == 0x0c6d || objtype == 0x0d3a || objtype == 0x09e9 )
		return 1;
	elseif( objtype == 0x09f2 || objtype == 0x09b6 || objtype == 0x09ea )
		return 1;
	elseif( objtype == 0x103b || objtype == 0x098c || objtype == 0x160c )
		return 1;
	elseif( objtype == 0x1e1f || objtype == 0x09c1 || objtype == 0x1608 )
		return 1;
	elseif( objtype == 0x160a || objtype == 0x1e1d || objtype == 0x1e1e )
		return 1;
	elseif( objtype == 0xc950 || objtype == 0x7059 )
		return 1;
	elseif( objtype >= 0xdc01 && objtype <= 0xdc03 )
		return 1;
	elseif( objtype >= 0xdc0b && objtype <= 0xdc16 )
		return 1;
	else
		return 0;
	endif

endfunction


function IsEquipped( who, what )

	var hand1	:= GetEquipmentByLayer( who, 0x01 );
	var hand2	:= GetEquipmentByLayer( who, 0x02 );

	if( hand1 == what || hand2 == what )
		return 1;
	elseif( !Accessible( who, what ) )
		return 0;
	elseif(what.container.objtype == UOBJ_CORPSE  )
		SendSysMessage( who, "You cannot equip that!");
		return;
	Else
		return EquipItem( who, what );
	endif

endfunction


function IsFish( item )

        var res := 0;

	if( item == 0x09cc )
		res := 1;
	elseif( item == 0x09cd )
		res := 1;
	elseif( item == 0x09ce )
		res := 1;
	elseif( item == 0x09cf )
		res := 1;
	elseif( item == 0x8BCA )
		res := 1;
	elseif( item == 0x8BCB )
		res := 1;
	elseif( item == 0x8BCC )
		res := 1;
	elseif( item == 0x8BCD )
		res := 1;
	elseif( item == 0x8BCE )
		res := 1;
	elseif( item == 0x8BCF )
		res := 1;
	else
		res := 0;
	endif
 
    return res;
	
endfunction


function IsIDable( item )

	if( item.graphic >= 0x182a && item.graphic <= 0x1848 )
		return 0;
	elseif( item.graphic >= 0x0efb && item.graphic <= 0x0f0e )
		return 0;
	elseif( item.graphic >= 0x100e && item.graphic <= 0x1013 )
		return 0;
	elseif( IsStackable( item ) )
		return 0;
	else
		return 1;
	endif

endfunction


function IsInContainer( container, item )

   	foreach thing in EnumerateItemsInContainer( container )
		if( thing.serial == item.serial )
			return 1;
		endif
   	endforeach

   	return 0;

endfunction


function IsIngot( item )

	if(( item.objtype >= UOBJ_INGOTS_START  and item.objtype <= UOBJ_INGOTS_END  ) or
	   ( item.objtype >= UOBJ_INGOTS2_START and item.objtype <= UOBJ_INGOTS2_END ) or
	   ( item.objtype  == UOBJ_GOLD_INGOT ) or (item.objtype  == 0x5000) or (item.objtype  == 0x5050) or (item.objtype  == 0x6090) or (item.objtype  == 0x5070) or (item.objtype  == 0x5090) or (item.objtype  == 0x5010))
		return 1;
	else
		return 0;
	endif

endfunction


function IsLog( item )

	if(( item.objtype >= UOBJ_LOGS_START  && item.objtype <= UOBJ_LOGS_END ) ||
	   ( item.objtype  == UOBJ_LOGS ))
		return 1;
	else
		return 0;
	endif

endfunction


function IsMinable( theobj, othertype )

	if( ((theobj >= 0xe2)  && (theobj <= 0xe7))  ||
	    ((theobj >= 0xf3)  && (theobj <= 0xf7))  ||
	    ((theobj >= 0x104) && (theobj <= 0x107)) ||
	    ((theobj >= 0x110) && (theobj <= 0x113)) ||
	    ((theobj >= 0x122) && (theobj <= 0x125)) ||
	    ((theobj >= 0x1d3) && (theobj <= 0x1da)) ||
	    ((theobj >= 0x21f) && (theobj <= 0x230)) ||
	    ((theobj >= 0x232) && (theobj <= 0x23b)) ||
	    ((theobj >= 0x6cd) && (theobj <= 0x6d1)) ||
	    ((theobj >= 0x6da) && (theobj <= 0x6dd)) ||
	    ((theobj >= 0x6eb) && (theobj <= 0x6fe)) ||
	    ((theobj >= 0x70d) && (theobj <= 0x714)) ||
	    ((theobj >= 0x71d) && (theobj <= 0x720)) ||
	    ((theobj >= 0x72b) && (theobj <= 0x732)) ||
	    ((theobj >= 0x73b) && (theobj <= 0x73e)) ||
	    ((theobj >= 0x749) && (theobj <= 0x750)) ||
	    ((theobj >= 0x759) && (theobj <= 0x75c)) )
		return 1;
	
	elseif( (othertype >= 0x053b) && (othertype <= 0x0553) && (othertype != 0x0550 ) )
		return 1;
	else
		return 0;
	endif

endfunction


function IsOre( item )

	if( item.objtype >= UOBJ_ORE_START  && item.objtype <= UOBJ_ORE_END )
		return 1;
	elseif( item.objtype >= UOBJ_ORE2_START && item.objtype <= UOBJ_ORE2_END )
		return 1;
	elseif( item.objtype >= UOBJ_ORE3_START && item.objtype <= UOBJ_ORE3_END )
		return 1;
	elseif( item.objtype == UOBJ_MAGMA_ORE)
		return 1;
	elseif( item.objtype == UOBJ_MITH_ORE)
		return 1;
	else
		return 0;
	endif

endfunction


function IsReagent( item )

	if( item.objtype >= UOBJ_REAGENT_START && item.objtype <= UOBJ_REAGENT_END )
		return 1;
	else
		return 0;
	endif

endfunction


function IsSand( theobj )

	if( ((theobj >= 0x0016 ) && (theobj <= 0x004b )) ||
	    ((theobj >= 0x011e ) && (theobj <= 0x012d )) ||
	    ((theobj >= 0x0192 ) && (theobj <= 0x01ab )) ||
	    ((theobj >= 0x01b9 ) && (theobj <= 0x01d1 )) ||
	    ((theobj >= 0x0282 ) && (theobj <= 0x0291 )) ||
	    ((theobj >= 0x03b7 ) && (theobj <= 0x03ca )) ||
	    ((theobj >= 0x064b ) && (theobj <= 0x0672 )) )
		return 1;
	else
		return 0;
	endif

endfunction


function IsStackable( item )

	if( Cint(item.amount) > 1 )
		return 1;
	elseif( item.graphic = 0x09ea )
		return 1;
	elseif( item.graphic = 0x0f3f )
		return 1;
	elseif( item.graphic >= 0x0e20 and item.graphic <= 0x0e21 )
		return 1;
	elseif( item.graphic >= 0x0e34 and item.graphic <= 0x0e3a )
		return 1;
	elseif( item.graphic >= 0x0eea and item.graphic <= 0x0ef9 )
		return 1;
	elseif( item.graphic >= 0x0f0f and item.graphic <= 0x0f30 )
		return 1;
	elseif( item.graphic >= 0x0f78 and item.graphic <= 0x0fa1 )
		return 1;
	elseif( item.graphic >= 0x1039 and item.graphic <= 0x1046 )
		return 1;
	elseif( item.graphic >= 0x1078 and item.graphic <= 0x1079 )
		return 1;
	elseif( item.graphic >= 0x14fb and item.graphic <= 0x14fc )
		return 1;
	elseif( item.graphic >= 0x171d and item.graphic <= 0x172d )
		return 1;
	elseif( item.graphic >= 0x1f2d and item.graphic <= 0x1f72 )
		return 1;
	else
		var copy := CreateItemAtLocation( 5283, 1184, 0, CInt(item.objtype), 2 );
		if( copy )
			DestroyItem(copy);
			return 1;
		else
			return 0;
		endif
	endif

	return 0;

endfunction


function IsSwamp( theobjtype )

	if( ((theobjtype >= 0x240 ) && (theobjtype <= 0x250 )) ||
	    ((theobjtype >= 0x3d65) && (theobjtype <= 0x3ef0)) )
		return 1;
	else
		return 0;
	endif

endfunction


function IsTree( theobj )

	if((theobj == 0x0c9e) || (theobj == 0x0ca8) || (theobj == 0x0caa) || (theobj == 0x0cab))
		return 1;
	elseif((theobj >= 0x0c99) && (theobj <= 0x0cea))
		return 1;
	elseif((theobj >= 0x0cf3) && (theobj <= 0x0d03))
		return 1;
	elseif((theobj >= 0x0d41) && (theobj <= 0x0dab))
		return 1;
	elseif((theobj >= 0x0d37) && (theobj <= 0x0d38))
		return 1;
	else
		return 0;
	endif
	
endfunction


function IsWater( theobj )

	if( theobj.item )
		if( (theobj.objtype >=0x346e) && (theobj.objtype <= 0x3485) )
			return 1;
		elseif( (theobj.objtype >= 0x3494) && (theobj.objtype <= 0x34ab) )
			return 1;
		elseif( (theobj.objtype >= 0x34b8) && (theobj.objtype <= 0x34ca) )
			return 1;
		elseif( (theobj.objtype >= 0x1796) && (theobj.objtype <= 0x17b2) )
			return 1;
		endif
	endif

	var info := GetMapInfo( CInt(theobj.x), CInt(theobj.y) );
	var tile := info.landtile;

	if( tile >= 0x04c && tile <= 0x06f )
		return 1;
	elseif( tile >= 0x0a8 && tile <= 0x0ab )
		return 1;
	elseif( tile == 0x0136 || tile == 0x0137 )
		return 1;
	elseif( tile >= 0x3ff0 && tile <= 0x3ff3 )
    		return 1;
    	endif
    
	return 0;

endfunction


function PlayMagicCircleEffect( who )

	var parms := {};
	parms[1] := who;
	parms[2] := 1500;
	parms[3] := 0;
	parms[4] := 0;

	start_script( ":summoning:magiccircleappear", parms );

endfunction


function PlayWaterfallEffect( who )

	var parms := {};
	parms[1] := who;
	parms[2] := 5000;
	parms[3] := 0;
	parms[4] := 0x218;

	start_script( ":summoning:waterfallappear", parms );

endfunction


function ResetAllHitscriptPropsExcep( item, excep := "" )

	var cprops := {	"ChanceOfEffect",
				"EffectCircle",
				"HitWithSpell",
				"Poisonlvl",
				"Powerlevel",
				"ProtectedType",
				"SlayType"	};
			
	foreach cprop in cprops
		if( cprop != excep )
			EraseObjProperty( item, cprop );
		endif
	endforeach

endfunction

function GetCurseLevel( byref item )

	return CInt(GetObjProperty( item, PROPID_ITEM_CURSED ));

endfunction

function SetCurseLevel( byref item, byref level )

	level := CInt(level);
	if( level != SETTING_CURSE_LEVEL_NOT_CURSED )
		return SetObjProperty( item, PROPID_ITEM_CURSED, level );
	else
		return EraseObjProperty( item, PROPID_ITEM_CURSED );
	endif

endfunction
