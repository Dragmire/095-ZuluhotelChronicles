use uo;

include "include/client";
//include "include/attributes";

function CopySkills( original, clone )

	var i;
	for( i := 0; i <= SKILLID__HIGHEST; i := i + 1 )
		SetBaseSkill( clone, i, GetBaseSkill( original, i ) );
	endfor

endfunction