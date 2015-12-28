function main_AI_loop(next_wander := 0)

    var ev;
    var wanders := 60;
    var next_loot := readgameclock() + 20;

    EnableMainEvents();

    while (1)

	if (readgameclock() > next_wander)
        	wander_around();
		next_wander := readgameclock()+1;
		wanders := wanders +1;
		if (wanders > 60)
			wanders :=0;
			ev := sleepmode();
    		endif
	else
		ev := os::wait_for_event( 3 );
	endif

        repeat

            case (ev.type)
                SYSEVENT_ENTEREDAREA:
                SYSEVENT_DAMAGED:
                SYSEVENT_ENGAGED:
                    Fight( ev.source );
                default:
		    process_noncombat_event(ev);
            endcase

        until (! (ev := os::wait_for_event(1)) );

   endwhile      

endfunction        

function look_around()

	return;

endfunction

function EnableMainEvents()

    cleareventque();
    DisableEvents( SYSEVENT_SPEECH + SYSEVENT_LEFTAREA + SYSEVENT_DISENGAGED + SYSEVENT_OPPONENT_MOVED );
    EnableEvents( SYSEVENT_ENGAGED + SYSEVENT_DAMAGED + SYSEVENT_ENTEREDAREA, HALT_THRESHOLD );

endfunction

function DisableMainEvents()

    cleareventque();
    DisableEvents( SYSEVENT_ENGAGED + SYSEVENT_DAMAGED + SYSEVENT_ENTEREDAREA);

endfunction
