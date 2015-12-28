////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////
//  CLIENT.INC - defines client releated constants.
//
//  This include file is designed to hold all the client lowlevel constants.
//  Not all constants might be usable as of now, but in the future, they
//  might be.
//
//  Author: Ignatius 1999/01/20
//
//  Recent Modifications
//      1999/01/25 Ignatius added animations/actions/sounds.
//      1999/01/26 Ignatius moved skillids/constants into this file and
//                 added a lot of more sounds. 
//      1999/01/27 Ignatius found out that I got the sounds all wrong
//                 it seems, fixed up a lot of things there. Started
//                 to map out the T2A sounds. Added some creature IDs.
////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////

include "include/attributes";

////
// Soundeffects
// The first section is just an enum of existing sounds,
// the second builds on the first ones, but providing more
// logical names. 
///
const SFX_1     :=  0x0001; // forest
const SFX_2     :=  0x0002; // forest
const SFX_3     :=  0x0003; // forest
const SFX_4     :=  0x0004; // jungle
const SFX_5     :=  0x0005; // jungle
const SFX_6     :=  0x0006; // jungle
const SFX_7     :=  0x0007; // swamp
const SFX_8     :=  0x0008; // swamp
const SFX_9     :=  0x0009; // forest
const SFX_A     :=  0x000a; // forest
const SFX_B     :=  0x000b; // generic
const SFX_C     :=  0x000c; // generic
const SFX_D     :=  0x000d; // jungle
const SFX_E     :=  0x000e; // jungle
const SFX_F     :=  0x000f; // swamp
const SFX_10    :=  0x0010; // swamp
const SFX_11    :=  0x0011; // water
const SFX_12    :=  0x0012; // water
const SFX_13    :=  0x0013; // waves
const SFX_14    :=  0x0014; // waves
const SFX_15    :=  0x0015; // wind
const SFX_16    :=  0x0016; // wind
const SFX_17    :=  0x0017; // wind
const SFX_18    :=  0x0018; // bird
const SFX_19    :=  0x0019; // bird
const SFX_1A    :=  0x001a; // bird
const SFX_1B    :=  0x001b; // bird
const SFX_1C    :=  0x001c; // bird
const SFX_1D    :=  0x001d; // bird
const SFX_1E    :=  0x001e; // bird
const SFX_1F    :=  0x001f; // bird
const SFX_20    :=  0x0020; // bird
const SFX_21    :=  0x0021; // bubbles
const SFX_22    :=  0x0022; // bubbles
const SFX_23    :=  0x0023; // dripping
const SFX_24    :=  0x0024; // dripping
const SFX_25    :=  0x0025; // dripping
const SFX_26    :=  0x0026; // splashing
const SFX_27    :=  0x0027; // splashing
const SFX_28    :=  0x0028; // splashing
const SFX_29    :=  0x0029; // thundr01.wav, thunder
const SFX_2A    :=  0x002a; // thundr02.wav, thunder
const SFX_2B    :=  0x002b; // anvil.wav, anvil
const SFX_2C    :=  0x002c; // bellows.wav, bellows
const SFX_2D    :=  0x002d; // chstcls3.wav, chest close
const SFX_2E    :=  0x002e; // chstopn2.wav, chest open
const SFX_2F    :=  0x002f; // drawercl.wav, drawer close
const SFX_30    :=  0x0030; // drawerop.wav, drawer open
const SFX_31    :=  0x0031; // drink01.wav, drink
const SFX_32    :=  0x0032; // drink05.wav, drink
const SFX_33    :=  0x0033; // dropgem1.wav, drop gem
const SFX_34    :=  0x0034; // dropgem2.wav, drop gem
const SFX_35    :=  0x0035; // dropgem3.wav, drop gem
const SFX_36    :=  0x0036; // dropmny1.wav, drop money
const SFX_37    :=  0x0037; // dropmny2.wav, drop money
const SFX_38    :=  0x0038; // dropmny3.wav, drop money
const SFX_39    :=  0x0039; // drum01.wav, drum
const SFX_3A    :=  0x003a; // drum01_b.wav, drum
const SFX_3B    :=  0x003b; // eat01.wav, eat
const SFX_3C    :=  0x003c; // eat03.wav, eat
const SFX_3D    :=  0x003d; // eat06.wav,eat
const SFX_3E    :=  0x003e; // flute01.wav, flute
const SFX_3F    :=  0x003f; // glasbrk1.wav, glassbreak
const SFX_40    :=  0x0040; // glasbrk2.wav, glassbreak
const SFX_41    :=  0x0041; // glasbrk3.wav, glassbreak
const SFX_42    :=  0x0042; // glasbrk4.wav, glassbreak
const SFX_43    :=  0x0043; // hamer01.wav, hammer
const SFX_44    :=  0x0044; // harp01.wav, harp
const SFX_45    :=  0x0045; // harp01_b.wav, harp
const SFX_46    :=  0x0046; // harp02.wav, harp
const SFX_47    :=  0x0047; // harp02_b.wav, harp
const SFX_48    :=  0x0048; // igntorch.wav, ignite torch
const SFX_49    :=  0x0049; // leather1.wav, leather
const SFX_4A    :=  0x004a; // lever01.wav, lever
const SFX_4B    :=  0x004b; // lever02.wav, lever
const SFX_4C    :=  0x004c; // lever05.wav, lever
const SFX_4D    :=  0x004d; // lute01.wav, lute
const SFX_4E    :=  0x004e; // lute01_b.wav, lute
const SFX_4F    :=  0x004f; // pouring.wav, pouring
const SFX_50    :=  0x0050; // rustle.wav, rustle
const SFX_51    :=  0x0051; // swallow2.wav, swallow
const SFX_52    :=  0x0052; // switch01.wav, switch
const SFX_53    :=  0x0053; // tamborin.wav, tamborine
const SFX_54    :=  0x0054; // tambrn_b.wav, tamborine
const SFX_55    :=  0x0055; // torch01.wav, torch
const SFX_56    :=  0x0056; // turnpage.wav, turn page
const SFX_57    :=  0x0057; // unsheth1.wav, ?
const SFX_58    :=  0x0058; // usecloth.wav, use cloth
const SFX_59    :=  0x0059; // uselethr.wav, use leather
const SFX_5A    :=  0x005a; // uselthr1.wav, use leather
const SFX_5B    :=  0x005b; // aligatr1.wav, alligator
const SFX_5C    :=  0x005c; // aligatr2.wav, alligator
const SFX_5D    :=  0x005d; // aligatr3.wav, alligator
const SFX_5E    :=  0x005e; // aligatr4.wav, alligator
const SFX_5F    :=  0x005f; // aligatr5.wav, alligator
const SFX_60    :=  0x0060; // bear1.wav, bear
const SFX_61    :=  0x0061; // bear2.wav, bear
const SFX_62    :=  0x0062; // bear3.wav, bear
const SFX_63    :=  0x0063; // bear4.wav, bear
const SFX_64    :=  0x0064; // bear5.wav, bear
const SFX_65    :=  0x0065; // bull1.wav, bull
const SFX_66    :=  0x0066; // bull2.wav, bull
const SFX_67    :=  0x0067; // bull3.wav, bull
const SFX_68    :=  0x0068; // bull4.wav, bull
const SFX_69    :=  0x0069; // bull5.wav, bull
const SFX_6A    :=  0x006a; // cat1.wav
const SFX_6B    :=  0x006b; // cat2.wav
const SFX_6C    :=  0x006c; // cat3.wav
const SFX_6D    :=  0x006d; // cat4.wav
const SFX_6E    :=  0x006e; // cat5.wav
const SFX_6F    :=  0x006f; // chicken1.wav
const SFX_70    :=  0x0070; // chicken2.wav
const SFX_71    :=  0x0071; // chicken3.wav
const SFX_72    :=  0x0072; // chicken4.wav
const SFX_73    :=  0x0073; // chicken5.wav
const SFX_74    :=  0x0074; // cougar1.wav
const SFX_75    :=  0x0075; // cougar2.wav
const SFX_76    :=  0x0076; // cougar3.wav
const SFX_77    :=  0x0077; // cougar4.wav
const SFX_78    :=  0x0078; // cougar5.wav
const SFX_79    :=  0x0079; // cow1.wav
const SFX_7A    :=  0x007a; // cow2.wav
const SFX_7B    :=  0x007b; // cow3.wav
const SFX_7C    :=  0x007c; // cow4.wav
const SFX_7D    :=  0x007d; // cow5.wav
const SFX_7E    :=  0x007e; // crow1.wav
const SFX_7F    :=  0x007f; // crow2.wav
const SFX_80    :=  0x0080; // crow3.wav
const SFX_81    :=  0x0081; // crow4.wav
const SFX_82    :=  0x0082; // crow5.wav
const SFX_83    :=  0x0083; // deer3.wav
const SFX_84    :=  0x0084; // deer4.wav
const SFX_85    :=  0x0085; // deer5.wav
const SFX_86    :=  0x0086; // dog1.wav
const SFX_87    :=  0x0087; // dog2.wav
const SFX_88    :=  0x0088; // dog3.wav
const SFX_89    :=  0x0089; // dog4.wav
const SFX_8A    :=  0x008a; // dog5.wav
const SFX_8B    :=  0x008b; // dolphin1.wav
const SFX_8C    :=  0x008c; // dolphin2.wav
const SFX_8D    :=  0x008d; // dolphin3.wav
const SFX_8E    :=  0x008e; // dolphin4.wav
const SFX_8F    :=  0x008f; // dolphin5.wav
const SFX_90    :=  0x0090; // eagle1.wav
const SFX_91    :=  0x0091; // eagle2.wav
const SFX_92    :=  0x0092; // eagle3.wav
const SFX_93    :=  0x0093; // eagle4.wav
const SFX_94    :=  0x0094; // eagle5.wav
const SFX_95    :=  0x0095; // frstbrd1.wav
const SFX_96    :=  0x0096; // frstbrd2.wav
const SFX_97    :=  0x0097; // frstbrd3.wav
const SFX_98    :=  0x0098; // frstbrd4.wav
const SFX_99    :=  0x0099; // frstbrd5.wav
const SFX_9A    :=  0x009a; // goat1.wav
const SFX_9B    :=  0x009b; // goat2.wav
const SFX_9C    :=  0x009c; // goat3.wav
const SFX_9D    :=  0x009d; // goat4.wav
const SFX_9E    :=  0x009e; // goat5.wav
const SFX_9F    :=  0x009f; // gorilla1.wav
const SFX_A0    :=  0x00a0; // gorilla2.wav
const SFX_A1    :=  0x00a1; // gorilla3.wav
const SFX_A2    :=  0x00a2; // gorilla4.wav
const SFX_A3    :=  0x00a3; // gorilla5.wav
const SFX_A4    :=  0x00a4; // grizzly1.wav
const SFX_A5    :=  0x00a5; // grizzly2.wav
const SFX_A6    :=  0x00a6; // grizzly3.wav
const SFX_A7    :=  0x00a7; // grizzly4.wav
const SFX_A8    :=  0x00a8; // grizzly5.wav
const SFX_A9    :=  0x00a9; // horse1.wav
const SFX_AA    :=  0x00aa; // horse2.wav
const SFX_AB    :=  0x00ab; // horse3.wav
const SFX_AC    :=  0x00ac; // horse4.wav
const SFX_AD    :=  0x00ad; // horse5.wav
const SFX_AE    :=  0x00ae; // jungbrd1.wav
const SFX_AF    :=  0x00af; // jungbrd2.wav
const SFX_B0    :=  0x00b0; // jungbrd3.wav
const SFX_B1    :=  0x00b1; // jungbrd4.wav
const SFX_B2    :=  0x00b2; // jungbrd5.wav
const SFX_B3    :=  0x00b3; // lion1.wav
const SFX_B4    :=  0x00b4; // lion2.wav
const SFX_B5    :=  0x00b5; // lion3.wav
const SFX_B6    :=  0x00b6; // lion4.wav
const SFX_B7    :=  0x00b7; // lion5.wav
const SFX_B8    :=  0x00b8; // llama3.wav
const SFX_B9    :=  0x00b9; // llama4.wav
const SFX_BA    :=  0x00ba; // llama5.wav
const SFX_BB    :=  0x00bb; // panther1.wav
const SFX_BC    :=  0x00bc; // panther2.wav
const SFX_BD    :=  0x00bd; // panther3.wav
const SFX_BE    :=  0x00be; // panther4.wav
const SFX_BF    :=  0x00bf; // panther5.wav
const SFX_C0    :=  0x00c0; // parrot1.wav
const SFX_C1    :=  0x00c1; // parrot2.wav
const SFX_C2    :=  0x00c2; // parrot3.wav
const SFX_C3    :=  0x00c3; // parrot4.wav
const SFX_C4    :=  0x00c4; // parrot5.wav
const SFX_C5    :=  0x00c5; // pig1.wav
const SFX_C6    :=  0x00c6; // pig2.wav
const SFX_C7    :=  0x00c7; // pig3.wav
const SFX_C8    :=  0x00c8; // pig4.wav
const SFX_C9    :=  0x00c9; // pig5.wav
const SFX_CA    :=  0x00ca; // rabbit3.wav
const SFX_CB    :=  0x00cb; // rabbit4.wav
const SFX_CC    :=  0x00cc; // rabbit5.wav
const SFX_CD    :=  0x00cd; // rat1.wav
const SFX_CE    :=  0x00ce; // rat2.wav
const SFX_CF    :=  0x00cf; // rat3.wav
const SFX_D0    :=  0x00d0; // rat4.wav
const SFX_D1    :=  0x00d1; // rat5.wav
const SFX_D2    :=  0x00d2; // raven1.wav
const SFX_D3    :=  0x00d3; // raven2.wav
const SFX_D4    :=  0x00d4; // raven3.wav
const SFX_D5    :=  0x00d5; // raven4.wav
const SFX_D6    :=  0x00d6; // raven5.wav
const SFX_D7    :=  0x00d7; // sheep1.wav
const SFX_D8    :=  0x00d8; // sheep2.wav
const SFX_D9    :=  0x00d9; // sheep3.wav
const SFX_DA    :=  0x00da; // sheep4.wav
const SFX_DB    :=  0x00db; // sheep5.wav
const SFX_DC    :=  0x00dc; // snake1.wav
const SFX_DD    :=  0x00dd; // snake2.wav
const SFX_DE    :=  0x00de; // snake3.wav
const SFX_DF    :=  0x00df; // snake4.wav
const SFX_E0    :=  0x00e0; // snake5.wav
const SFX_E1    :=  0x00e1; // walrus1.wav
const SFX_E2    :=  0x00e2; // walrus2.wav
const SFX_E3    :=  0x00e3; // walrus3.wav
const SFX_E4    :=  0x00e4; // walrus4.wav
const SFX_E5    :=  0x00e5; // walrus5.wav
const SFX_E6    :=  0x00e6; // wolf1.wav
const SFX_E7    :=  0x00e7; // wolf2.wav
const SFX_E8    :=  0x00e8; // wolf3.wav
const SFX_E9    :=  0x00e9; // wolf4.wav
const SFX_EA    :=  0x00ea; // wolf5.wav
const SFX_EB    :=  0x00eb; // open01a.wav
const SFX_EC    :=  0x00ec; // open03a.wav
const SFX_ED    :=  0x00ed; // open04b.wav
const SFX_EE    :=  0x00ee; // open09.wav
const SFX_EF    :=  0x00ef; // portclos.wav
const SFX_F0    :=  0x00f0; // portcul4.wav
const SFX_F1    :=  0x00f1; // portcul5.wav
const SFX_F2    :=  0x00f2; // shut03a.wav
const SFX_F3    :=  0x00f3; // shut07a.wav
const SFX_F4    :=  0x00f4; // shut14b.wav
const SFX_F5    :=  0x00f5; // shut17.wav
const SFX_F6    :=  0x00f6; // sfx01.wav
const SFX_F7    :=  0x00f7; // sfx02.wav
const SFX_F8    :=  0x00f8; // sfx04.wav
const SFX_F9    :=  0x00f9; // sfx05.wav
const SFX_FA    :=  0x00fa; // sfx06.wav
const SFX_FB    :=  0x00fb; // sfx08.wav
const SFX_FC    :=  0x00fc; // sfx10.wav
const SFX_FD    :=  0x00fd; // sfx11.wav
const SFX_FE    :=  0x00fe; // sfx12.wav
const SFX_FF    :=  0x00ff; // sfx13.wav
const SFX_100   :=  0x0100; // sfx14_l.wav
const SFX_101   :=  0x0101; // sfx15_l.wav
const SFX_102   :=  0x0102; // sfx16_l.wav
const SFX_103   :=  0x0103; // sfx17_l.wav
const SFX_104   :=  0x0104; // sfx18_l.wav
const SFX_105   :=  0x0105; // sfx20_l.wav
const SFX_106   :=  0x0106; // sfx21_l.wav
const SFX_107   :=  0x0107; // sfx22_l.wav
const SFX_108   :=  0x0108; // airelem1.wav
const SFX_109   :=  0x0109; // airelem2.wav
const SFX_10A   :=  0x010a; // airelem3.wav
const SFX_10B   :=  0x010b; // airelem4.wav
const SFX_10C   :=  0x010c; // airelem5.wav
const SFX_10D   :=  0x010d; // erthel1.wav
const SFX_10E   :=  0x010e; // erthel2.wav
const SFX_10F   :=  0x010f; // erthel3.wav
const SFX_110   :=  0x0110; // erthel4.wav
const SFX_111   :=  0x0111; // erthel5.wav
const SFX_112   :=  0x0112; // firelem1.wav
const SFX_113   :=  0x0113; // firelem2.wav
const SFX_114   :=  0x0114; // firelem3.wav
const SFX_115   :=  0x0115; // firelem4.wav
const SFX_116   :=  0x0116; // firelem5.wav
const SFX_117   :=  0x0117; // watrel1.wav
const SFX_118   :=  0x0118; // watrel2.wav
const SFX_119   :=  0x0119; // watrel3.wav
const SFX_11A   :=  0x011a; // watrel4.wav
const SFX_11B   :=  0x011b; // watrel5.wav
const SFX_11C   :=  0x011c; // exp01.wav
const SFX_11D   :=  0x011d; // exp04.wav
const SFX_11E   :=  0x011e; // exp05.wav
const SFX_11F   :=  0x011f; // exp06.wav
const SFX_120   :=  0x0120; // bigfoot1.wav
const SFX_121   :=  0x0121; // bigfoot2.wav
const SFX_122   :=  0x0122; // feet01a.wav
const SFX_123   :=  0x0123; // feet01b.wav
const SFX_124   :=  0x0124; // feet03a.wav
const SFX_125   :=  0x0125; // feet03b.wav
const SFX_126   :=  0x0126; // feet05a.wav
const SFX_127   :=  0x0127; // feet05b.wav
const SFX_128   :=  0x0128; // feet08a.wav
const SFX_129   :=  0x0129; // feet08b.wav
const SFX_12A   :=  0x012a; // feet10a.wav
const SFX_12B   :=  0x012b; // feet10b.wav
const SFX_12C   :=  0x012c; // feet12a.wav
const SFX_12D   :=  0x012d; // feet12b1wav
const SFX_12E   :=  0x012e; // feet13a.wav
const SFX_12F   :=  0x012f; // feet13b.wav
const SFX_130   :=  0x0130; // feet14a.wav
const SFX_131   :=  0x0131; // feet14b.wav
const SFX_132   :=  0x0132; // feet15a.wav
const SFX_133   :=  0x0133; // feet15b.wav
const SFX_134   :=  0x0134; // feet15c.wav
const SFX_135   :=  0x0135; // feet15d.wav
const SFX_136   :=  0x0136; // hit01.wav
const SFX_137   :=  0x0137; // hit02.wav
const SFX_138   :=  0x0138; // hit03.wav
const SFX_139   :=  0x0139; // hit04.wav
const SFX_13A   :=  0x013a; // hit05.wav
const SFX_13B   :=  0x013b; // hit06.wav
const SFX_13C   :=  0x013c; // hit07.wav
const SFX_13D   :=  0x013d; // hit08.wav
const SFX_13E   :=  0x013e; // hit09.wav
const SFX_13F   :=  0x013f; // hit10.wav
const SFX_140   :=  0x0140; // hit11.wav
const SFX_141   :=  0x0141; // hit12.wav
const SFX_142   :=  0x0142; // hit13.wav
const SFX_143   :=  0x0143; // hit14.wav
const SFX_144   :=  0x0144; // hit15.wav
const SFX_145   :=  0x0145; // hit16.wav
const SFX_146   :=  0x0146; // hit17.wav
const SFX_147   :=  0x0147; // hit18.wav
const SFX_148   :=  0x0148; // hit19.wav
const SFX_149   :=  0x0149; // hit20.wav
const SFX_14A   :=  0x014a; // hit21.wav
const SFX_14B   :=  0x014b; // hit22.wav
const SFX_14C   :=  0x014c; // foomph01.wav
const SFX_14D   :=  0x014d; // foomph06.wav
const SFX_14E   :=  0x014e; // foomph07.wav
const SFX_14F   :=  0x014f; // foomph08.wav
const SFX_150   :=  0x0150; // foomph09.wav
const SFX_151   :=  0x0151; // f_die_01.wav
const SFX_152   :=  0x0152; // f_die_02.wav
const SFX_153   :=  0x0153; // f_die_03.wav
const SFX_154   :=  0x0154; // f_die_04.wav
const SFX_155   :=  0x0155; // moomph01.wav
const SFX_156   :=  0x0156; // moomph02.wav
const SFX_157   :=  0x0157; // moomph03.wav
const SFX_158   :=  0x0158; // moomph04.wav
const SFX_159   :=  0x0159; // moomph05.wav
const SFX_15A   :=  0x015a; // moomph13.wav
const SFX_15B   :=  0x015b; // m_die_01.wav
const SFX_15C   :=  0x015c; // m_die_02.wav
const SFX_15D   :=  0x015d; // m_die_03.wav
const SFX_15E   :=  0x015e; // m_die_04.wav
const SFX_15F   :=  0x015f; // fyrbal01.wav
const SFX_160   :=  0x0160; // fyrbal02.wav
const SFX_161   :=  0x0161; // fyrbal03.wav
const SFX_162   :=  0x0162; // corpsr1.wav
const SFX_163   :=  0x0163; // corpsr3.wav
const SFX_164   :=  0x0164; // corpsr4.wav
const SFX_165   :=  0x0165; // corpsr5.wav
const SFX_166   :=  0x0166; // daemon1.wav
const SFX_167   :=  0x0167; // daemon2.wav
const SFX_168   :=  0x0168; // daemon3.wav
const SFX_169   :=  0x0169; // daemon4.wav
const SFX_16A   :=  0x016a; // daemon5.wav
const SFX_16B   :=  0x016b; // dragon1.wav
const SFX_16C   :=  0x016c; // dragon2.wav
const SFX_16D   :=  0x016d; // dragon3.wav
const SFX_16E   :=  0x016e; // dragon4.wav
const SFX_16F   :=  0x016f; // dragon5.wav
const SFX_170   :=  0x0170; // ettin1.wav
const SFX_171   :=  0x0171; // ettin2.wav
const SFX_172   :=  0x0172; // ettin3.wav
const SFX_173   :=  0x0173; // ettin4.wav
const SFX_174   :=  0x0174; // ettin5.wav
const SFX_175   :=  0x0175; // gargyl1.wav
const SFX_176   :=  0x0176; // gargyl2.wav
const SFX_177   :=  0x0177; // gargyl3.wav
const SFX_178   :=  0x0178; // gargyl4.wav
const SFX_179   :=  0x0179; // gargyl5.wav
const SFX_17A   :=  0x017a; // gazer1.wav
const SFX_17B   :=  0x017b; // gazer2.wav
const SFX_17C   :=  0x017c; // gazer3.wav
const SFX_17D   :=  0x017d; // gazer4.wav
const SFX_17E   :=  0x017e; // gazer5.wav
const SFX_17F   :=  0x017f; // ghost1.wav
const SFX_180   :=  0x0180; // ghost2.wav
const SFX_181   :=  0x0181; // ghost3.wav
const SFX_182   :=  0x0182; // ghost4.wav 
const SFX_183   :=  0x0183; // ghost5.wav
const SFX_184   :=  0x0184; // gispidr1.wav
const SFX_185   :=  0x0185; // gispidr2.wav
const SFX_186   :=  0x0186; // gispidr3.wav
const SFX_187   :=  0x0187; // gispidr4.wav
const SFX_188   :=  0x0188; // gispidr5.wav
const SFX_189   :=  0x0189; // grat1.wav
const SFX_18A   :=  0x018a; // grat2.wav
const SFX_18B   :=  0x018b; // grat3.wav
const SFX_18C   :=  0x018c; // grat4.wav
const SFX_18D   :=  0x018d; // grat5.wav
const SFX_18E   :=  0x018e; // gscorp1.wav
const SFX_18F   :=  0x018f; // gscorp2.wav
const SFX_190   :=  0x0190; // gscorp3.wav
const SFX_191   :=  0x0191; // gscorp4.wav
const SFX_192   :=  0x0192; // gscorp5.wav
const SFX_193   :=  0x0193; // harpy1.wav
const SFX_194   :=  0x0194; // harpy2.wav
const SFX_195   :=  0x0195; // harpy3.wav
const SFX_196   :=  0x0196; // harpy4.wav
const SFX_197   :=  0x0197; // harpy5.wav
const SFX_198   :=  0x0198; // headls1.wav
const SFX_199   :=  0x0199; // headls2.wav
const SFX_19A   :=  0x019a; // headls3.wav
const SFX_19B   :=  0x019b; // headls4.wav
const SFX_19C   :=  0x019c; // headls5.wav
const SFX_19D   :=  0x019d; // liche1.wav
const SFX_19E   :=  0x019e; // liche2.wav
const SFX_19F   :=  0x019f; // liche3.wav
const SFX_1A0   :=  0x01a0; // liche4.wav
const SFX_1A1   :=  0x01a1; // liche5.wav
const SFX_1A2   :=  0x01a2; // lzrdmn1.wav
const SFX_1A3   :=  0x01a3; // lzrdmn2.wav
const SFX_1A4   :=  0x01a4; // lzrdmn3.wav
const SFX_1A5   :=  0x01a5; // lzrdmn4.wav
const SFX_1A6   :=  0x01a6; // lzrdmn5.wav
const SFX_1A7   :=  0x01a7; // mngbat1.wav
const SFX_1A8   :=  0x01a8; // mngbat2.wav
const SFX_1A9   :=  0x01a9; // mngbat3.wav
const SFX_1AA   :=  0x01aa; // mngbat4.wav
const SFX_1AB   :=  0x01ab; // mngbat5.wav
const SFX_1AC   :=  0x01ac; // ogre1.wav
const SFX_1AD   :=  0x01ad; // ogre2.wav
const SFX_1AE   :=  0x01ae; // ogre3.wav
const SFX_1AF   :=  0x01af; // ogre4.wav
const SFX_1B0   :=  0x01b0; // ogre5.wav
const SFX_1B1   :=  0x01b1; // orc1.wav
const SFX_1B2   :=  0x01b2; // orc2.wav
const SFX_1B3   :=  0x01b3; // orc3.wav
const SFX_1B4   :=  0x01b4; // orc4.wav
const SFX_1B5   :=  0x01b5; // orc5.wav
const SFX_1B6   :=  0x01b6; // ratman1.wav
const SFX_1B7   :=  0x01b7; // ratman2.wav
const SFX_1B8   :=  0x01b8; // ratman3.wav
const SFX_1B9   :=  0x01b9; // ratman4.wav
const SFX_1BA   :=  0x01ba; // ratman5.wav
const SFX_1BB   :=  0x01bb; // reaper1.wav
const SFX_1BC   :=  0x01bc; // reaper2.wav
const SFX_1BD   :=  0x01bd; // reaper3.wav
const SFX_1BE   :=  0x01be; // reaper4.wav
const SFX_1BF   :=  0x01bf; // reaper5.wav
const SFX_1C0   :=  0x01c0; // seaserp1.wav
const SFX_1C1   :=  0x01c1; // seaserp3.wav
const SFX_1C2   :=  0x01c2; // seaserp4.wav
const SFX_1C3   :=  0x01c3; // seaserp5.wav
const SFX_1C4   :=  0x01c4; // skletn1.wav
const SFX_1C5   :=  0x01c5; // skletn2.wav
const SFX_1C6   :=  0x01c6; // skletn3.wav
const SFX_1C7   :=  0x01c7; // skletn4.wav
const SFX_1C8   :=  0x01c8; // skletn5.wav
const SFX_1C9   :=  0x01c9; // slime1.wav
const SFX_1CA   :=  0x01ca; // slime2.wav
const SFX_1CB   :=  0x01cb; // slime3.wav
const SFX_1CC   :=  0x01cc; // slime4.wav
const SFX_1CD   :=  0x01cd; // slime5.wav
const SFX_1CE   :=  0x01ce; // troll1.wav
const SFX_1CF   :=  0x01cf; // troll2.wav
const SFX_1D0   :=  0x01d0; // troll3.wav
const SFX_1D1   :=  0x01d1; // troll4.wav
const SFX_1D2   :=  0x01d2; // troll5.wav
const SFX_1D3   :=  0x01d3; // wisp1.wav
const SFX_1D4   :=  0x01d4; // wisp2.wav
const SFX_1D5   :=  0x01d5; // wisp3.wav
const SFX_1D6   :=  0x01d6; // wisp4.wav
const SFX_1D7   :=  0x01d7; // wisp5.wav
const SFX_1D8   :=  0x01d8; // zombie1.wav
const SFX_1D9   :=  0x01d9; // zombie2.wav
const SFX_1DA   :=  0x01da; // zombie3.wav
const SFX_1DB   :=  0x01db; // zombie4.wav
const SFX_1DC   :=  0x01dc; // zombie5.wav
const SFX_1DD   :=  0x01dd; // elec_l.wav
const SFX_1DE   :=  0x01de; // fire_l.wav
const SFX_1DF   :=  0x01df; // hiss_l.wav
const SFX_1E0   :=  0x01e0; // clumsy.wav
const SFX_1E1   :=  0x01e1; // cure.wav
const SFX_1E2   :=  0x01e2; // curse.wav
const SFX_1E3   :=  0x01e3; // c_food.wav
const SFX_1E4   :=  0x01e4; // c_light.wav
const SFX_1E5   :=  0x01e5; // feblmind.wav
const SFX_1E6   :=  0x01e6; // m_arrow.wav
const SFX_1E7   :=  0x01e7; // weaken.wav
const SFX_1E8   :=  0x01e8; // agility.wav
const SFX_1E9   :=  0x01e9; // archcure.wav
const SFX_1EA   :=  0x01ea; // birdseye.wav
const SFX_1EB   :=  0x01eb; // bless.wav
const SFX_1EC   :=  0x01ec; // cunning.wav
const SFX_1ED   :=  0x01ed; // identify.wav
const SFX_1EE   :=  0x01ee; // protect.wav
const SFX_1EF   :=  0x01ef; // strength.wav
const SFX_1F0   :=  0x01f0; // trap.wav
const SFX_1F1   :=  0x01f1; // untrap.wav
const SFX_1F2   :=  0x01f2; // harm.wav
const SFX_1F3   :=  0x01f3; // heal.wav
const SFX_1F4   :=  0x01f4; // magic_fyrbal01.
const SFX_1F5   :=  0x01f5; // m_lock.wav
const SFX_1F6   :=  0x01f6; // teleknes.wav
const SFX_1F7   :=  0x01f7; // walstone.wav
const SFX_1F8   :=  0x01f8; // aprotect.wav
const SFX_1F9   :=  0x01f9; // manadran.wav
const SFX_1FA   :=  0x01fa; // manavamp.wav
const SFX_1FB   :=  0x01fb; // mark.wav
const SFX_1FC   :=  0x01fc; // masscurs.wav
const SFX_1FD   :=  0x01fd; // recall.wav
const SFX_1FE   :=  0x01fe; // reveal.wav
const SFX_1FF   :=  0x01ff; // teleport.wav
const SFX_200   :=  0x0200; // unlock.wav
const SFX_201   :=  0x0201; // bladsprt.wav
const SFX_202   :=  0x0202; // dispfild.wav
const SFX_203   :=  0x0203; // gratheal.wav
const SFX_204   :=  0x0204; // invisibl.wav
const SFX_205   :=  0x0205; // paralyze.wav
const SFX_206   :=  0x0206; // poison.wav
const SFX_207   :=  0x0207; // thundr01.wav
const SFX_208   :=  0x0208; // explode.wav
const SFX_209   :=  0x0209; // flamstrk.wav
const SFX_20A   :=  0x020a; // massdisp.wav
const SFX_20B   :=  0x020b; // nrgybolt.wav
const SFX_20C   :=  0x020c; // parafild.wav
const SFX_20D   :=  0x020d; // posnfild.wav
const SFX_20E   :=  0x020e; // earthqke.wav
const SFX_20F   :=  0x020f; // gatetrvl.wav
const SFX_210   :=  0x0210; // morph.wav
const SFX_211   :=  0x0211; // nergyfld.wav
const SFX_212   :=  0x0212; // nrgywind.wav
const SFX_213   :=  0x0213; // dethvrtx.wav
const SFX_214   :=  0x0214; // mindblst.wav
const SFX_215   :=  0x0215; // resurect.wav
const SFX_216   :=  0x0216; // sumncrtr.wav
const SFX_217   :=  0x0217; // sumndemn.wav
const SFX_218   :=  0x0218; // sumnelem.wav
const SFX_219   :=  0x0219; // blade01.wav
const SFX_21A   :=  0x021a; // blade02.wav
const SFX_21B   :=  0x021b; // blade03.wav
const SFX_21C   :=  0x021c; // blade04.wav
const SFX_21D   :=  0x021d; // blade05.wav
const SFX_21E   :=  0x021e; // boulder1.wav
const SFX_21F   :=  0x021f; // boulder2.wav
const SFX_220   :=  0x0220; // crumble1.wav
const SFX_221   :=  0x0221; // crumble2.wav
const SFX_222   :=  0x0222; // crumble3.wav
const SFX_223   :=  0x0223; // crumble4.wav
const SFX_224   :=  0x0224; // dart01.wav
const SFX_225   :=  0x0225; // dart02.wav
const SFX_226   :=  0x0226; // flame01.wav
const SFX_227   :=  0x0227; // flame03.wav
const SFX_228   :=  0x0228; // flame05.wav
const SFX_229   :=  0x0229; // mushrm01.wav
const SFX_22A   :=  0x022a; // mushrm02.wav
const SFX_22B   :=  0x022b; // mushrm03.wav
const SFX_22C   :=  0x022c; // spike01.wav
const SFX_22D   :=  0x022d; // spike02.wav
const SFX_22E   :=  0x022e; // spike03.wav
const SFX_22F   :=  0x022f; // spike04.wav
const SFX_230   :=  0x0230; // vapor01.wav
const SFX_231   :=  0x0231; // vapor02.wav
const SFX_232   :=  0x0232; // vapor03.wav
const SFX_233   :=  0x0233; // axe01.wav
const SFX_234   :=  0x0234; // blunt01.wav
const SFX_235   :=  0x0235; // crossbow.wav
const SFX_236   :=  0x0236; // gilotin1.wav
const SFX_237   :=  0x0237; // hvyswrd1.wav
const SFX_238   :=  0x0238; // hvyswrd4.wav
const SFX_239   :=  0x0239; // swish01.wav
const SFX_23A   :=  0x023a; // swish02.wav
const SFX_23B   :=  0x023b; // swish03.wav
const SFX_23C   :=  0x023c; // sword1.wav
const SFX_23D   :=  0x023d; // sword7.wav
const SFX_23E   :=  0x023e; // carpntry.wav
const SFX_23F   :=  0x023f; // dye.wav
const SFX_240   :=  0x0240; // fshsplsh.wav
const SFX_241   :=  0x0241; // liquid.wav
const SFX_242   :=  0x0242; // lockpick.wav
const SFX_243   :=  0x0243; // mortar.wav
const SFX_244   :=  0x0244; // mystery1.wav
const SFX_245   :=  0x0245; // mystery2.wav
const SFX_246   :=  0x0246; // mystery3.wav
const SFX_247   :=  0x0247; // poison.wav
const SFX_248   :=  0x0248; // powder.wav
const SFX_249   :=  0x0249; // scissors.wav
const SFX_24A   :=  0x024a; // scribe.wav
const SFX_24B   :=  0x024b; // spirtspk.wav
const SFX_24C   :=  0x024c; // z_horseft2.wav
const SFX_24D   :=  0x024d; // z_horseft1.wav
const SFX_24E   :=  0x024e; // Tera.Warrior 1
const SFX_24F   :=  0x02ef; // Tera.Warrior 2

// Fill in the rest of the T2A sounds here.
// * music *
const SFX_MUSIC_LUTE_GOOD           :=  SFX_4D;
const SFX_MUSIC_LUTE_FAIL           :=  SFX_4E;
const SFX_MUSIC_DRUM_GOOD           :=  SFX_39;
const SFX_MUSIC_DRUM_FAIL           :=  SFX_3A;
const SFX_MUSIC_HARP_LARGE_GOOD     :=  SFX_44;
const SFX_MUSIC_HARP_LARGE_FAIL     :=  SFX_45;
const SFX_MUSIC_HARP_LAP_GOOD       :=  SFX_46;
const SFX_MUSIC_HARP_LAP_FAIL       :=  SFX_47;
const SFX_MUSIC_TAMBORINE_GOOD      :=  SFX_53;
const SFX_MUSIC_TAMBORINE_FAIL      :=  SFX_54;


// * skills *
const SFX_SKILL_SPIRITSPEAK         :=  SFX_24B;
const SFX_SKILL_LUMBERJACK          :=  SFX_13F;

// * items *
const SFX_TRAP_NEEDLE               :=  SFX_225;
const SFX_TRAP_POISON               :=  SFX_206;
const SFX_TRAP_EXPLOSION            :=  SFX_208;
const SFX_ANVIL                     :=  SFX_2B;
const SFX_PICK                      :=  SFX_13B;
const SFX_HAMMER                    :=  SFX_43;
const SFX_GLASSBREAK4               :=  SFX_42;
const SFX_HARP_SUCC                 :=  SFX_46;
const SFX_LUTE_SUCC                 :=  SFX_4D;
const SFX_DRUM_SUCC                 :=  SFX_39;
const SFX_TAMB_SUCC                 :=  SFX_53;

const SFX_HARP_FAIL                 :=  SFX_47;
const SFX_LUTE_FAIL                 :=  SFX_4E;
const SFX_DRUM_FAIL                 :=  SFX_3A;
const SFX_TAMB_FAIL                 :=  SFX_54;


// * doors *
const SFX_OPEN_WOODEN_DOOR          :=  SFX_EB;
const SFX_CLOSE_WOODEN_DOOR         :=  SFX_F2;
const SFX_OPEN_METAL_DOOR           :=  SFX_ED;
const SFX_CLOSE_METAL_DOOR          :=  SFX_F4;


////
// Animations/Actions
///
// * Human animations (all humans have these) (this is not complete, will update later)
const ANIM_WALK_UNARMED         :=  0x0000; // Walk unarmed.
const ANIM_WALK_ARMED           :=  0x0001; // Walk armed.
const ANIM_RUN_UNARMED          :=  0x0002; // Run unarmed.
const ANIM_RUN_ARMED            :=  0x0003; // Run armed.
const ANIM_STAND                :=  0x0004; // Stand.
const ANIM_FIDGET_1             :=  0x0005; // Twist a little (look around?).
const ANIM_FIDGET_2             :=  0x0006; // Look down.
const ANIM_STAND_1HAND          :=  0x0007; // Stand 1 handed attack.
const ANIM_STAND_2HAND          :=  0x0008; // Stand 2 handed attack.
const ANIM_ATTACK_1HAND_WIDE    :=  0x0009; // Attack 1 handed wide (sword/any).
const ANIM_ATTACK_1HAND_JAB     :=  0x000a; // Attack 1 handed jab (fencing).
const ANIM_ATTACK_1HAND_DOWN    :=  0x000b; // Attack 1 handed down (mace).
const ANIM_ATTACK_2HAND_DOWN    :=  0x000c; // Attack 2 handed jab (mace).
const ANIM_ATTACK_2HAND_WIDE    :=  0x000d; // Attack 2 handed wide.
const ANIM_ATTACK_2HAND_JAB     :=  0x000e; // Attack 2 handed jab (spear).
const ANIM_WALK_WARMODE         :=  0x000f; // Walk in warmode.
const ANIM_CAST_DIR             :=  0x0010; // Spellcasting direction.
const ANIM_CAST_AREA            :=  0x0011; // Spellcasting area.
const ANIM_ATTACK_BOW           :=  0x0012; // Attack bow.
const ANIM_ATTACK_XBOW          :=  0x0013; // Attack xbow.
const ANIM_HIT                  :=  0x0014; // Get hit.
const ANIM_DIE_BACK             :=  0x0015; // Die backward.
const ANIM_DIE_FOR              :=  0x0016; // Die forward.
const ANIM_BOW                  :=  0x0020; // Bow.
const ANIM_SALUTE               :=  0x0021; // Salute.
const ANIM_EAT                  :=  0x0022; // Eat.

////
// Graphicaleffects (itemIDs)
///
// * general *
const FX_SPLASH         :=  0x352d; //
const FX_EXPLODE_1      :=  0x36CA; //
const FX_EXPLODE_2      :=  0x36BD; //
const FX_EXPLODE_3      :=  0x36B0; //
const FX_FIREBALL       :=  0x36d4; //
const FX_MAGIC_ARROW    :=  0x36e4; //
const FX_FIRE_BOLT      :=  0x36f4; // Firesnake. (pagan?)
const FX_EXPLODE_BALL   :=  0x36fe; // Not used.

const FX_FLAMESTRIKE    :=  0x3709; //
const FX_SMOKE          :=  0x3728;
const FX_TELE_VANISH    :=  0x372a; // Teleport vanish.
const FX_SPELL_FAIL     :=  0x3735; //
const FX_BLESS_EFFECT   :=  0x373a; //
const FX_CURSE_EFFECT   :=  0x374a; //
const FX_SPARK_EFFECT   :=  0x375a; // 
const FX_HEAL_EFFECT    :=  0x376a; //
const FX_MARK_EFFECT    :=  0x3779;
const FX_BLUEMOONSTART  :=  0x3789; // Deathvortex?
const FX_ENERGY_BOLT    :=  0x379f; //
const FX_BLADES_EMERGE  :=  0x37a0; // Not used.
const FX_GLOW           :=  0x37b9; // Not used.
const FX_GLOW_SPIKE     :=  0x37c3; // Not used.
const FX_DEATH_FUNNEL   :=  0x37cc; //
const FX_BLADES         :=  0x37eb; //
const FX_STATIC         :=  0x3818; // Not used. (pink static)
const FX_POISON_F_EW    :=  0x3914; // Poison field.
const FX_POISON_F_NS    :=  0x3920; // Poison field.
const FX_ENERGY_F_EW    :=  0x3947; // Energy field.
const FX_ENERGY_F_NS    :=  0x3956; // Energy field.
const FX_PARA_F_EW      :=  0x3967; // Paralyze field.
const FX_PARA_F_NS      :=  0x3979; // Paralyze field.
const FX_FIRE_F_EW      :=  0x398c; // Fire field.
const FX_FIRE_F_NS      :=  0x3996; // Fire field.

////
// Layers
/// 
const LAYER_NONE        :=  0x00;   // Not used?
const LAYER_HAND1       :=  0x01;   // One handed weapon.
const LAYER_HAND2       :=  0x02;   // Two handed weapon, shield or misc.
const LAYER_SHOES       :=  0x03;   // Shoes.
const LAYER_PANTS       :=  0x04;   // Pants.
const LAYER_SHIRT       :=  0x05;   // Shirt.
const LAYER_HELM        :=  0x06;   // Helm or Hat.
const LAYER_GLOVES      :=  0x07;   // Gloves.
const LAYER_RING        :=  0x08;   // Ring.
const LAYER_UNUSED9     :=  0x09;   // Unused.
const LAYER_NECK        :=  0x0a;   // Neck.
const LAYER_HAIR        :=  0x0b;   // Hair
const LAYER_WAIST       :=  0x0c;   // Waist (half apron).
const LAYER_CHEST       :=  0x0d;   // Torso (inner) (chest armor).
const LAYER_WRIST       :=  0x0e;   // Bracelet.
const LAYER_PACK2       :=  0x0f;   // Unused (backpack, but ord. bp is 0x15).
const LAYER_BEARD       :=  0x10;   // Facial hair.
const LAYER_TUNIC       :=  0x11;   // Torso (middle) (tunic, sash etc.).
const LAYER_EARS        :=  0x12;   // Earrings.
const LAYER_ARMS        :=  0x13;   // Arms.
const LAYER_CAPE        :=  0x14;   // Back (cloak).
const LAYER_PACK        :=  0x15;   // Backpack
const LAYER_ROBE        :=  0x16;   // Torso (outer) (robe)
const LAYER_SKIRT       :=  0x17;   // Legs (outer) (skirt/robe).
const LAYER_LEGS        :=  0x18;   // Legs (inner) (leg armor).
const LAYER_MOUNT       :=  0x19;   // Mount (horse, ostard etc.).
const LAYER_VENDORSTOCK :=  0x1a;   // This vendor will sell and restock.
const LAYER_VENDOREXTRA :=  0x1b;   // This vendor will resell to players but not restock.
const LAYER_VENDORBUY   :=  0x1c;   // This vendor can buy from players but does not stock.
const LAYER_BANKBOX     :=  0x1d;   // Contents of bankbox
const LAYER_TRADE       :=  0x1e;   // Can be multiple of these, do not use directly.

////
// Fonts
/// 
const FONT_MAX          :=  0x00;   // Lowest font.
const FONT_MIN          :=  0x09;   // Highest font.

const FONT_BOLD         :=  0x00;   // Bold text.
const FONT_SHADOW       :=  0x01;   // Text with shadow.
const FONT_BOLD_SHAD    :=  0x02;   // Bold text with shadow.
const FONT_NORMAL       :=  0x03;   // Normal (default).
const FONT_GOTHIC       :=  0x04;   // Gothic.
const FONT_ITALIC       :=  0x05;   // Italic
const FONT_SMALL_DARK   :=  0x06;   // Small dark letters.
const FONT_COLOR        :=  0x07;   // Colorful font.
const FONT_RUNE         :=  0x08;   // Rune font (only capitals).
const FONT_SMALL_LIGHT  :=  0x09;   // Small light letters.

////
// Creature IDs ( hardcoded graphic IDs )
/// 
const CID_ZERO			:= 0x0000;  // Not used.
const CID_OGRE			:= 0x0001;  // Ogre.
const CID_ETTIN			:= 0x0002;  // Ettin.
const CID_ZOMBIE		:= 0x0003;  // Zombie.
const CID_GARGOYLE		:= 0x0004;  // Gargoyle.
const CID_EAGLE			:= 0x0005;  // Eagle.
const CID_BIRD			:= 0x0006;  // Bird.
const CID_ORC_LORD		:= 0x0007;  // Orc Lord.
const CID_CORPSER		:= 0x0008;  // Corpser.
const CID_DAEMON		:= 0x0009;  // Daemon.
const CID_DAEMON_SWORD		:= 0x000a;  // Daemon with sword.
const CID_DRAGON_GREY		:= 0x000c;  // Dragon grey.
const CID_AIR_ELEMENTAL		:= 0x000d;  // Air Elemental.
const CID_EARTH_ELEMENTAL	:= 0x000e;  // Earth Elemental.
const CID_FIRE_ELEMENTAL	:= 0x000f;  // Fire Elemental.
const CID_WATER_ELEMENTAL	:= 0x0010;  // Water elemental.
const CID_ORC			:= 0x0011;  // Orc.
const CID_ETTIN_AXE		:= 0x0012;  // Ettin with axe.
const CID_GIANT_SNAKE		:= 0x0015;  // Giant
const CID_UNSHORN_SHEEP		:= 0x00cf;
const CID_SHORN_SHEEP		:= 0x00df;

const CID_HUMAN_MALE		:= 0x0190;
const CID_HUMAN_FEMALE		:= 0x0191;
const CID_GM			:= 0x03db;

////
// Directions
/// 
const DIR_N             :=  0x00;   // North.
const DIR_NE            :=  0x01;   // Northeast.
const DIR_E             :=  0x02;   // East.
const DIR_SE            :=  0x03;   // Southeast.
const DIR_S             :=  0x04;   // South.
const DIR_SW            :=  0x05;   // Southwest.
const DIR_W             :=  0x06;   // West.
const DIR_NW            :=  0x07;   // Northwest.

// * Colors *
// This is not suposed to be a "complete" colorchart, but a
// quick way to access normal colors.
const COLOR_DEFAULT         := 0x0000;
const COLOR_BLACK           := 0x0001;
const COLOR_INDIGO_DARK     := 0x0007;
const COLOR_INDIGO          := 0x0008;
const COLOR_INDIGO_LIGHT    := 0x0009;

const COLOR_VIOLET_DARK     := 0x000c;
const COLOR_VIOLET          := 0x000d;
const COLOR_VIOLET_LIGHT    := 0x000e;
const COLOR_MAGENTA_DARK    := 0x0011;
const COLOR_MAGENTA         := 0x0012;
const COLOR_MAGENTA_LIGHT   := 0x0013;
const COLOR_RED_DARK        := 0x0020;
const COLOR_RED             := 0x0022;
const COLOR_RED_LIGHT       := 0x0023;
const COLOR_ORANGE_DARK     := 0x002a;
const COLOR_ORANGE          := 0x002b;
const COLOR_ORANGE_LIGHT    := 0x002c;
const COLOR_YELLOW_DARK     := 0x0034;
const COLOR_YELLOW          := 0x0035;
const COLOR_YELLOW_LIGHT    := 0x0036;
const COLOR_GREEN_DARK      := 0x003e;
const COLOR_GREEN           := 0x003f;
const COLOR_GREEN_LIGHT     := 0x0040;
const COLOR_CYAN_DARK       := 0x0057;
const COLOR_CYAN            := 0x0058;
const COLOR_CYAN_LIGHT      := 0x0059;
const COLOR_BLUE_DARK       := 0x0061;
const COLOR_BLUE            := 0x0062;
const COLOR_BLUE_LIGHT      := 0x0063;
const COLOR_GRAY_DARK       := 0x0386;
const COLOR_GRAY            := 0x0387;
const COLOR_GRAY_LIGHT      := 0x0388;
const COLOR_BLACKMETAL      := 0x044e;
const COLOR_GOLDMETAL       := 0x046e;
const COLOR_BSHIMMER        := 0x0480;	// T2A Only : Waterelemental color.
const COLOR_WHITE           := 0x0481;	// T2A Only : True white.
const COLOR_STONE           := 0x0482;	// T2A Only : Rock ( stoneharpy?)
const COLOR_SPECTRAL        := 0x4631;  // Spectral
const COLOR_TRANSLUCENT     := 0x7cf8;  // Translucent

////
// Font Colours.
////
const FONTCOLOR_RED		:= 0x0026;
const FONTCOLOR_GREEN		:= 0x0044;
const FONTCOLOR_BLUE		:= 0x005a;
const FONTCOLOR_MAUVE		:= 0x001e;
const FONTCOLOR_LAVENDER	:= 0x0014;
const FONTCOLOR_BLACK		:= 0x0001;
const FONTCOLOR_BROWN		:= 0x002e;
const FONTCOLOR_YELLOW		:= 0x0035;

////
// SkillIDs
/// 
const SKILLID_ALCHEMY           := 0;
const SKILLID_ANATOMY           := 1;
const SKILLID_ANIMALLORE        := 2;
const SKILLID_ITEMID            := 3;
const SKILLID_ARMSLORE          := 4;
const SKILLID_BATTLE_DEFENSE    := 5;
const SKILLID_PARRY             := 5;
const SKILLID_BEGGING           := 6;
const SKILLID_BLACKSMITHY       := 7;
const SKILLID_BOWCRAFT          := 8;
const SKILLID_PEACEMAKING       := 9;
const SKILLID_CAMPING           := 10;
const SKILLID_CARPENTRY         := 11;
const SKILLID_CARTOGRAPHY       := 12;
const SKILLID_COOKING           := 13;
const SKILLID_DETECTINGHIDDEN   := 14;
const SKILLID_ENTICEMENT        := 15;
const SKILLID_EVALINT           := 16;
const SKILLID_HEALING           := 17;
const SKILLID_FISHING           := 18;
const SKILLID_FORENSICS         := 19;
const SKILLID_HERDING           := 20;
const SKILLID_HIDING            := 21;
const SKILLID_PROVOCATION       := 22;
const SKILLID_INSCRIPTION       := 23;
const SKILLID_LOCKPICKING       := 24;
const SKILLID_MAGERY            := 25;
const SKILLID_MAGICRESISTANCE   := 26;
const SKILLID_TACTICS           := 27;
const SKILLID_SNOOPING          := 28;
const SKILLID_MUSICIANSHIP      := 29;
const SKILLID_POISONING         := 30;
const SKILLID_ARCHERY           := 31;
const SKILLID_SPIRITSPEAK       := 32;
const SKILLID_STEALING          := 33;
const SKILLID_TAILORING         := 34;
const SKILLID_TAMING            := 35;
const SKILLID_TASTEID           := 36;
const SKILLID_TINKERING         := 37;
const SKILLID_TRACKING          := 38;
const SKILLID_VETERINARY        := 39;
const SKILLID_SWORDSMANSHIP     := 40;
const SKILLID_MACEFIGHTING      := 41;
const SKILLID_FENCING           := 42;
const SKILLID_WRESTLING         := 43;
const SKILLID_LUMBERJACKING     := 44;
const SKILLID_MINING            := 45;
const SKILLID_MEDITATION        := 46;
const SKILLID_STEALTH           := 47;
const SKILLID_REMOVETRAP        := 48;
const SKILLID__HIGHEST          := 48;


/////////////////////////////////////  SPELLS START  //////////////////////////////

///////////////////////
//        All        //
///////////////////////

const ACTION_BOW		:= 0x0020;	// Bow animation

const SFX_SPELL_FIZZLE		:= 0x05d;	// Fizzling a spell SFX
const FX_SPELL_FIZZLE		:= 0x3735; 	// Fizzle a spell FX
const MOVING_SPELL_FIZZLE	:= 0;
const SPEED_SPELL_FIZZLE	:= 7;		// Speed for fizzling effect
const LOOP_SPELL_FIZZLE		:= 7;		// Loop for fizzling effect


const CORPSE_OBJTYPE		:= 0x2006;	// Objtype of a corpse


///////////////////////
// 1st Circle Spells //
///////////////////////

//Clumsy
const SPELLID_CLUMSY  		:= 1;
const SFX_SPELL_CLUMSY 		:= 0x01e0;
const FX_SPELL_CLUMSY		:= 0x374a;
const MOVING_SPELL_CLUMSY	:= 0;
const SPEED_SPELL_CLUMSY	:= 7;
const LOOP_SPELL_CLUMSY		:= 7;

//Create Food
const SPELLID_CREATE_FOOD	:= 2;
const SFX_SPELL_CREATE_FOOD	:= 0x01e3;
				// Have no FX

//Feeblemind
const SPELLID_FEEBLEMIND	:= 3;
const SFX_SPELL_FEEBLEMIND      := 0x01e5;
const FX_SPELL_FEEBLEMIND   	:= 0x374a;
const MOVING_SPELL_FEEBLEMIND	:= 0;
const SPEED_SPELL_FEEBLEMIND	:= 7;
const LOOP_SPELL_FEEBLEMIND	:= 7;

//Heal
const SPELLID_HEAL		:= 4;
const SFX_SPELL_HEAL            := 0x01f3;
const FX_SPELL_HEAL    		:= 0x376a;
const MOVING_SPELL_HEAL		:= 0;
const SPEED_SPELL_HEAL		:= 7;
const LOOP_SPELL_HEAL		:= 0x10;

//Magic Arrow
const SPELLID_MAGIC_ARROW	:= 5;
const SFX_SPELL_MAGIC_ARROW     := 0x01e6;
const FX_SPELL_MAGIC_ARROW    	:= 0x36e4;
const MOVING_SPELL_MAGIC_ARROW 	:= 1;
const SPEED_SPELL_MAGIC_ARROW  	:= 5;
const LOOP_SPELL_MAGIC_ARROW	:= 1;

//Night Sight
const SPELLID_NIGHTSIGHT	:= 6;
const SFX_SPELL_NIGHT_SIGHT     := 0x01e4;
const FX_SPELL_NIGHT_SIGHT   	:= 0x373a;
const MOVING_SPELL_NIGHT_SIGHT 	:= 0;
const SPEED_SPELL_NIGHT_SIGHT  	:= 10;
const LOOP_SPELL_NIGHT_SIGHT	:= 10;

//Reactive Armor
const SPELLID_REACTIVE_ARMOR	:= 7;
const SFX_SPELL_REACTIVE_ARMOR  := 0x01f3;
const FX_SPELL_REACTIVE_ARMOR	:= 0x373a;
const MOVING_SPELL_REACTIVE_ARMOR 	:= 0;
const SPEED_SPELL_REACTIVE_ARMOR  	:= 5;
const LOOP_SPELL_REACTIVE_ARMOR		:= 5;

//Weaken
const SPELLID_WEAKEN		:= 8;
const SFX_SPELL_WEAKEN          := 0x01e7;
const FX_SPELL_WEAKEN	   	:= 0x374a;
const MOVING_SPELL_WEAKEN	:= 0;
const SPEED_SPELL_WEAKEN	:= 7;
const LOOP_SPELL_WEAKEN		:= 7;


///////////////////////
// 2nd Circle Spells //
///////////////////////

//Agility
const SPELLID_AGILITY		:= 9;
const SFX_SPELL_AGILITY         := 0x01e8;
const FX_SPELL_AGILITY 		:= 0x373a;
const MOVING_SPELL_AGILITY	:= 0;
const SPEED_SPELL_AGILITY	:= 7;
const LOOP_SPELL_AGILITY	:= 7;

//Cunning
const SPELLID_CUNNING		:= 10;
const SFX_SPELL_CUNNING         := 0x01ec;
const FX_SPELL_CUNNING   	:= 0x373a;
const MOVING_SPELL_CUNNING	:= 0;
const SPEED_SPELL_CUNNING	:= 7;
const LOOP_SPELL_CUNNING	:= 7;

//Cure
const SPELLID_CURE		:= 11;
const SFX_SPELL_CURE            := 0x01e1;
const FX_SPELL_CURE   		:= 0x373a;
const MOVING_SPELL_CURE		:= 0;
const SPEED_SPELL_CURE		:= 10;
const LOOP_SPELL_CURE		:= 10;

//Harm
const SPELLID_HARM		:= 12;
const SFX_SPELL_HARM            := 0x01f2;
const FX_SPELL_HARM		:= 0x37c3;
const MOVING_SPELL_HARM		:= 0;
const SPEED_SPELL_HARM		:= 0x0a;
const LOOP_SPELL_HARM		:= 0x1e;

//Magic Trap
const SPELLID_MAGIC_TRAP	:= 13;
const SFX_SPELL_MAGIC_TRAP1 	:= 0x01f0;
const SFX_SPELL_MAGIC_TRAP2 	:= 0x0236;
				// Unknow FX

//Magic Untrap
const SPELLID_MAGIC_UNTRAP	:= 14;
const SFX_SPELL_MAGIC_UNTRAP1	:= 0x01f1;
const SFX_SPELL_MAGIC_UNTRAP2	:= 0x011f;
				// Unknow FX

//Protection
const SPELLID_PROTECTION	:= 15;
const SFX_SPELL_PROTECTION      := 0x01ee;
const FX_SPELL_PROTECTION	:= 0x373a;
const MOVING_SPELL_PROTECTION	:= 0;
const SPEED_SPELL_PROTECTION	:= 7;
const LOOP_SPELL_PROTECTION	:= 7;

//Strength
const SPELLID_STRENGTH		:= 16;
const SFX_SPELL_STRENGTH        := 0x01ef;
const FX_SPELL_STRENGTH		:= 0x373a;
const MOVING_SPELL_STRENGTH	:= 0;
const SPEED_SPELL_STRENGTH	:= 7;
const LOOP_SPELL_STRENGTH	:= 7;


///////////////////////
// 3rd Circle Spells //
///////////////////////

//Bless
const SPELLID_BLESS		:= 17;
const SFX_SPELL_BLESS           := 0x01eb;
const FX_SPELL_BLESS   		:= 0x373a;
const MOVING_SPELL_BLESS	:= 0;
const SPEED_SPELL_BLESS		:= 10;
const LOOP_SPELL_BLESS		:= 10;

//Fireball
const SPELLID_FIREBALL		:= 18;
const SFX_SPELL_FIREBALL        := 0x0160;
const FX_SPELL_FIREBALL		:= 0x36d4;
const MOVING_SPELL_FIREBALL	:= 1;
const SPEED_SPELL_FIREBALL	:= 5;
const LOOP_SPELL_FIREBALL	:= 1;

//Magic Lock
const SPELLID_MAGIC_LOCK	:= 19;
const SFX_SPELL_MAGIC_LOCK1	:= 0x01f5;
const SFX_SPELL_MAGIC_LOCK2	:= 0x011f;
				// Unknow FX

//Poison
const SPELLID_POISON		:= 20;
const SFX_SPELL_POISON          := 0x0247;
const FX_SPELL_POISON	   	:= 0x374a;
const MOVING_SPELL_POISON	:= 0;
const SPEED_SPELL_POISON	:= 0x0a;
const LOOP_SPELL_POISON		:= 0x1e;

//Telekinesis
const SPELLID_TELEKINESIS	:= 21;
const SFX_SPELL_TELEKINESIS     := 0x01f6;
				// No FX

//Teleport
const SPELLID_TELEPORT		:= 22;
const SFX_SPELL_TELEPORT        := 0x01ff;
const FX_SPELL_TELEPORT		:= 0x3728;
const MOVING_SPELL_TELEPORT	:= 0;
const SPEED_SPELL_TELEPORT	:= 0xa;
const LOOP_SPELL_TELEPORT	:= 0xa;

//Unlock
const SPELLID_UNLOCK		:= 23;
const SFX_SPELL_UNLOCK1  	:= 0x0200;
const SFX_SPELL_UNLOCK2  	:= 0x011f;
				// Unknow FX

//Wall of Stone
const SPELLID_WALL_OF_STONE	:= 24;
const SFX_SPELL_WALL_OF_STONE   := 0x01f7;
				// No FX (Create the Wall)


///////////////////////
// 4th Circle Spells //
///////////////////////

//Arch Cure
const SPELLID_ARCH_CURE		:= 25;
const SFX_SPELL_ARCH_CURE       := 0x01e9;
const FX_SPELL_ARCH_CURE	:= 0x373a;
const MOVING_SPELL_ARCH_CURE	:= 0;
const SPEED_SPELL_ARCH_CURE	:= 10;
const LOOP_SPELL_ARCH_CURE	:= 10;

//Arch Protection
const SPELLID_ARCH_PROTECTION	:= 26;
const SFX_SPELL_ARCH_PROTECTION := 0x01f8;
const FX_SPELL_ARCH_PROTECTION	:= 0x373a;
const MOVING_SPELL_ARCH_PROTECTION	:= 0;
const SPEED_SPELL_ARCH_PROTECTION	:= 7;
const LOOP_SPELL_ARCH_PROTECTION	:= 7;

//Curse
const SPELLID_CURSE		:= 27;
const SFX_SPELL_CURSE           := 0x01e2;
const FX_SPELL_CURSE	   	:= 0x374a;
const MOVING_SPELL_CURSE	:= 0;
const SPEED_SPELL_CURSE		:= 10;
const LOOP_SPELL_CURSE		:= 10;

//Fire Field
const SPELLID_FIRE_FIELD	:= 28;
const SFX_SPELL_FIRE_FIELD      := 0x01de;
const FX_SPELL_FIRE_FIELD_EW    := 0x398c;
const FX_SPELL_FIRE_FIELD_NS    := 0x3996;

//Greater Heal
const SPELLID_GREATER_HEAL	:= 29;
const SFX_SPELL_GREATER_HEAL    := 0x0203;
const FX_SPELL_GREATER_HEAL   	:= 0x375a;
const MOVING_SPELL_GREATER_HEAL	:= 0;
const SPEED_SPELL_GREATER_HEAL	:= 7;
const LOOP_SPELL_GREATER_HEAL	:= 0x10;

//Lightning
const SPELLID_LIGHTNING		:= 30;
const SFX_SPELL_LIGHTNING       := 0x02a;
const MOVING_SPELL_LIGHTNING	:= 2;
	// For FX use :		PlayLightningBoltEffect(cast_on); from UO.em

//Mana Drain
const SPELLID_MANA_DRAIN	:= 31;
const SFX_SPELL_MANA_DRAIN      := 0x01f9;
const FX_SPELL_MANA_DRAIN	:= 0x376a;
const MOVING_SPELL_MANA_DRAIN	:= 0;
const SPEED_SPELL_MANA_DRAIN	:= 7;
const LOOP_SPELL_MANA_DRAIN	:= 0x10;

//Recall
const SPELLID_RECALL		:= 32;
const SFX_SPELL_RECALL1  	:= 0x0210;
const SFX_SPELL_RECALL2		:= 0x01fd;
const SFX_SPELL_RECALL		:= 0x01fd;
				// No FX

///////////////////////
// 5th Circle Spells //
///////////////////////

//Blade Spirit
const SPELLID_BLADE_SPIRIT	:= 33;
const SFX_SPELL_BLADE_SPIRIT 	:= 0x0213;
const FX_SPELL_BLADE_SPIRIT	:= 0x3728;
const MOVING_SPELL_BLADE_SPIRIT := 0;
const SPEED_SPELL_BLADE_SPIRIT  := 0xa;
const LOOP_SPELL_BLADE_SPIRIT	:= 0xa;

//Dispel Field
const SPELLID_DISPEL_FIELD	:= 34;
const SFX_SPELL_DISPEL_FIELD    := 0x0202;
const FX_SPELL_DISPEL_FIELD	:= 0x3728;
const MOVING_SPELL_DISPEL_FIELD := 0;
const SPEED_SPELL_DISPEL_FIELD  := 0xa;
const LOOP_SPELL_DISPEL_FIELD	:= 0xa;

//Incognito
const SPELLID_INCOGNITO		:= 35;
const SFX_SPELL_INCOGNITO       := 0x01e3;
				// No FX

//Spell Reflection
const SPELLID_MAGIC_REFLECTION	:= 36;
const SFX_SPELL_MAGIC_REFLECTION:= 0x01e8;
const FX_SPELL_MAGIC_REFLECTION := 0x374a;
const MOVING_SPELL_MAGIC_REFLECTION 	:= 0;
const SPEED_SPELL_MAGIC_REFLECTION  	:= 10;
const LOOP_SPELL_MAGIC_REFLECTION	:= 10;

//Mind Blast
const SPELLID_MIND_BLAST	:= 37;
const SFX_SPELL_MIND_BLAST      := 0x0214;
const FX_SPELL_MIND_BLAST 	:= 0x374a;
const MOVING_SPELL_MIND_BLAST 	:= 0;
const SPEED_SPELL_MIND_BLAST  	:= 7;
const LOOP_SPELL_MIND_BLAST	:= 0x10;

//Paralyze
const SPELLID_PARALYZE		:= 38;
const SFX_SPELL_PARALYZE        := 0x0205;
const FX_SPELL_PARALYZE 	:= 0x374a;
const MOVING_SPELL_PARALYZE 	:= 0;
const SPEED_SPELL_PARALYZE  	:= 10;
const LOOP_SPELL_PARALYZE	:= 0xa;

//Poison Field
const SPELLID_POISON_FIELD	:= 39;
const SFX_SPELL_POISON_FIELD	:= 0x0247;
const FX_SPELL_POISON_FIELD_EW 	:= 0x3914;
const FX_SPELL_POISON_FIELD_NS 	:= 0x3920;

//Summon Creature
const SPELLID_SUMMON_CREATURE	:= 40;
const SFX_SPELL_SUMMON_CREATURE := 0x0216;
const FX_SPELL_SUMMON_CREATURE	:= 0x3728;
const MOVING_SPELL_SUMMON_CREATURE	:= 0;
const SPEED_SPELL_SUMMON_CREATURE	:= 0xa;
const LOOP_SPELL_SUMMON_CREATURE	:= 0xa;


///////////////////////
// 6th Circle Spells //
///////////////////////

//Dispel
const SPELLID_DISPEL		:= 41;
const SFX_SPELL_DISPEL          := 0x0202;
const FX_SPELL_DISPEL		:= 0x3728;
const MOVING_SPELL_DISPEL	:= 0;
const SPEED_SPELL_DISPEL	:= 0xa;
const LOOP_SPELL_DISPEL		:= 0xa;

//Energy Bolt
const SPELLID_ENERGY_BOLT	:= 42;
const SFX_SPELL_ENERGY_BOLT     := 0x020b;
const FX_SPELL_ENERGY_BOLT    	:= 0x379f;
const MOVING_SPELL_ENERGY_BOLT	:= 1;
const SPEED_SPELL_ENERGY_BOLT	:= 0xa;
const LOOP_SPELL_ENERGY_BOLT	:= 0x1e;

//Explosion
const SPELLID_EXPLOSION		:= 43;
const SFX_SPELL_EXPLOSION       := 0x0208;
const FX_SPELL_EXPLOSION      	:= 0x36b0;
const MOVING_SPELL_EXPLOSION	:= 0;
const SPEED_SPELL_EXPLOSION	:= 7;
const LOOP_SPELL_EXPLOSION	:= 0x10;

//Invisibility
const SPELLID_INVISIBILITY	:= 44;
const SFX_SPELL_INVISIBILITY    := 0x0204;
const FX_SPELL_INVISIBILITY	:= 0;
const MOVING_SPELL_INVISIBILITY	:= 0;
const SPEED_SPELL_INVISIBILITY	:= 0;
const LOOP_SPELL_INVISIBILITY	:= 0;

//Mark
const SPELLID_MARK		:= 45;
const SFX_SPELL_MARK            := 0x01fb;
const FX_SPELL_MARK    		:= 0x3779;
const MOVING_SPELL_MARK		:= 0;
const SPEED_SPELL_MARK		:= 10;
const LOOP_SPELL_MARK		:= 10;

//Mass Curse
const SPELLID_MASS_CURSE	:= 46;
const SFX_SPELL_MASS_CURSE      := 0x01fc;
const FX_SPELL_MASS_CURSE 	:= 0x374a;
const MOVING_SPELL_MASS_CURSE	:= 0;
const SPEED_SPELL_MASS_CURSE	:= 10;
const LOOP_SPELL_MASS_CURSE	:= 10;

//Paralyze Field
const SPELLID_PARALYZE_FIELD	:= 47;
const SFX_SPELL_PARALYZE_FIELD  := 0x020c;
const FX_SPELL_PARALYZE_FIELD_EW:= 0x3967;
const FX_SPELL_PARALYZE_FIELD_NS:= 0x3979;

//Reveal
const SPELLID_REVEAL		:= 48;
const SFX_SPELL_REVEAL          := 0x01fe;
				// No FX

///////////////////////
// 7th Circle Spells //
///////////////////////

//Chain Lightning
const SPELLID_CHAIN_LIGHTNING	:= 49;
const SFX_SPELL_CHAIN_LIGHTNING := 0x02a;
const MOVING_SPELL_CHAIN_LIGHTNING	:= 2;
	//For FX use :		PlayLightningBoltEffect(cast_on); from UO.em

//Energy Field
const SPELLID_ENERGY_FIELD	:= 50;
const SFX_SPELL_ENERGY_FIELD    := 0x0211;

//Flame Strike
const SPELLID_FLAME_STRIKE	:= 51;
const SFX_SPELL_FLAME_STRIKE    := 0x0209;
const FX_SPELL_FLAME_STRIKE    	:= 0x3709;
const MOVING_SPELL_FLAME_STRIKE	:= 0;
const SPEED_SPELL_FLAME_STRIKE	:= 0x0a;
const LOOP_SPELL_FLAME_STRIKE	:= 0x1e;

//Gate Travel
const SPELLID_GATE_TRAVEL	:= 52;
const SFX_SPELL_GATE_TRAVEL     := 0x020f;
				// No FX

//Mana Vampire
const SPELLID_MANA_VAMPIRE	:= 53;
const SFX_SPELL_MANA_VAMPIRE    := 0x01fa;
const FX_SPELL_MANA_VAMPIRE	:= 0x37b9;
const MOVING_SPELL_MANA_VAMPIRE	:= 0;
const SPEED_SPELL_MANA_VAMPIRE	:= 7;
const LOOP_SPELL_MANA_VAMPIRE	:= 0x10;

//Mass Dispel
const SPELLID_MASS_DISPEL	:= 54;
const SFX_SPELL_MASS_DISPEL     := 0x020a;
const FX_SPELL_MASS_DISPEL	:= 0x3728;
const MOVING_SPELL_MASS_DISPEL	:= 0;
const SPEED_SPELL_MASS_DISPEL	:= 0xa;
const LOOP_SPELL_MASS_DISPEL	:= 0xa;

//Meteor Swarm
const SPELLID_METEOR_SWARM	:= 55;
const SFX_SPELL_METEOR_SWARM    := 0x0161;
const FX_SPELL_METEOR_SWARM	:= 0x36d4;
const MOVING_SPELL_METEOR_SWARM	:= 1;
const SPEED_SPELL_METEOR_SWARM	:= 5;
const LOOP_SPELL_METEOR_SWARM	:= 1;

//Polymorph
const SPELLID_POLYMORPH		:= 56;
const SFX_SPELL_POLYMORPH       := 0x020a;
const FX_SPELL_POLYMORPH	:= 0x01fa;
const MOVING_SPELL_POLYMORPH	:= 0;
const SPEED_SPELL_POLYMORPH	:= 0xa;
const LOOP_SPELL_POLYMORPH	:= 0xa;


///////////////////////
// 8th Circle Spells //
///////////////////////

//Earthquake
const SPELLID_EARTHQUAKE	:= 57;
const SFX_SPELL_EARTHQUAKE	:= 0x020e;
const SFX_SPELL_EARTHQUAKE1     := 0x0220;
const SFX_SPELL_EARTHQUAKE2	:= 0x0223;
const FX_SPELL_EARTHQUAKE	:= 0x3728;
const MOVING_SPELL_EARTHQUAKE	:= 0;
const SPEED_SPELL_EARTHQUAKE	:= 7;
const LOOP_SPELL_EARTHQUAKE	:= 7;

//Energy Vortex
const SPELLID_ENERGY_VORTEX	:= 58;
const SFX_SPELL_ENERGY_VORTEX   := 0x0213;
const FX_SPELL_ENERGY_VORTEX	:= 0x3728;
const MOVING_SPELL_ENERGY_VORTEX	:= 0;
const SPEED_SPELL_ENERGY_VORTEX	:= 0xa;
const LOOP_SPELL_ENERGY_VORTEX	:= 0xa;

//Resurrection
const SPELLID_RESURRECTION	:= 59;
const SFX_SPELL_RESURRECTION    := 0x0215;
const FX_SPELL_RESURRECTION	:= 0;
const MOVING_SPELL_RESURRECTION	:= 0;
const SPEED_SPELL_RESURRECTION	:= 0;
const LOOP_SPELL_RESURRECTION	:= 0;

//Summon Air Elemental
const SPELLID_SUMMON_AIR_ELEMENTAL	:= 60;
const SFX_SPELL_SUMMON_AIR_ELEMENTAL   	:= 0x0218;
const SFX_SPELL_SUMMON_ELEMENTAL	:= 0x0218;
					// No FX

//Summon Daemon
const SPELLID_SUMMON_DAEMON	:= 61;
const SFX_SPELL_SUMMON_DAEMON   := 0x0217;
				// No FX

//Summon Earth Elemental
const SPELLID_SUMMON_EARTH_ELEMENTAL	:= 62;
const SFX_SPELL_SUMMON_EARTH_ELEMENTAL 	:= 0x0218;
					// No FX

//Summon Fire Elemental
const SPELLID_SUMMON_FIRE_ELEMENTAL	:= 63;
const SFX_SPELL_SUMMON_FIRE_ELEMENTAL  	:= 0x0218;
					// No FX

//Summon Water Elemental
const SPELLID_SUMMON_WATER_ELEMENTAL	:= 64;
const SFX_SPELL_SUMMON_WATER_ELEMENTAL 	:= 0x0218;
					// No FX
///////////////////////////////////////
//           Holy Spells             //
///////////////////////////////////////

//Turn Undead
const SPELLID_TURN_UNDEAD		:= 167;
const SFX_SPELL_TURN_UNDEAD		:= 0x0216;
const FX_SPELL_TURN_UNDEAD  		:= 0x376a;
const MOVING_SPELL_TURN_UNDEAD 	:= 0;
const SPEED_SPELL_TURN_UNDEAD 	:= 10;
const LOOP_SPELL_TURN_UNDEAD		:= 10;

//Karma Blast
const SPELLID_KARMA_BLAST		:= 174;
const SFX_SPELL_KARMA_BLAST   	:= 0x0228;
const FX_SPELL_KARMA_BLAST	 	:= 0x375a;
const MOVING_SPELL_KARMA_BLAST 	:= 0;
const SPEED_SPELL_KARMA_BLAST  	:= 7;
const LOOP_SPELL_KARMA_BLAST		:= 0x10;

//Touch of God
const SPELLID_TOUCH_OF_GOD	 := 169;
const SFX_SPELL_TOUCH_OF_GOD	 := 0x0203;
const FX_SPELL_TOUCH_OF_GOD  	 := 0x375a;
const MOVING_SPELL_TOUCH_OF_GOD := 0;
const SPEED_SPELL_TOUCH_OF_GOD  := 7;
const LOOP_SPELL_TOUCH_OF_GOD   := 0x10;

//Holy Bolt
const SPELLID_HOLY_BOLT		:= 170;
const SFX_SPELL_HOLY_BOLT	:= 0x0207;
const FX_SPELL_HOLY_BOLT	:= 0x376a;
const MOVING_SPELL_HOLY_BOLT	:= 0;
const SPEED_SPELL_HOLY_BOLT	:= 10;
const LOOP_SPELL_HOLY_BOLT	:= 10;

//Holy Bless
const SPELLID_HOLY_BLESS	  := 171;
const SFX_SPELL_HOLY_BLESS	  := 0x01eb;
const FX_SPELL_HOLY_BLESS     := 0x373a;
const MOVING_SPELL_HOLY_BLESS := 0;
const SPEED_SPELL_HOLY_BLESS  := 10;
const LOOP_SPELL_HOLY_BLESS	  := 10;

//Angelic Gate
const SPELLID_ANGELIC_GATE	:= 172;
const SFX_SPELL_ANGELIC_GATE	:= 0x020f;

//Great Feast
const SPELLID_ANGELIC_FEAST	:= 166;
const SFX_SPELL_ANGELIC_FEAST	:= 0x01e3;

//Light of Day
const SPELLID_LIGHT_OF_DAY		:= 168;
const SFX_SPELL_LIGHT_OF_DAY		:= 0x01e4;
const FX_SPELL_LIGHT_OF_DAY   	:= 0x373a;
const MOVING_SPELL_LIGHT_OF_DAY 	:= 0;
const SPEED_SPELL_LIGHT_OF_DAY  	:= 10;
const LOOP_SPELL_LIGHT_OF_DAY		:= 10;

//Divine Fury
const SPELLID_DIVINE_FURY		:= 175;
const SFX_SPELL_DIVINE_FURY		:= 0x0209;
const FX_SPELL_DIVINE_FURY		:= 0x37be;
const MOVING_SPELL_DIVINE_FURY	:= 0;
const SPEED_SPELL_DIVINE_FURY		:= 10;
const LOOP_SPELL_DIVINE_FURY		:= 10;

//Enlightenment
const SPELLID_ENLIGHTENMENT		:= 177;
const SFX_SPELL_ENLIGHTENMENT		:= 0xF8;
const FX_SPELL_ENLIGHTENMENT		:= 0x375a;
const MOVING_SPELL_ENLIGHTENMENT	:= 0;
const SPEED_SPELL_ENLIGHTENMENT	:= 10;
const LOOP_SPELL_ENLIGHTENMENT	:= 10;

//Revive
const SPELLID_REVIVE			:= 178;
const SFX_SPELL_REVIVE    		:= 0x0215;
const FX_SPELL_REVIVE			:= 0;
const MOVING_SPELL_REVIVE		:= 0;
const SPEED_SPELL_REVIVE		:= 0;
const LOOP_SPELL_REVIVE			:= 0;

//Summon Guardian
const SPELLID_SUMMON_GUARDIAN	:= 180;

//Astral Storm
const SPELLID_ASTRAL_STORM		:= 176;
const SFX_SPELL_ASTRAL_STORM		:= 0x17;
const FX_SPELL_ASTRAL_STORM		:= 0x36fe;
const MOVING_SPELL_ASTRAL_STORM	:= 0;
const SPEED_SPELL_ASTRAL_STORM	:= 10;
const LOOP_SPELL_ASTRAL_STORM		:= 10;

//Remove Curse
const SPELLID_REMOVE_CURSE		:= 173;
const SFX_SPELL_REMOVE_CURSE		:= 0x0207;
const FX_SPELL_REMOVE_CURSE 		:= 0x376a;
const MOVING_SPELL_REMOVE_CURSE	:= 0;
const SPEED_SPELL_REMOVE_CURSE	:= 10;
const LOOP_SPELL_REMOVE_CURSE		:= 10;

//Sanctuary
const SPELLID_SANCTUARY		:= 179;
const SFX_SPELL_SANCTUARY	:= 0x01e1;
const FX_SPELL_SANCTUARY   	:= 0x373a;
const MOVING_SPELL_SANCTUARY 	:= 0;
const SPEED_SPELL_SANCTUARY  	:= 10;
const LOOP_SPELL_SANCTUARY	:= 10;

//Apockerlips :)
const SPELLID_APOCOLYPSE	:= 181;
const SFX_SPELL_APOCOLYPSE := 0x02a;
const MOVING_SPELL_APOCOLYPSE	:= 2;

///////////////////////////////////////
//			Songs              //
///////////////////////////////////////

//Song of Light
const SPELLID_SONG_OF_LIGHT := 182;

//Song of Haste
const SPELLID_SONG_OF_HASTE := 183;

//Song of Defense
const SPELLID_SONG_OF_DEFENSE := 184;

//Song of Glory
const SPELLID_SONG_OF_GLORY := 185;

//Song of Cloaking
const SPELLID_SONG_OF_CLOAKING := 186;

//Song of Remedy
const SPELLID_SONG_OF_REMEDY := 187;

//Song of Life
const SPELLID_SONG_OF_LIFE := 188;

//Song of Dismissal
const SPELLID_SONG_OF_DISMISSAL := 189;

//Song of Sirens
const SPELLID_SONG_OF_SIRENS := 190;

//Song of Earth
const SPELLID_SONG_OF_EARTH := 191;

//Song of Air
const SPELLID_SONG_OF_AIR := 192;

//Song of Fire
const SPELLID_SONG_OF_FIRE := 193;

//Song of Water
const SPELLID_SONG_OF_WATER := 194;

//Song of Beckon
const SPELLID_SONG_OF_BECKON := 195;

//Song of Fright
const SPELLID_SONG_OF_FRIGHT := 196;

//Song of Salvation
const SPELLID_SONG_OF_SALVATION := 197;

/////////////////////////////////
// Lesser Chants of Necromancy //
/////////////////////////////////

//Control Undead
const SPELLID_CONTROL_UNDEAD	:= 65;
const SFX_SPELL_CONTROL_UNDEAD	:= 0;
const FX_SPELL_CONTROL_UNDEAD	:= 0;
const MOVING_SPELL_CONTROL_UNDEAD := 0;
const SPEED_SPELL_CONTROL_UNDEAD := 0;
const LOOP_SPELL_CONTROL_UNDEAD	:= 0;

//Darkness
const SPELLID_DARKNESS		:= 66;
const SFX_SPELL_DARKNESS	:= 0x01e4;
const FX_SPELL_DARKNESS		:= 0x0373a;
const MOVING_SPELL_DARKNESS	:= 0;
const SPEED_SPELL_DARKNESS	:= 0xa;
const LOOP_SPELL_DARKNESS	:= 0xa;

//Decaying Ray
const SPELLID_DECAYING_RAY	:= 67;
const SFX_SPELL_DECAYING_RAY	:= 0x00fe;
const FX_SPELL_DECAYING_RAY	:= 0;
const MOVING_SPELL_DECAYING_RAY	:= 0;
const SPEED_SPELL_DECAYING_RAY	:= 0;
const LOOP_SPELL_DECAYING_RAY	:= 0;

//Specter's Touch
const SPELLID_SPECTER_TOUCH	:= 68;
const SFX_SPELL_SPECTER_TOUCH	:= 0x01f2;
const FX_SPELL_SPECTER_TOUCH	:= 0x37c3;
const MOVING_SPELL_SPECTER_TOUCH := 0;
const SPEED_SPELL_SPECTER_TOUCH	:= 0xa;
const LOOP_SPELL_SPECTER_TOUCH	:= 0x1e;

//Abyssal Flame
const SPELLID_ABYSSAL_FLAME	:= 69;
const SFX_SPELL_ABYSSAL_FLAME	:= 0x0160;
const FX_SPELL_ABYSSAL_FLAME	:= 0x36d4;
const MOVING_SPELL_ABYSSAL_FLAME := 1;
const SPEED_SPELL_ABYSSAL_FLAME	:= 5;
const LOOP_SPELL_ABYSSAL_FLAME	:= 1;

//Animate Dead
const SPELLID_ANIMATE_DEAD	:= 70;
const SFX_SPELL_ANIMATE_DEAD	:= 0x022b;
const FX_SPELL_ANIMATE_DEAD	:= 0x37b9;
const MOVING_SPELL_ANIMATE_DEAD	:= 0;
const SPEED_SPELL_ANIMATE_DEAD	:= 7;
const LOOP_SPELL_ANIMATE_DEAD	:= 0xa;
const ANIMATE_DEAD_CORPSE_COLOR	:= 0x482;

//Sacrifice
const SPELLID_SACRIFICE		:= 71;
const SFX_SPELL_SACRIFICE	:= 0x0208;
const FX_SPELL_SACRIFICE	:= 0x36b0;
const MOVING_SPELL_SACRIFICE	:= 0;
const SPEED_SPELL_SACRIFICE	:= 7;
const LOOP_SPELL_SACRIFICE	:= 0x10;
	//Plus a :		PlayLightningBoltEffect(cast_on);

//Wraith's Breath
const SPELLID_WRAITH_BREATH	:= 72;
const SFX_SPELL_WRAITH_BREATH	:= 0x1fa;
const FX_SPELL_WRAITH_BREATH	:= 0x374a;
const MOVING_SPELL_WRAITH_BREATH := 0;
const SPEED_SPELL_WRAITH_BREATH := 7;
const LOOP_SPELL_WRAITH_BREATH	:= 0x10;



//////////////////////////////////
// Greater Chants of Necromancy //
//////////////////////////////////


//Raise Dead
const SPELLID_SORCERERS_BANE	:= 73;
const SFX_SPELL_SORCERERS_BANE	:= 0x0209;
const FX_SPELL_SORCERERS_BANE	:= 0x3709;
const MOVING_SPELL_SORCERERS_BANE	:= 0;
const SPEED_SPELL_SORCERERS_BANE	:= 0x0a;
const LOOP_SPELL_SORCERERS_BANE	:= 0x1e;

//Summon Spirit
const SPELLID_SUMMON_SPIRIT	:= 74;
const SFX_SPELL_SUMMON_SPIRIT	:= 0x022b;

//Wraithform
const SPELLID_WRAITHFORM	:= 75;
const WRAITHFORM_DRAIN_SOUND	:= 0x1fa;
const WRAITHFORM_MORPH_SOUND	:= 0x210;
const WRAITHFORM_WRAITH_GRAPHIC	:= 0x1a;
const WRAITHFORM_WRAITH_COLOR	:= 0x482;
const WRAITHFORM_DRAIN_EFFECT	:= 0x374a;
const WRAITHFORM_MORPH_EFFECT	:= 0x3709;
const MOVING_SPELL_WRAITHFORM	:= 0;
const SPEED_SPELL_WRAITHFORM	:= 1;
const LOOP_SPELL_WRAITHFORM	:= 0x10;

//Wyvern Strike
const SPELLID_WYVERN_STRIKE	:= 76;
const SFX_SPELL_WYVERN_STRIKE	:= 0x1e2;
const FX_SPELL_WYVERN_STRIKE	:= 0x3709;
const MOVING_SPELL_WYVERN_STRIKE := 1;
const SPEED_SPELL_WYVERN_STRIKE	:= 5;
const LOOP_SPELL_WYVERN_STRIKE	:= 1;

//Kill
const SPELLID_KILL		:= 77;
const SFX_SPELL_KILL		:= 0x202;
const FX_SPELL_KILL		:= 0x375a;
const MOVING_SPELL_KILL 	:= 0;
const SPEED_SPELL_KILL		:= 1;
const LOOP_SPELL_KILL		:= 0x10;

//Liche
const SPELLID_LICHE		:= 78;
const LICHE_KILL_SOUND 		:= 0x202;
const LICHE_MORPH_SOUND 	:= 0x20a;
const FX_SPELL_LICHE	 	:= 0x375a;
const MOVING_SPELL_LICHE 	:= 0;
const SPEED_SPELL_LICHE		:= 1;
const LOOP_SPELL_LICHE		:= 0x10;

//Plague
const SPELLID_PLAGUE		:= 79;
const SFX_SPELL_PLAGUE		:= 0x1e2;
const FX_SPELL_PLAGUE		:= 0x374a;
const MOVING_SPELL_PLAGUE 	:= 0;
const SPEED_SPELL_PLAGUE	:= 7;
const LOOP_SPELL_PLAGUE		:= 0x10;

//Spellbind
const SPELLID_SPELLBIND		:= 80;
const SFX_SPELL_SPELLBIND	:= 0x20d;
const FX_SPELL_SPELLBIND	:= 0x37b9;
const MOVING_SPELL_SPELLBIND	:= 0;
const SPEED_SPELL_SPELLBIND	:= 7;
const LOOP_SPELL_SPELLBIND	:= 0x10;



///////////////////////////////////////
// Lesser 1st circle of Earth Spells //
///////////////////////////////////////

//Antidote
const SPELLID_ANTIDOTE		:= 81;
const SFX_SPELL_ANTIDOTE	:= 0x01e1;
const FX_SPELL_ANTIDOTE   	:= 0x373a;
const MOVING_SPELL_ANTIDOTE 	:= 0;
const SPEED_SPELL_ANTIDOTE  	:= 10;
const LOOP_SPELL_ANTIDOTE	:= 10;

//Owl Sight
const SPELLID_OWL_SIGHT		:= 82;
const SFX_SPELL_OWL_SIGHT	:= 0x01e4;
const FX_SPELL_OWL_SIGHT   	:= 0x373a;
const MOVING_SPELL_OWL_SIGHT 	:= 0;
const SPEED_SPELL_OWL_SIGHT  	:= 10;
const LOOP_SPELL_OWL_SIGHT	:= 10;

//Shifting Earth
const SPELLID_SHIFTING_EARTH	  := 83;
const SFX_SPELL_SHIFTING_EARTH	  := 0x020e;
const FX_SPELL_SHIFTING_EARTH     := 0x3789;
const MOVING_SPELL_SHIFTING_EARTH := 0;
const SPEED_SPELL_SHIFTING_EARTH  := 0xa;
const LOOP_SPELL_SHIFTING_EARTH	  := 0xa;

//Summon Mammals
const SPELLID_SUMMON_MAMMALS	:= 84;


////////////////////////////////////////
// Greater 1st circle of Earth Spells //
////////////////////////////////////////


//Call Lightning
const SPELLID_CALL_LIGHTNING	  := 85;
const SFX_SPELL_CALL_LIGHTNING	  := 0x0207;
const MOVING_SPELL_CALL_LIGHTNING := 3;

//Earth Blessing
const SPELLID_EARTH_BLESSING	  := 86;
const SFX_SPELL_EARTH_BLESSING	  := 0x01eb;
const FX_SPELL_EARTH_BLESSING     := 0x373a;
const MOVING_SPELL_EARTH_BLESSING := 0;
const SPEED_SPELL_EARTH_BLESSING  := 10;
const LOOP_SPELL_EARTH_BLESSING	  := 10;

//Earth Portal
const SPELLID_EARTH_PORTAL	:= 87;
const SFX_SPELL_EARTH_PORTAL	:= 0x020f;

//Nature's Touch
const SPELLID_NATURES_TOUCH	 := 88;
const SFX_SPELL_NATURES_TOUCH	 := 0x0203;
const FX_SPELL_NATURES_TOUCH   	 := 0x375a;
const MOVING_SPELL_NATURES_TOUCH := 0;
const SPEED_SPELL_NATURES_TOUCH  := 7;
const LOOP_SPELL_NATURES_TOUCH	 := 0x10;


///////////////////////////////////////
// Lesser 2nd circle of Earth Spells //
///////////////////////////////////////

//Gust of Air
const SPELLID_GUST_OF_AIR	:= 89;
const SFX_SPELL_GUST_OF_AIR1	:= 0x0108;
const SFX_SPELL_GUST_OF_AIR2	:= 0x0109;
const FX_SPELL_GUST_OF_AIR   	:= 0x37cc;
const MOVING_SPELL_GUST_OF_AIR	:= 4;
const SPEED_SPELL_GUST_OF_AIR	:= 30;
const LOOP_SPELL_GUST_OF_AIR	:= 30;

//Rising Fire
const SPELLID_RISING_FIRE	:= 90;
const SFX_SPELL_RISING_FIRE	:= 0x0209;
const FX_SPELL_RISING_FIRE   	:= 0x3709;
const MOVING_SPELL_RISING_FIRE	:= 0;
const SPEED_SPELL_RISING_FIRE	:= 0x0a;
const LOOP_SPELL_RISING_FIRE	:= 0x1e;

//Shapeshift
const SPELLID_SHAPESHIFT	:= 91;
const SFX_SPELL_SHAPESHIFT	:= 0x020a;
const FX_SPELL_SHAPESHIFT1   	:= 0x1;
const FX_SPELL_SHAPESHIFT2   	:= 0x373a;
const MOVING_SPELL_SHAPESHIFT	:= 0;
const SPEED_SPELL_SHAPESHIFT	:= 10;
const LOOP_SPELL_SHAPESHIFT	:= 10;


////////////////////////////////////////
// Greater 2nd circle of Earth Spells //
////////////////////////////////////////

//Ice Strike
const SPELLID_ICE_STRIKE	:= 92;
const SFX_SPELL_ICE_STRIKE1	:= 0x0117;
const SFX_SPELL_ICE_STRIKE2	:= 0x0118;
const FX_SPELL_ICE_STRIKE	:= 0x3789;
const MOVING_SPELL_ICE_STRIKE	:= 0;
const SPEED_SPELL_ICE_STRIKE	:= 30;
const LOOP_SPELL_ICE_STRIKE	:= 30;

//Earth Spirir
const SPELLID_EARTH_SPIRIT	:= 93;

//Flame Spirit
const SPELLID_FLAME_SPIRIT	:= 94;

//Storm Spirit
const SPELLID_STORM_SPIRIT	:= 95;

//Water Spirit
const SPELLID_WATER_SPIRIT	:= 96;



////////////////////////////////////
//	Tome of Enchantment       //
////////////////////////////////////

const SPELLID_RITUAL_OF_CHANNEL_MANA	:= 97;
const SPELLID_RITUAL_OF_CONSECRATION	:= 98;
const SPELLID_RITUAL_OF_FREE_MOVEMENT	:= 99;
const SPELLID_RITUAL_OF_QUICK_HEALING	:= 100;
const SPELLID_RITUAL_OF_REGENERATION	:= 101;
const SPELLID_RITUAL_OF_RESILIENCE	:= 102;
const SPELLID_RITUAL_OF_RESTORATION	:= 103;
const SPELLID_RITUAL_OF_VENOM_BANE	:= 104;
const SPELLID_RITUAL_OF_CURSING		:= 105;
const SPELLID_RITUAL_OF_DISENCHANTMENT	:= 106;
const SPELLID_RITUAL_OF_ELEMENTAL_WARD	:= 107;
const SPELLID_RITUAL_OF_MANA_FLUX	:= 108;
const SPELLID_RITUAL_OF_PLANAR_WARD	:= 109;
const SPELLID_RITUAL_OF_SANCTIFYING	:= 110;
const SPELLID_RITUAL_OF_SKILL_INFUSION	:= 111;
const SPELLID_RITUAL_OF_VENOM_MASTERY	:= 112;
const SPELLID_RITUAL_OF_BLOODSEEKING	:= 113;
const SPELLID_RITUAL_OF_HARDENING	:= 114;
const SPELLID_RITUAL_OF_MANA_DIMISSAL	:= 115;
const SPELLID_RITUAL_OF_PHYSICAL_WARD	:= 116;
const SPELLID_RITUAL_OF_PROTECTIVE_AURA	:= 117;
const SPELLID_RITUAL_OF_SPELL_BOUNCING	:= 118;
const SPELLID_RITUAL_OF_SPELL_WARDING	:= 119;
const SPELLID_RITUAL_OF_VITAL_INFUSION	:= 120;
const SPELLID_RITUAL_OF_ADVANCED_THEURGY := 121;
const SPELLID_RITUAL_OF_ATTUNEMENT	:= 122;
const SPELLID_RITUAL_OF_BASIC_THEURGY	:= 123;
const SPELLID_RITUAL_OF_ENHANCEMENT	:= 124;
const SPELLID_RITUAL_OF_IMMUTABILITY	:= 125;
const SPELLID_RITUAL_OF_PERILOUS_THEURGY := 126;
const SPELLID_RITUAL_OF_PURIFICATION	:= 127;
const SPELLID_RITUAL_OF_RACIAL_THEURGY	:= 128;


////////////////////////
//      Highest       //
////////////////////////

const MAX_NORMAL_SPELL		:= 64;
const MAX_NECRO_SPELL		:= 80;
const MAX_EARTH_SPELL		:= 96;
const MAX_RITUAL_SPELL		:= 128;
const SPELLID_HIGHEST		:= 128;



//////////////////////////////////////END OF SPELLS///////////////////////////////////
