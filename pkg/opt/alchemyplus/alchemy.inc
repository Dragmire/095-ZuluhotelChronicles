///////////////////
//  This function returns a string that is the name of the keg, dependant on the type of potion inside it
//////////////////

function get_keg_name(potion_objtype, potion_subtype)
	var the_string := 0;
	case (potion_objtype)
		0xdc01:		the_string := "a keg of light healing potions";
		0xdc02:		the_string := "a keg of healing potions";
		0xdc03:		the_string := "a keg of greater healing potions";
		0xdc04:		the_string := "a keg of lesser poison potions";
		0xdc05:		the_string := "a keg of poison potions";
		0xdc06:		the_string := "a keg of greater poison potions";
		0xdc07:		the_string := "a keg of greater explosion potions";
		0xdc08:		the_string := "a keg of lesser explosion potions";
		0xdc09:		the_string := "a keg of explosion potions";
		0xdc0b:		the_string := "a keg of lesser agility potions";
		0xdc0c:		the_string := "a keg of agility potions";
		0xdc0d:		the_string := "a keg of greater agility potions";
		0xdc0e:		the_string := "a keg of refresh potions";
		0xdc0f:		the_string := "a keg of greater refresh potions";
		0xdc10:		the_string := "a keg of lesser strength potions";
		0xdc11:		the_string := "a keg of strength potions";
		0xdc12:		the_string := "a keg of greater strength potions";
		0xdc14:		the_string := "a keg of lesser cure potions";
		0xdc15:		the_string := "a keg of cure potions";
		0xdc16:		the_string := "a keg of greater cure potions";
		0xdc17:		the_string := "a keg of deadly poison potions";
		0xdce6:		the_string := "a keg of nightsight potions";
		0x7059:
			case (potion_subtype)
				23:	the_string := "a keg of invisibility potions";
				24:	the_string := "a keg of Phandel's Fine Intellect potions";
				25:	the_string := "a keg of Phandel's Fabulous Intellect potions";
				26:	the_string := "a keg of Phandel's Fantastic Intellect potions";
				27:	the_string := "a keg of lesser Mego Invulnerability potions";
				28:	the_string := "a keg of Mego Invulnerability potions";
				29:	the_string := "a keg of greater Mego Invulnerability potions";
				30:	the_string := "a keg of Grand Mage Refresh Elixir";
				31:	the_string := "a keg of Homeric Might potions";
				32:	the_string := "a keg of Greater Homeric Might potions";
				33:	the_string := "a keg of Tamla Heal potions";
				34:	the_string := "a keg of Taint's Minor Transmutation potions";
				35:	the_string := "a keg of Taint's Major Transmutation potions";
			endcase;
	endcase;

	return the_string;
endfunction




///////////////////
//  This function returns a string that is the name of the potion
//////////////////

function get_potion_name(potion_objtype, potion_subtype)
	var the_string := 0;
	case (potion_objtype)
		0xdc01:		the_string := "a light healing potion";
		0xdc02:		the_string := "a healing potion";
		0xdc03:		the_string := "a greater healing potion";
		0xdc04:		the_string := "a lesser poison potion";
		0xdc05:		the_string := "a poison potion";
		0xdc06:		the_string := "a greater poison potion";
		0xdc07:		the_string := "a greater explosion potion";
		0xdc08:		the_string := "a lesser explosion potion";
		0xdc09:		the_string := "an explosion potion";
		0xdc0b:		the_string := "a lesser agility potion";
		0xdc0c:		the_string := "an agility potion";
		0xdc0d:		the_string := "a greater agility potion";
		0xdc0e:		the_string := "a refresh potion";
		0xdc0f:		the_string := "a greater refresh potion";
		0xdc10:		the_string := "a lesser strength potion";
		0xdc11:		the_string := "a strength potion";
		0xdc12:		the_string := "a greater strength potion";
		0xdc14:		the_string := "a lesser cure potion";
		0xdc15:		the_string := "a cure potion";
		0xdc16:		the_string := "a greater cure potion";
		0xdc17:		the_string := "a deadly poison potion";
		0xdce6:		the_string := "a nightsight potion";
		0x7059:
			case (potion_subtype)
				23:	the_string := "an invisibility potion";
				24:	the_string := "Phandel's Fine Intellect";
				25:	the_string := "Phandel's Fabulous Intellect";
				26:	the_string := "Phandel's Fantastic Intellect";
				27:	the_string := "a lesser Mego Invulnerability potion";
				28:	the_string := "a Mego Invulnerability potion";
				29:	the_string := "a greater Mego Invulnerability potion";
				30:	the_string := "a Grand Mage Refresh Elixir";
				31:	the_string := "a Homeric Might potion";
				32:	the_string := "a Greater Homeric Might potion";
				33:	the_string := "a Tamla Heal potion";
				34:	the_string := "Taint's Minor Transmutation";
				35:	the_string := "Taint's Major Transmutation";
			endcase;
	endcase;

	return the_string;
endfunction




///////////////////
//  This function returns a dictionary of all reagents used in alchemy relating them to their names.
//  its used in the potionbook script to translate names
///////////////////

function define_reagent_name_dictionary()
	var reagent := dictionary;

	//normal reagents
	reagent [ 0x0f78 ]		:= "bat wing";
	reagent [ 0x0f79 ]		:= "blackmoor";
	reagent [ 0x0f7a ]		:= "black pearl";
	reagent [ 0x0f7b ]		:= "blood moss";
	reagent [ 0x0f7c ]		:= "blood spawn";
	reagent [ 0x0f7d ]		:= "vial of blood";
	reagent [ 0x0f7e ]		:= "bone";
	reagent [ 0x0f7f ]		:= "brimstome";
	reagent [ 0x0f80 ]		:= "deamon bone";
	reagent [ 0x0f81 ]		:= "fertile dirt";
	reagent [ 0x0f82 ]		:= "dragon's blood";
	reagent [ 0x0f83 ]		:= "executioner's cap";
	reagent [ 0x0f84 ]		:= "garlic";
	reagent [ 0x0f85 ]		:= "ginseng";
	reagent [ 0x0f86 ]		:= "mandrake root";
	reagent [ 0x0f87 ]		:= "eye of newt";
	reagent [ 0x0f88 ]		:= "nightshade";
	reagent [ 0x0f89 ]		:= "obsidian";
	reagent [ 0x0f8a ]		:= "pig iron";
	reagent [ 0x0f8b ]		:= "pumice";
	reagent [ 0x0f8c ]		:= "sulfurous ash";
	reagent [ 0x0f8d ]		:= "spider's silk";
	reagent [ 0x0f8e ]		:= "serpent scale";
	reagent [ 0x0f8f ]		:= "volcanic ash";
	reagent [ 0x0f90 ]		:= "dead wood";
	reagent [ 0x0f91 ]		:= "wyrm's heart";

	//other potions
	reagent [ 0xdc01 ]		:= "l. heal potion";
	reagent [ 0xdc02 ]		:= "heal potion";
	reagent [ 0xdc03 ]		:= "gr. heal potion";
	reagent [ 0xdc04 ]		:= "l. poison potion";
	reagent [ 0xdc05 ]		:= "poison potion";
	reagent [ 0xdc06 ]		:= "gr. poison potion";
	reagent [ 0xdc07 ]		:= "gr. explosion pot.";
	reagent [ 0xdc08 ]		:= "l. explosion pot.";
	reagent [ 0xdc09 ]		:= "exposion potion";
	reagent [ 0xdc0b ]		:= "l. agility potion";
	reagent [ 0xdc0c ]		:= "agility potion";
	reagent [ 0xdc0d ]		:= "gr. agility pot.";
	reagent [ 0xdc0e ]		:= "refresh potion";
	reagent [ 0xdc0f ]		:= "full refresh pot.";
	reagent [ 0xdc10 ]		:= "l. strength pot.";
	reagent [ 0xdc11 ]		:= "strength potion";
	reagent [ 0xdc12 ]		:= "gr. strength pot.";
	reagent [ 0xdc14 ]		:= "l. cure potion";
	reagent [ 0xdc15 ]		:= "cure potion";
	reagent [ 0xdc16 ]		:= "gr. cure potion";
	reagent [ 0xdc17 ]		:= "deadly poison pot.";
	reagent [ 0xdce6 ]		:= "nightsight potion";

	//gems
	reagent [ 0x0f0f ]		:= "star sapphire";
	reagent [ 0x0f10 ]		:= "emerald";
	reagent [ 0x0f11 ]		:= "sapphire";
	reagent [ 0x0f12 ]		:= "sapphire";
	reagent [ 0x0f13 ]		:= "ruby";
	reagent [ 0x0f14 ]		:= "ruby";
	reagent [ 0x0f15 ]		:= "citrine";
	reagent [ 0x0f16 ]		:= "amethyst";
	reagent [ 0x0f17 ]		:= "amethyst";
	reagent [ 0x0f18 ]		:= "tourmaline";
	reagent [ 0x0f19 ]		:= "sapphire";
	reagent [ 0x0f1a ]		:= "ruby";
	reagent [ 0x0f1b ]		:= "star sapphire";
	reagent [ 0x0f1c ]		:= "ruby";
	reagent [ 0x0f1d ]		:= "ruby";
	reagent [ 0x0f1e ]		:= "tourmaline";
	reagent [ 0x0f1f ]		:= "sapphire";
	reagent [ 0x0f20 ]		:= "tourmaline";
	reagent [ 0x0f21 ]		:= "star sapphire";
	reagent [ 0x0f22 ]		:= "amethyst";
	reagent [ 0x0f23 ]		:= "citrine";
	reagent [ 0x0f24 ]		:= "citrine";
	reagent [ 0x0f25 ]		:= "amber";
	reagent [ 0x0f26 ]		:= "diamond";
	reagent [ 0x0f27 ]		:= "diamond";
	reagent [ 0x0f28 ]		:= "diamond";
	reagent [ 0x0f29 ]		:= "diamond";
	reagent [ 0x0f2a ]		:= "ruby";
	reagent [ 0x0f2b ]		:= "ruby";
	reagent [ 0x0f2c ]		:= "citrine";
	reagent [ 0x0f2d ]		:= "tourmaline";
	reagent [ 0x0f2e ]		:= "amethyst";
	reagent [ 0x0f2f ]		:= "emerald";
	reagent [ 0x0f30 ]		:= "diamond";

	//other stuff
	reagent [ 0x0f0e ]		:= "empty bottle";
	reagent [ 0x7022 ]		:= "troll hide";

	return reagent;
endfunction
