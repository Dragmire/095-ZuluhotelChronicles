/////////////////////////////////////////////////////////////////////
// Settings.inc
//
// Contains misc internal settings for all script except the
// spellsystem, which can be found in spellsyssetting.inc
/////////////////////////////////////////////////////////////////////


const SETTING_ATTACHED_SCRIPT_SPELLID		:= 200;

const SETTING_ATTRIBUTES_VALUE_MAX		:= 60000;
const SETTING_ATTRIBUTES_VALUE_MIN		:= 0;

const SETTING_CURSE_LEVEL_NOT_CURSED		:= 0;
const SETTING_CURSE_LEVEL_UNREVEALED		:= 1;
const SETTING_CURSE_LEVEL_REVEALED_CANT_UNEQUIP	:= 2;
const SETTING_CURSE_LEVEL_REVEALED_CAN_UNEQUIP	:= 3;

const SETTING_DURATION_PERMANENT		:= 9999;

const SETTING_ENCHANTMENTS_STAT_MULTIPLIER	:= 5;		// For stat gains, the base level([1,6]) will be multiplied by this to give the amount
const SETTING_ENCHANTMENTS_WEAPON_MULTIPLIER	:= 5;		// For skill gains on weapons, the base level([1,6]) will be multiplied by this to give the amount

const SETTING_MAX_ONLINE_TIME_FOR_NEWBIE_STATUS	:= 10;		// In days.

const SETTING_MAX_SKILL_FOR_SKILL_ITEM_LEVEL1	:= 500;		// In base value for apprentice items.
const SETTING_MAX_SKILL_FOR_SKILL_ITEM_LEVEL2	:= 750;		// In base value for journeyman items.
const SETTING_MAX_SKILL_FOR_SKILL_ITEM_LEVEL3	:= 1050;		// In base value for expert items.
const SETTING_MAX_SKILL_FOR_SKILL_ITEM_LEVEL4	:= 1250;	// In base value for adept items.
const SETTING_MAX_SKILL_FOR_SKILL_ITEM_LEVEL5	:= 1400;	// In base value for master items.
const SETTING_MAX_SKILL_FOR_SKILL_ITEM_LEVEL6	:= 1500;	// In base value for grandmaster items.

const SETTING_POISONING_SHOT_PER_PLVL		:= 2;		// Number of hits before reducing the plvl of a poisoned weapon.

const SETTING_POTIONKEG_MAX_CAPACITY		:= 100;

const SETTING_SKILL_ALWAYS_GAIN_UNTIL		:= 10;		// Always award a part of the points when the base skill is lower than this
const SETTING_SKILL_CHECK_MAX_CHANCE		:= 98;		// Max % of success.
const SETTING_SKILL_CHECK_MIN_CHANCE		:= 1;		// Min % of success.
const SETTING_SKILL_CHECK_EXCEPTIONAL_CHANCE	:= 10;
const SETTING_SKILL_DELAY_DEFAULT		:= 10;
const SETTING_SKILL_MULTIPLIER_LOCKED		:= 9999;