//Edited by Sno 17/1/03. RenameBySkill altered.

use uo;
use cfgfile;
//include "include/attributes";

var immunities := {  "AirProtection",
			"EarthProtection",
			"FreeAction",
			"FireProtection",
			"HealingIncrease",
			"HolyProtection",
			"NecroProtection",
			"PermMagicImmunity",
			"Permmr",
			"PermPoisonImmunity",
			"PhysicalProtection",
		  	"WaterProtection"
		  	 			};
		  	 		
var regenerations := { "HpRegen",
			  "ManaRegen",
			  "StamRegen"		};
			 

function SetNameByEnchant( item, cursed := 5 )

	if( GetObjProperty( item, "UnIDedMagicalItem" ) )
		EraseObjProperty( item, "UnIDedMagicalItem" );
	endif

	SetObjProperty( item, "IDed", 1 );

	var staticname;
	if( cursed == 5 )
		staticname := GetObjProperty( item, "StaticName" );
	else
		staticname := GetObjProperty( item, "StaticCursedName" );
	endif

	if( staticname )
		var static_c := CInt( GetObjProperty( item, "StaticColor" ) );
		if( static_c )
			item.color := static_c;
		endif
		SetName( item, staticname );
		return;
	endif

	var basename := GetObjProperty( item, "BaseName" );
	if( !basename )
		var conf := ReadConfigFile(":*:itemdesc");
		var newname := conf[item.objtype].desc;
		SetName( item, newname );
	else
		SetName( item, basename );
	endif


	//See if the base item is a normal one or a special one
	if (GetObjProperty( item, "Enchanted" ))
		SetName( item, GetObjProperty( item, "Enchanted" ) + " " + item.desc );
	endif

	//See if there's a special color for the item
	if (GetObjProperty( item, "EnchantColor" ))
		item.color := CInt( GetObjProperty( item, "EnchantColor" ) );
	endif

	//See if it's a gm item
	var gmname := GetObjProperty( item, "IsGMItem" );
	if ( gmname )
		SetName( item, gmname );
		SetObjProperty(item, "IDed", 1 );
		return;
	endif

	//See if the item have a special hitscript and apply the name
	var hitscript := GetObjProperty( item, "HitscriptNumber" );
	if ( hitscript )
		RenameByHitscript( item, hitscript, cursed );
	endif


	//See if the item have a special onhitscript and apply the name
	var onhit := GetObjProperty( item, "OnHitscriptNumber" );
	if ( onhit )
		RenameByOnHitscript( item, onhit, cursed );
	endif


	//See if the item have a dmg mod and apply the name
	var dmgmod := item.dmg_mod;
	if ( dmgmod )
		RenameByMod( item, "dmg", dmgmod, cursed );
	endif


	//See if the item have a armor mod and apply the name
	var armod := item.ar_mod;
	if ( armod )
		RenameByMod( item, "ar", armod, cursed );
	endif


	//See if the item got an armor bonus and apply the name	 
	var arbonus := GetObjProperty( item, "ArBonus" );
	if ( arbonus )
		RenameByMod( item, "ArBonus", arbonus * 5, cursed );
	endif


	//See if the item have immunities and apply the name	 
	foreach prot in immunities
		if ( GetObjProperty( item, prot ) )
			RenameByImmunity( item, prot, GetObjProperty( item, prot ), cursed );
		endif
	endforeach

	//Look for the regenerations mods
	foreach mod in regenerations
		if ( GetObjProperty( item, mod ) )
			RenameByImmunity( item, mod, CInt(GetObjProperty( item, mod )/100), cursed );
		endif
	endforeach

	//See if the item have a poison protection
	if ( GetObjProperty( item, "PoisonImmunity" ) )
		RenameByProt( item, "PoisonImmunity", cursed );
	endif


	//See if the item have a magic protection
	if ( GetObjProperty( item, "MagicImmunity" ) )
		RenameByProt( item, "MagicImmunity", cursed );
	endif


	//See if the item have a reflection enchantment
	if ( GetObjProperty( item, "SpellReflect" ) )
		RenameByProt( item, "SpellReflect", cursed );
	endif


	//See if the item have a hp mod and apply the name
	var hpmod := item.maxhp_mod;
	if ( hpmod )
		RenameByMod( item, "maxhp", hpmod / 2, cursed );
	endif


	//See if the item have a stat mod and apply the name
	if ( GetObjProperty( item, "str" ) )
		RenameByMod( item, "str", CInt(GetObjProperty( item, "str" )), cursed );
	elseif ( GetObjProperty( item, "int" ) )
		RenameByMod( item, "int", CInt(GetObjProperty( item, "int" )), cursed );
	elseif ( GetObjProperty( item, "dex" ) )
		RenameByMod( item, "dex", CInt(GetObjProperty( item, "dex" )), cursed );
	endif


	//See if the item have a skill mod and apply the name
	var skillid := GetObjProperty( item, "skilladv" );
	if ( skillid || skillid == 0 )
		RenameBySkill( item, skillid, cursed );
	endif

	var static_color := CInt( GetObjProperty( item, "StaticColor" ) );
	if( static_color )
		item.color := static_color;
	endif

endfunction



function RenameByHitscript( item, hitscript, cursed := 0 )

	var itemcfg	:= ReadConfigFile( ":combat:hitscriptdesc" );
	var elem	:= FindConfigElem( itemcfg, hitscript );
	var key	:= "Name";
	item.hitscript	:= CStr( elem.hitscript );
	SetAdjective( item, elem, key, cursed );

endfunction



function RenameByOnHitscript( item, onhit, cursed := 0 )

	var itemcfg := ReadConfigFile( ":combat:onhitscriptdesc" );
	var elem := FindConfigElem( itemcfg, onhit );
	var key := "Name";
	SetAdjective( item, elem, key, cursed );

endfunction



function RenameByMod( item, stat, modam, cursed := 0 )

	var itemcfg := ReadConfigFile( ":combat:modenchantdesc" );
	var elem := FindConfigElem( itemcfg, stat );
	modam := modam / 5;
	var key := "Name" + modam;
	SetAdjective( item, elem, key, cursed );

endfunction


function RenameBySkill( item, id := 0, cursed := 0)

	var itemcfg := ReadConfigFile( ":combat:modenchantdesc" );
	var elem := FindConfigElem( itemcfg, id );

	var amount := CInt(GetObjProperty( item, "skilladvamount" )); //Removed checking of SpecMult and weapon class.

	var key := "Name" + amount;
	SetAdjective( item, elem, key, cursed );

endfunction


function RenameByImmunity( item, id, power, cursed := 0 )

	var cfg := ReadConfigFile( ":combat:modenchantdesc" );
	var elem := FindConfigElem( cfg, id );
	var key := "Name" + power;
	SetAdjective( item, elem, key, cursed );

endfunction


function RenameByProt( item, id, cursed )

	var cfg := ReadConfigFile( ":combat:modenchantdesc" );
	var elem := FindConfigElem( cfg, id );
	var key := "Name";
	SetAdjective( item, elem, key, cursed );

endfunction


function RevealCurse( item )

	SetNameByEnchant( item, 1 );
	OpposeEffect( item );
	SetObjProperty( item, "Cursed", 2 );

endfunction


function BanishCurse( item )

	var curselevel := GetObjProperty( item, "Cursed" );
	if( !curselevel )
		if( GetObjProperty( item, "UnIDedMagicalItem" ) )
			SetNameByEnchant( item );
		endif

	elseif( curselevel == 1 )
		EraseObjProperty( item, "Cursed" );

	else
		OpposeEffect( item );
		if (!GetObjProperty( item, "UnIDedMagicalItem" ))
			var conf := ReadConfigFile(":*:itemdesc");
			var newname := conf[item.objtype].desc;
			SetName( item, newname );
		endif
		SetNameByEnchant( item );
		EraseObjProperty( item, "Cursed" );
		EraseObjProperty( item, "StayEquipped" );
		SetObjProperty( item, "WasCursed", 1 );
	endif

endfunction


function OpposeEffect( item )

	if ( item.maxhp_mod )
		item.maxhp_mod := 0 - item.maxhp_mod;
		if( item.hp > item.maxhp )
			item.hp := item.maxhp;
		endif
	endif

	if ( GetObjProperty( item, "skilladv" ) )
		var amount := CInt(GetObjProperty( item, "skilladvamount" ));
		SetObjProperty( item, "skilladvamount", 0 - amount );
	endif

	if ( GetObjProperty( item, "str" ) )
		SetObjProperty( item, "str", 0 - CInt(GetObjProperty(item, "str")) );
	endif

	if ( GetObjProperty( item, "int" ) )
		SetObjProperty( item, "int", 0 - CInt(GetObjProperty(item, "int")) );
	endif

	if ( GetObjProperty( item, "dex" ) )
		SetObjProperty( item, "dex", 0 - CInt(GetObjProperty(item, "dex")) );
	endif

	if ( item.dmg_mod )
		item.dmg_mod := 0 - item.dmg_mod;
	endif

	if ( item.ar_mod )
		item.ar_mod := 0 - item.ar_mod;
	endif

	if ( GetObjProperty( item, "ArBonus" ) )
		SetObjProperty( item, "ArBonus", 0 - CInt(GetObjProperty( item, "ArBonus" )) );
	endif

	foreach prot in immunities
		if ( GetObjProperty( item, prot ) )
			SetObjProperty( item, prot, 0 - CInt( GetObjProperty( item, prot )) );
		endif
	endforeach

	foreach regen in regenerations
		if ( GetObjProperty( item, regen ) )
			SetObjProperty( item, regen, 0 - CInt( GetObjProperty( item, regen )) );
		endif
	endforeach


endfunction


function SetAdjective( item, elem, basekey, cursed := 0 )

	var colorkey := "Color";

	if ( cursed == 1 )
		basekey := "C" + basekey;
		colorkey := "C" + colorkey;
	endif

	var place := GetConfigInt( elem, "Place" );
	var adjective := GetConfigString( elem, basekey );
	if (place == 1)
		SetName( item, adjective + " " + item.desc );
	else
		SetName( item, item.desc + " " + adjective );
	endif

	var color := CInt( GetConfigString( elem, colorkey ) );
	if( color )
		item.color := color;
	endif

endfunction