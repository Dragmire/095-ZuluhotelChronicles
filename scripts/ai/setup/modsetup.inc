use uo;
use os;
use cfgfile;

include "include/attributes";

var modnpc := Self();

if( !modnpc.strength_mod )
	var strmod := GetObjProperty( modnpc , "BaseStrmod" );
	if (strmod)
       	 	SetStrengthMod( modnpc, strmod );
        	SetHp( modnpc, GetMaxHp( modnpc ) );
	endif
endif


if( !modnpc.intelligence_mod )	
	var intmod := GetObjProperty( modnpc , "BaseIntmod" );
	if (intmod)
        	SetIntelligenceMod( modnpc, intmod );
        	SetMana( modnpc, GetMaxMana( modnpc ) );
	endif
endif


if( !modnpc.dexterity_mod )
	var dexmod := GetObjProperty( modnpc , "BaseDexmod" );
	if (dexmod)
        	SetDexterityMod( modnpc, dexmod );
        	SetStamina( modnpc, GetMaxStamina( modnpc ) );
	endif
endif


if( GetObjProperty( modnpc , "BaseHpRegen" ) and modnpc.hp_regen_rate == 100 )
	var base_hp_regen := GetObjProperty( modnpc, "BaseHpRegen" );
	SetObjProperty( modnpc, "baseregen", base_hp_regen );
	SetHpRegenRate(modnpc , ( base_hp_regen));
endif


if( GetObjProperty( modnpc , "BaseManaRegen" ) and modnpc.mana_regen_rate == 100 )
	var base_mana_regen := GetObjProperty( modnpc, "BaseManaRegen" );
	SetObjProperty( modnpc, "basemanaregen", base_mana_regen );
	SetManaRegenRate(modnpc , ( base_mana_regen));
endif


if( GetObjProperty( modnpc , "BaseStaminaRegen" ) and modnpc.stamina_regen_rate == 100 )
	var base_stamina_regen := GetObjProperty( modnpc, "BaseStaminaRegen" );
	SetObjProperty( modnpc, "basestaminaregen", base_stamina_regen );
	SetStaminaRegenRate(modnpc , ( base_stamina_regen) * 12);
endif

if( 1 )
	var equip_cfg := ReadConfigFile(":*:equip");
	if( equip_cfg )
		var equip_elem := FindConfigelem(equip_cfg, modnpc.npctemplate);
		if( equip_elem )
			EquipFromTemplate(modnpc, modnpc.npctemplate);
		endif
	endif
endif


if( !GetObjProperty( modnpc , "Karma" ) )
	var npc_cfg	:= ReadConfigFile( "::npcdesc" );
	var stat_tot	:= modnpc.strength + modnpc.dexterity + modnpc.intelligence;
	var ar	:= modnpc.ar + 3;
	var base	:= Cint(stat_tot * ar / 12);
	if( !base )
		base	:= 1;
	endif
	
	var multiply	:= 1;
	case( modnpc.script )
		"spellkillpcs":	
		"firebreather":	multiply := 1.2;
				break;	
		default:
	endcase
	
	base := Cint(base * multiply);
		
	var bonus := 0;
	foreach item in ListEquippedItems( modnpc )
		if( item.skillid )
			case( item.hitscript )
				":combat:mainhit":		break;
				":combat:banishscript":		bonus := 250;	break;
				":combat:poisonhit":		bonus := 100 + (GetObjProperty( item , "Poisonlvl" ) * 150);	break;
				":combat:piercingscript":	bonus := 500;
				":combat:voidscript":		bonus := 1000;
				":combat:lifedrainscript":	bonus := 250;
				":combat:manadrainscript":	bonus := 200;
				":combat:spellstrikescript":	bonus := 100 + (GetObjProperty( item , "EffectCircle" ) * 50);	break;
				default:
			endcase
		endif
	endforeach

	if( GetObjProperty( modnpc , "BaseHpRegen" ) )
		bonus := bonus + GetObjProperty( modnpc , "BaseHpRegen" );
	endif
	
	if( GetObjProperty( modnpc , "BaseManaRegen" ) )
		bonus := bonus + GetObjProperty( modnpc , "BaseManaRegen" );
	endif
	
	if( GetObjProperty( modnpc , "BaseStaminaRegen" ) )
		bonus := bonus + GetObjProperty( modnpc , "BaseStaminaRegen" );
	endif
	
	var possible_prots := { "PermPoisonImmunity",
			 	  "PermMagicImmunity",
			 	  "Permmr",
			 	  "FireProtection",
			 	  "WaterProtection",
			 	  "AirProtection",
			 	  "EarthProtection",
			 	  "FreeAction",
			 	  "NecroProtection",
			 	  "HolyProtection",
			 	  "PhysicalProtection",
			 	  "HealingIncrease" };
			 	  
	foreach prot in possible_prots
		if( GetObjProperty( modnpc , prot ) )
			bonus := bonus + (GetObjProperty( modnpc , prot ) * 100);
		endif
	endforeach
	
	base := base + bonus;
	if( base > 15000 )
		base := 15000;
	endif
	
	var karma := Cint( base * (Random(21)+90) / 100 );
	var fame  := Cint( base * (Random(21)+90) / 100 * 0.875 );

	case( npc_cfg[modnpc.npctemplate].alignment )
		"evil":		karma := 0 - karma;	break;
		"good":		break;
		
		default:	karma := 0 - karma;	break;
	endcase
	
	SetObjProperty( modnpc , "Karma" , karma );
	SetObjProperty( modnpc , "Fame"  , fame  );
endif


if( !GetObjProperty( modnpc , "AiSerial" ) or GetObjProperty( modnpc , "AiSerial" ) != modnpc.serial )
	SetObjProperty( modnpc , "AiSerial" , modnpc.serial );
endif


if( GetProperty( "Anchor" ) )
	var anchor := GetProperty( "Anchor" );
	SetAnchor( cint(anchor.x), cint(anchor.y), cint(anchor.range), cint(anchor.psub) );
endif