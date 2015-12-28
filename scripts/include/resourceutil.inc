/*
   Author: Unreal (MontuZ@Gmail.com) Oct 11, 2005.
   Version: 1.0
   Core: 093
   Bugs: None. Atleast none that I know of..
   PS: You know it was done by me when it's so clean.
*/

Use uo;

Include "include/client";

/* Ores */
Const ORE_IRON          := 0x6009;
Const ORE_BRONZE        := 0x600A;
Const ORE_DULL          := 0x600b;
Const ORE_COPPER        := 0x600c;
Const ORE_ONYX          := 0x600d;
Const ORE_PYRITE        := 0x600e;
Const ORE_MALACHITE     := 0x600f;
Const ORE_AZURITE       := 0x6010;
Const ORE_PLATINUM      := 0xc500;
Const ORE_LAVAROCK      := 0xc501;
Const ORE_MYSTIC        := 0xc502;
Const ORE_SPIKE         := 0xc504;
Const ORE_FRUITY        := 0xc505;
Const ORE_ICEROCK       := 0xc506;
Const ORE_SILVER        := 0xc507;
Const ORE_SPECTRAL      := 0xc508;
Const ORE_UNDEAD        := 0xc509;
Const ORE_DARKPAGAN     := 0xc50a;
Const ORE_BRITAIN       := 0xc50b;
Const ORE_VIRGINITY     := 0xc50c;
Const ORE_DWARF         := 0xc50d;
Const ORE_REDELVEN      := 0xc50e;
Const ORE_DRIPSTONE     := 0xc530;
Const ORE_EXECUTOR      := 0xc531;
Const ORE_PEACHBLUE     := 0xc532;
Const ORE_DESTRUCTION   := 0xc533;
Const ORE_ANRA          := 0xc534;
Const ORE_CRYSTAL       := 0xc536;
Const ORE_DOOM          := 0xc537;
Const ORE_ZULU          := 0xc535;
Const ORE_EBON          := 0xc538;
Const ORE_RUBY          := 0xc539;
Const ORE_NIMBUS        := 0xc53a;
Const ORE_UNREAL        := 0xc503;
/* Ingots */
Const INGOT_IRON        := 0x6011;
Const INGOT_BRONZE      := 0x6012;
Const INGOT_DULL        := 0x6013;
Const INGOT_COPPER      := 0x6014;
Const INGOT_ONYX        := 0x6015;
Const INGOT_PYRITE      := 0x6016;
Const INGOT_MALACHITE   := 0x6017;
Const INGOT_AZURITE     := 0x6018;
Const INGOT_PLATINUM    := 0xc510;
Const INGOT_LAVAROCK    := 0xc511;
Const INGOT_MYSTIC      := 0xc512;
Const INGOT_SPIKE       := 0xc514;
Const INGOT_FRUITY      := 0xc515;
Const INGOT_ICEROCK     := 0xc516;
Const INGOT_SILVER      := 0xc517;
Const INGOT_SPECTRAL    := 0xc518;
Const INGOT_UNDEAD      := 0xc519;
Const INGOT_DARKPAGAN   := 0xc51a;
Const INGOT_BRITAIN     := 0xc51b;
Const INGOT_VIRGINITY   := 0xc51c;
Const INGOT_DWARF       := 0xc51d;
Const INGOT_REDELVEN    := 0xc51e;
Const INGOT_DRIPSTONE   := 0xc51f;
Const INGOT_EXECUTOR    := 0xc520;
Const INGOT_PEACHBLUE   := 0xc521;
Const INGOT_DESTRUCTION := 0xc522;
Const INGOT_ANRA        := 0xc523;
Const INGOT_CRYSTAL     := 0xc525;
Const INGOT_DOOM        := 0xc526;
Const INGOT_ZULU        := 0xc524;
Const INGOT_EBON        := 0xc527;
Const INGOT_RUBY        := 0xc528;
Const INGOT_NIMBUS      := 0xc529;
Const INGOT_UNREAL      := 0xc513;
/* Logs */
Const LOG_REG           := 0x1BDD;
Const LOG_PINE          := 0x7300;
Const LOG_CHERRY        := 0x7301;
Const LOG_OAK           := 0x7302;
Const LOG_PASSION       := 0x7303;
Const LOG_GOLDEN        := 0x7304;
Const LOG_JADE          := 0x7305;
Const LOG_DARKWOOD      := 0x7306;
Const LOG_STONE         := 0x7307;
Const LOG_SUN           := 0x7308;
Const LOG_SWAMP         := 0x7309;
Const LOG_STARDUST      := 0x730a;
Const LOG_SILVER        := 0x730b;
Const LOG_STORM         := 0x730c;
Const LOG_EMERALD       := 0x730d;
Const LOG_BLOOD         := 0x730e;
Const LOG_CRYSTAL       := 0x730f;
Const LOG_DOOM          := 0x7310;
Const LOG_RANGER        := 0x7312;
Const LOG_GUANTLET      := 0x7313;
Const LOG_HOURSE        := 0x7314;
Const LOG_ZULU          := 0x7311;
Const LOG_UNREAL        := 0x7315;
Const LOG_ELEMENT       := 0x7316;
Const LOG_CHAOTIC       := 0x7317;
Const LOG_MYTHRIL       := 0x7318;
Const LOG_ALCATRAZ      := 0x7319;
Const LOG_ANIAS         := 0x7320;
Const LOG_KIERI         := 0x7321;
Const LOG_TREVIZE       := 0x7322;
Const LOG_LOTHIAN       := 0x7323;

/* Hides */
Const HIDE_REG          := 0x1078;
Const HIDE_RAT          := 0x7020;
Const HIDE_LIZARD       := 0x7023;
Const HIDE_TROLL        := 0x7022;
Const HIDE_OSTARD       := 0x7025;
Const HIDE_WOLF         := 0x702c;
Const HIDE_SERPENT      := 0x7024;
Const HIDE_BEAR         := 0x702d;
Const HIDE_ORC          := 0xdc0a;
Const HIDE_TERATHAN     := 0xdc13;
Const HIDE_NECRO        := 0x7028;
Const HIDE_LICHE        := 0x7029;
Const HIDE_LAVA         := 0x7027;
Const HIDE_ICE          := 0x702e;
Const HIDE_WYRM         := 0x702a;
Const HIDE_DRAGON       := 0x7021;
Const HIDE_GDRAGON      := 0x702b;
Const HIDE_BALRON       := 0x7026;
Const HIDE_CHAOTIC      := 0xff19;
Const HIDE_MYTHRIL      := 0xff20;
Const HIDE_ALCATRAZ     := 0xff21;
Const HIDE_ANIAS        := 0xff22;
Const HIDE_KIERI        := 0xff23;
Const HIDE_TREVIZE      := 0xff24;
Const HIDE_LOTHIAN      := 0xff25;
/* Gems */
Const GEM_STARSAPPHIRE  := 0x0F0F;
Const GEM_EMERALD       := 0x0F10;
Const GEM_SAPPHIRE      := 0x0F11;
Const GEM_RUBY          := 0x0F13;
Const GEM_CITRINE       := 0x0F15;
Const GEM_AMETHYST      := 0x0F16;
Const GEM_TOURMALINE    := 0x0F18;
Const GEM_AMBER         := 0x0F25;
Const GEM_DIAMOND       := 0x0F30;
/* Reags */
Const REAG_BLACKPEARL    := 0xF7A;
Const REAG_BLOODMOSS     := 0xF7B;
Const REAG_GARLIC        := 0xF84;
Const REAG_GINSENG       := 0xF85;
Const REAG_MANDRAKE      := 0xF86;
Const REAG_NIGHTSHADE    := 0xF88;
Const REAG_SULFUROUSASH  := 0xF8C;
Const REAG_SPIDERSILK    := 0xF8D;

Var gid_logs := {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

Function ShowLogsDialog( who )

    If ( CInt(GetObjProperty( who, "#logs_view" ) ) > ReadGameClock( ) )
    SendSysMessage( who, "Log List is already open.", FONT_NORMAL, 2611 );
    Return;
    Else
    SetObjProperty( who, "#logs_view", ReadGameClock( ) + 600 );
    Endif

    Var layout := {
    "page 0",
    "resizepic 0 0 3600 415 315",
    "text 25 15 2494 0",
    "text 25 35 2597 1",
    "text 25 55 2597 29",
    "text 25 75 2597 30",
    "text 25 95 2597 31",
    "text 25 115 2597 32",
    "text 25 135 2597 33",
    "text 25 155 2597 34",
    "text 25 175 2597 35",
    "text 25 195 2597 36",
    "text 25 215 2597 37",
    "text 25 235 2597 38",
    "text 25 255 2597 39",
    "text 25 275 2597 40",
    "text 215 35 2597 41",
    "text 215 55 2597 42",
    "text 215 75 2597 43",
    "text 215 95 2597 44",
    "text 215 115 2597 45",
    "text 215 135 2597 46",
    "text 215 155 2597 47",
    "text 215 175 2597 48",
    "text 215 195 2597 49",
    "text 215 215 2597 50",
    "text 215 235 2597 51",
//    "text 120 295 2494 53",   // My Tag =)
    };

    Var data := {
    "( Log List )",
    "Regular",
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    "Pinetree",
    "Cherry",
    "Oak",
    "Passion",
    "Reflections",
    "Jade",
    "Darkwood",
    "Stonewood",
    "Hardranger",
    "Swamp",
    "Stardust",
    "Silverleaf",
    "Stormteal",
    "Emerald",
    "Blood",
    "Crystal",
    "Doom",
    "Bloodhorse",
    "Sun",
    "Guantlet",
    "Zulu",
    "Unreal",
    "Elemental",
//    "[ Scripted By MontuZ ]",
    };

    Var layout_qty := {
    "text 115 35 ",
    "text 115 55 ",
    "text 115 75 ",
    "text 115 95 ",
    "text 115 115 ",
    "text 115 135 ",
    "text 115 155 ",
    "text 115 175 ",
    "text 115 195 ",
    "text 115 215 ",
    "text 115 235 ",
    "text 115 255 ",
    "text 115 275 ",
    "text 295 35 ",
    "text 295 55 ",
    "text 295 75 ",
    "text 295 95 ",
    "text 295 115 ",
    "text 295 135 ",
    "text 295 155 ",
    "text 295 175 ",
    "text 295 195 ",
    "text 295 215 ",
    "text 295 235 ",
    "text 295 255 ",
    };

    Var n;

    For( n := 1; n < 25; n := n + 1 )
    data[n+2] := gid_logs[n];
    Endfor

    Var color;

    For( n := 1; n < 25; n := n + 1 )
    color := 2494;
    layout_qty[n] := layout_qty[n] + color + " " + ( n+1 );
    layout.append ( layout_qty[n] );
    Endfor

    Var result := SendDialogGump( who, layout, data );

    EraseObjProperty( who, "#logs_view" );

EndFunction

Function is_log( what )

    If ( what.objtype >= 0x1bdd )
    Return 1;
    Else
    Return 0;
    Endif

EndFunction

Function is_a_backpack( what )

    If ( ( what.objtype == 0x0E75 ) || ( what.objtype == 0x190 ) || ( what.objtype == 0x191 ) )
    Return 1;
    Else
    Return 0;
    Endif

EndFunction

Function store_logs( who, log )

    Case( log.objtype )
    LOG_REG:      gid_logs[1]  := gid_logs[1]  + log.amount; Break;
    LOG_PINE:     gid_logs[2]  := gid_logs[2]  + log.amount; Break;
    LOG_CHERRY:   gid_logs[3]  := gid_logs[3]  + log.amount; Break;
    LOG_OAK:      gid_logs[4]  := gid_logs[4]  + log.amount; Break;
    LOG_PASSION:  gid_logs[5]  := gid_logs[5]  + log.amount; Break;
    LOG_GOLDEN:   gid_logs[6]  := gid_logs[6]  + log.amount; Break;
    LOG_JADE:     gid_logs[7]  := gid_logs[7]  + log.amount; Break;
    LOG_DARKWOOD: gid_logs[8]  := gid_logs[8]  + log.amount; Break;
    LOG_STONE:    gid_logs[9]  := gid_logs[9]  + log.amount; Break;
    LOG_RANGER:   gid_logs[10] := gid_logs[10] + log.amount; Break;
    LOG_SWAMP:    gid_logs[11] := gid_logs[11] + log.amount; Break;
    LOG_STARDUST: gid_logs[12] := gid_logs[12] + log.amount; Break;
    LOG_SILVER:   gid_logs[13] := gid_logs[13] + log.amount; Break;
    LOG_STORM:    gid_logs[14] := gid_logs[14] + log.amount; Break;
    LOG_EMERALD:  gid_logs[15] := gid_logs[15] + log.amount; Break;
    LOG_BLOOD:    gid_logs[16] := gid_logs[16] + log.amount; Break;
    LOG_CRYSTAL:  gid_logs[17] := gid_logs[17] + log.amount; Break;
    LOG_DOOM:     gid_logs[18] := gid_logs[18] + log.amount; Break;
    LOG_HOURSE:   gid_logs[19] := gid_logs[19] + log.amount; Break;
    LOG_SUN:      gid_logs[20] := gid_logs[20] + log.amount; Break;
    LOG_GUANTLET: gid_logs[21] := gid_logs[21] + log.amount; Break;
    LOG_ZULU:     gid_logs[22] := gid_logs[22] + log.amount; Break;
    LOG_UNREAL:   gid_logs[23] := gid_logs[23] + log.amount; Break;
    LOG_ELEMENT:  gid_logs[24] := gid_logs[24] + log.amount; Break;
    EndCase

EndFunction

Function count_logs( who, container, byref logs_counted )

    Foreach j In EnumerateItemsInContainer( container )
    If ( is_log( j ) )
    store_logs ( who, j );
    logs_counted := 1;
    Endif
    Endforeach

EndFunction

Var gid_hides := {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

Function ShowHidesDialog( who )

    If ( CInt(GetObjProperty( who, "#hides_view" ) ) > ReadGameClock( ) )
    SendSysMessage( who, "Hide List is already open.", FONT_NORMAL, 2611 );
    Return;
    Else
    SetObjProperty( who, "#hides_view", ReadGameClock( ) + 600 );
    Endif

    Var layout := {
    "page 0",
    "resizepic 0 0 3600 385 255",
    "text 25 15 2494 0",

    "text 25 35 2597 1",
    "text 25 55 2597 29",
    "text 25 75 2597 30",
    "text 25 95 2597 31",
    "text 25 115 2597 32",
    "text 25 135 2597 33",
    "text 25 155 2597 34",
    "text 25 175 2597 35",
    "text 25 195 2597 36",
    "text 25 215 2597 37",
    "text 200 35 2597 38",
    "text 200 55 2597 39",
    "text 200 75 2597 40",
    "text 200 95 2597 41",
    "text 200 115 2597 42",
    "text 200 135 2597 43",
    "text 200 155 2597 44",
    "text 200 175 2597 45",
    "text 200 195 2597 46",
//    "text 110 235 2557 47",   // My Tag =)
    };

    Var data := {
    "( Hide List )",
    "Regular",
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    "Rat",
    "Lizard",
    "Troll",
    "Ostard",
    "Wolf",
    "Serpent",
    "Bear",
    "Orc",
    "Terathan",
    "Necro",
    "Liche",
    "Lava",
    "Ice",
    "Wyrm",
    "Dragon",
    "G-Dragon",
    "Balron",
    "Balrog",
//    "[ Scripted By MontuZ ]",
    };

    Var layout_qty := {
    "text 100 35 ",
    "text 100 55 ",
    "text 100 75 ",
    "text 100 95 ",
    "text 100 115 ",
    "text 100 135 ",
    "text 100 155 ",
    "text 100 175 ",
    "text 100 195 ",
    "text 100 215 ",
    "text 275 35 ",
    "text 275 55 ",
    "text 275 75 ",
    "text 275 95 ",
    "text 275 115 ",
    "text 275 135 ",
    "text 275 155 ",
    "text 275 175 ",
    "text 275 195 ",
    };

    Var n;

    For( n := 1; n < 20; n := n + 1 )
    data[n+2] := gid_hides[n];
    Endfor

    Var color;

    For( n := 1; n < 20; n := n + 1 )
    color := 2494;
    layout_qty[n] := layout_qty[n] + color + " " + ( n+1 );
    layout.append ( layout_qty[n] );
    Endfor

    Var result := SendDialogGump( who, layout, data );

    EraseObjProperty( who, "#hides_view" );

EndFunction

Function is_hide( what )

    If ( what.objtype >= 0x1078 )
    Return 1;
    Else
    Return 0;
    Endif

EndFunction

Function store_hides( who, hide )

    Case( hide.objtype )
    HIDE_REG:      gid_hides[1]  := gid_hides[1]  + hide.amount; Break;
    HIDE_RAT:      gid_hides[2]  := gid_hides[2]  + hide.amount; Break;
    HIDE_LIZARD:   gid_hides[3]  := gid_hides[3]  + hide.amount; Break;
    HIDE_TROLL:    gid_hides[4]  := gid_hides[4]  + hide.amount; Break;
    HIDE_OSTARD:   gid_hides[5]  := gid_hides[5]  + hide.amount; Break;
    HIDE_WOLF:     gid_hides[6]  := gid_hides[6]  + hide.amount; Break;
    HIDE_SERPENT:  gid_hides[7]  := gid_hides[7]  + hide.amount; Break;
    HIDE_BEAR:     gid_hides[8]  := gid_hides[8]  + hide.amount; Break;
    HIDE_ORC:      gid_hides[9]  := gid_hides[9]  + hide.amount; Break;
    HIDE_TERATHAN: gid_hides[10] := gid_hides[10] + hide.amount; Break;
    HIDE_NECRO:    gid_hides[11] := gid_hides[11] + hide.amount; Break;
    HIDE_LAVA:     gid_hides[12] := gid_hides[12] + hide.amount; Break;
    HIDE_LICHE:    gid_hides[13] := gid_hides[13] + hide.amount; Break;
    HIDE_ICE:      gid_hides[14] := gid_hides[14] + hide.amount; Break;
    HIDE_WYRM:     gid_hides[15] := gid_hides[15] + hide.amount; Break;
    HIDE_DRAGON:   gid_hides[16] := gid_hides[16] + hide.amount; Break;
    HIDE_GDRAGON:  gid_hides[17] := gid_hides[17] + hide.amount; Break;
    HIDE_BALRON:   gid_hides[18] := gid_hides[18] + hide.amount; Break;
    HIDE_BALROG:   gid_hides[19] := gid_hides[19] + hide.amount; Break;
    EndCase

EndFunction

Function count_hides( who, container, byref hides_counted )

    Foreach j In EnumerateItemsInContainer( container )
    If ( is_hide( j ) )
    store_hides ( who, j );
    hides_counted := 1;
    Endif
    Endforeach

EndFunction

Var gid_ores := {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

Function ShowOresDialog( who )

    If ( CInt(GetObjProperty( who, "#ores_view" ) ) > ReadGameClock( ) )
    SendSysMessage( who, "Ore List is already open.", FONT_NORMAL, 2611 );
    Return;
    Else
    SetObjProperty( who, "#ores_view", ReadGameClock( ) + 600 );
    Endif

    Var layout := {
    "page 0",
    "resizepic 0 0 3600 565 315",
    "tilepic 475 235 6585",
    "text 25 15 2494 0",
    "text 25 35 2597 1",
    "text 25 55 2597 36",
    "text 25 75 2597 37",
    "text 25 95 2597 38",
    "text 25 115 2597 39",
    "text 25 135 2597 40",
    "text 25 155 2597 41",
    "text 25 175 2597 42",
    "text 25 195 2597 43",
    "text 25 215 2597 44",
    "text 25 235 2597 45",
    "text 25 255 2597 46",
    "text 25 275 2597 47",
    "text 215 35 2597 48",
    "text 215 55 2597 49",
    "text 215 75 2597 50",
    "text 215 95 2597 51",
    "text 215 115 2597 52",
    "text 215 135 2597 53",
    "text 215 155 2597 54",
    "text 215 175 2597 55",
    "text 215 195 2597 56",
    "text 215 215 2597 57",
    "text 215 235 2597 58",
    "text 215 255 2597 59",
    "text 215 275 2597 60",
    "text 405 35 2597 61",
    "text 405 55 2597 62",
    "text 405 75 2597 63",
    "text 405 95 2597 64",
    "text 405 115 2597 65",
    "text 405 135 2597 66",
    "text 405 155 2597 67",
    "text 405 175 2597 68",
//    "text 25 295 2494 69",   // My Tag =)
    };

    Var data := {
    "( Ore List )",
    "Iron",
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    "Bronze",
    "Dull Copper",
    "Copper",
    "Onyx",
    "Pyrite",
    "Malachite",
    "Azurite",
    "Platinum",
    "Lavarock",
    "Mystic",
    "Spike",
    "Fruity",
    "Icerock",
    "Silverrock",
    "Spectral",
    "Undead",
    "Darkpagan",
    "Oldbritain",
    "Virginity",
    "Blackdwarf",
    "Redelven",
    "Dripstone",
    "Executor",
    "Peachblue",
    "Destruction",
    "Anra",
    "Crystal",
    "Doom",
    "Zulu",
    "Ebon",
    "Ruby",
    "Nimbus",
    "Unreal",
//    "[ Scripted By MontuZ ]",
    };

    Var layout_qty := {
    "text 115 35 ",
    "text 115 55 ",
    "text 115 75 ",
    "text 115 95 ",
    "text 115 115 ",
    "text 115 135 ",
    "text 115 155 ",
    "text 115 175 ",
    "text 115 195 ",
    "text 115 215 ",
    "text 115 235 ",
    "text 115 255 ",
    "text 115 275 ",
    "text 305 35 ",
    "text 305 55 ",
    "text 305 75 ",
    "text 305 95 ",
    "text 305 115 ",
    "text 305 135 ",
    "text 305 155 ",
    "text 305 175 ",
    "text 305 195 ",
    "text 305 215 ",
    "text 305 235 ",
    "text 305 255 ",
    "text 305 275 ",
    "text 475 35 ",
    "text 475 55 ",
    "text 475 75 ",
    "text 475 95 ",
    "text 475 115 ",
    "text 475 135 ",
    "text 475 155 ",
    "text 475 175 ",
    };

    Var n;

    For( n := 1; n < 35; n := n + 1 )
    data[n+2] := gid_ores[n];
    Endfor

    Var color;

    For( n := 1; n < 35; n := n + 1 )
    color := 2494;
    layout_qty[n] := layout_qty[n] + color + " " + ( n+1 );
    layout.append ( layout_qty[n] );
    Endfor

    Var result := SendDialogGump( who, layout, data );

    EraseObjProperty( who, "#ores_view" );

EndFunction

Function is_ore( what )

    If ( what.objtype >= 0x19B9 )
    Return 1;
    Else
    Return 0;
    Endif

EndFunction

Function store_ores( who, ore )

    Case( ore.objtype )
    ORE_IRON:        gid_ores[1]  := gid_ores[1]  + ore.amount; Break;
    ORE_BRONZE:      gid_ores[2]  := gid_ores[2]  + ore.amount; Break;
    ORE_DULL:        gid_ores[3]  := gid_ores[3]  + ore.amount; Break;
    ORE_COPPER:      gid_ores[4]  := gid_ores[4]  + ore.amount; Break;
    ORE_ONYX:        gid_ores[5]  := gid_ores[5]  + ore.amount; Break;
    ORE_PYRITE:      gid_ores[6]  := gid_ores[6]  + ore.amount; Break;
    ORE_MALACHITE:   gid_ores[7]  := gid_ores[7]  + ore.amount; Break;
    ORE_AZURITE:     gid_ores[8]  := gid_ores[8]  + ore.amount; Break;
    ORE_PLATINUM:    gid_ores[9]  := gid_ores[9]  + ore.amount; Break;
    ORE_LAVAROCK:    gid_ores[10] := gid_ores[10] + ore.amount; Break;
    ORE_MYSTIC:      gid_ores[11] := gid_ores[11] + ore.amount; Break;
    ORE_SPIKE:       gid_ores[12] := gid_ores[12] + ore.amount; Break;
    ORE_FRUITY:      gid_ores[13] := gid_ores[13] + ore.amount; Break;
    ORE_ICEROCK:     gid_ores[14] := gid_ores[14] + ore.amount; Break;
    ORE_SILVER:      gid_ores[15] := gid_ores[15] + ore.amount; Break;
    ORE_SPECTRAL:    gid_ores[16] := gid_ores[16] + ore.amount; Break;
    ORE_UNDEAD:      gid_ores[17] := gid_ores[17] + ore.amount; Break;
    ORE_DARKPAGAN:   gid_ores[18] := gid_ores[18] + ore.amount; Break;
    ORE_BRITAIN:     gid_ores[19] := gid_ores[19] + ore.amount; Break;
    ORE_VIRGINITY:   gid_ores[20] := gid_ores[20] + ore.amount; Break;
    ORE_DWARF:       gid_ores[21] := gid_ores[21] + ore.amount; Break;
    ORE_REDELVEN:    gid_ores[22] := gid_ores[22] + ore.amount; Break;
    ORE_DRIPSTONE:   gid_ores[23] := gid_ores[23] + ore.amount; Break;
    ORE_EXECUTOR:    gid_ores[24] := gid_ores[24] + ore.amount; Break;
    ORE_PEACHBLUE:   gid_ores[25] := gid_ores[25] + ore.amount; Break;
    ORE_DESTRUCTION: gid_ores[26] := gid_ores[26] + ore.amount; Break;
    ORE_ANRA:        gid_ores[27] := gid_ores[27] + ore.amount; Break;
    ORE_CRYSTAL:     gid_ores[28] := gid_ores[28] + ore.amount; Break;
    ORE_DOOM:        gid_ores[29] := gid_ores[29] + ore.amount; Break;
    ORE_ZULU:        gid_ores[30] := gid_ores[30] + ore.amount; Break;
    ORE_EBON:        gid_ores[31] := gid_ores[31] + ore.amount; Break;
    ORE_RUBY:        gid_ores[32] := gid_ores[32] + ore.amount; Break;
    ORE_NIMBUS:      gid_ores[33] := gid_ores[33] + ore.amount; Break;
    ORE_UNREAL:      gid_ores[34] := gid_ores[34] + ore.amount; Break;
    EndCase

EndFunction

Function count_ores( who, container, byref ores_counted )

    Foreach j In EnumerateItemsInContainer( container )
    If ( is_ore( j ) )
    store_ores ( who, j );
    ores_counted := 1;
    Endif
    Endforeach

EndFunction

Var gid_ingots := {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

Function ShowIngotsDialog( who )

    If ( CInt(GetObjProperty( who, "#ingots_view" ) ) > ReadGameClock( ) )
    SendSysMessage( who, "Ingot List is already open.", FONT_NORMAL, 2611 );
    Return;
    Else
    SetObjProperty( who, "#ingots_view", ReadGameClock( ) + 600 );
    Endif

    Var layout := {
    "page 0",
    "resizepic 0 0 3600 565 315",
    "tilepic 475 240 7159",
    "text 25 15 2494 0",
    "text 25 35 2597 1",
    "text 25 55 2597 36",
    "text 25 75 2597 37",
    "text 25 95 2597 38",
    "text 25 115 2597 39",
    "text 25 135 2597 40",
    "text 25 155 2597 41",
    "text 25 175 2597 42",
    "text 25 195 2597 43",
    "text 25 215 2597 44",
    "text 25 235 2597 45",
    "text 25 255 2597 46",
    "text 25 275 2597 47",
    "text 215 35 2597 48",
    "text 215 55 2597 49",
    "text 215 75 2597 50",
    "text 215 95 2597 51",
    "text 215 115 2597 52",
    "text 215 135 2597 53",
    "text 215 155 2597 54",
    "text 215 175 2597 55",
    "text 215 195 2597 56",
    "text 215 215 2597 57",
    "text 215 235 2597 58",
    "text 215 255 2597 59",
    "text 215 275 2597 60",
    "text 405 35 2597 61",
    "text 405 55 2597 62",
    "text 405 75 2597 63",
    "text 405 95 2597 64",
    "text 405 115 2597 65",
    "text 405 135 2597 66",
    "text 405 155 2597 67",
    "text 405 175 2597 68",
//    "text 200 295 2557 69",   // My Tag =)
    };

    Var data := {
    "( Ingot List )",
    "Iron",
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    "Bronze",
    "Dull Copper",
    "Copper",
    "Onyx",
    "Pyrite",
    "Malachite",
    "Azurite",
    "Platinum",
    "Lavarock",
    "Mystic",
    "Spike",
    "Fruity",
    "Icerock",
    "Silverrock",
    "Spectral",
    "Undead",
    "Darkpagan",
    "Oldbritain",
    "Virginity",
    "Blackdwarf",
    "Redelven",
    "Dripstone",
    "Executor",
    "Peachblue",
    "Destruction",
    "Anra",
    "Crystal",
    "Doom",
    "Zulu",
    "Ebon",
    "Ruby",
    "Nimbus",
    "Unreal",
//    "[ Scripted By MontuZ ]",
    };

    Var layout_qty := {
    "text 115 35 ",
    "text 115 55 ",
    "text 115 75 ",
    "text 115 95 ",
    "text 115 115 ",
    "text 115 135 ",
    "text 115 155 ",
    "text 115 175 ",
    "text 115 195 ",
    "text 115 215 ",
    "text 115 235 ",
    "text 115 255 ",
    "text 115 275 ",
    "text 305 35 ",
    "text 305 55 ",
    "text 305 75 ",
    "text 305 95 ",
    "text 305 115 ",
    "text 305 135 ",
    "text 305 155 ",
    "text 305 175 ",
    "text 305 195 ",
    "text 305 215 ",
    "text 305 235 ",
    "text 305 255 ",
    "text 305 275 ",
    "text 475 35 ",
    "text 475 55 ",
    "text 475 75 ",
    "text 475 95 ",
    "text 475 115 ",
    "text 475 135 ",
    "text 475 155 ",
    "text 475 175 ",
    };

    Var n;

    For( n := 1; n < 35; n := n + 1 )
    data[n+2] := gid_ingots[n];
    Endfor

    Var color;

    For( n := 1; n < 35; n := n + 1 )
    color := 2494;
    layout_qty[n] := layout_qty[n] + color + " " + ( n+1 );
    layout.append ( layout_qty[n] );
    Endfor

    Var result := SendDialogGump( who, layout, data );

    EraseObjProperty( who, "#ingots_view" );

EndFunction

Function is_ingot( what )

    If ( what.objtype >= 0x1bf2 )
    Return 1;
    Else
    Return 0;
    Endif

EndFunction

Function store_ingots( who, ingot )

    Case( ingot.objtype )
    INGOT_IRON:        gid_ingots[1]  := gid_ingots[1]  + ingot.amount; Break;
    INGOT_BRONZE:      gid_ingots[2]  := gid_ingots[2]  + ingot.amount; Break;
    INGOT_DULL:        gid_ingots[3]  := gid_ingots[3]  + ingot.amount; Break;
    INGOT_COPPER:      gid_ingots[4]  := gid_ingots[4]  + ingot.amount; Break;
    INGOT_ONYX:        gid_ingots[5]  := gid_ingots[5]  + ingot.amount; Break;
    INGOT_PYRITE:      gid_ingots[6]  := gid_ingots[6]  + ingot.amount; Break;
    INGOT_MALACHITE:   gid_ingots[7]  := gid_ingots[7]  + ingot.amount; Break;
    INGOT_AZURITE:     gid_ingots[8]  := gid_ingots[8]  + ingot.amount; Break;
    INGOT_PLATINUM:    gid_ingots[9]  := gid_ingots[9]  + ingot.amount; Break;
    INGOT_LAVAROCK:    gid_ingots[10] := gid_ingots[10] + ingot.amount; Break;
    INGOT_MYSTIC:      gid_ingots[11] := gid_ingots[11] + ingot.amount; Break;
    INGOT_SPIKE:       gid_ingots[12] := gid_ingots[12] + ingot.amount; Break;
    INGOT_FRUITY:      gid_ingots[13] := gid_ingots[13] + ingot.amount; Break;
    INGOT_ICEROCK:     gid_ingots[14] := gid_ingots[14] + ingot.amount; Break;
    INGOT_SILVER:      gid_ingots[15] := gid_ingots[15] + ingot.amount; Break;
    INGOT_SPECTRAL:    gid_ingots[16] := gid_ingots[16] + ingot.amount; Break;
    INGOT_UNDEAD:      gid_ingots[17] := gid_ingots[17] + ingot.amount; Break;
    INGOT_DARKPAGAN:   gid_ingots[18] := gid_ingots[18] + ingot.amount; Break;
    INGOT_BRITAIN:     gid_ingots[19] := gid_ingots[19] + ingot.amount; Break;
    INGOT_VIRGINITY:   gid_ingots[20] := gid_ingots[20] + ingot.amount; Break;
    INGOT_DWARF:       gid_ingots[21] := gid_ingots[21] + ingot.amount; Break;
    INGOT_REDELVEN:    gid_ingots[22] := gid_ingots[22] + ingot.amount; Break;
    INGOT_DRIPSTONE:   gid_ingots[23] := gid_ingots[23] + ingot.amount; Break;
    INGOT_EXECUTOR:    gid_ingots[24] := gid_ingots[24] + ingot.amount; Break;
    INGOT_PEACHBLUE:   gid_ingots[25] := gid_ingots[25] + ingot.amount; Break;
    INGOT_DESTRUCTION: gid_ingots[26] := gid_ingots[26] + ingot.amount; Break;
    INGOT_ANRA:        gid_ingots[27] := gid_ingots[27] + ingot.amount; Break;
    INGOT_CRYSTAL:     gid_ingots[28] := gid_ingots[28] + ingot.amount; Break;
    INGOT_DOOM:        gid_ingots[29] := gid_ingots[29] + ingot.amount; Break;
    INGOT_ZULU:        gid_ingots[30] := gid_ingots[30] + ingot.amount; Break;
    INGOT_EBON:        gid_ingots[31] := gid_ingots[31] + ingot.amount; Break;
    INGOT_RUBY:        gid_ingots[32] := gid_ingots[32] + ingot.amount; Break;
    INGOT_NIMBUS:      gid_ingots[33] := gid_ingots[33] + ingot.amount; Break;
    INGOT_UNREAL:      gid_ingots[34] := gid_ingots[34] + ingot.amount; Break;
    EndCase

EndFunction

Function count_ingots( who, container, byref ingots_counted )

    Foreach j In EnumerateItemsInContainer( container )
    If ( is_ingot( j ) )
    store_ingots ( who, j );
    ingots_counted := 1;
    Endif
    Endforeach

EndFunction

Var gid_gems := {0,0,0,0,0,0,0,0,0};

Function ShowGemsDialog( who )

    If ( CInt(GetObjProperty( who, "#gems_view" ) ) > ReadGameClock( ) )
    SendSysMessage( who, "Gem List is already open.", FONT_NORMAL, 2611 );
    Return;
    Else
    SetObjProperty( who, "#gems_view", ReadGameClock( ) + 600 );
    Endif

    Var layout := {
    "page 0",
    "resizepic 0 0 3600 205 230",
    "text 25 15 2494 0",
    "text 25 35 2597 1",
    "text 25 55 2597 14",
    "text 25 75 2597 15",
    "text 25 95 2597 16",
    "text 25 115 2597 17",
    "text 25 135 2597 18",
    "text 25 155 2597 19",
    "text 25 175 2597 20",
    "text 25 195 2597 21",
//    "text 120 295 2494 53",   // My Tag =)
    };

    Var data := {
    "( Gem List )",
    "Starsapphire",
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    "Emerald",
    "Sapphire",
    "Ruby",
    "Citrine",
    "Amethyst",
    "Tourmaline",
    "Amber",
    "Diamond",
//    "[ Scripted By MontuZ ]",
    };

    Var layout_qty := {
    "text 125 35 ",
    "text 125 55 ",
    "text 125 75 ",
    "text 125 95 ",
    "text 125 115 ",
    "text 125 135 ",
    "text 125 155 ",
    "text 125 175 ",
    "text 125 195 ",
    };

    Var n;

    For( n := 1; n < 10; n := n + 1 )
    data[n+2] := gid_gems[n];
    Endfor

    Var color;

    For( n := 1; n < 10; n := n + 1 )
    color := 2494;
    layout_qty[n] := layout_qty[n] + color + " " + ( n+1 );
    layout.append ( layout_qty[n] );
    Endfor

    Var result := SendDialogGump( who, layout, data );

    EraseObjProperty( who, "#gems_view" );

EndFunction

Function is_gem( what )

    If( what.objtype >= 0x0F0F )
    Return 1;
    Else
    Return 0;
    Endif

EndFunction

Function store_gems( who, gem )

    Case( gem.objtype )
    GEM_STARSAPPHIRE: gid_gems[1]  := gid_gems[1]  + gem.amount; Break;
    GEM_EMERALD:      gid_gems[2]  := gid_gems[2]  + gem.amount; Break;
    GEM_SAPPHIRE:     gid_gems[3]  := gid_gems[3]  + gem.amount; Break;
    GEM_RUBY:         gid_gems[4]  := gid_gems[4]  + gem.amount; Break;
    GEM_CITRINE:      gid_gems[5]  := gid_gems[5]  + gem.amount; Break;
    GEM_AMETHYST:     gid_gems[6]  := gid_gems[6]  + gem.amount; Break;
    GEM_TOURMALINE:   gid_gems[7]  := gid_gems[7]  + gem.amount; Break;
    GEM_AMBER:        gid_gems[8]  := gid_gems[8]  + gem.amount; Break;
    GEM_DIAMOND:      gid_gems[9]  := gid_gems[9]  + gem.amount; Break;
    EndCase

EndFunction

Function count_gems( who, container, byref gems_counted )

    Foreach j In EnumerateItemsInContainer( container )
    If ( is_gem( j ) )
    store_gems ( who, j );
    gems_counted := 1;
    Endif
    Endforeach

EndFunction

Var gid_reags := {0,0,0,0,0,0,0,0};

Function ShowReagsDialog( who )

    If ( CInt(GetObjProperty( who, "#reags_view" ) ) > ReadGameClock( ) )
    SendSysMessage( who, "Reag List is already open.", FONT_NORMAL, 2611 );
    Return;
    Else
    SetObjProperty( who, "#reags_view", ReadGameClock( ) + 600 );
    Endif

    Var layout := {
    "page 0",
    "resizepic 0 0 3600 230 210",
    "text 25 15 2494 0",
    "text 25 35 2597 1",
    "text 25 55 2597 13",
    "text 25 75 2597 14",
    "text 25 95 2597 15",
    "text 25 115 2597 16",
    "text 25 135 2597 17",
    "text 25 155 2597 18",
    "text 25 175 2597 19",
//    "text 120 295 2494 53",   // My Tag =)
    };

    Var data := {
    "( Reag List )",
    "Black Pearl",
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    "Blood Moss",
    "Garlic",
    "Ginseng",
    "Mandrake",
    "Nightshade",
    "Sulfurous Ash",
    "Spider's Silk",
//    "[ Scripted By MontuZ ]",
    };

    Var layout_qty := {
    "text 145 35 ",
    "text 145 55 ",
    "text 145 75 ",
    "text 145 95 ",
    "text 145 115 ",
    "text 145 135 ",
    "text 145 155 ",
    "text 145 175 ",
    "text 145 195 ",
    };

    Var n;

    For( n := 1; n < 9; n := n + 1 )
    data[n+2] := gid_reags[n];
    Endfor

    Var color;

    For( n := 1; n < 9; n := n + 1 )
    color := 2494;
    layout_qty[n] := layout_qty[n] + color + " " + ( n+1 );
    layout.append ( layout_qty[n] );
    Endfor

    Var result := SendDialogGump( who, layout, data );

    EraseObjProperty( who, "#reags_view" );

EndFunction

Function is_reag( what )

    If( what.objtype >= 0xF7A )
    Return 1;
    Else
    Return 0;
    Endif

EndFunction

Function store_reags( who, reag )

    Case( reag.objtype )
    REAG_BLACKPEARL:   gid_reags[1]  := gid_reags[1]  + reag.amount; Break;
    REAG_BLOODMOSS:    gid_reags[2]  := gid_reags[2]  + reag.amount; Break;
    REAG_GARLIC:       gid_reags[3]  := gid_reags[3]  + reag.amount; Break;
    REAG_GINSENG:      gid_reags[4]  := gid_reags[4]  + reag.amount; Break;
    REAG_MANDRAKE:     gid_reags[5]  := gid_reags[5]  + reag.amount; Break;
    REAG_NIGHTSHADE:   gid_reags[6]  := gid_reags[6]  + reag.amount; Break;
    REAG_SULFUROUSASH: gid_reags[7]  := gid_reags[7]  + reag.amount; Break;
    REAG_SPIDERSILK:   gid_reags[8]  := gid_reags[8]  + reag.amount; Break;
    EndCase

EndFunction

Function count_reags( who, container, byref reags_counted )

    Foreach j In EnumerateItemsInContainer( container )
    If ( is_reag( j ) )
    store_reags ( who, j );
    reags_counted := 1;
    Endif
    Endforeach

EndFunction
