include "include/attributes";
include "include/random";

function process_combat_event(ev)

	spellattack(ev.source);
        if (ev.type = SYSEVENT_DAMAGED)
		if ((GetHP(me) * 100/GetMaxHP(me)) < flee_point)
			EraseObjProperty(me,"#flees");
			flee(ev.source);
		endif
        endif

endfunction

function spellattack(opponent);

	var ev := array;
	ev.+type := SYSEVENT_DAMAGED;
	ev.+source := me;
 
	if (opponent)
		if (distance(me,opponent) < 2)
			var opmagery := cint(GetEffectiveSkill(opponent,SKILLID_MAGERY));
			if (opmagery)
				SendEvent(opponent, ev);
				applyrawdamage(opponent, Random(cint(opmagery/15)) );
			endif
		endif
	endif

endfunction

function in_combat_event_loop(opponent)

	spellattack(opponent);
         
endfunction

function prepare_for_fight(opponent)

	DisableMainEvents();
	EnableCombatEvents();

endfunction

function post_combat()

	DisableCombatEvents();
	EnableMainEvents();

	SetWarMode( 0 );
	SetOpponent( 0 );

	sleep(1);
	look_around();

endfunction
