include "include/attributes";

function process_combat_event(ev)

        if (ev.type = SYSEVENT_DAMAGED)
                        if ((GetHP(me) * 100/GetMaxHP(me)) < flee_point)
				EraseObjProperty(me,"#flees");
                                flee(ev.source);
                        endif
        endif

endfunction

function in_combat_event_loop(opponent)

	return;

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
