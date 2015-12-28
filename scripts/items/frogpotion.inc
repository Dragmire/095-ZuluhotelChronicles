use uo;
include "include/client"l

program frog_potion (character, potion)
const POISON_SOUND := 0x247;
const DRINK_SOUND := 0x32;
const UOBJ_EMPTY_BOTTLE := 0x0f0e;
const EFFECT_BLUE_SPARKLE  := 0x373a;
const SOUND_EFFECT_CURE	:= 0x1e1;
const EFFECT_SPARKLE  := 0x374a;
const HIT_ACTION := 0x148b;
const MOVING_EFFECT_PURPLE_POTION  := 0x0f0d;
const SOUND_EFFECT_EXPLOSION	:= 0x208;
const SOUND_EFFECT_HEAL	:= 0x1f3;
const EFFECT_EXPLOSION := 0x36b0;
const SKILLID_TASTEID := 36;


SendSysMessage(character, "You feel funny!");
    PlaySoundEffect(character, DRINK_SOUND);
    CreateItemInBackpack(character, UOBJ_EMPTY_BOTTLE, 1);
    DestroyItem(potion);
    PlayObjectCenteredEffect( character, EFFECT_BLUE_SPARKLE, 10,10); 