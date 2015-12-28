/*
   Author: Unreal (MontuZ@Gmail.com) Jan 29, 2006.
   Version: 0.9
   Core: 095
   Bugs: None. Atleast none that I know of..
   PS: You know it was done by me when it's so clean.


// Order Races
Const CITYID_GANDLATHAR  := "Gandlathar";
//Const COORDID_GANDLATHAR := { MinX, MinY, MaxX, MaxY };

Const RACEID_TROLL      := "Troll";
Const RACEID_ORC        := "Orc";
Const RACEID_NIGHTELVE  := "Night-Elve";

// Chaos Races
Const CITYID_YORKSHIRE   := "Yorkshire";
//Const COORDID_YORKSHIRE  := { MinX, MinY, MaxX, MaxY };

Const RACEID_DAEMON   := "Daemon";
Const RACEID_VAMPIRE  := "Vampire";
Const RACEID_DARKELVE := "Dark-Elve";

// Neutral Races
Const CITYID_IRONVALE    := "Ironvale";
//Const COORDID_IRONVALE   := { MinX, MinY, MaxX, MaxY };

Const RACEID_HUMAN   := "Human";

Const RACEID_BONUS   := 1.10;

Function GetRaceCombatBonus( Who, IsMeleeBonus := 0, IsMagicBonus := 0, IsRangedBonus := 0 )

    Var PlayerRace := Who.title_race;
    Var Result := 1;
    
    If( !PlayerRace )
    Return 1;
    Endif
    
    If( IsMeleeBonus )
    Case( PlayerRace )
    RACEID_ORC:     Result := RACEID_BONUS;
    RACEID_VAMPIRE: Result := RACEID_BONUS;
    Endcase
    Return Result;
    Endif
    
    If( IsMagicBonus )
    Case( PlayerRace )
    RACEID_TROLL:  Result := RACEID_BONUS;
    RACEID_DAEMON: Result := RACEID_BONUS;
    Endcase
    Return Result;
    Endif
    
    If( IsRangedBonus )
    Case( PlayerRace )
    RACEID_NIGHTELVE:  Result := RACEID_BONUS;
    RACEID_DARKELVE: Result := RACEID_BONUS;
    Endcase
    Return Result;
    Endif


Endfunction

Function GetRaceSkillBonus( Who, IsStrBonus := 0, IsIntBonus := 0, IsDexBonus := 0 )

    Var PlayerRace := Who.title_race;
    Var Result := 1;

    If( !PlayerRace )
    Return 1;
    Endif

    If( IsStrBonus )
    Case( PlayerRace )
    RACEID_ORC:     Result := RACEID_BONUS;
    RACEID_VAMPIRE: Result := RACEID_BONUS;
    Endcase
    Return Result;
    Endif

    If( IsIntBonus )
    Case( PlayerRace )
    RACEID_TROLL:  Result := RACEID_BONUS;
    RACEID_DAEMON: Result := RACEID_BONUS;
    Endcase
    Return Result;
    Endif
    
    If( IsDexBonus )
    Case( PlayerRace )
    RACEID_NIGHTELVE: Result := RACEID_BONUS;
    RACEID_DARKELVE:  Result := RACEID_BONUS;
    Endcase
    Return Result;
    Endif

Endfunction

*/
