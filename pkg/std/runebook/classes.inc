use uo;



const CLASSE_BONUS        := 1.5;
const CLASSEID_BARD       := "IsBard";
const CLASSEID_CRAFTER    := "IsCrafter";
const CLASSEID_MAGE       := "IsMage";
const CLASSEID_RANGER     := "IsRanger";
const CLASSEID_THIEF      := "IsThief";
const CLASSEID_WARRIOR    := "IsWarrior";

const EACH_MUST_REPRESENT := 7.5;
const REPRESENT_LEVEL_MOD := 1.0;
const AVERAGE_SKILL       := 75;
const AVERAGE_LEVEL_MOD   := 15;
const BONUS_PER_LEVEL     := 0.25;


function ClasseBonus( who , classeid )

	var level := CInt( GetObjProperty( who , classeid ) );

	if( level )
		return( 1.0 + BONUS_PER_LEVEL * level );
	else
		return( 1.0 );
	endif

endfunction


function ClasseBonusByLevel( level )

	return CDbl( 1.0 + ( BONUS_PER_LEVEL * CDbl(level) ) );

endfunction


function ClasseBonusBySkillId( who, skillid )

	return( ClasseBonusByLevel( IsSpecialisedIn( who , skillid ) ) );

endfunction


function EnumerateRestrictedItemTypesFromClasse( classeid )

	var fract_array := {};
	var restricted_types := {};

	case( classeid )

		CLASSEID_BARD:		fract_array.append( GetPlatemailArmorGraphics() );
					fract_array.append( GetShieldGraphics() );
					break;

		CLASSEID_CRAFTER:	fract_array.append( GetChainmailArmorGraphics() );
					fract_array.append( GetPlatemailArmorGraphics() );
					break;

		CLASSEID_MAGE:		fract_array.append( GetLeatherArmorGraphics() );
					fract_array.append( GetStuddedLeatherArmorGraphics() );
					fract_array.append( GetBoneArmorGraphics() );
					fract_array.append( GetRingmailArmorGraphics() );
					fract_array.append( GetChainmailArmorGraphics() );
					fract_array.append( GetPlatemailArmorGraphics() );
					fract_array.append( GetShieldGraphics() );
					break;

		CLASSEID_RANGER:	fract_array.append( GetPlatemailArmorGraphics() );
					fract_array.append( GetShieldGraphics() );
					break;

		CLASSEID_THIEF:		fract_array.append( GetBoneArmorGraphics() );
					fract_array.append( GetRingmailArmorGraphics() );
					fract_array.append( GetChainmailArmorGraphics() );
					fract_array.append( GetPlatemailArmorGraphics() );
					fract_array.append( GetShieldGraphics() );
					break;

		CLASSEID_WARRIOR:

	endcase


	foreach type in fract_array
		foreach graphic in type
			restricted_types.append( graphic );
		endforeach
	endforeach

	return restricted_types;

endfunction


function GetClasseIdForSkill( skillid )

	foreach id in GetClasseIds()
		if( skillid in GetClasseSkills( id ) )
			return id;
		endif
	endforeach

	return 0;

endfunction


function GetClasseIds()

	return { CLASSEID_BARD,
		 CLASSEID_CRAFTER,
		 CLASSEID_MAGE,
		 CLASSEID_RANGER,
		 CLASSEID_THIEF,
		 CLASSEID_WARRIOR };

endfunction


function GetClasseName( classeid )

        case( classeid )

                CLASSEID_BARD:		return( "Bard" );
                CLASSEID_CRAFTER:	return( "Crafter" );
                CLASSEID_MAGE:		return( "Mage" );
                CLASSEID_RANGER:	return( "Ranger" );
                CLASSEID_THIEF:		return( "Thief" );
                CLASSEID_WARRIOR:	return( "Warrior" );
                default:		return( "INVALID" );

        endcase

endfunction


function GetClasseSkills( classeid )

	case( classeid )

		CLASSEID_BARD:		return { SKILLID_BEGGING	,
						 SKILLID_CARTOGRAPHY	,
						 SKILLID_ENTICEMENT	,
						 SKILLID_HERDING	,
						 SKILLID_MUSICIANSHIP	,
						 SKILLID_PEACEMAKING	,
						 SKILLID_PROVOCATION	,
						 SKILLID_TASTEID	};

		CLASSEID_CRAFTER:	return { SKILLID_ARMSLORE	,
						 SKILLID_BLACKSMITHY	,
						 SKILLID_BOWCRAFT	,
						 SKILLID_CARPENTRY	,
						 SKILLID_LUMBERJACKING	,
						 SKILLID_MINING		,
						 SKILLID_TAILORING	,
						 SKILLID_TINKERING	};

		CLASSEID_MAGE:		return { SKILLID_ALCHEMY	,
						 SKILLID_EVALINT	,
						 SKILLID_INSCRIPTION	,
						 SKILLID_ITEMID		,
						 SKILLID_MAGERY		,
						 SKILLID_MEDITATION	,
						 SKILLID_MAGICRESISTANCE,
						 SKILLID_SPIRITSPEAK	};

		CLASSEID_RANGER:	return { SKILLID_ANIMALLORE	,
						 SKILLID_TAMING		,
						 SKILLID_ARCHERY	,
						 SKILLID_CAMPING	,
						 SKILLID_COOKING	,
						 SKILLID_FISHING	,
						 SKILLID_TRACKING	,
						 SKILLID_VETERINARY	};

		CLASSEID_THIEF:		return { SKILLID_DETECTINGHIDDEN,
						 SKILLID_HIDING		,
						 SKILLID_LOCKPICKING	,
						 SKILLID_POISONING	,
						 SKILLID_REMOVETRAP	,
						 SKILLID_SNOOPING	,
						 SKILLID_STEALING	,
						 SKILLID_STEALTH	};

		CLASSEID_WARRIOR:	return { SKILLID_ANATOMY	,
						 SKILLID_FENCING	,
						 SKILLID_HEALING	,
						 SKILLID_MACEFIGHTING	,
						 SKILLID_PARRY		,
						 SKILLID_SWORDSMANSHIP	,
						 SKILLID_TACTICS	,
						 SKILLID_WRESTLING	};

		default:		return {};

	endcase

endfunction


function GetGeneralSkills()

	return { SKILLID_BEGGING	,
		 SKILLID_ARMSLORE	,
		 SKILLID_MAGICRESISTANCE,
		 SKILLID_ARCHERY	,
		 SKILLID_HIDING		,
		 SKILLID_TACTICS	};

endfunction


function GetMaxCircle( who )

	foreach classeid in GetClasseIds()
		if( GetObjProperty( who , classeid ) )
			return GetMaxCircleForClasse( classeid );
		endif
	endforeach

	return 0;

endfunction


function GetMaxCircleForClasse( classeid )

	case( classeid )

		CLASSEID_BARD:		return 10;

		CLASSEID_CRAFTER:	return 6;

		CLASSEID_MAGE:		return 0;

		CLASSEID_RANGER:	return 8;

		CLASSEID_THIEF:		return 0;

		CLASSEID_WARRIOR:	return 4;

		default:		return 0;

	endcase

endfunction


function GetSkillPointsMultiplier( who, skillid )

	return ClasseBonusByLevel( IsSpecialisedIn( who, skillid ) );

endfunction


function GetStatPointsMultiplier( who , stat )

	var level   := HaveStatAffinity( who , stat );
	var mult    := 1.0;
	if( level )
		mult  := ClasseBonusByLevel( level );
	else
		level := HaveStatDifficulty( who , stat );
		if( level )
			mult := CDbl( 1.0 / ClasseBonusByLevel( level ) );
		endif
	endif

	return mult;

endfunction


function HaveInvalidSkillEnchantmentForClasse( item , classeid )

	var ret	:= 0;
	var skillnum	:= GetObjProperty( item , "skilladv" );

	if( (skillnum) or (skillnum = 0) and !(skillnum in GetGeneralSkills()) )
		if( !(skillnum in GetClasseSkills( classeid )) )
			ret := 1;
		endif
	endif

	return ret;

endfunction


function HaveRestrictedModEnchantmentForClasse( who , item , classeid )

	var ret := 0;

	case( classeid )

		CLASSEID_BARD:		break;

		CLASSEID_CRAFTER:	break;

		CLASSEID_MAGE:		break;

		CLASSEID_RANGER:	break;

		CLASSEID_THIEF:		break;

		CLASSEID_WARRIOR:	if( GetObjProperty( item , "MagicImmunity" ) )
						ret := 1;
					elseif( GetObjProperty( item , "SpellReflect" ) )
						ret := 1;
					elseif( GetObjProperty( item , "PermMagicImmunity" ) )
						ret := 1;
					elseif( GetObjProperty( item , "Permmr" ) )
						ret := 1;
					endif
					break;

	endcase

	return ret;

endfunction


function HaveStatAffinity( who , stat )

	var classeids;

	case( stat )
		"str":	classeids := {  CLASSEID_CRAFTER,
					CLASSEID_WARRIOR };	break;

		"dex":	classeids := {  CLASSEID_BARD,
					CLASSEID_THIEF   };	break;

		"int":	classeids := {  CLASSEID_BARD,
					CLASSEID_MAGE    };	break;

		default:	classeids := {};
	endcase

	foreach id in classeids
		var level := CInt( GetObjProperty( who , id ) );
		if( level )
			return level;
		endif
	endforeach

	return 0;

endfunction


function HaveStatDifficulty( who , stat )

	var classeids, level;

	case( stat )
		"str":
			classeids := {
				CLASSEID_BARD,
				CLASSEID_MAGE
			}; break;
		"dex":
			classeids := {
			};	break;
		"int":
			classeids := {
				CLASSEID_CRAFTER,
				CLASSEID_WARRIOR
			};	break;
		default:
			classeids := {
			};
	endcase

	foreach id in classeids
		level := CInt( GetObjProperty( who , id ) );
		if( level )
			return level;
		endif
	endforeach

	return 0;

endfunction


function IsSpecialisedIn( who, skillid )

	var classeid := GetClasseIdForSkill( skillid );
	if( classeid )
		return CInt( GetObjProperty( who, classeid ) );
	endif

endfunction


function IsBard( who )
	return IsFromThatClasse( who , GetClasseSkills( CLASSEID_BARD ) );
endfunction
function IsCrafter( who )
	return IsFromThatClasse( who , GetClasseSkills( CLASSEID_CRAFTER ) );
endfunction
function IsMage( who )
	return IsFromThatClasse( who , GetClasseSkills( CLASSEID_MAGE ) );
endfunction
function IsRanger( who )
	return IsFromThatClasse( who , GetClasseSkills( CLASSEID_RANGER ) );
endfunction
function IsThief( who )
	return IsFromThatClasse( who , GetClasseSkills( CLASSEID_THIEF ) );
endfunction
function IsWarrior( who )
	return IsFromThatClasse( who , GetClasseSkills( CLASSEID_WARRIOR ) );
endfunction


function IsFromThatClasse( who , classe_skills )

	var classe	:= 0;
	var total	:= 0;
	var number := Len( classe_skills );

	for i := 0 to SKILLID__HIGHEST
		var amount := GetSkill( who , i );
		total := total + amount;
		if( i in classe_skills )
			classe := classe + amount;
		endif
	endfor

	if( classe < AVERAGE_SKILL * number )
		return 0;
	elseif( classe < CInt(total * number * EACH_MUST_REPRESENT * 0.01) )
		return 0;
	else
		var level     := 1;
		var represent := EACH_MUST_REPRESENT + REPRESENT_LEVEL_MOD;
		var percent   := CInt( total * number * represent * 0.01 );
		var average_t := CInt( (AVERAGE_SKILL + AVERAGE_LEVEL_MOD) * number );
		while( (classe >= average_t) and (classe >= percent) )
			level     := level + 1;
			represent := CDbl( represent + REPRESENT_LEVEL_MOD );
			percent   := CInt( total * number * represent * 0.01 );
			average_t := CInt( average_t + AVERAGE_LEVEL_MOD * number );
		endwhile

		return level;
	endif

endfunction


function IsProhibitedByClasse( who , item )

	var ret := 0;

	if( GetObjProperty( who , CLASSEID_BARD	) )
		if( HaveInvalidSkillEnchantmentForClasse( item , CLASSEID_BARD ) )
			ret := 1;
		elseif( item.graphic in EnumerateRestrictedItemTypesFromClasse( CLASSEID_BARD ) )
			ret := 1;
		endif

	elseif( GetObjProperty( who , CLASSEID_CRAFTER ) )
		if( HaveInvalidSkillEnchantmentForClasse( item , CLASSEID_CRAFTER ) )
			ret := 1;
		elseif( GetObjProperty( item , "str" ) )
			ret := 1;
		elseif( item.graphic in EnumerateRestrictedItemTypesFromClasse( CLASSEID_CRAFTER ) )
			ret := 1;
		endif

	elseif( GetObjProperty( who , CLASSEID_MAGE ) )
		if( HaveInvalidSkillEnchantmentForClasse( item , CLASSEID_MAGE ) )
			ret := 1;
		elseif( GetObjProperty( item , "str" ) )
			ret := 1;
		elseif( GetObjProperty( item , "ArBonus" ) )
			ret := 1;
		elseif( item.graphic in EnumerateRestrictedItemTypesFromClasse( CLASSEID_MAGE ) )
			ret := 1;
		endif

	elseif( GetObjProperty( who , CLASSEID_RANGER ) )
		if( HaveInvalidSkillEnchantmentForClasse( item , CLASSEID_RANGER ) )
			ret := 1;
		elseif( item.graphic in EnumerateRestrictedItemTypesFromClasse( CLASSEID_RANGER ) )
			ret := 1;
		endif

	elseif( GetObjProperty( who , CLASSEID_THIEF ) )
		if( HaveInvalidSkillEnchantmentForClasse( item , CLASSEID_THIEF ) )
			ret := 1;
		elseif( item.graphic in EnumerateRestrictedItemTypesFromClasse( CLASSEID_THIEF ) )
			ret := 1;
		endif

	elseif( GetObjProperty( who , CLASSEID_WARRIOR ) )
		if( HaveInvalidSkillEnchantmentForClasse( item , CLASSEID_WARRIOR ) )
			ret := 1;
		elseif( GetObjProperty( item , "int" ) )
			ret := 1;
		elseif( item.graphic in EnumerateRestrictedItemTypesFromClasse( CLASSEID_WARRIOR ) )
			ret := 1;
		elseif( HaveRestrictedModEnchantmentForClasse( who , item , CLASSEID_WARRIOR ) )
			ret := 1;
		endif
	endif

	return ret;

endfunction


function AssignClasse( character )

	var t;

	foreach classe in GetClasseIds()
		EraseObjProperty( character , CLASSEID_BARD );
		t := IsFromThatClasse( character , GetClasseSkills( classe ) );
		if( t )
			SetObjProperty( character , classe , t );
		endif
	endforeach

endfunction
