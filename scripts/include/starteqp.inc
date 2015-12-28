use cfgfile;
use os;

include "include/client";
include "include/random";

//
//  See starteqp.cfg for a description of what we expect in the config file.
//

const WEAPON 	:= 1;
const ARMOR 	:= 2;
const SHIELD 	:= 3;
const CLOTHING 	:= 4;
const MISC 	:= 5;
const PROF 	:= 6;
const MAX_COLOR	:= 1184;

var availspells   := 0;
var availtypes 	  := 0;
var availeffects  := 0;
var availgreaters := 0;
var availspellonhit	:= 0;
var availtypeonhit	:= 0;
var availeffectonhit	:= 0;
var availgreateronhit	:= 0;

var magicspawnchance 	:= 0;
var magiclevel 		:= 0;
var basechance 		:= 0;
var baselevel 		:= 0;
var making_starting_equipment := 0;

var starteqp_cfg;
var magiccfg;
var hitscriptcfg;
var onhitcfg;

var unique_items_created := {};


function MakeLoot( corpse , lootgroup := 0, magic_chance_default := 0, magic_level_default := 0 )

	starteqp_cfg := ReadConfigFile( "::nlootgroup" );
	
	if( lootgroup )
		if ( (lootgroup >= 5) and (lootgroup <= 9) )
			magicspawnchance := lootgroup * 10;
			magiclevel := lootgroup - 3;
			basechance := magicspawnchance;
			baselevel  := magiclevel;
		endif

		//spawnchests are lootgroups 109 through 119
		if ( (lootgroup >= 109) and (lootgroup <= 119) )
			magicspawnchance := lootgroup - 75;
			magiclevel := Cint((lootgroup - 109) / 3); 
			basechance := magicspawnchance;
			baselevel  := magiclevel;
		endif
		
		if( magic_chance_default )
			magicspawnchance := magic_chance_default;
			basechance := magicspawnchance;
		endif
		
		if( magic_level_default )
			magiclevel := magic_level_default; 
			baselevel  := magiclevel;
		endif
		
		CreateFromGroup( corpse , Cint(lootgroup) );
		
	else
		var npcdesc := ReadConfigFile( "::npcdesc" );
		var elem := FindConfigElem( npcdesc, GetObjProperty( corpse, "npctemplate" ) );
		var mprop;
		var mlevel;
		var lootgroups;
		if( elem )
			mprop  := GetConfigInt( elem, "Magicitemchance");
			mlevel := GetConfigInt( elem, "Magicitemlevel");
			lootgroups := GetConfigStringArray( elem, "lootgroup" );
		endif

		if( mprop )
			magicspawnchance := mprop;
			basechance := magicspawnchance;
		endif

		if( mlevel )
			magiclevel := mlevel;
			baselevel := magiclevel;
		endif

        	foreach str in lootgroups
            		CreateFromGroup( corpse , cint(str) );
        	endforeach
	endif
	
endfunction



function CreateStartingEquipment( who, skillids )

    	making_starting_equipment := 1;
    	starteqp_cfg := ReadConfigFile( "::starteqp" );

    	foreach skillid in skillids
        	var skillname := GetSkillName( CInt(skillid) );
        	CreateFromGroup( who.backpack, skillname );
    	endforeach

        CreateFromGroup(who.backpack, "all");
        
endfunction



function CreateFromGroup( who, group )

    	var elem := starteqp_cfg[ group ];
	if(!elem)
		return;
	endif

    	foreach str in GetConfigStringArray( elem, "Random" )
        	CreateFromRandomString( who, str );
     	endforeach

    	foreach str in GetConfigStringArray( elem, "Stack" )
        	CreateFromStackString( who, str );
    	endforeach

    	foreach str in GetConfigStringArray( elem, "Item" )
        	CreateFromItemString( who, str );
    	endforeach

    	foreach str in GetConfigStringArray( elem, "Unique" )
        	CreateFromUniqueString( who, str );
    	endforeach

    	foreach str in GetConfigStringArray( elem, "Group" )
        	CreateFromGroup( who, str );
    	endforeach

endfunction



function GetSkillName( skillid )

    	var cfg := ReadConfigFile( "::skills" );
    	return cfg[skillid].name;
    	
endfunction



/////////////////////////////////////////////////////////////////////////////
//
//  An 'Item' string can have one of the following forms:
//
//  FORM                                    EXAMPLE
//  --------------------------------------------------------------------
//  "Item [ObjTypeName]"                    "Item Mortar"
//  "Item [Count] [ObjTypeName]"            "Item 4 EmptyBottle"
//  "Item [ObjTypeName] [Colornum]"         "Item Robe 0xE9"
//  "Item [Count] [ObjTypeName] [Colornum]" "Item 2 Robe 0xE9"
//  "item [ObjTypeName] [chancetospawn][colornum]  "item Longsword 100 0"
//  "Item [Count] [ObjTypeName] [chancetospawn][colornum]  "item 1 Longsword 100 0"
//
//Item 1 level1map 0 1
//
/////////////////////////////////////////////////////////////////////////////

function CreateFromItemString( who, str )

    	var params := SplitWords( str );
    	var count;
    	var objname;
	var chance;
	if ( RandomDiceStr( params[1] ) )
		count := RandomDiceStr( params[1] );
        	params[1] := params[2];
        	params[2] := params[3];
        	params[3] := params[4];
    	else
        	count := 1;
    	endif

    	objname := params[1];
	if (!objname) return; endif
    	if ( CInt(params[2]) )
        	chance := CInt( params[2] );
    	else
        	chance := 100;
    	endif


	while( count )
  		if( Random(100) < chance )
        		var item := CreateItemInContainer( who, objname );
        		var ismagic;
			if ( CInt(params[3]) )
        			item.color := CInt( params[3] );
    			endif

        		if(making_starting_equipment)
           			item.newbie := 1;
        		endif

			while( magiclevel > 0 )
				if( (Random(100)+1) <= magicspawnchance )
					ismagic := 1;
					break;
				else
					magicspawnchance := magicspawnchance + 10;
					magiclevel := magiclevel - 1;
				endif
			endwhile
			
      			if( ismagic )
        			var canbemagic := MagicAllowedandType( objname ); //for magic items!
				var enchant := (Random(75)+26) * Cint(magiclevel/2 + 1);
				if (magiclevel = 5)
					enchant := enchant + 51;
				endif

        			case (canbemagic)
           				WEAPON: 	
                				if(enchant < 75)
							ApplyHPMod( item );

						elseif(enchant < 150)
							ApplyWeapSkillMod( item );

						elseif(enchant < 300)
							ApplyDmgMod ( item );

						elseif(enchant > 350)
							ApplyWeapHitscript ( who , item );
						endif
						AddName( item );
						break;
						
           				ARMOR: 
	                			if(enchant < 75)
							ApplyHPMod( item );
						
						elseif(enchant < 150)
							ApplyArSkillMod( item );
	
						elseif(enchant < 350)
							ApplyARMod( item );
	
						else
							ApplyOnHitScript ( who , item );
						endif
						AddName( item );
						break;
	 
	 				SHIELD:
	 					if(enchant < 100)
							ApplyHPMod( item );
						
						elseif(enchant < 200)
							ApplyArSkillMod( item );
	
						else
							ApplyARMod( item );
						endif
						AddName( item );
						break;
						
					CLOTHING:
						if(enchant < 250)
							ApplyMiscSkillMod( item );

						else
							ApplyMiscArMod ( item );
						endif
						AddName( item );
						AddRandomColor( item );
						break;

					MISC:
	                			if(enchant < 250)
							ApplyMiscSkillMod( item );
						elseif(enchant < 300 )
							ApplyEnchant ( who , item );
						else
							ApplyMiscArMod( item );
						endif
						
						AddName( item );
						break;

					PROF:
						ApplyMiscSkillMod( item );
						AddName( item );
						break;

	           			default:
	
	        		endcase
      			endif
		endif
		count := count - 1;
		magicspawnchance := basechance;
		magiclevel := baselevel;
  	endwhile
  	
endfunction



/////////////////////////////////////////////////////////////////////////////
//
//  A 'Random' string follows the following form:
//
//  FORM                                    EXAMPLE
//  --------------------------------------------------------------------
//  "Random [Count] [GroupName]"            "Random 4 Reagents"
//  "Random [Count] [GroupName] [chancetospawn]"   "Random 4 Reagents 50"
//
//  'Count' entries from 'GroupName' are chosen randomly.  The same entry
//  will not be chosen twice.
//
/////////////////////////////////////////////////////////////////////////////

function CreateFromRandomString( who, desc )

    	var params := SplitWords( desc );
	var count;
	var group;
	var chance;
	var elem;
	var items;
	var stacks;

	if ( RandomDiceStr( params[1] ) )
		count := RandomDiceStr( params[1] );
        	params[1] := params[2];
        	params[2] := params[3];
    	else
        	count := 1;
    	endif

    	group := params[1];

    	if ( CInt(params[2]) )
        	chance := CInt( params[2] );
    	else
        	chance := 100;
    	endif

    	elem := FindConfigElem( starteqp_cfg , group);
    	if( elem = error )
        	return;
    	endif
    	
    	items := GetConfigStringArray( elem , "Item" );
	stacks := GetConfigStringArray( elem , "Stack" );

        if( len(items) )
        
        	if( count > len( items ) )
        		count := len( items );
        	endif
        	
		while( count )
	    		if( Random(100) < chance )
        			var n := RandomDiceStr( "1d"+len(items) );
          		  	if( items[n] )
             	   			CreateFromItemString( who , items[n] );
             	   			items[n] := 0;
            			else
            				continue;
            			endif
            		endif
			count := count - 1;
        	endwhile
        	
        elseif( len(stacks) )

		if( count > len( stacks ) )
        		count := len( stacks );
        	endif

        	while( count )
	    		if( Random(100) < chance )
        			var n := RandomDiceStr( "1d" + len(stacks) );
          		  	if( stacks[n] )
             	   			CreateFromStackString( who , stacks[n] );
             	   			stacks[n] := 0;
            			else
            				continue;
            			endif		
            		endif
			count := count - 1;
        	endwhile	
        endif	
        
endfunction



/////////////////////////////////////////////////////////////////////////////
//
//  A 'Unique' string has the following form:
//
//  FORM                                    EXAMPLE
//  --------------------------------------------------------------------
//  "Unique [ObjTypeName]"                  "Unique Spellbook"
//
//  Only one of a unique item will be created as starting equipment.
//
/////////////////////////////////////////////////////////////////////////////

function CreateFromUniqueString( who, str )

    	var objtype := GetObjtypeByName( str );
    	if (!objtype)
        	return;
    	endif
        
    	if (objtype in unique_items_created)
        	return;
    	endif

    	unique_items_created[ len(unique_items_created) + 1 ] := objtype;
    	var uitem := CreateItemInContainer( who, objtype );
    	
    	if(making_starting_equipment)
           	uitem.newbie := 1;
    	endif
    	
endfunction



/////////////////////////////////////////////////////////////////////////////
//
//  A 'Stack' string is just like "Item" but stacks the item instead of making
//  count number of individual items.
//
/////////////////////////////////////////////////////////////////////////////

function CreateFromStackString( who, str )

    	var params := SplitWords( str );
	var count;
	var objname;
    	var chance;
    	if ( RandomDiceStr( params[1] ) )
        	count := RandomDiceStr( params[1] );
        	params[1] := params[2];
        	params[2] := params[3];
        	params[3] := params[4];
    	else
        	count := 1;
    	endif

    	objname := params[1];
	if (!objname) return; endif
    	if ( CInt(params[2]) )
        	chance := CInt( params[2] );
    	else
        	chance := 100;
    	endif

  	if( Random(100) < chance )
  	
        	var item := CreateItemInContainer( who , objname , count );
        	if (!item)
			return;
        	endif
 
    		if ( CInt(params[3]) )
        		item.color := CInt( params[3] );
    		endif

        	if(making_starting_equipment)
           		item.newbie := 1;
        	endif
        	
  	endif

endfunction



////
//Checks to see if that item is allowed to be magic and returns the type
////
function MagicAllowedandType( objname )

	if( !magiccfg )
		magiccfg := ReadConfigFile( ":combat:enchantableitems" );
	endif

   	var elem1 := FindConfigElem( magiccfg , WEAPON );
   	var data1 := GetConfigInt( elem1 , objname );
   	if( data1 )
      		return WEAPON;
   	endif

   	var elem2 := FindConfigElem( magiccfg , ARMOR );
   	var data2 := GetConfigInt( elem2 , objname );
   	if( data2 )
      		return ARMOR;
   	endif

   	var elem3 := FindConfigElem( magiccfg , SHIELD );
   	var data3 := GetConfigInt( elem3 , objname );
   	if( data3 )
      		return SHIELD;
   	endif

	var elem4 := FindConfigElem( magiccfg , CLOTHING );
	var data4 := GetConfigInt( elem4 , objname );
	if( data4 )
		return CLOTHING;
	endif

	var elem5 := FindConfigElem( magiccfg , MISC );
	var data5 := GetConfigInt( elem5 , objname );
	if( data5 )
		return MISC;
	endif

	var elem6 := FindConfigElem( magiccfg , PROF );
	var data6 := GetConfigInt( elem6 , objname );
	if( data6 )
		return PROF;
	endif
	
   	return 0;

endfunction



////
//Picks and assigns a damagemod and a suffix for the item
////
function ApplyDmgMod( item )

   	var numb := (Random(50)+1) * magiclevel * 2;
	case( Cint(magiclevel / 3) )
		0:	break;
		1:	if( numb < 150 )
				numb := 150;
			endif
			break;
			
		2:	if( numb < 300 )
				numb := 300;
			endif
			break;
	endcase
	
   	if( numb < 100 )
       		item.dmg_mod := 5;
   	elseif( numb < 200 )
       		item.dmg_mod := 10;
   	elseif( numb < 300 )
       		item.dmg_mod := 15;
   	elseif( numb < 500 )
       		item.dmg_mod := 20;
   	elseif( numb < 600 )
       		item.dmg_mod := 25;
	else
		item.dmg_mod := 30;
   	endif


   	if( (Random(100)+1) <= (10 * magiclevel) )
       		if ((Random(100)+1) <= 75)
       			ApplyHPMod( item );
		else
			ApplyWeapSkillMod( item );
		endif
   	endif

endfunction



////
//Picks and assigns a new HP and prefix for the item
////
function ApplyHPMod( item )

   	var numb := (Random(50)+1) * magiclevel * 2;
   	var hp;
   	
   	case( Cint(magiclevel / 3) )
		0:	break;
		1:	if( numb < 75 )
				numb := 75;
			endif
			break;
			
		2:	if( numb < 150 )
				numb := 150;
			endif
			break;
	endcase

   	if( numb < 75 )
		hp := 10;
   	elseif( numb < 150 )
		hp := 20;
   	elseif( numb < 300 )
		hp := 30;
   	elseif( numb < 400 )
		hp := 40;
   	elseif( numb < 550 )
		hp := 50;
	else
		hp := 60;
   	endif

   	item.maxhp_mod := hp;
   	item.hp := item.maxhp;

endfunction



////
//Picks a AR mod and suffix for the item
////
function ApplyARMod( item )

   	var numb := (Random(50)+1) * magiclevel * 2;
   	
	case( Cint(magiclevel / 3) )
		0:	break;
		1:	if( numb < 150 )
				numb := 150;
			endif
			break;
			
		2:	if( numb < 300 )
				numb := 300;
			endif
			break;
	endcase
	
   	if( numb < 150 )
       		item.ar_mod := 5;
   	elseif( numb < 300 )
       		item.ar_mod := 10;
   	elseif( numb < 400 )
       		item.ar_mod := 15;
   	elseif( numb < 500 )
       		item.ar_mod := 20;
   	elseif( numb < 600 )
       		item.ar_mod := 25;
	else
		item.ar_mod := 30;
   	endif


	//Check for another enchantment
   	if( (Random(100)+1) <= (10 * magiclevel) )
       		if ((Random(100)+1) <= 75)
       			ApplyHPMod( item );
		else
			ApplyArSkillMod( item );
		endif
   	endif


endfunction



function ApplyMiscArMod( item )

	var numb := (Random(50)+1) * magiclevel * 2;
	var amount;
	
	case( Cint(magiclevel / 3) )
		0:	break;
		1:	if( numb < 200 )
				numb := 200;
			endif
			break;
			
		2:	if( numb < 350 )
				numb := 350;
			endif
			break;
	endcase

   	if( numb < 200 )
       		amount := 1;
   	elseif( numb < 350 )
       		amount := 2;
   	elseif( numb < 450 )
       		amount := 3;
   	elseif( numb < 550 )
       		amount := 4;
   	elseif( numb < 600 )
       		amount := 5;
	else
		amount := 6;
   	endif
   	
   	SetObjProperty( item , "ArBonus" , amount );
   	
   	//Check for another enchantment
   	if( (Random(100)+1) <= (8 * magiclevel) )
		ApplyMiscSkillMod( item );
   	endif
   	
endfunction



function ApplyWeapHitscript( who , item )

	CountAvailHitscripts( );
	var scripttype := (Random(94)+1) + (magiclevel * 2);
	if (scripttype <= 40)
		ApplySpellHitscript( item );
	elseif (scripttype <= 80)
		ApplySlayerHitscript( item );
	elseif (scripttype <= 100)
		ApplyEffectHitscript( item );
	elseif (scripttype <= 105)
		DestroyItem( item );
		CreateFromRandomString( who , "GMWeapon" );
	else
		ApplyGreaterHitscript( item );
	endif

endfunction



function ApplySpellHitscript( item )

	set_critical( 1 );
	var multiplier := 10;
	
	//Set the spell
	var n := RandomDiceStr( "1d" + availspells );
	var spell := hitscriptcfg[n].Spellid;
	SetObjProperty( item , "HitWithSpell" , spell );
	
	//Set the spell power
	var ascircle := (Random(100)+1) * (magiclevel - 3);
	if (ascircle < 50)
		ascircle := 1;
	elseif (ascircle < 100)
		ascircle := 2;
	elseif (ascircle < 150)
		ascircle := 3;
	elseif (ascircle < 200)
		ascircle := 4;
	elseif (ascircle < 250)
		ascircle := 5;
	elseif (ascircle < 300)
		ascircle := 6;
	else
		ascircle := 7;
	endif


	var ascirclemod := hitscriptcfg[n].AsCircleMod;
	if (ascirclemod)
		ascircle := ascircle + ascirclemod;
	endif

	if (ascircle <= 0)
		ascircle := 1;
	endif

	SetObjProperty( item , "EffectCircle" , ascircle );


	//Set the spell chance
	var chanceofeffect := RandomDiceStr("1d10") * magiclevel;
	var chanceofeffectmod := hitscriptcfg[n].ChanceOfEffectMod;
	if (chanceofeffectmod)
		chanceofeffect := chanceofeffect + chanceofeffectmod;
	endif
	
	if (chanceofeffect <= 0)
		chanceofeffect := 4;
	endif

	SetObjProperty( item , "ChanceOfEffect" , chanceofeffect );
	
	SetHitscript( item , n , multiplier );
	set_critical( 0 );

endfunction



function ApplySlayerHitscript( item )

	set_critical( 1 );
	
	var multiplier := 15;
	
	//Set the creature type
	var n;
	var power := (Random(100)+1) * (magiclevel - 3);
	if (power < 10)
		n := 1;
	elseif (power < 25)
		n := 2;
	elseif (power < 50)
		n := 3;
	elseif (power < 75)
		n := 4;
	elseif (power < 100)
		n := 5;
	elseif (power < 125)
		n := 6;
	elseif (power < 150)
		n := 7;
	elseif (power < 175)
		n := 8;
	elseif (power < 200)
		n := 9;
	elseif (power < 215)
		n := 10;
	elseif (power < 230)
		n := 11;
	elseif (power < 245)
		n := 12;
	elseif (power < 260)
		n := 13;
	elseif (power < 275)
		n := 14;
	elseif (power < 290)
		n := 15;
	elseif (power < 300)
		n := 16;
	else
		n := 17;
	endif

	n := n + availspells;
	
	var type := hitscriptcfg[n].Type;
	SetObjProperty( item , "SlayType" , type );

	SetHitscript( item , n , multiplier );
	
	set_critical( 0 );

endfunction



function ApplyEffectHitscript( item )

	set_critical( 1 );
	
	var multiplier := 10;
	
	//Find the good effect
	var n := RandomDiceStr("1d"+availeffects) + availspells + availtypes;
	SetHitscript( item , n , multiplier );
	
	set_critical( 0 );

endfunction



function ApplyGreaterHitscript ( item )

	set_critical( 1 );
	
	var multiplier := 2;
	
	//Find the good effect
	var n := RandomDiceStr("1d"+availgreaters) + availspells + availtypes + availeffects;
	SetHitscript( item , n , multiplier );
	
	set_critical( 0 );

endfunction



function ApplyWeapSkillMod( item )

	var chance := Random(1000)+1;
	if( chance <= 5 )
		ApplyStatMod( item );
		return;
	endif

	var degree := (Random(50)+1) * magiclevel * 2;
	var amount;
	
	case( Cint(magiclevel / 3) )
		0:	break;
		1:	if( degree < 100 )
				degree := 100;
			endif
			break;
			
		2:	if( degree < 200 )
				degree := 200;
			endif
			break;
	endcase
	
   	if( degree < 100 )
		amount := 5;
   	elseif( degree < 200 )
		amount := 10;
   	elseif( degree < 350 )
		amount := 15;
   	elseif( degree < 450 )
		amount := 20;
   	elseif( degree < 550 )
		amount := 25;
	else
		amount := 30;
   	endif

	var skillid;
	case(Random(2)+1)	
		1:	skillid := item.skillid;
			break;

		default: skillid := SKILLID_TACTICS;
	endcase


	SetObjProperty( item , "skilladv" , skillid );
	SetObjProperty( item , "skilladvamount" , amount );
	SetObjProperty( item , "WeapAdv" , 1 );

	//Check for another enchantment
	if ((Random(100)+1) <= 5 * magiclevel)
		ApplyHpMod( item );
	endif

endfunction



function ApplyArSkillMod( item )

	var chance := Random(1000)+1;
	if (chance <= 5)
		ApplyStatMod( item );
		return;
	endif

	var skillid;
	var amount;
	var numb := (Random(50)+1) * magiclevel * 2;
	
	case( Cint(magiclevel / 3) )
		0:	break;
		1:	if( numb < 200 )
				numb := 200;
			endif
			break;
			
		2:	if( numb < 300 )
				numb := 300;
			endif
			break;
	endcase
	
   	if( numb < 200 )
		amount := 1;
   	elseif( numb < 300 )
		amount := 2;
   	elseif( numb < 400 )
		amount := 3;
   	elseif( numb < 500 )
		amount := 4;
   	elseif( numb < 600 )
		amount := 5;
	else
		amount := 6;
   	endif
	
	case( Random(2)+1 )
		1:	skillid := SKILLID_MAGICRESISTANCE;
			break;
			
		default: skillid := SKILLID_HIDING;
	endcase	


	SetObjProperty( item , "skilladv" , skillid );
	SetObjProperty( item , "skilladvamount" , amount );

	//Check for another enchantment
	if ((Random(100)+1) <= 5 * magiclevel)
		ApplyHpMod( item );
	endif
	
endfunction



function ApplyMiscSkillMod( item )

	var chance := Random(1000)+1;
	if (chance <= 5)
		ApplyStatMod( item );
		return;
	endif


	var skillid;
	var amount;

	var numb := (Random(50)+1) * magiclevel * 2;
	
	case( Cint(magiclevel / 3) )
		0:	break;
		1:	if( numb < 200 )
				numb := 200;
			endif
			break;
			
		2:	if( numb < 300 )
				numb := 300;
			endif
			break;
	endcase
	
   	if( numb < 200 )
		amount := 1;
   	elseif( numb < 300 )
		amount := 2;
   	elseif( numb < 400 )
		amount := 3;
   	elseif( numb < 500 )
		amount := 4;
   	elseif( numb < 600 )
		amount := 5;
	else
		amount := 6;
   	endif

	var multiplier := Cint( GetObjProperty( item , "SpecMult" ) );
	if( multiplier )
		amount := amount * multiplier;
	endif
		
	var skills := GetObjProperty( item , "AvailSkills" );
	if ( skills )
		skillid := skills[RandomDiceStr("1d" + len(skills))];
	else		
		skillid := Random(SKILLID__HIGHEST + 1);
	endif

	SetObjProperty( item , "skilladv" , skillid );
	SetObjProperty( item , "skilladvamount" , amount );

endfunction



function ApplyOnHitScript ( who , item )

	CountAvailOnHitscripts( );
	var scripttype := (Random(94)+1) + (magiclevel * 2);
	if (scripttype <= 40)
		ApplySpellOnHitscript( item );
	elseif (scripttype <= 80)
		ApplyResistantOnHitscript( item );
	elseif (scripttype <= 100)
		ApplyEffectOnHitscript( item );
	elseif (scripttype <= 105)
		DestroyItem( item );
		CreateFromRandomString( who , "GMArmor" );
	else
		ApplyGreaterOnHitscript( item );
	endif
	
endfunction



function ApplySpellOnHitscript( item )

	set_critical( 1 );
	
	var multiplier := 10;
	
	//Set the spell
	var n := RandomDiceStr( "1d"+availspellonhit );
	var spell := onhitcfg[n].Spellid;
	SetObjProperty( item , "HitWithSpell" , spell );

	//Set the spell power
	var ascircle := (Random(100)+1) * (magiclevel - 3);
	if (ascircle < 50)
		ascircle := 1;
	elseif (ascircle < 100)
		ascircle := 2;
	elseif (ascircle < 150)
		ascircle := 3;
	elseif (ascircle < 200)
		ascircle := 4;
	elseif (ascircle < 250)
		ascircle := 5;
	elseif (ascircle < 300)
		ascircle := 6;
	else
		ascircle := 7;
	endif


	var ascirclemod := onhitcfg[n].AsCircleMod;
	if (ascirclemod)
		ascircle := ascircle + ascirclemod;
	endif

	if (ascircle <= 0)
		ascircle := 1;
	endif

	SetObjProperty( item , "EffectCircle" , ascircle );


	//Set the spell chance
	var chanceofeffect := RandomDiceStr("1d10") * magiclevel;
	var chanceofeffectmod := onhitcfg[n].ChanceOfEffectMod;
	if (chanceofeffectmod)
		chanceofeffect := chanceofeffect + chanceofeffectmod;
	endif
	
	if (chanceofeffect <= 0)
		chanceofeffect := 4;
	endif

	SetObjProperty( item , "ChanceOfEffect" , chanceofeffect );

	SetOnHitscript( item , n , multiplier );

	set_critical( 0 );
	
endfunction



function ApplyResistantOnHitscript( item )

	set_critical( 1 );
	
	var multiplier := 15;
	
	//Set the creature type
	var n;
	var power := (Random(100)+1) * (magiclevel - 3);
	if (power < 10)
		n := 1;
	elseif (power < 25)
		n := 2;
	elseif (power < 50)
		n := 3;
	elseif (power < 75)
		n := 4;
	elseif (power < 100)
		n := 5;
	elseif (power < 125)
		n := 6;
	elseif (power < 150)
		n := 7;
	elseif (power < 175)
		n := 8;
	elseif (power < 200)
		n := 9;
	elseif (power < 215)
		n := 10;
	elseif (power < 230)
		n := 11;
	elseif (power < 245)
		n := 12;
	elseif (power < 260)
		n := 13;
	elseif (power < 275)
		n := 14;
	elseif (power < 290)
		n := 15;
	elseif (power < 300)
		n := 16;
	else
		n := 17;
	endif

	n := n + availspellonhit;
	
	var type := onhitcfg[n].Type;
	SetObjProperty( item , "ProtectedType" , type );

	SetOnHitscript( item , n , multiplier );

	set_critical( 0 );
	
endfunction



function ApplyEffectOnHitscript( item )

	set_critical( 1 );
	
	var multiplier := 10;
	
	//Find the good effect
	var n := RandomDiceStr( "1d"+availeffectonhit) + availspellonhit + availtypeonhit;
	SetOnHitscript( item , n , multiplier );

	set_critical( 0 );
	
endfunction



function ApplyGreaterOnHitscript( item )
	
	set_critical( 1 );
	
	var multiplier := 2;
	
	//Find the good script
	var n := RandomDiceStr( "1d"+availgreateronhit) + availspellonhit + availtypeonhit + availeffectonhit;
	SetOnHitscript( item , n , multiplier );

	set_critical( 0 );
	
endfunction



function ApplyStatMod ( item )

	var numb := (Random(100)+1) * magiclevel;
	var amount;
   	if( numb < 200 )
		amount := 5;
   	elseif( numb < 300 )
		amount := 10;
   	elseif( numb < 400 )
		amount := 15;
   	elseif( numb < 500 )
		amount := 20;
   	elseif( numb < 600 )
		amount := 25;
	else
		amount := 30;
   	endif

	var id := Random(3)+1;
	if( id = 1 )
		SetObjProperty( item , "str" , amount );
		
	elseif( id = 2 )
		SetObjProperty( item , "int" , amount );
	
	else
		SetObjProperty( item , "dex" , amount );
	endif

	//Check for another enchantment
	if ((Random(100)+1) <= 2 * magiclevel)
		ApplyHpMod( item );
	endif

endfunction



function ApplyEnchant( who , item )

	var numb := (Random(100)+1) * magiclevel;
	if( numb < 300 )
		ApplyProtection( item );
	elseif( numb < 500 )
		ApplyElementalImmunity( item );
	elseif( numb < 550 )
		DestroyItem( item );
		CreateFromRandomString( who , "MiscMagicItem" );
		return;
	else
		ApplyImmunity( item );
	endif
	
	//Check for another enchantment
	if ((Random(100)+1) <= (5 * magiclevel))
		var secchance := Random(100)+1;
		if (secchance < 75)
       			ApplyMiscSkillMod( item );
		else
			ApplyMiscArMod( item );
		endif
	endif

endfunction



function ApplyProtection( item )

	var numb := (Random(50)+1) * magiclevel * 2;
	var ptype;
	var charges;
	
	case( Cint(magiclevel / 3) )
		0:	break;
		1:	if( numb < 75 )
				numb := 75;
			endif
			break;
			
		2:	if( numb < 150 )
				numb := 150;
			endif
			break;
	endcase
	
	if( numb < 75 )
		charges := 5;
   	elseif( numb < 150 )
		charges := 10;
   	elseif( numb < 300 )
		charges := 15;
   	elseif( numb < 400 )
		charges := 20;
   	elseif( numb < 550 )
		charges := 25;
	else
		charges := 30;
   	endif
   	

	case( RandomDiceStr( "1d3" ) )
		1:	ptype := "PoisonImmunity";
			break;
			 
		2:	ptype := "MagicImmunity";
			break;
			 
		3:	ptype := "SpellReflect";
			break;
			 
		default: ptype := "SpellReflect";
	endcase

	SetObjProperty( item , ptype , charges );
	
endfunction



function ApplyImmunity( item )

	var n;
	var itype;
	var power := (Random(100)+1) * (magiclevel - 3);
	
	case( Cint(magiclevel / 3) )
		0:	break;
		1:	if( power < 170 )
				power := 170;
			endif
			break;
			
		2:	if( power < 200 )
				power := 200;
			endif
			break;
	endcase
	
	if (power < 170)
		n := 1;
	elseif (power < 200)
		n := 2;
	elseif (power < 230)
		n := 3;
	elseif (power < 270)
		n := 4;
	elseif (power < 300)
		n := 5;
	else
		n := 6;
	endif
	
	case(Random(3)+1)
		1:	itype := "PermPoisonImmunity";
			break;
			
		2:	itype := "PermMagicImmunity";
			break;
			
		default: itype := "Permmr";
	endcase

	SetObjProperty( item , itype , n );
	
endfunction



function ApplyElementalImmunity( item )

	var element;
	var power;
	var numb := (Random(100)+1) * magiclevel;
	
	case( Cint(magiclevel / 3) )
		0:	break;
		1:	if( numb < 150 )
				numb := 150;
			endif
			break;
			
		2:	if( numb < 300 )
				numb := 300;
			endif
			break;
	endcase
	
	if( numb < 150 )
       		power := 1;
   	elseif( numb < 300 )
       		power := 2;
   	elseif( numb < 450 )
       		power := 3;
   	elseif( numb < 550 )
       		power := 4;
   	elseif( numb < 600 )
       		power := 5;
	else
		power := 6;
   	endif
	
	case(Random(9)+1)
		1:	element := "FireProtection";
			break;
		
		2:	element := "WaterProtection";
			break;
		
		3:	element := "AirProtection";
			break;
		
		4:	element := "EarthProtection";
			break;
		
		5:	element := "FreeAction";
			power := 1;
			break;
		
		6:	element := "NecroProtection";
			break;
		
		7:	element := "HolyProtection";
			break;
			
		8:	element := "HealingIncrease";
			break;
		
		default: element := "PhysicalProtection";
	endcase

	SetObjProperty( item , element , power );
	
endfunction

	

////
//Adds "a magic " to the beginning of the item's desc.
////
function AddName( item )

   	var currdesc := item.desc;
   	if( currdesc[1] = "a" )
      		var space := find( item.desc, " ", 1 );
      		var newname := currdesc[space + 1 , len(item.desc)];
      		SetName( item , "a magic " + newname );
   	else
      		SetName( item , "magic " + currdesc );
   	endif

	if( GetObjProperty( item , "IsGMItem" ))
		return;
	endif
	
	SetObjProperty( item , "UnIDedMagicalItem" , 1 );
	
	if( (item.objtype < 0x1eff or item.objtype > 0x1f04) and (Random(100)+1) <= 5 )
		SetObjProperty(item , "Cursed" , 1 );
	endif

endfunction



function AddRandomColor( item )

	SetObjProperty( item , "Undyeable" , 1 );
	if( !GetObjProperty( item , "EnchantColor" ) )
		var color := RandomDiceStr( "1d"+MAX_COLOR );
		while( color > 999 and color < 1152 )
			color := RandomDiceStr( "1d"+MAX_COLOR );
		endwhile
	
		SetObjProperty( item , "EnchantColor" , color );
	endif

endfunction



function CountAvailHitscripts( )

	hitscriptcfg 		:= ReadConfigFile( ":combat:hitscriptdesc" );
	var availelem 	:= FindConfigElem( hitscriptcfg , "data" );
	availspells 		:= GetConfigInt( availelem , "NbSpell" );
	availtypes 		:= GetConfigInt( availelem , "NbSlayer" );
	availeffects 		:= GetConfigInt( availelem , "NbEffect" );
	availgreaters 		:= GetConfigInt( availelem , "NbGreater" );

endfunction



function CountAvailOnHitscripts( )

	onhitcfg 		:= ReadConfigFile( ":combat:onhitscriptdesc" );
	var availelem 	:= FindConfigElem( onhitcfg , "data" );
	availspellonhit 	:= GetConfigInt( availelem , "NbSpell" );
	availtypeonhit 		:= GetConfigInt( availelem , "NbSlayer" );
	availeffectonhit 	:= GetConfigInt( availelem , "NbEffect" );
	availgreateronhit 	:= GetConfigInt( availelem , "NbGreater" );
	
endfunction



function SetHitscript( item , n , multiplier )

	set_critical( 1 );
	
	//Apply the hitscript
	hitscriptcfg	:= ReadConfigFile( ":combat:hitscriptdesc" );
	item.hitscript	:= hitscriptcfg[n].Hitscript;
	SetObjProperty( item , "HitscriptNumber" , n );
	
	var CProp := hitscriptcfg[n].CProp;
	if( CProp )
		var CPropVal := hitscriptcfg[n].CPropVal;
		if( !CPropVal )
			var power := (Random(10)+1) * magiclevel;
			CPropVal := Cint(power / 6);
			var mult := onhitcfg[n].Multiplier;
			if( mult )
				CPropVal := Cint(CPropVal * mult);
			endif
			
			if( CProp = "Poisonlvl" )
				CPropVal := CPropVal - 3;
			endif
			
			if( CPropVal < 1 )
				CPropVal := 1;
			endif
		endif
		SetObjProperty( item , CProp , CPropVal );
	endif
	
	//Check for another enchantment
	if (hitscriptcfg[n].Place = 2)
		if ( (Random(100)+1) <= (multiplier * magiclevel))
			if ((Random(100)+1) <= 75)
       				ApplyHPMod( item );
			else
				ApplyWeapSkillMod( item );
			endif
		endif

	else
		if ( (Random(100)+1) <= (multiplier * magiclevel))
			var secchance := (Random(100)+1);
			if (secchance < 60)
       				ApplyHPMod( item );
			elseif (secchance < 90)
				ApplyWeapSkillMod( item );
			else
				ApplyDmgMod( item );
			endif
		endif
	endif
	
	set_critical( 0 );
	
endfunction



function SetOnHitscript( item , n , multiplier )

	set_critical( 1 );
	
	//Apply the hitscript
	onhitcfg := ReadConfigFile( ":combat:onhitscriptdesc" );
	SetObjProperty( item , "OnHitScript" , onhitcfg[n].OnHitscript);
	SetObjProperty( item , "OnHitscriptNumber" , n );
	
	var CProp := onhitcfg[n].CProp;
	if( CProp )
		var CPropVal := onhitcfg[n].CPropVal;
		if( !CPropVal )
			var power := (Random(10)+1) * magiclevel;
			CPropVal := Cint(power / 6);
			var mult := onhitcfg[n].Multiplier;
			if( mult )
				CPropVal := Cint(CPropVal * mult);
			endif
			
			if( CProp = "Poisonlvl" )
				CPropVal := CPropVal - 3;
			endif
			
			if( CPropVal < 1 )
				CPropVal := 1;
			endif
		endif
		SetObjProperty( item , CProp , CPropVal );
	endif
	
	//Check for another enchantment
	if (onhitcfg[n].Place = 2)
		if ( (Random(100)+1) <= (multiplier * magiclevel))
			if ((Random(100)+1) <= 75)
       				ApplyHPMod( item );
			else
				ApplyArSkillMod( item );
			endif
		endif

	else
		if ( (Random(100)+1) <= (multiplier * magiclevel))
			var secchance := Random(100)+1;
			if (secchance < 60)
       				ApplyHPMod( item );
			elseif (secchance < 90)
				ApplyArSkillMod( item );
			else
				ApplyARMod( item );
			endif
		endif
	endif
	
	set_critical( 0 );
	
endfunction