include "include/attributes";
include "include/random";

function process_combat_event(ev)

	spellattack(ev.source);

	case (ev.type)
        	SYSEVENT_DAMAGED:
			if ( ( GetHP(me) < (GetStrength(me)/2)) and !(GetObjProperty( me , "Type" ) = "Undead" ) )
				CastSpell(me,me,"gheal");
				Sleepms(500);
				if( me.poisoned )
					CastSpell(me,me,"cure");
					Sleepms(500);
					CastSpell(me,ev.source,"poison");
				endif
			endif
                        if ((GetHP(me) * 100/GetMaxHP(me)) < flee_point)
				EraseObjProperty(me,"#flees");
                                flee(ev.source);
                        endif
			break;
        	default: break;
	endcase

endfunction

function spellattack(opponent)

	if (!GetObjProperty(me,"#lastbreath"))
		SetObjProperty(me,"#lastbreath",ReadGameClock() + 1);
	endif

	if (GetObjProperty(me,"#lastbreath") > ReadGameClock() )
		return;
	endif

	if (Random(3) != 1)
		sleep(1);
		cast_offensive_spell(me,opponent);
	endif

	SetObjProperty(me,"#lastbreath",ReadGameClock() + 1);

endfunction

function in_combat_event_loop(opponent)

	spellattack(opponent);

endfunction

function prepare_for_fight(opponent)

	if( !GetObjProperty( me , "mr") )
		CastSpell( me , me , "reflect" );
	endif

	DisableMainEvents();
	EnableCombatEvents();

endfunction

function post_combat()

	if( GetHP(me) < (GetStrength(me)/2) and !(GetObjProperty( me , "Type" ) = "Undead" ) )
		CastSpell(me,me,"gheal");
		Sleepms(500);
	endif

	DisableCombatEvents();
	EnableMainEvents();

	SetWarMode( 0 );
	SetOpponent( 0 );

	summons := 1;

	sleep(1);
	look_around();
  
endfunction
