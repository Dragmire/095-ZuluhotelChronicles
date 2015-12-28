////////////////////////////////////////////////////////////////////////////
//
// eventids.inc
//
// Contains users defined events, those must use at least 2 bits,
// since sysevent.inc use one bit events.
//
// Maintainer : Shilohen
// Last modified : 26/04/2001
//
////////////////////////////////////////////////////////////////////////////


/* FIXME: these need to be renumbered, one clashes with a reserved event */
// OBSOLETE NOW with AI Package...
const EVID_SPELL_ATTACK     	:= 0x00000202;
const EVID_BUDDYATTACKED     	:= 0x00000204;
const EVID_PEACEMADE         	:= 0x00000206;

// AI Package Grouping Messages.
const EVID_GROUP_JOIN   	:= 0x00001002;
const EVID_GROUP_DEATH    	:= 0x00001004;
const EVID_GROUP_HELP		:= 0x00001008;

// SpawnRegion Package Messages.
const EVID_SPAWNREGION_DEATH	:= 0x00003001;


// AI Tamed messages.
const EVID_ALL_ATTACK_CMD   	:= 0x00002001;
const EVID_ALL_FOLLOW_CMD   	:= 0x00002002;
const EVID_ALL_GUARD_CMD	:= 0x00002004;

// Zulu var chat system
const EVID_CTF_MAKE_FLAG	:= 0x00007101;
const EVID_CTF_CAPTURE		:= 0x00007102;
const EVID_CTF_START		:= 0x00007104;
const EVID_CTF_END		:= 0x00007108;


///////////////////////////////////////////////////////////////////////////////////////////////
// MANAGERS EVENT IDS
///////////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////
// GENERAL						//
//////////////////////////////////////////////////////////

// Managers answer message
const EVID_MANAGER_ANSWER		:= 0x00001100;



//////////////////////////////////////////////////////////
// SPAWNERS	** Use 13th bits as identifier **	//
//////////////////////////////////////////////////////////

// SpawnBookcases Package Messages
const EVID_BOOKCASE_CREATED		:= 0x00001001;
const EVID_BOOKCASE_DESTROYED 		:= 0x00001002;
const EVID_BOOKCASE_SPAWN_ALL		:= 0x00001004;
const EVID_BOOKCASE_SPAWN_SOME		:= 0x00001008;
const EVID_BOOKCASE_REFRESH_CASES	:= 0x00001010;
const EVID_BOOKCASE_REQUEST_CASES	:= 0x00001020;

// SpawnChest Package Messages
const EVID_CHEST_CREATED		:= 0x00001001;
const EVID_CHEST_DESTROYED 		:= 0x00001002;
const EVID_CHEST_SPAWN_ALL		:= 0x00001004;
const EVID_CHEST_SPAWN_SOME		:= 0x00001008;
const EVID_CHEST_REFRESH_CHESTS		:= 0x00001010;
const EVID_CHEST_REQUEST_CHESTS		:= 0x00001020;

// SpawnPoint Package Messages.
const EVID_SPAWNPOINT_CHECK_POINT	:= 0x00001001;
const EVID_SPAWNPOINT_CREATED		:= 0x00001002;
const EVID_SPAWNPOINT_DEATH		:= 0x00001004;
const EVID_SPAWNPOINT_DESTROYED 	:= 0x00001008;
const EVID_SPAWNPOINT_RESETED		:= 0x00001010;
const EVID_SPAWNPOINT_SPAWN_ALL		:= 0x00001020;
const EVID_SPAWNPOINT_REFRESH_POINTS	:= 0x00001040;
const EVID_SPAWNPOINT_REQUEST_POINTS	:= 0x00001080;

// old
//const EVID_SPAWN_RUNE            := 0x00001400;
//const EVID_SPAWNPOINT_CHANGED    := 0x00001401;
//const EVID_SPAWN_DEATH           := 0x00001402;
//const EVID_SPAWN_ALL_POINTS_CMD  := 0x00001403;

//////////////////////////////////////////////////////////
// MISC CONTROLLERS ** Use 14th bits as identifier **	//
//////////////////////////////////////////////////////////

// Auction Package Messages
const EVID_AUCTION_ADD_ITEM		:= 0x00002001;
const EVID_AUCTION_ADD_PLAYER		:= 0x00002002;
const EVID_AUCTION_BID_ON_ITEM		:= 0x00002004;
const EVID_AUCTION_REMOVE_PLAYER	:= 0x00002008;
const EVID_AUCTION_SELL_ITEM		:= 0x00002010;
const EVID_AUCTION_REQUEST_ITEMS	:= 0x00002020;
const EVID_AUCTION_REQUEST_PLAYERS	:= 0x00002040;

// Lists Manager Messages
const EVID_LISTS_ADD_TO_AUCTION_LIST		:= 0x00002001;
const EVID_LISTS_REMOVE_FROM_AUCTION_LIST	:= 0x00002002;
const EVID_LISTS_REQUEST_AUCTION_LIST		:= 0x00002004;
const EVID_LISTS_ADD_TO_MSG_LIST		:= 0x00002010;
const EVID_LISTS_REMOVE_FROM_MSG_LIST		:= 0x00002020;
const EVID_LISTS_REQUEST_MSG_LIST		:= 0x00002040;
const EVID_LISTS_ADD_TO_STAFF_LIST		:= 0x00002100;
const EVID_LISTS_REMOVE_FROM_STAFF_LIST		:= 0x00002200;
const EVID_LISTS_REQUEST_STAFF_LIST		:= 0x00002400;