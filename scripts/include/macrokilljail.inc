use uo;

include "include/objtype";
include "include/spelldata";
include "include/areas";
include "include/client";
include "../pkg/std/housing/utility";

function JailPlayer( player )

	var tick_per_day := 86400;
	var jail_days := 1;    
	var jailtime := tick_per_day * jail_days;  //was 30  grrr
	var acc := player.acct;
	var playername := Cstr( player.name );
	if(GetObjProperty(player,"starttime"))
		Eraseobjproperty(player,"starttime");
		acc.setprop("Release", (ReadGameClock() + jailtime ));

		MoveCharacterToLocation( player, 5304, 1184, 0, 0);

		SendSysMessage( player , "You have been jailed for one day. Reason: Breaking macro rule." );

		Broadcast( playername + " HAS BEEN JAILED DUE TO MACROING!", FONT_BOLD, 33 );
		Broadcast( playername + " HAS BEEN JAILED DUE TO MACROING!", FONT_BOLD, 33 );

		sleep(5*60);

		DisconnectClient( player );
	endif
endfunction
  