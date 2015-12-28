/////////////////////////////////////////////////////////////////
//
// GUMPS.INC - v2.6
//
// Gump Functions - to make life easier! :) 
//	-Myr
// Tastes good with ketchup too.
//	-Austin
//
// Author: Myrathi <tjh@myrathi.co.uk>
// Maintainer: Austin <Austin@tsse.net>
//
//==Revision v2.6
// Updated: 23-Apr-2003, HellRazor
//  - Added GFCheckerTrans function for gumps with transparent backgrounds (code by Kiwi)
//
//==Revision v2.5
// Updated: 06-Jan-2003, Austin
// - Added GFHTMLArea()
//
//==Revision v2.4b
// Updated: 28-May-2002, Austin
//  - Fixed the scroll constant.
//  - Added an extra scroll constant.
//
//==Revision v2.4
// Updated: 05-Dec-2001, Austin
// - Fixed character width constants.
//
//==Revision v2.3
// Updated: 26-Nov-2001, Austin
// - Fixed a lot of the {} syntax into array() and struct.
// - Added ability to arbitrarily assign return values for buttons
// - Fixed text area. Will set it to "" if nothing is passed 
//   for the default text.
// - 'local' updated to 'var'
//
//==Revision v2.2==
// Updated: 15-Aug-2001, Myrathi
//  - Fixed a bug in GFUser2() that would stop compilation with
//    the latest ECompile executables (092+)
//  - Ensured 093/094 compatibility.
//
//==Revision v2.1==
// Updated: 24-Apr-2000, Myrathi
//  - Added BKGND_???????? 'gumpid' constants for GFResizePic()
//  - Added some missing characters to Shini's align-functions
//
//==Revision v2.0==
// Updated: 19-Apr-2000, Myrathi
//  - Couple of minor bugfixes.
//  - Updated the HTML help files.
//  - Code more robust. Moved to full revision v2.0! :)
//
//==Revision v1.3==
// Updated: 04-Feb-2000, Myrathi
//	- Added a sleepms() in places to stop runaway scripts! Yay!
//	- Added GFExtractData(): extracts string from TextEntry key
//
//==Revision v1.2==
// Updated: 30-Jan-2000, Myrathi
//	- Added storage/retrieval functions to allow multiple gumps
//	  in different functions in the same script! (headache)
//	- GFSendGumpV() displays a gump from a "stored gump" var. :)
//	- Added Shinigami's text-positioning functions...
//	  ( XGFTextWidth/Left/Mid/Right() )
//
//==Revision v1.1==
// Updated: 27-Jan-2000, Myrathi
//	- Changed the GFref variable to a structure (nicer)
//	- GFInitGump now accepts optional 'x', 'y' origin params.
//	- GFSetRef now returns the old {x,y} origin
//	- GFSetRefRel added - new origin is *relative* to old one
//	- GFTextCrop added. Supports "croppedtext" control
//	- GF[Get|Set]NextIndex and GFIncIndex functions added
//	- GF[Get|Set]Data and GFGet/SetLayout added to stop mixups
//	  between zero-based and one-based indexing. (Use 0-idxs!!)
//	- Appropriate functions now return a structure containing
//	  indexes to the changes in the layout array as well as
//	  data-index and/or keyid values (see headers or help file)
//	- Added constants for the index functions
//	- Added two internal helper-functions (XGFxxxxxxxx)
//
//==Revision v1.0==
// Updated: 25-Jan-2000, Myrathi
//	- GFInitGump now auto-inserts "nodispose".
//	- GFSetRadioGroup added for advanced radio-button support
//  - Minor bugs skwished. No other bugs found.
//  - Updated to full revision v1.0 :)
//
//==Revision v0.1a==
// Created: 24-Jan-2000, Myrathi
//  - Basic gump creation. A couple of minor bugs :/
//
// Notes:
//	+ All functions take hex values and convert to integer
//	  form, where necessary (gumps crash with hex values! Ugh!)
//
//	+ "Page 0" is the main background! It shows at ALL times!
//	  Anything you want on separate pages should be on page
//	  1, 2, 3 and so on showing 0+1, 0+2, 0+3, 0+4, etc, etc.
//
// To do:
//	+ Add the option of supplying the KeyIDs (is this wanted?)
//	+ Update the const-list of commonly used ID's (GFX + colours)
//  + Update "GFTextMid()" to cater for mid-x coord only (no 'w')
//
// Bugs:
//	- None known... now :)
//
// Thanks:
//	+ To Ignatius for his GUMPDOCS file which cleared up
//	  a couple of issues I was unsure of. :)
//	+ To Shinigami for "croppedtext" and his align-functions :]
//	+ To Horus for shutting up and letting me work! :P"
//
/////////////////////////////////////////////////////////////////

use uo;
use os;
use basic;

// Constants (for GF[Get|Set]NextIndex)
/////////////////////////////////////////////////////////////////
const GFIDX_TEXT        := 0x01;	// Static Text (TextLine)
const GFIDX_TEXTENTRY   := 0x02;	// Return Text (TextEntry)
const GFIDX_BUTTON      := 0x03;	// Action Buttons (ButtonID)
const GFIDX_CHECKBOX    := 0x04;	// Check-boxes
const GFIDX_RADIO       := 0x05;	// Radio Buttons
/////////////////////////////////////////////////////////////////

// Constants for index starting values (SHOULD be enough! Heh!)
/////////////////////////////////////////////////////////////////
const GFINIT_TEXT       := 0x000;	// Static Text (GFdata[])
const GFINIT_TEXTENTRY  := 0x201;	// Return Text (GFdata[])
const GFINIT_BUTTON     := 0x401;	// Action Buttons (KeyIDs)
const GFINIT_CHECKBOX   := 0x601;	// Check-boxes (KeyIDs)
const GFINIT_RADIO      := 0x801;	// Radio Buttons (KeyIDs)
/////////////////////////////////////////////////////////////////

// 'gumpid' Constants for the GFResizePic() function
/////////////////////////////////////////////////////////////////
const BKGND_SILVERTRIM          := 83;    // Fancy, dark-grey backing
const BKGND_SCROLL              := 2520;  // UO journal scroll
const BKGND_OLD_JOURNAL_SCROLL  := 5150;  // Old journal scroll
const BKGND_GOLDTRIM            := 2620;  // Gold-press, black backing
const BKGND_PAPER               := 3000;  // Very thin edging
const BKGND_PAPER_EX            := 3500;  //  \_with fancy inner border
const BKGND_BLACKSLAB           := 3600;  // Raised edge (blocky)
const BKGND_STONESLAB           := 5054;  // Plain, small corners
const BKGND_STONE               := 5100;  // Marble stone, rounded edge
const BKGND_DARK_STONE          := 5120;  // Same as previous, but much darker
/////////////////////////////////////////////////////////////////

//Standard text colors on TSSE
/////////////////////////////////////////////////////////////////
const StdColor := 1890;
const HeaderColor := 1890;
const SelectedColor := 1720;
/////////////////////////////////////////////////////////////////

// 'gumpid' Constants for the buttons or gumppics (All have a 0 and 1)
/////////////////////////////////////////////////////////////////
const G_BLACKGOLD_ARROW_UP_0	:= 0x00fa;
const G_BLACKGOLD_ARROW_UP_1	:= 0x00fb;
const G_BLACKGOLD_ARROW_DOWN_0	:= 0x00fc;
const G_BLACKGOLD_ARROW_DOWN_1	:= 0x00fd;
const G_BLUE_DIAMOND_0		:= 0x0868;
const G_BLUE_DIAMOND_1		:= 0x0867;
const G_BLUE_DIAMOND_CHECK_0	:= 0x086a;
const G_BLUE_DIAMOND_CHECK_1	:= 0x0869;
const G_BLUE_LARGE_CIRCLE_0	:= 0x0846;
const G_BLUE_LARGE_CIRCLE_1	:= 0x0845;
const G_BLUE_SMALL_CIRCLE_0	:= 0x0838;
const G_BLUE_SMALL_CIRCLE_1	:= 0x0837;
const G_BUTTON_ADD_0		:= 0x099c;
const G_BUTTON_ADD_1		:= 0x099d;
const G_BUTTON_APPLY_0		:= 0x084c;
const G_BUTTON_APPLY_1		:= 0x084b;
const G_BUTTON_CANCEL_0		:= 0x0849;
const G_BUTTON_CANCEL_1		:= 0x0848;
const G_BUTTON_DEFAULT_0	:= 0x084f;
const G_BUTTON_DEFAULT_1	:= 0x084e;
const G_BUTTON_DELETE_0		:= 0x099f;
const G_BUTTON_DELETE_1		:= 0x09a0;
const G_BUTTON_NEXT_0		:= 0x09a5;
const G_BUTTON_NEXT_1		:= 0x09a6;
const G_BUTTON_OKAY_0		:= 0x0852;
const G_BUTTON_OKAY_1		:= 0x0851;
const G_BUTTON_PREVIOUS_0	:= 0x09a2;
const G_BUTTON_PREVIOUS_1	:= 0x09a3;
const G_GOLD_ARROW_UP_0		:= 0x0984;
const G_GOLD_ARROW_UP_1		:= 0x0983;
const G_GOLD_ARROW_DOWN_0	:= 0x0985;
const G_GOLD_ARROW_DOWN_1	:= 0x0986;
const G_GOLDTRIM_MINUS_0	:= 0x0a54;
const G_GOLDTRIM_MINUS_1	:= 0x0a55;
const G_GOLDTRIM_X_0		:= 0x0a50;
const G_GOLDTRIM_X_1		:= 0x0a51;
const G_GRAY_CIRCLE_0		:= 0x00d0;
const G_GRAY_CIRCLE_1		:= 0x00d1;
const G_GREEN_ARROW_RIGHT_0	:= 0x15a4;
const G_GREEN_ARROW_RIGHT_1	:= 0x15a6;
const G_MARBLE_ARROW_DOWN_0	:= 0x0a58;
const G_MARBLE_ARROW_DOWN_1	:= 0x0a59;
const G_MARBLE_ARROW_UP_0	:= 0x0a5a;
const G_MARBLE_ARROW_UP_1	:= 0x0a5b;
const G_MARBLE_MINUS_0		:= 0x0a96;
const G_MARBLE_MINUS_1		:= 0x0a97;
const G_MARBLE_X_0		:= 0x0a94;
const G_MARBLE_X_1		:= 0x0a95;
const G_MINI_SCROLL_0		:= 0x0fc0;
const G_MINI_SCROLL_1		:= 0x0fc1;
const G_PARTY_0			:= 0x0fa8;
const G_PARTY_1			:= 0x0faa;
const G_PARTY_ARROW_LEFT_0	:= 0x0fae;
const G_PARTY_ARROW_LEFT_1	:= 0x0fb0;
const G_PARTY_ARROW_RIGHT_0	:= 0x0fa5;
const G_PARTY_ARROW_RIGHT_1	:= 0x0fa7;
const G_PARTY_CANCEL_0		:= 0x0fb4;
const G_PARTY_CANCEL_1		:= 0x0fb6;
const G_PARTY_E_0		:= 0x0fba;
const G_PARTY_E_1		:= 0x0fbc;
const G_PARTY_OK_0		:= 0x0fb7;
const G_PARTY_OK_1		:= 0x0fb9;
const G_PARTY_SAVE_0		:= 0x0fbd;
const G_PARTY_SAVE_1		:= 0x0fbf;
const G_PARTY_SCROLL_0		:= 0x0fab;
const G_PARTY_SCROLL_1		:= 0x0fad;
const G_PARTY_X_0		:= 0x0fb1;
const G_PARTY_X_1		:= 0x0fb3;
const G_PARTY_X_GUY_0		:= 0x0fa2;
const G_PARTY_X_GUY_1		:= 0x0fa4;
const G_RED_ARROW_LEFT_0	:= 0x15a1;
const G_RED_ARROW_LEFT_1	:= 0x15a3;
const G_RED_DIAMOND_0		:= 0x09a8;
const G_RED_DIAMOND_1		:= 0x09a9;
const G_STONE_CHECK_0		:= 0x13ba;
const G_STONE_CHECK_1		:= 0x13bb;
const G_STONE_X_0		:= 0x13bc;
const G_STONE_X_1		:= 0x13bd;

// 'gumpid' Constants for the text areas
/////////////////////////////////////////////////////////////////
const G_TX_MARBLE_S_DK		:= 0x098c;
const G_TX_MARBLE_M		:= 0x098d;
const G_TX_MARBLE_SQ_L		:= 0x098e;
const G_TX_GOLDTRIM_LONG	:= 0x0476;
const G_TX_GOLDTRIM_LONG_LIGHT	:= 0x0477;
const G_TX_GOLDTRIM_LONG_DARK	:= 0x0475;

// 'gumpid' Constants for the checkboxes
/////////////////////////////////////////////////////////////////
const G_GRAY_CHECKBOX_0		:= 0x00d2;
const G_GRAY_CHECKBOX_1		:= 0x00d3;
const G_SMALL_SQUARE_CHECKBOX_0	:= 0x09ce;
const G_SMALL_SQUARE_CHECKBOX_1	:= 0x09cf;
const G_STONE_CHECKBOX_0	:= 0x146e;
const G_STONE_CHECKBOX_1	:= 0x146f;

// 'gumpid' Constants for the simple gumppics
/////////////////////////////////////////////////////////////////
const G_BOOK_LARGE_GOLDCORNER		:= 0x01f4;
const G_BOOK_LARGE_WOODCORNER		:= 0x01fe;
const G_BOOK_SMALL_1			:= 0x0898;
const G_BOOK_SMALL_2			:= 0x0899;
const G_BOOK_SMALL_3			:= 0x089a;
const G_BOOK_SMALL_4			:= 0x089b;
const G_BOOK_TITLE_GUMPPIC		:= 0x089c;
const G_BUYWIN_MINUS			:= 0x0038;
const G_BUYWIN_PLUS			:= 0x0037;
const G_CORNER_LEFT			:= 0x089d;
const G_CORNER_RIGHT			:= 0x089e;
const G_CORNER_GOLD_LEFT		:= 0x01f5;
const G_CORNER_GOLD_RIGHT		:= 0x01f6;
const G_CORNER_WOOD_LEFT		:= 0x01ff;
const G_CORNER_WOOD_RIGHT		:= 0x0200;
const G_DECO_LINE_LEFT			:= 0x0039;
const G_DECO_LINE_CENTER		:= 0x003a;
const G_DECO_LINE_RIGHT			:= 0x003b;
const G_GOLDEN_BOARD			:= 0x0064;
const G_GRAVESTONE_ROUND		:= 0x0065;
const G_GRAVESTONE_SQUARE		:= 0x0066;
const G_PAPERDOLL_OTHERS		:= 0x07d1;
const G_PAPERDOLL_SELF			:= 0x07d0;
const G_SKILLWIN_ARROW_DOWN_S		:= 0x0826;
const G_SKILLWIN_ARROW_RIGHT_S		:= 0x0827;
const G_SKILLWIN_LINE_L			:= 0x082b;
const G_SKILLWIN_LINE_S			:= 0x0835;
const G_SKILLWIN_LOCKER			:= 0x082c;
const G_SMALL_BLUE_CIRCLE		:= 0x093a;
const G_SMALL_GREEN_CIRCLE		:= 0x0939;
const G_SMALL_RED_CIRCLE		:= 0x0938;
const G_SPELLBOOK			:= 0x08ac;
const G_SPELLBOOK_CORNER_LEFT		:= 0x08bb;
const G_SPELLBOOK_CORNER_RIGHT		:= 0x08bc;
const G_SPELLBOOK_REDUCED		:= 0x08ba;
const G_SPELLCIRCLE_1			:= 0x08b1;
const G_SPELLCIRCLE_2			:= 0x08b2;
const G_SPELLCIRCLE_3			:= 0x08b3;
const G_SPELLCIRCLE_4			:= 0x08b4;
const G_SPELLCIRCLE_5			:= 0x08b5;
const G_SPELLCIRCLE_6			:= 0x08b6;
const G_SPELLCIRCLE_7			:= 0x08b7;
const G_SPELLCIRCLE_8			:= 0x08b8;
const G_SPELLICON_CLUMSY		:= 0x08c0;
const G_SPELLICON_CREATE_FOOD		:= 0x08c1;
const G_SPELLICON_FEEBLEMIND		:= 0x08c2;
const G_SPELLICON_HEAL			:= 0x08c3;
const G_SPELLICON_MAGIC_ARROW		:= 0x08c4;
const G_SPELLICON_NIGHTSIGHT		:= 0x08c5;
const G_SPELLICON_REACTIVE_ARMOR	:= 0x08c6;
const G_SPELLICON_WEAKEN		:= 0x08c7;
const G_SPELLICON_AGILITY		:= 0x08c8;
const G_SPELLICON_CUNNING		:= 0x08c9;
const G_SPELLICON_CURE			:= 0x08ca;
const G_SPELLICON_HARM			:= 0x08cb;
const G_SPELLICON_MAGIC_TRAP		:= 0x08cc;
const G_SPELLICON_MAGIC_UNTRAP		:= 0x08cd;
const G_SPELLICON_PROTECTION		:= 0x08ce;
const G_SPELLICON_STRENGTH		:= 0x08cf;
const G_SPELLICON_BLESS			:= 0x08d0;
const G_SPELLICON_FIREBALL		:= 0x08d1;
const G_SPELLICON_MAGIC_LOCK		:= 0x08d2;
const G_SPELLICON_POISON		:= 0x08d3;
const G_SPELLICON_TELEKINESIS		:= 0x08d4;
const G_SPELLICON_TELEPORT		:= 0x08d5;
const G_SPELLICON_UNLOCK		:= 0x08d6;
const G_SPELLICON_WALL_OF_STONE		:= 0x08d7;
const G_SPELLICON_ARCH_CURE		:= 0x08d8;
const G_SPELLICON_ARCH_PROTECTION	:= 0x08d9;
const G_SPELLICON_CURSE			:= 0x08da;
const G_SPELLICON_FIRE_FIELD		:= 0x08db;
const G_SPELLICON_GREATER_HEAL		:= 0x08dc;
const G_SPELLICON_LIGHTNING		:= 0x08dd;
const G_SPELLICON_MANA_DRAIN		:= 0x08de;
const G_SPELLICON_RECALL		:= 0x08df;
const G_SPELLICON_BLADE_SPIRIT		:= 0x08e0;
const G_SPELLICON_DISPEL_FIELD		:= 0x08e1;
const G_SPELLICON_INCOGNITO		:= 0x08e2;
const G_SPELLICON_MAGIC_REFLECTION	:= 0x08e3;
const G_SPELLICON_MIND_BLAST		:= 0x08e4;
const G_SPELLICON_PARALYZE		:= 0x08e5;
const G_SPELLICON_POISON_FIELD		:= 0x08e6;
const G_SPELLICON_SUMMON_CREATURE	:= 0x08e7;
const G_SPELLICON_DISPEL		:= 0x08e8;
const G_SPELLICON_ENERGY_BOLT		:= 0x08e9;
const G_SPELLICON_EXPLOSION		:= 0x08ea;
const G_SPELLICON_INVISIBILITY		:= 0x08eb;
const G_SPELLICON_MARK			:= 0x08ec;
const G_SPELLICON_MASS_CURSE		:= 0x08ed;
const G_SPELLICON_PARALYZE_FIELD	:= 0x08ee;
const G_SPELLICON_REVEAL		:= 0x08ef;
const G_SPELLICON_CHAIN_LIGHTNING	:= 0x08f0;
const G_SPELLICON_ENERGY_FIELD		:= 0x08f1;
const G_SPELLICON_FLAME_STRIKE		:= 0x08f2;
const G_SPELLICON_GATE_TRAVEL		:= 0x08f3;
const G_SPELLICON_MANA_VAMPIRE		:= 0x08f4;
const G_SPELLICON_MASS_DISPEL		:= 0x08f5;
const G_SPELLICON_METEOR_SWARM		:= 0x08f6;
const G_SPELLICON_POLYMORPH		:= 0x08f7;
const G_SPELLICON_EARTHQUAKE		:= 0x08f8;
const G_SPELLICON_ENERGY_VORTEX		:= 0x08f9;
const G_SPELLICON_RESURRECTION		:= 0x08fa;
const G_SPELLICON_SUMMON_AIR_ELEMENTAL	:= 0x08fb;
const G_SPELLICON_SUMMON_DAEMON		:= 0x08fc;
const G_SPELLICON_SUMMON_EARTH_ELEMENTAL:= 0x08fd;
const G_SPELLICON_SUMMON_FIRE_ELEMENTAL	:= 0x08fe;
const G_SPELLICON_SUMMON_WATER_ELEMENTAL:= 0x08ff;
const G_STONE_ARROW_UP			:= 0x1458;
const G_STONE_ARROW_DOWN		:= 0x1459;
const G_STONE_ARROW_LEFT		:= 0x1467;
const G_STONE_ARROW_RIGHT		:= 0x1468;

// Function List
/////////////////////////////////////////////////////////////////
//
// GFSetRef( x := 0, y := 0 )
// GFSetRefRel( dx, dy );
// GFInitGump( sx := 0, sy := 0 )
// GFPage( page )
// GFNoClose()
// GFNoDispose()
// GFNoMove()
// GFUser1( line )
// GFUser2( l_line, d_pos, d_line )
// GFGumpPic( x, y, gumpid )
// GFResizePic( x, y, gumpid, w, h )
// GFHTMLArea(x, y, width, height, background:=1, scroll_bar:=1, text:="")
// GFTilePic( x, y, tileid )
// GFTextLine( x, y, colour, text );
// GFTextMid(x, y, w, colour, text );
// GFTextRight( rx, y, colour, text );
// GFTextCrop( x, y, w, h, colour, text );
// GFTextEntry( x, y, w, h, colour, text := "" )
// GFButtonPage( x, y, release, press, page )
// GFButtonID( x, y, release, press, close )
// GFCheckBox( x, y, off, on, state )
// GFRadioButton( x, y, off, on, state )
// GFSetRadioGroup( group )
//
// GFExtractData( keyid, keyarray )
//
// GFGetNextIndex( type )
// GFSetNextIndex( type, value )
// GFIncIndex( type )
//
// GFGetData( index )
// GFSetData( index, text )
// GFGetLayout( index )
// GFSetLayout( index, text )
//
// GFStoreGump()
// GFRestoreGump( gumpvar )
//
// GFSendGump( who )
// GFSendGumpV( who, gumpvar )
//
// GFCheckerTrans( x, y, w, h )
//
/////////////////////////////////////////////////////////////////

// Internal Functions
/////////////////////////////////////////////////////////////////
//
// XGFReset()
// XGFRetVal( lytidx := -1, dtidx := -1, keyid := -1 )
//
// XGFTextWidth(gumptext)
// XGFTextLeft(gumptext, x, width)
// XGFTextMid(gumptext, x, width)
// XGFTextRight(gumptext, rightx)
//
/////////////////////////////////////////////////////////////////

// Global variables
/////////////////////////////////////////////////////////////////
var GFref := struct;		// X- and Y-offsets for gump operations
    GFref.+x := 0;
    GFref.+y := 0;

var GFlayout := array();// Main layout array for entire gump
var GFdata := array();	// Storage array for static-text and
			//  text-entry initialisation strings
			// Indexes/KeyIDs for...
var GFdtidx;		// ...text in GFdata (index)
var GFtxtid;		// ...TeXT-entry returns (keyid)
var GFbutid;		// ...'action' BUTtons (keyid)
var GFcbxid;		// ...CheckBoXes (keyid)
var GFradid;		// ...RADio buttons (keyid)
/////////////////////////////////////////////////////////////////

// Return-value structure layout
/////////////////////////////////////////////////////////////////
//  rvsl.lytidx;	// ...index into layout array
//  rvsl.dtidx;	// ...index into data array
//  rvsl.keyid;	// ...KeyID allocated / other data (eg. page#)
/////////////////////////////////////////////////////////////////

// Global Initialisation (Just in case! :-P )
/////////////////////////////////////////////////////////////////
//
XGFReset();

// Function Definitions
/////////////////////////////////////////////////////////////////

// Sets the top-left co-ordinate origin (absolute)
//
// Returns: A structure {x,y} containing the old origin
//
function GFSetRef( x := 0, y := 0 )
	var oldref := GFref;
	GFref.x := CInt(x);
	GFref.y := CInt(y);
	return oldref;
endfunction

// Sets the top-left co-ordinate origin (relative to current)
//
// Returns: A structure {x,y} containing the old origin
//
function GFSetRefRel( dx, dy )
	var oldref := GFref;
	GFref.x := GFref.x + CInt(dx);
	GFref.y := GFref.y + CInt(dy);
	return oldref;
endfunction

// Initialises this include file's global variables
//
function GFInitGump( sx := 0, sy := 0 )
	XGFReset();
	GFSetRef( sx, sy );
	GFPage( 0 );
	GFNoDispose();
endfunction

// Gump page #x - start of definition
//
// Returns: A structure...
//	.lytidx = Layout-array index changed
//	.keyid  = Page number
//
function GFPage( page )
	page := CInt(page);
	GFlayout.append( "page " + CStr(page) );
	return XGFRetVal( GFlayout.size(), -1, page );
endfunction

// Won't let the gump be closed with a right-click
//
// Returns: A structure...
//	.lytidx = Layout-array index changed
//
function GFNoClose()
	GFlayout.append( "noclose" );
	return XGFRetVal( GFlayout.size() );
endfunction

// Won't let the gump be closed by clicking ESCAPE
//
// Returns: A structure...
//	.lytidx = Layout-array index changed
//
function GFNoDispose()
	GFlayout.append( "nodispose" );
	return XGFRetVal( GFlayout.size() );
endfunction

// Disallows dragging of the gump.
//
// Returns: A structure...
//	.lytidx = Layout-array index changed
//
function GFNoMove()
	GFlayout.append( "nomove" );
	return XGFRetVal( GFlayout.size() );
endfunction

// Adds a generic line to the GFlayout array
//
// Returns: A structure...
//	.lytidx = Layout-array index changed
//
function GFUser1( l_line )
	GFlayout.append( l_line );
	return XGFRetVal( GFlayout.size() );
endfunction

// Adds a generic line to the GFlayout array and
// a line to the GFdata array at position 'd_pos'
//
// Returns: A structure...
//	.lytidx = Layout-array index changed
//	.dtidx  = Data-array index changed
//
function GFUser2( l_line, d_pos, d_line )
	GFlayout.append( l_line );
	GFdata[CInt(d_pos)] := d_line;
	return XGFRetVal( GFlayout.size(), d_pos );
endfunction

// Single "art gump"
// (Uses "Gump" art from InsideUO)
//
// Returns: A structure...
//	.lytidx = Layout-array index changed
//
function GFGumpPic( x, y, gumpid )
	var line := "gumppic " + CStr(GFref.x + CInt(x)) + " " + CStr(GFref.y + CInt(y));
	line := line + " " + CStr(CInt(gumpid));
	GFlayout.append( line );
	return XGFRetVal( GFlayout.size() );
endfunction

// Resized "gump" made up of art from 'gumpid' to 'gumpid+8'
// (Uses "Gump" art from InsideUO)
//
// Returns: A structure...
//	.lytidx = Layout-array index changed
//
function GFResizePic( x, y, gumpid, w, h )
	var line := "resizepic " + CStr(GFref.x + CInt(x)) + " " + CStr(GFref.y + CInt(y));
	line := line + " " + CStr(CInt(gumpid)) + " " + CStr(CInt(w)) + " " + CStr(CInt(h));
	GFlayout.append( line );
	return XGFRetVal( GFlayout.size() );
endfunction

//
// Sets up an area on the gump that can be used as an html gump
//
// Returns: A structure...
//	.lytidx = Layout-array index changed
//	.dtidx  = Data-array index changed (0-based index)
//
function GFHTMLArea(x, y, width, height, background:=1, scroll_bar:=1, text:="")
	//x y w h l# bg sb
	//"htmlgump 52 79 276 348 1 0 1",
	var line := "htmlgump "+CStr(GFref.x+CInt(x))+" "+CStr(GFref.y+CInt(y));
	line := line+" "+CStr(CInt(width))+" "+CStr(CInt(height));
	line := line+" "+CStr(GFdtidx);
	line := line+" "+CStr(CInt(background))+" "+CStr(CInt(scroll_bar));
	GFlayout.append(line);
	
	GFdtidx := GFdtidx + 1;		// Update index into GFdata[]
	GFdata[GFdtidx] := text;	// arrays start at #1... id#0 goes into [1]!!
	
	return XGFRetVal( GFlayout.size(), GFdtidx - 1 );
endfunction

// Single "tile" graphic
// (Uses "Static Tiles" from InsideUO [under Artwork])
//
// Returns: A structure...
//	.lytidx = Layout-array index changed
//
function GFTilePic( x, y, tileid )
	var line := "tilepic " + CStr(GFref.x + CInt(x)) + " " + CStr(GFref.y + CInt(y));
	line := line + " " + CStr(CInt(tileid));
	GFlayout.append( line );
	return XGFRetVal( GFlayout.size() );
endfunction

// Display a line of text on the gump
//
// Returns: A structure...
//	.lytidx = Layout-array index changed
//	.dtidx  = Data-array index changed (0-based index)
//
function GFTextLine(x, y, colour, text)
	text := CStr(text);
	var line := "text " + CStr(GFref.x + CInt(x)) + " " + CStr(GFref.y + CInt(y));
	line := line + " " + CStr(CInt(colour)) + " " + CStr(GFdtidx);
	GFlayout.append( line );
	GFdtidx := GFdtidx + 1;		// Update index into GFdata[]
	GFdata[GFdtidx] := text;	// arrays start at #1... id#0 goes into [1]!!
	return XGFRetVal( GFlayout.size(), GFdtidx - 1 );
endfunction

// Display a centred line of text on the gump
//
// Returns: A structure...
//	.lytidx = Layout-array index changed
//	.dtidx  = Data-array index changed (0-based index)
//
function GFTextMid(x, y, w, colour, text )
	text := CStr(text);
	x := XGFTextMid( text, CInt(x), w );
	var line := "text " + CStr(GFref.x + x) + " " + CStr(GFref.y + CInt(y));
	line := line + " " + CStr(CInt(colour)) + " " + CStr(GFdtidx);
	GFlayout.append( line );
	GFdtidx := GFdtidx + 1;		// Update index into GFdata[]
	GFdata[GFdtidx] := text;	// arrays start at #1... id#0 goes into [1]!!
	return XGFRetVal( GFlayout.size(), GFdtidx - 1 );
endfunction

// Display a right-aligned line of text on the gump
//
// Returns: A structure...
//	.lytidx = Layout-array index changed
//	.dtidx  = Data-array index changed (0-based index)
//
function GFTextRight( rx, y, colour, text )
	text := CStr(text);
	rx := XGFTextRight( text, CInt(rx) );
	var line := "text " + CStr(GFref.x + rx) + " " + CStr(GFref.y + CInt(y));
	line := line + " " + CStr(CInt(colour)) + " " + CStr(GFdtidx);
	GFlayout.append( line );
	GFdtidx := GFdtidx + 1;		// Update index into GFdata[]
	GFdata[GFdtidx] := text;	// arrays start at #1... id#0 goes into [1]!!
	return XGFRetVal( GFlayout.size(), GFdtidx - 1 );
endfunction

// Display a line of text on the gump but restrict it to a bounding box
// (shows '...' if it exceeds the rightmost edge)
//
// Syntax : x   y   w   h  colour  dtidx
// Example: 125 300 150 50 32      0
//
// Returns: A structure...
//	.lytidx = Layout-array index changed
//	.dtidx  = Data-array index changed (0-based index)
//
function GFTextCrop( x, y, w, h, colour, text )
	text := CStr(text);
	var line := "croppedtext " + CStr(GFref.x + CInt(x)) + " " + CStr(GFref.y + CInt(y));
	line := line + " " + CStr(CInt(w)) + " " + CStr(CInt(h)) + " " + CStr(CInt(colour));
	line := line + " " + CStr(GFdtidx);
	GFlayout.append( line );
	GFdtidx := GFdtidx + 1;		// Update index into GFdata[]
	GFdata[GFdtidx] := text;	// arrays start at #1... id#0 goes into [1]!!
	return XGFRetVal( GFlayout.size(), GFdtidx - 1 );
endfunction

// Display a text-entry control on the gump
//
// Syntax : x   y   w   h  colour  txtid  dtidx
// Example: 125 300 150 50 32      1050   0
//
// Returns: A structure...
//	.lytidx = Layout-array index changed
//	.dtidx  = Data-array index changed (0-based index)
//	.keyid  = KeyID allocated to the text when the Gump returns
//	          (This method is DAFT! But hey, I didn't write it! :-P" )
//              (Returns eg:  "Key=2024, Value=2024: This is the text" )
//
function GFTextEntry( x, y, w, h, colour, text := "" )
	if ( text == error )
		text := "";
	else
		text := CStr(text);
	endif
	
	var line := "textentry " + CStr(GFref.x + CInt(x)) + " " + CStr(GFref.y + CInt(y));
	line := line + " " + CStr(CInt(w)) + " " + CStr(CInt(h)) + " " + CStr(CInt(colour));
	line := line + " " + CStr(GFtxtid) + " " + CStr(GFdtidx);
	GFlayout.append( line );
	GFdtidx := GFdtidx + 1;		// Update index into GFdata[]
	GFdata[GFdtidx] := text;	// arrays start at #1... id#0 goes into [1]!!
	GFtxtid := GFtxtid + 1;		// Update KeyID (txtid)
	return XGFRetVal( GFlayout.size(), GFdtidx - 1, GFtxtid - 1 );
endfunction

// Standard "button" syntax:
// "button x y release press close page keyid"

// Display a button that changes to another page
//
// Syntax: x, y, release, press, 0, page
// (close=0 - don't want it closing when it's changing page, eh?)
//
// Returns: A structure...
//	.lytidx = Layout-array index changed
//	.keyid  = Page number that the button changes to
//
function GFButtonPage( x, y, release, press, page )
	// "button x y release press 0 page"
	var line := "button " + CStr(GFref.x + CInt(x)) + " " + CStr(GFref.y + CInt(y));
	line := line + " " + CStr(CInt(release)) + " " + CStr(CInt(press));
	line := line + " 0 " + CStr(CInt(page));
	GFlayout.append( line );
	return XGFRetVal( GFlayout.size(), -1, page );
endfunction

// Display an "action button" (returns a key value and can close gump)
//
// Syntax: x, y, release, press, close, 0, keyid
// (page=0 - it returns a value instead of changing page)
//
// Returns: A structure...
//	.lytidx = Layout-array index changed
//	.keyid  = KeyID allocated to the button - returned from Gump if pressed
//	          (butid)
//
function GFButtonID( x, y, release, press, close, id := 0 )
	// "button x y release press close 0 key"
	var line := "button " + CStr(GFref.x + CInt(x)) + " " + CStr(GFref.y + CInt(y));
	line := line + " " + CStr(CInt(release)) + " " + CStr(CInt(press)) + " ";
	if ( close == 0 )
		line := line + "0 0 ";
	else
		line := line + "1 0 ";
	endif
	id := CInt(id);		// Ensure it's an integer
	if ( id < 1 )		// Catch errors (0) and invalid (negative) values
		id := GFbutid;
		GFbutid := GFbutid + 1;		// Update KeyID (butid) (only if used)
	endif
	line := line + CStr(id);
	GFlayout.append( line );
	return XGFRetVal( GFlayout.size(), -1, id );
endfunction

// Displays a check-box (off/on)
//
// Syntax: x, y, off, on, initial state (0/1), cbxid
//
// Returns: A structure...
//	.lytidx = Layout-array index changed
//	.keyid  = KeyID allocated to the checkbox (cbxid)
//
function GFCheckBox( x, y, off, on, state, id := 0)
	var line := "checkbox " + CStr(GFref.x + CInt(x)) + " " + CStr(GFref.y + CInt(y));
	line := line + " " + CStr(CInt(off)) + " " + CStr(CInt(on)) + " ";
	if ( state == 0 )
		line := line + "0 ";
	else
		line := line + "1 ";
	endif
	id := Cint(id);
	if (id < 1)
		id := GFcbxid;
		GFcbxid := GFcbxid + 1;	
	endif
	line := line + CStr(id);

	GFlayout.append( line );
	return XGFRetVal( GFlayout.size(), -1, id );
endfunction

// Displays a radio button (off/on)
//
// Syntax: x, y, off, on, initial state (0/1), radid
//
// Returns: A structure...
//	.lytidx = Layout-array index changed
//	.keyid  = KeyID allocated to the radio-button (radid)
//
function GFRadioButton( x, y, off, on, state, id := 0)
	if (state == error)
		state := 0;
	endif
	var line := "radio " + CStr(GFref.x + CInt(x)) + " " + CStr(GFref.y + CInt(y));
	line := line + " " + CStr(CInt(off)) + " " + CStr(CInt(on)) + " ";
	if ( state == 0 )
		line := line + "0 ";
	else
		line := line + "1 ";
	endif
	id := CInt(id);
	if (id < 1)
		id := GFradid;
		GFradid := GFradid + 1;
	endif
	line := line + CStr(id);
	
	GFlayout.append( line );
	return XGFRetVal( GFlayout.size(), -1, id );
endfunction

// Groups radio button (I think)
//
// Returns: A structure...
//	.lytidx = Layout-array index changed
//	.keyid  = The group number (integer form)
//
function GFSetRadioGroup( group )
	group := CInt(group);
	GFlayout.append( "group " + CStr(group) );
	return XGFRetVal( GFlayout.size(), -1, group );
endfunction

// Extracts string from a TextEntry key
//
// Returns: The text string
//
function GFExtractData( keyid, keyarray )
	var keystr := CStr(keyid)+": ";
	var datstr := keyarray[CInt(keyid)];
	var retval := datstr[len(keystr)+1,len(datstr)];
	sleepms(2);
	return retval;
endfunction

// Returns: Value of the next index to be used
//
function GFGetNextIndex( type )
	sleepms(2);
	case ( type )
		GFIDX_TEXT:
			return GFdtidx;
		GFIDX_TEXTENTRY:
			return GFtxtid;
		GFIDX_BUTTON:
			return GFbutid;
		GFIDX_CHECKBOX:
			return GFcbxid;
		GFIDX_RADIO:
			return GFradid;
		default:
			print( "GFGetNextIndex(): Bad type" );
	endcase
	return;
endfunction

// Sets the next index to be used
//
// Returns: The old index value
//
function GFSetNextIndex( type, value )
	var oldidx;
	value := CInt(value);
	sleepms(2);
	case ( type )
		GFIDX_TEXT:
			oldidx := GFdtidx;
			GFdtidx := value;
		GFIDX_TEXTENTRY:
			oldidx := GFtxtid;
			GFtxtid := value;
		GFIDX_BUTTON:
			oldidx := GFbutid;
			GFbutid := value;
		GFIDX_CHECKBOX:
			oldidx := GFcbxid;
			GFcbxid := value;
		GFIDX_RADIO:
			oldidx := GFradid;
			GFradid := value;
		default:
			print( "GFSetNextIndex(): Bad type" );
			return;
	endcase
	return oldidx;
endfunction

// Increments the current <type> index by one
//
// Returns: The new index value
//
function GFIncIndex( type )
	var oldidx := GFSetNextIndex( type, GFGetNextIndex( type ) + 1 );
	return (oldidx + 1); // Because it's just been incremented! :P"
endfunction

// Gets text from GFdata[]
//
// Returns: the text
//
function GFGetData( index )
	// Internally, the gump uses 0-based indexing...
	// Take that into account when altering the 1-based array
	return GFdata[index+1];
endfunction

// Set the text in GFdata[]
//
// **WARNING** NO ERROR CHECKING!
//
// Returns: Index changed
//
function GFSetData( index, text )
	// Internally, the gump uses 0-based indexing...
	// Take that into account when altering the 1-based array
	GFdata[index+1] := text;
	return index;
endfunction

// Get a text item from the layout array
//
// Returns: the text
//
function GFGetLayout( index )
	return GFlayout[index];
endfunction

// Sets a specified text item in the layout array
//
// **WARNING** NO ERROR CHECKING!
//
// Returns: Index changed
//
function GFSetLayout( index, text )
	GFlayout[index] := text;
	return index;
endfunction

// Stores a structure containing the gump and extra details
//
// Returns: A structure:
//	.layout =	A copy of GFlayout[]
//	.data   =	A copy of GFdata[]
//	.indexes
//		.dt	= Copy of GFdtidx
//		.txt	= Copy of GFtxtid
//		.but	= Copy of GFbutid
//		.cbx	= Copy of GFcbxid
//		.rad	= Copy of GFradid
//
function GFStoreGump()
	var idx := struct;
	idx.+dt := GFdtidx;
	idx.+txt := GFtxtid;
	idx.+but := GFbutid;
	idx.+cbx := GFcbxid;
	idx.+rad := GFradid;

	var ret := struct;
	ret.+layout := GFlayout;
	ret.+data := GFdata;
	ret.+indexes := idx;

	return ret;
endfunction

// Restores a gump layout from a structure saved by GFStoreGump()
//
// Returns:
//	0 = Failure
//	1 = Success
//
function GFRestoreGump( gumpvar )
	if ( !(gumpvar.layout) or !(gumpvar.data) or !(gumpvar.indexes) )
		print("GFRG(): missing one of .layout/.data/.indexes");
		return 0;
	endif
	var idx := gumpvar.indexes;
	if ( !(idx.dt) or !(idx.txt) or !(idx.but) or !(idx.cbx) or !(idx.rad) )
		print("GFRG(): missing index value");
		return 0;
	endif

	GFlayout := gumpvar.layout;
	GFdata := gumpvar.data;
	GFdtidx := idx.dt;
	GFtxtid := idx.txt;
	GFbutid := idx.but;
	GFcbxid := idx.cbx;
	GFradid := idx.rad;
	return 1;
endfunction

// Call this to display/use the defined gump
//
// Returns: an array of keys and values
//          (ie. what the SendDialogGump() returns)
//
// NOTE: This WILL crash the client if you've created duff arrays!!
//
function GFSendGump( who )
	return SendDialogGump( who, GFlayout, GFdata );
endfunction

// Call this to display a gump using "gumpvar"
//
// Returns: an array of keys and values
//		(ie. what the SendDialogGump() returns)
//
// NOTE: This WILL crash the client if you've corrupted the array!
//
function GFSendGumpV( who, gumpvar )
	if ( !(gumpvar.layout) or !(gumpvar.data) )
		return;
	endif
	return SendDialogGump( who, gumpvar.layout, gumpvar.data );
endfunction

/////////////////////////////////////////////////////////////////
//
// INTERNAL FUNCTIONS
//
/////////////////////////////////////////////////////////////////

// Called (internally) to reset all the variables.
//
function XGFReset( )
	GFlayout := array();
	GFdata := array();
	GFdtidx := GFINIT_TEXT;
	GFtxtid := GFINIT_TEXTENTRY;
	GFbutid := GFINIT_BUTTON;
	GFcbxid := GFINIT_CHECKBOX;
	GFradid := GFINIT_RADIO;
endfunction

// Called (internally) to setup the return structure
// of a function
//
//  rvsl.lytidx;	// ...index into layout array
//  rvsl.dtidx;	// ...index into data array
//  rvsl.keyid;	// ...KeyID allocated / other data (eg. page#)
//
function XGFRetVal( lytidx := -1, dtidx := -1, keyid := -1 )
	var rvsl := struct;
	if ( lytidx > -1 )
		rvsl.+lytidx := lytidx;
	endif
	if ( dtidx > -1 )
		rvsl.+dtidx := dtidx;
	endif
	if ( keyid > -1 )
		rvsl.+keyid := keyid;
	endif
	sleepms(2);	// Will hopefully stop runaway script problem :/

	return rvsl;
endfunction

/////////////////////////////////////////////////////////////////
//  Author:    Shinigami
//  eMail:     Shinigami@gmx.net
//  Modified:  Myrathi
/////////////////////////////////////////////////////////////////

// Constants
/////////////////////////////////////////////////////////////////
var aGFTlength := struct;
       aGFTlength.+charsf:=   // Space as Filler is not allowed
         "||||||||||||||"+ //  2
         "`',.;:::::::::"+ //  3
         "!!!!!!!!!!!!!!"+ //  4
         "il1[]]]]]]]]]\""+ //  5
         "bcejotî(){}==="+ //  6
         "adfpqrszIÑ~~~~"+ //  7
         "ghnuvyÅ <>----"+ //  8
         "xJ578$?+++++++"+ //  9
         "kCE2369^/*****"+ // 10
         "mwABDFOPéô40%%"+ // 11
         "GLNQSZ@#######"+ // 12
         "HRT&__________"+ // 13
         "KöUYYYYYYYYYYY"+ // 14
         "XXXXXXXXXXXXXX"+ // 15
         "VVVVVVVVVVVVVV"+ // 16
         "MMMMMMMMMMMMMM"+ // 18
         "WWWWWWWWWWWWWW"; // 21
       aGFTlength.+width:= array
       (
          2, 3, 4, 5, 6, 7, 8, 9, 10, 11,
          12, 13, 14, 15, 16, 18, 21
       );
/////////////////////////////////////////////////////////////////

// Functions
/////////////////////////////////////////////////////////////////

// Returns the Width of GumpText
//
Function XGFTextWidth(gumptext)
  var points:=0;
  var j;

  For (j:=len(gumptext); j>0; j:=j-1)
    var i:=Find(aGFTlength.charsf, gumptext[j], 1)-1;
    If (i>=0)
      points:=points+aGFTlength.width[CInt(i/14)+1];
    Else
      print("XGFTextWidth: Unknown Character = '"+gumptext[j]+"'");
    EndIf
  EndFor

  Return (points);
EndFunction

// Returns the X-Value (Left-Alignment)
//
Function XGFTextLeft(gumptext, x, width)
  Return (x);
EndFunction

// Returns the X-Value (Mid-Alignment)
//
Function XGFTextMid(gumptext, x, width)
  Return (x+CInt((width-XGFTextWidth(gumptext))/2));
EndFunction

// Returns the X-Value (Right-Alignment)
//

Function XGFTextRight(gumptext, rightx)
  Return (rightx-XGFTextWidth(gumptext));
EndFunction

// Creates gump with tranparent background
//
function GFCheckerTrans( x, y, w, h )
	var line := "checkertrans" + " " + CStr(GFref.x + CInt(x)) + " " + CStr(GFref.y + CInt(y));
	line := line + " " + CStr(CInt(w)) + " " + CStr(CInt(h));
	GFlayout.append( line );
	return XGFRetVal( GFlayout.size() );
endfunction
