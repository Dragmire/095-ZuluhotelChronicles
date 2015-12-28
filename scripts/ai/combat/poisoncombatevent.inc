include "include/dotempmods";
include "include/random";
include "include/attributes";

function process_combat_event(ev)

	DoPoison(ev.source);

        if (ev.type = SYSEVENT_DAMAGED)
		if ((GetHP(me) * 100/GetMaxHP(me)) < flee_point)
			EraseObjProperty(me,"#flees");
			flee(ev.source);
		endif
        endif

endfunction

function in_combat_event_loop(opponent)

	DoPoison(opponent);

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

function DoPoison(you)

	if (!GetObjProperty(me,"#lastbreath"))
		SetObjProperty(me,"#lastbreath",ReadGameClock() + 10);
	endif

	if (GetObjProperty(me,"#lastbreath") > ReadGameClock() )
		return;
	endif

	SetObjProperty(me,"#lastbreath",ReadGameClock() + 10);

	if ( (distance(me,you)<2) and (Random(4)=1) )

		var plvl := Random(GetMaxHP(me)/40)+1;
		SetPoison(you,plvl,"You have been poisoned by " + me.name);

	endif

endfunction
