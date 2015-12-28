function main_AI_loop()

    var ev;
    var wanders := 60;
    var next_wander := readgameclock();
    var next_news := readgameclock();
    EnableMainEvents();

	var mydestx := 0;
	var mydesty := 0;
	var steps := 0;

	SetAnchor( cint(me.x), cint(me.y), 4, 50 );

    while (1)

	if (readgameclock() > next_wander)
//		if (readgameclock() > next_news)
//			SpoutTheNews();
//			next_news := ReadGameClock()+60;
//		endif

		if (mydestx != 0)
			WalkTowardLocation(mydestx, mydesty);
			if ( (me.x = mydestx and me.y = mydesty) or ( steps > 10 ) )
				mydestx := 0;
			endif
		else	
			wander();
			wanders := wanders +1;
		endif

		next_wander := readgameclock()+5;
		if (wanders > 60)
			wanders :=0;
			walkhome();
			ev := sleepmode();
    		endif
	else
		ev := os::wait_for_event( 2 );
	endif

	if (ev)
        repeat
            case (ev.type)
                SYSEVENT_SPEECH:
		    if (!ev.source.npctemplate)
		    	if (lower(ev.text) = "news")
				wanders :=0;
		    		next_wander := readgameclock()+60;
		    		SpoutTheNews();
		    	endif
		    endif
                SYSEVENT_ENGAGED:
                SYSEVENT_DAMAGED:
                    Fight( ev.source );
		    ReturnHome();
		EVID_ALL_FOLLOW_CMD:
			mydestx := cint(ev.x);
			mydesty := cint(ev.y);
			steps := 0;
			SetAnchor( mydestx, mydesty, 4, 50 );
			WalkTowardLocation(mydestx, mydesty);
		SYSEVENT_ENTEREDAREA:
		saynews:=1;
		SpoutTheNews();
		SYSEVENT_LEFTAREA:
		saynews:=0;
            endcase

        until (! (ev := os::wait_for_event(2)) );
	endif

   endwhile      

endfunction        

function look_around()

	return;

endfunction

function EnableMainEvents()

    DisableEvents( SYSEVENT_LEFTAREA + SYSEVENT_DISENGAGED + SYSEVENT_OPPONENT_MOVED );
    EnableEvents( SYSEVENT_SPEECH + SYSEVENT_ENGAGED + SYSEVENT_DAMAGED, HALT_THRESHOLD );
    EnableEvents( SYSEVENT_SPEECH, 3 );
    DisableEvents(SYSEVENT_ITEM_GIVEN);

endfunction

function DisableMainEvents()

    DisableEvents( SYSEVENT_SPEECH + SYSEVENT_ENGAGED + SYSEVENT_DAMAGED );
    DisableEvents(SYSEVENT_ITEM_GIVEN);

endfunction

function SpoutTheNews()

	var news := GetGlobalProperty("news");
	if (!news)
		Say("No news is good news.");
		return;
	endif

	var i;
	for (i := 1; i <= len(news); i := i + 1)
		if (saynews)
		  Say(news[i]);
		  sleep(2);
		else
		  break;
		endif
	endfor

endfunction

function ReturnHome()

	var myhome := GetObjProperty(me,"myhome");
	MoveCharacterToLocation(me,myhome[1],myhome[2],myhome[3],MOVECHAR_FORCELOCATION);

endfunction
