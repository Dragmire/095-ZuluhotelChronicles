include "include/attributes";
include "include/classes";

function Found( finder, hider )

	var finder_skill := GetAttribute( finder, ATTRIBUTEID_DETECTINGHIDDEN );
	var hider_skill  := CInt( GetAttribute( hider, ATTRIBUTEID_HIDING ) / 1.25);


	if( GetObjProperty( hider, CLASSEID_THIEF ) )
		hider_skill := CInt( hider_skill * ClasseBonus( hider, CLASSEID_THIEF ) );
	endif

	if( finder_skill > hider_skill )
		return 1;
	else
		return 0;
	endif

endfunction