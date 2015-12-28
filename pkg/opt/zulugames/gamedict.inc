// GAMEDICT.INC
//
// Creator: Myrathi <tjh@myrathi.co.uk>
// Created: 25-Apr-2001

const GD_KEY	:= 1;
const GD_VALUE	:= 2;

// Takes an array of key/value arrays and turns it into a dictionary
//
function gdMakeDict( zarray )
	var dtmp := dictionary;
	foreach pair in zarray
		dtmp[pair[GD_KEY]] := pair[GD_VALUE];
	endforeach
	return dtmp;
endfunction