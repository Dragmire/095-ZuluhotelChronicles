///////////////////////////////////////////////////////////
// Creaturetypes.inc
//
// Constants for all the possible creature types
///////////////////////////////////////////////////////////

// Humanoids
const CREATURE_TYPE_HUMAN		:= 0x00001;
const CREATURE_TYPE_GIANTKIN		:= 0x00002;
const CREATURE_TYPE_ORC			:= 0x00004;
const CREATURE_TYPE_TROLL		:= 0x00008;

// Animalkin
const CREATURE_TYPE_ANIMAL		:= 0x00010;
const CREATURE_TYPE_DRAGONKIN		:= 0x00020;
const CREATURE_TYPE_GARGOYLE		:= 0x00040;
const CREATURE_TYPE_OPHIDIAN		:= 0x00080;
const CREATURE_TYPE_RATKIN		:= 0x00100;
const CREATURE_TYPE_TERATHAN		:= 0x00200;

// Others
const CREATURE_TYPE_BEHOLDER		:= 0x01000;
const CREATURE_TYPE_BEWITCHED		:= 0x02000;
const CREATURE_TYPE_DEMON		:= 0x04000;
const CREATURE_TYPE_ELEMENTAL		:= 0x08000;
const CREATURE_TYPE_PLANT		:= 0x10000;
const CREATURE_TYPE_SLIME		:= 0x20000;
const CREATURE_TYPE_UNDEAD		:= 0x40000;

const DEFAULT_CREATURE_TYPE		:= CREATURE_TYPE_HUMAN;