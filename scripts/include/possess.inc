include "include/myutil";
//include "include/attributes";

function possess( me, npc )

	if ( GetObjProperty(me,"possess") )
		var oldnpc := SystemFindObjectBySerial(CInt(GetObjProperty(me,"possess")));
		if ( oldnpc )
			unpossess(me);
		endif
	endif

	if (npc.enable( "invul" ) )
		GrantPrivilege( me, "invul" );
		me.enable( "invul" );
	else
		RevokePrivilege( me, "invul" );
	endif

	me.concealed := 1;
	var oldpack := MoveMyPack(me);

	SetObjProperty(me,"oldname",me.name);
	SetObjProperty(me,"oldprefix",me.title_prefix);
	SetObjProperty(me,"oldsuffix",me.title_suffix);
	me.name := npc.name;
	me.title_prefix := npc.title_prefix;
	me.title_suffix := npc.title_suffix;

	clone(npc, me);
	EquipItem(npc, oldpack);
	SetObjProperty(me,"possess",npc.serial);

	foreach item in ListRootItemsInContainer(npc.backpack)
		if (item.newbie) MoveItemToContainer(item, me.backpack); endif
	endforeach

endfunction

function MoveMyPack(me)

	if (!me.backpack)
		var newbackpack := CreateItemAtLocation(5123, 1779, 0, 0xe75,1);
		EquipItem(me, newbackpack);
	endif

	var mypack := me.backpack;
	foreach thing in ListEquippedItems(me)
		if ( thing.serial != mypack.serial )
			MoveItemToContainer(thing, mypack);
		endif
	endforeach

	MoveItemToLocation(mypack,5123, 1779, 0, MOVEITEM_FORCELOCATION);

	return mypack;

endfunction

function clone(npc, me)

	if (!npc.backpack)
		var newbackpack := CreateItemAtLocation(5123, 1779, 0, 0xe75,1);
		EquipItem(npc, newbackpack);
	endif

	if (npc.color == CInt(0x4631))
		npc.color := 1002;
	endif

	me.graphic := npc.graphic;
	me.color := npc.color;
	me.facing := npc.facing;
	me.hidden := npc.hidden;

	SetBaseStrength(me, GetStrength(npc) );
	SetBaseIntelligence(me, GetIntelligence(npc) );
	SetBaseDexterity(me, GetDexterity(npc) );
	SetHp(me, npc.hp);
	SetMana(me, npc.mana);
	SetStamina(me, npc.stamina);

	foreach it in ListEquippedItems(npc)
		EquipItem(me,it);
	endforeach

	var i;
	for (i := 0; i <= SKILLID__HIGHEST; i := i + 1)
		SetBaseSkill( me, i, GetBaseSkill(npc,i) );
	endfor

	MoveCharacterToLocation(me,npc.x, npc.y, npc.z, MOVECHAR_FORCELOCATION);
	MoveCharacterToLocation(npc,5276, 1164, 0, MOVECHAR_FORCELOCATION);
	me.concealed := 0;

	npc.hidden := 1;
	npc.frozen := 1;

endfunction

function unpossess( me )

	var npc;
	if ( GetObjProperty(me,"possess") )
		npc := SystemFindObjectBySerial(CInt(GetObjProperty(me,"possess")));
	endif
	if (!npc)
		EraseObjProperty(me,"possess");
		if ( GetObjProperty(me,"oldname") )
			me.name := GetObjProperty(me,"oldname");
			me.title_prefix := GetObjProperty(me,"oldprefix");
			me.title_suffix := GetObjProperty(me,"oldsuffix");
		endif
		SendSysMessage(me, "NPC not found.");
		return;
	endif


	me.concealed := 1;
	SwapClothes(me,npc);
	EraseObjProperty(me,"possess");
	if ( GetObjProperty(me,"oldname") )
		me.name := GetObjProperty(me,"oldname");
	endif

	me.name := GetObjProperty(me,"oldname");
	me.title_prefix := GetObjProperty(me,"oldprefix");
	me.title_suffix := GetObjProperty(me,"oldsuffix");

	EraseObjProperty(me,"oldname");
	EraseObjProperty(me,"oldprefix");
	EraseObjProperty(me,"oldsuffix");

	npc.hidden := me.hidden;
	npc.facing := me.facing;
	npc.frozen := 0;
	SetStamina(npc, me.stamina);
	SetHp(npc, me.hp);
	SetMana(npc, me.mana);

	MoveCharacterToLocation(npc,me.x, me.y, me.z,MOVECHAR_FORCELOCATION);


	var i;
	for (i := 0; i <= SKILLID__HIGHEST; i := i + 1)
		SetBaseSkill( me, i, 6000 );
	endfor

	SetBaseStrength(me, 100 );
	SetBaseIntelligence(me, 100 );
	SetBaseDexterity(me, 100 );
	SetHp(me, me.maxhp);
	SetMana(me, me.maxmana);
	SetStamina(me, me.maxstamina);

	me.graphic := me.trueobjtype;
	me.color := me.truecolor;

	var mypack := me.backpack;
	foreach thing in ListRootItemsInContainer(mypack)
		EquipItem(me, thing);
	endforeach

	var weaponone := GetEquipmentByLayer( me,  LAYER_HAND1 );
	var weapontwo := GetEquipmentByLayer( me,  LAYER_HAND2 );
	if (weaponone)
		MoveItemToContainer(weaponone, mypack );
	endif
	if (weapontwo)
		MoveItemToContainer(weapontwo, mypack );
	endif

	foreach item in ListRootItemsInContainer(npc.backpack)
		if (item.newbie) MoveItemToContainer(item, me.backpack); endif
	endforeach

endfunction

function SwapClothes(me, npc)

	if (!me.backpack)
		var newbackpack := CreateItemAtLocation(5123, 1779, 0, 0xe75,1);
		EquipItem(me, newbackpack);
	endif

	var hispack := npc.backpack;
	var mypack := me.backpack;

	if (hispack)
		MoveItemToLocation(hispack, 5123, 1779, 0, MOVEITEM_FORCELOCATION);
	else
		hispack := CreateItemAtLocation(5123, 1779, 0, 0xe75,1);
	endif

	foreach thing in ListEquippedItems(me)
		EquipItem(npc, thing);
	endforeach

	EquipItem(me, hispack);

	foreach item in ListRootItemsInContainer(npc.backpack)
		if (item.newbie) MoveItemToContainer(item, me.backpack); endif
	endforeach

endfunction

function unpossesscorpse( me, corpse )

	var npc;
	if ( GetObjProperty(me,"possess") )
		npc := SystemFindObjectBySerial(CInt(GetObjProperty(me,"possess")));
	endif
	if (!npc)
		EraseObjProperty(me,"possess");
		if ( GetObjProperty(me,"oldname") )
			me.name := GetObjProperty(me,"oldname");
			me.title_prefix := GetObjProperty(me,"oldprefix");
			me.title_suffix := GetObjProperty(me,"oldsuffix");
		endif
		return;
	endif

	me.concealed := 1;

	Resurrect( me );
	me.graphic := me.trueobjtype;
	me.color := me.truecolor;

	SwapClothes(me,npc);

	EraseObjProperty(me,"possess");

	me.name := GetObjProperty(me,"oldname");
	me.title_prefix := GetObjProperty(me,"oldprefix");
	me.title_suffix := GetObjProperty(me,"oldsuffix");
	EraseObjProperty(me,"oldname");
	EraseObjProperty(me,"oldprefix");
	EraseObjProperty(me,"oldsuffix");

	MoveCharacterToLocation(npc, 5288, 1176, 0, 0x40000000);
	SetObjProperty(npc, "guardkill", 1);
	RevokePrivilege( npc, "invul" );
	Damage( npc, GetHp(npc) );

	var i;
	for (i := 0; i <= SKILLID__HIGHEST; i := i + 1)
		SetBaseSkill( me, i, 6000 );
	endfor

	SetBaseStrength(me, 100 );
	SetBaseIntelligence(me, 100 );
	SetBaseDexterity(me, 100 );
	SetHp(me, me.maxhp);
	SetMana(me, me.maxmana);
	SetStamina(me, me.maxstamina);

	me.graphic := me.trueobjtype;
	me.color := me.truecolor;

	var mypack := me.backpack;
	foreach thing in ListRootItemsInContainer(mypack)
		EquipItem(me, thing);
	endforeach

	var weaponone := GetEquipmentByLayer( me,  LAYER_HAND1 );
	var weapontwo := GetEquipmentByLayer( me,  LAYER_HAND2 );
	if (weaponone)
		MoveItemToContainer(weaponone, mypack );
	endif
	if (weapontwo)
		MoveItemToContainer(weapontwo, mypack );
	endif

endfunction