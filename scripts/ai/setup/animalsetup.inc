// include "include/starteqp";

	set_critical(0);
	var me := self();
	var flee_point := 10;
	drop_anchor();

	if (!me.backpack)
		var npccfg := readconfigfile("npcdesc");
		var newbackpack := CreateItemAtLocation(5288 , 1176 , 0, 0xe75,1);
		EquipItem(me, newbackpack);
		if (npccfg[me.npctemplate].colorrange)
			var parms := splitwords(npccfg[me.npctemplate].colorrange);
			me.color := Random(cint(parms[2]) - cint(parms[1]))+cint(parms[1]);
			setobjproperty(me,"color",me.color);
		endif

		if( me.name["<random>"] )
			SetName ( me , RandomName( me ) );
		endif

		// MagicalEquip(me);

	endif
