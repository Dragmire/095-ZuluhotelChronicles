use uo;
use os;
use npc;

include "include/client";
//include "include/attributes";
include "include/dotempmods";
include "include/spelldata";
include "include/random";

function castspell( caster, cast_on, spellname )

	case (spellname)
	"summonskel":
		SummonSkel(caster,cast_on);

	default:
		var spellid := GetSpellID(spellname);
		if (!spellid)
			return;
		endif

		if (!PrepareToCast(caster,cast_on,spellid))
			return;
		endif

		var parms array;
		parms[1] := "#MOB";
		parms[2] := caster;
		parms[3] := cast_on;

		Detach();

		start_script( GetScript( spellid ), parms );
	endcase

endfunction

function SummonSkel(me, onwho)

	var timescasted := GetObjProperty(me, "timescasted");

	if ((!timescasted) || (timescasted!="")) timescasted :=0; endif

	timescasted := timescasted +1;
	SetObjProperty(me, "timescasted", timescasted);

	if (timescasted>=2) return; endif

	var utterance := Random(4);

	case (utterance)
        	0: say("Awake, my children! Come forth and take your rightful place!");
        	1: say("Come forth my minions!");
        	2: say("I call upon the forces of darkness to attend me!");
        	3: say("Mortal, you shall soon be my slave!");
	endcase

	NpcSummonCreature( me, "skeleton" );

endfunction


function GetSpellID(spellname)

	var spellid := 0;

	case (spellname)
	"clumsy"	: spellid := 1;
	"feeblemind"	: spellid := 3;
	"heal"		: spellid := 4;
	"magicarrow"	: spellid := 5;
	"reactivearmor"	: spellid := 7;
	"weaken"	: spellid := 8;
	"agility"	: spellid := 9;
	"cunning"	: spellid := 10;
	"cure"		: spellid := 11;
	"harm"		: spellid := 12;
	"protection"	: spellid := 15;
	"strength"	: spellid := 16;
	"bless"		: spellid := 17;
	"fireball"	: spellid := 18;
	"poison"	: spellid := 20;
	"teleport"	: spellid := 22;
	"wallofstone"	: spellid := 24;
	"archcure"	: spellid := 25;
	"archprot"	: spellid := 26;
	"curse"		: spellid := 27;
	"firefield"	: spellid := 28;
	"gheal"		: spellid := 29;
	"lightning"	: spellid := 30;
	"manadrain"	: spellid := 31;
	"blade_spirit"	: spellid := 33;
	"dispel_field"	: spellid := 34;
	"reflect"	: spellid := 36;
	"mindblast"	: spellid := 37;
	"paralyze"	: spellid := 38;
	"poisonfield"	: spellid := 39;
	"summon_creature": spellid := 40;
	"dispel"	: spellid := 41;
	"ebolt"		: spellid := 42;
	"explosion"	: spellid := 43;
	"invisibility"	: spellid := 44;
	"masscurse"	: spellid := 46;
	"parafield"	: spellid := 47;
	"reveal"	: spellid := 48;
	"chain_lightning": spellid := 49;
	"energy_field"	: spellid := 50;
	"fstrike"	: spellid := 51;
	"manavamp"	: spellid := 53;
	"massdispel"	: spellid := 54;
	"meteor_swarm"	: spellid := 55;
	"polymorph"	: spellid := 56;
	"earthquake"	: spellid := 57;
	"vortex"	: spellid := 58;
	"resurrect"	: spellid := 59;
	"summon_air"	: spellid := 60;
	"summon_daemon"	: spellid := 61;
	"summon_earth"	: spellid := 62;
	"summon_fire"	: spellid := 63;
	"summon_water"	: spellid := 64;
	"controlundead"	: spellid := 65;
	"darkness"	: spellid := 66;
	"decayingray"	: spellid := 67;
	"spectretouch"	: spellid := 68;
	"abyssalflame"	: spellid := 69;
	"animate_dead"	: spellid := 70;
	"sacrifice"	: spellid := 71;
	"wraithbreath"	: spellid := 72;
	"sorcerersbane"	: spellid := 73;
	"summon_spirit"	: spellid := 74;
	"wraithform"	: spellid := 75;
	"wyvernstrike"	: spellid := 76;
	"kill"		: spellid := 77;
	"liche"		: spellid := 78;
	"plague"	: spellid := 79;
	"spellbind"	: spellid := 80;
	"antidote"	: spellid := 81;
	"owlsight"	: spellid := 82;
	"shiftingearth"	: spellid := 83;
	"summonmammals"	: spellid := 84;
	"calllightning"	: spellid := 85;
	"earthblessing"	: spellid := 86;
	"earthportal"	: spellid := 87;
	"naturestouch"	: spellid := 88;
	"gustofair"	: spellid := 89;
	"risingfire"	: spellid := 90;
	"shapeshift"	: spellid := 91;
	"icestrike"	: spellid := 92;
	"earthspirit"	: spellid := 93;
	"flamespirit"	: spellid := 94;
	"stormspirit"	: spellid := 95;
	"waterspirit"	: spellid := 96;

	endcase

	return spellid;

endfunction

function PrepareToCast(caster, cast_on, spellid)

	if (!CheckLineOfSight( caster, cast_on ))
		return 0;
	endif

	if (saywords)
		SpeakPowerWords( me, spellid);
		PerformAction(caster,ANIM_CAST_DIR);
		sleep(1);
	endif

	if (GetEffectiveSkill(caster, SKILLID_MAGERY))
		if (!CheckSkill(caster, SKILLID_MAGERY, GetSpellDifficulty( spellid ), 100))
			PlaySoundEffect(caster,0x005d);
			PlayObjectCenteredEffect(caster, 0x3735,10, 30);
			return 0;
		endif
	endif

	if (! ConsumeMana( caster, spellid ))
		return 0;
	endif

	return 1;

endfunction

function cast_offensive_spell(caster, cast_on)

	var thespell := spells[Random( len(spells) +1 )];

if(thespell == 29)
        castspell(caster, caster, thespell);
else

	castspell(caster, cast_on, thespell);
endif


endfunction

function NpcSummonCreature( caster, npctemplate, sfx := 0x0218 )

	var parms := {};

	parms[1] := caster;
	parms[2] := npctemplate;
	parms[3] := sfx;

	start_script( ":summoning:npcsummoning", parms );

endfunction