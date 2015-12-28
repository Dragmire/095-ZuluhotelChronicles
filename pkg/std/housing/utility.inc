include "setup";

function IsOwner( who, house )
	if( who.serial == CInt( GetObjProperty( house, "ownerserial" ) ) )
		return( 1 );
	else
		var i;
		for( i := 1; i <= MAX_CO_OWNERS; i := i + 1 )
			if( who.serial == CInt( GetObjProperty( house, "Co-owner" + i ) ) )
				return( 1 );
			endif
		endfor
	endif
	return( 0 );
endfunction

function IsFriend( who, house )
	var i;
	for( i := 1; i <= MAX_FRIENDS; i := i + 1 )
		if( who.serial == CInt( GetObjProperty( house, "friend" + i ) ) )
			return( 1 );
		endif
	endfor
	return( 0 );
endfunction