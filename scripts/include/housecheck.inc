use uo;

include "include/objtype";
include "include/spelldata";
include "include/areas";
include "include/client";
include "../pkg/std/housing/utility";

function Housecheck(character)
	var multi := character.multi;
	if(multi)
		if( !IsOwner( character, multi ) )
			if( !IsFriend( character, multi ) )
				return 0;
			else
				return 1;
			endif
		else
			return 1;
		endif
	endif

endfunction  