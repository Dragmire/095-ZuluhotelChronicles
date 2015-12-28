// GAMEHELP.INC
//
// Creator: Myrathi <tjh@myrathi.co.uk>
// Created: 25-Apr-2001
use uo;
use basic;

var ascz := CAsc("Z");

function GetPieceGump( piece_code, dictpieces )
	if ( !dictpieces.exists( piece_code ) )
		return -1;
	endif
	return dictpieces[ piece_code ];
endfunction

function SetupChess( byref zboard )
	var zsetup := "RNBQKBNRPPPPPPPP................................pppppppprnbqkbnr";
	if ( TypeOf(zboard)["String"] )
		zboard := zsetup;
	endif
	return zsetup;
endfunction

// TOP   : White
// BOTTOM: Black
//
// Return: Move Ok? 1=y, 0=n
//
// TODO: "En Passant" (pawn-move 'in passing'), "Castling" (Rook/King swap)
//
function MakeChessMove( sqfrom, sqto, byref zboard )

	// Are both locations on the board?
	//
	if ( sqfrom < 1 || sqfrom > 64 || sqto < 1 || sqto > 64 )
		//return 0;
	endif

	// Is the board valid? (64 locs)
	//
	if ( zboard.size() != 64 )
		//return 0;
	endif

	// Get the piece
	//
	var piece := zboard[sqfrom];
	var dest := zboard[sqto];

	// Convert locations to {x,y} arrays (topleft origin)
	//
	var xyfrom := {((sqfrom-1)%8)+1,CInt((sqfrom-1)/8)+1};
	var xyto := {((sqto-1)%8)+1,CInt((sqto-1)/8)+1};

	// Set piece-direction by piece-colour
	// (+1 = down the board, -1 = up the board)
	//
	var dir := 1, color := "W", destcol := "W";
	if ( CAsc(piece) > ascz ) // lower case = black
		dir := -1;
		color := "B";
		piece := upper(piece);
	endif
	if ( CAsc(dest) > ascz )
		destcol := "B";
		dest := upper(dest);
	endif

	// Validate move (by piece type and direction)

	// Is the destination piece the same color? Fail.
	if ( color == destcol )
		return 0;
	endif

	// Ensure path validity and non-blockage.
	case( piece )
		"P": // Pawn
			break;
		"K": // King
			break;
		"B": // Bishop
		"R": // Rook (castle)
		"Q": // Queen
			break;
		"N": // kNight (horse)
			break;
		default:
			// Board has an invalid piece on it or they're trying to move nothing? :)
			if ( piece != "." ) // invalid
				return -1;
			endif
			break;
	endcase

	// A-Ok, if we got here! Move piece and return OK.
	//
	zboard[sqto] := zboard[sqfrom]; // need this to get original piece code
	zboard[sqfrom] := ".";
	return 1;

endfunction