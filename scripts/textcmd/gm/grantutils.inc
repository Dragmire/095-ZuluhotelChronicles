use os;
use uo;

function GrantPriv( who, Privilege )

	If( GrantPrivilege( who, Privilege ) )
	    who.enable ( Privilege );
	    return 1;
	  Else
	    return 0;
	EndIf

endfunction

function RevokePriv( who, Privilege )

	If( RevokePrivilege( who, Privilege ) )
	    who.disable ( Privilege );
	    return 1;
	  Else
	    return 0;
	EndIf

endfunction


