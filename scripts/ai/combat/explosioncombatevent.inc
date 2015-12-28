include "include/random";
include "include/attributes";

function process_combat_event(ev)

	ThrowPotion(ev.source);

        if (ev.type = SYSEVENT_DAMAGED)
		if ((GetHP(me) * 100/GetMaxHP(me)) < flee_point)
			EraseObjProperty(me,"#flees");
			flee(ev.source);
		endif
        endif

endfunction

function in_combat_event_loop(opponent)

	ThrowPotion(opponent);

endfunction

function post_combat()

	DisableCombatEvents();
	EnableMainEvents();

	SetWarMode( 0 );
	SetOpponent( 0 );

	sleep(1);
	look_around();

endfunction

function prepare_for_fight(opponent)

	DisableMainEvents();
	EnableCombatEvents();

endfunction

function ThrowPotion(you)

	if (!GetObjProperty(me,"#lastbreath"))
		SetObjProperty(me,"#lastbreath",ReadGameClock() + 5);
	endif

	if (GetObjProperty(me,"#lastbreath") > ReadGameClock() )
		return;
	endif

	SetObjProperty(me,"#lastbreath",ReadGameClock() + 5);

	if ( (distance(me,you)>2) and Random(2) )

		var parms := {};
		parms[1] := me;
		parms[2] := you;

		start_script( ":alchemy:explosion", parms ); 

	endif

endfunction
