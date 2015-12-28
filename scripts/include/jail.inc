/*
   Author: Unreal (MontuZ@Gmail.com) Jan 29, 2006.
   Version: 1.0
   Core: 095
   Bugs: None. Atleast none that I know of..
   PS: You know it was done by me when it's so clean.
*/

Use util;

Function SendPlayerToJail( Player )

    Var Location;

    Case( RandomInt( 3 ) )
    0:
    Location := { 5222, 1819, 0 }; Break;
    1:
    Location := { 5222, 1833, 0 }; Break;
    2:
    Location := { 5203, 1833, 0 }; Break;
    3:
    Location := { 5203, 1819, 0 }; Break;
    Default:
    Location := { 5203, 1833, 0 }; Break;
    Endcase

    MoveObjectToLocation( Player, Location[1], Location[2], Location[3], REALM_BRITANNIA, MOVEOBJECT_FORCELOCATION );

Endfunction

/*
Function GetJailTime( Who )

    Var Account := Who.acct;

    Var Release := Account.getprop( "Release" );

    If( !Release )
    Release := 0;
    Endif

    Var Seconds := CInt( Release - ReadGameClock() );

    If( Seconds < 0 )
    Return 0;
    Endif

    Var Days := ( Seconds / TIMEID_SECONDS_PER_DAY );
    Seconds  := Seconds % TIMEID_SECONDS_PER_DAY;

    Var Hours := ( Seconds / TIMEID_SECONDS_PER_HOUR );
    Seconds  := Seconds % TIMEID_SECONDS_PER_HOUR;

    Var Minutes := ( Seconds / TIMEID_SECONDS_PER_MINUTE );
    Seconds  := Seconds % TIMEID_SECONDS_PER_MINUTE;

    If( Hours < 10 )
    Hours := "0" + Hours;
    Endif

    If( Minutes < 10 )
    Minutes := "0" + Minutes;
    Endif

    If( Seconds < 10 )
    Seconds := "0" + Seconds;
    Endif

    Return { CInt( Days ), CInt( Hours ), CInt( Minutes ), CInt( Seconds ) };

Endfunction
*/
