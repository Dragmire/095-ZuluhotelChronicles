function main_AI_loop()

    var ev;
    var wanders := 60;
    var hatelist := "bird eagle rat chicken";

    EnableMainEvents();

	var mydestx := 0;
	var mydesty := 0;
	var steps := 0;

    while (1)

	if (mydestx != 0)
		WalkTowardLocation(mydestx, mydesty);
		if ( (me.x = mydestx and me.y = mydesty) or ( steps > 10 ) )
			mydestx := 0;
		endif
	else	
		wander();
		wanders := wanders +1;
	endif

	if (wanders > 60)
		wanders :=0;
		ev := sleepmode();
	else
		ev := os::wait_for_event( 2 );
	endif

	if (ev)
        repeat
	    case (ev.type)
		SYSEVENT_ENTEREDAREA:
		    if (!ev.source.npctemplate)
		    	PlaySoundEffect(me, 0x6B);
		    elseif ( hatelist[ev.source.npctemplate] )
	            	Fight( ev.source );
		    endif
                SYSEVENT_DAMAGED:
                SYSEVENT_ENGAGED:
                    Fight( ev.source );
		EVID_ALL_FOLLOW_CMD:
			mydestx := ev.x;
			mydesty := ev.y;
			steps := 0;
			drop_anchor();
			WalkTowardLocation(mydestx, mydesty);
            endcase
        until (! (ev := os::wait_for_event(2)) );
	endif

   endwhile      

endfunction        

function look_around()

	var hatelist := "bird eagle rat chicken";
	foreach critter in ListMobilesInLineOfSight( me, HALT_THRESHOLD )
		if ( (critter.npctemplate) and ( hatelist[critter.npctemplate] ) )
			Fight( critter );
			return;
		endif
	endforeach

endfunction

function EnableMainEvents()

    DisableEvents( SYSEVENT_SPEECH + SYSEVENT_LEFTAREA + SYSEVENT_DISENGAGED + SYSEVENT_OPPONENT_MOVED);
    EnableEvents( SYSEVENT_ENGAGED + SYSEVENT_DAMAGED + SYSEVENT_ENTEREDAREA, HALT_THRESHOLD );

endfunction

function DisableMainEvents()

    DisableEvents( SYSEVENT_SPEECH + SYSEVENT_ENGAGED + SYSEVENT_DAMAGED + SYSEVENT_ENTEREDAREA);

endfunction
