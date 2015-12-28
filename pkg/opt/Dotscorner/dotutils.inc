

function GrantPriv( who, privilege )

	if( GrantPrivilege( who, privilege ) )
	    who.enable ( privilege );
	    SendSysMessage(who, "Privilege: " + privilege + " has been enabled.");
	    return 1;
	  else
	    SendSysMessage(who, "Could not set " + privilege );
	    return 0;
	endif

endfunction

function RevokePriv( who, privilege )

	if( RevokePrivilege( who, privilege ) )
	    who.disable ( privilege );
	    SendSysMessage(who, "Privilege: " + privilege + " has been disabled.");
	    return 1;
	  else
	    SendSysMessage(who, "Could not set " + privilege );
	    return 0;
	endif

endfunction

