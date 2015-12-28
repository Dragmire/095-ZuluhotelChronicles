include "include/dotempmods";
include "include/random";
include "include/attributes";

function process_combat_event(ev)

	if (me.hp < me.maxhp/2)
		ApplyHealing();
	endif

        if (ev.type = SYSEVENT_DAMAGED)
		if ((GetHP(me) * 100/GetMaxHP(me)) < flee_point)
			EraseObjProperty(me,"#flees");
			flee(ev.source);
		endif
	endif

endfunction

function in_combat_event_loop(opponent)

	if (GetHP(me) < GetMaxHP(me)/2)
		ApplyHealing();
	endif

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

function ApplyHealing()

	if (!GetObjProperty(me,"#lasthealed"))
		SetObjProperty(me,"#lasthealed", ReadGameClock()-20);
	endif

	if ( GetObjProperty(me,"#lasthealed") < ReadGameClock())

		if (me.poisoned)
			CurePoison(me,0,0);
		else
			SetHP( me,  (GetHP(me) + (Random(GetMaxHP(me) - GetHP(me))+1) ));
		endif
		SetObjProperty(me,"#lasthealed", ReadGameClock()+20);

	endif

endfunction
