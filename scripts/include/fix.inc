//include "include/attributes";
function fix_item( byref user, byref item)
if(!ReserveItem(item))
	SendSysMessage(user, item.name+" is already in use.");
	return 0;
elseif(!Accessible(user,item))
	SendSysMessage(user,"You can't reach "+item.name);
	return 0;
elseif(!CheckLineOfSight(user,item ))
	SendSysMessage(user,"You can't see that.");
	return 0;
elseif(item.container.serial != user.backpack.serial)
	SendSysMessage(user, "That needs to be in your backpack.");
	return 0;
endif
return 1;
endfunction

function fix_equip( byref user, byref item)
if(!Accessible(user,item))
	SendSysMessage(user,"You can't reach "+item.name);
	return 0;
elseif(!CheckLineOfSight(user,item ))
	SendSysMessage(user,"You can't see that.");
	return 0;
endif
return 1;

endfunction

function fix_tool( byref user, byref item)
if(!ReserveItem(item))
	SendSysMessage(user,item.name+" is already in use.");
	return 0;
elseif(!Accessible(user,item))
	SendSysMessage(user,"You can't reach "+item.name);
	return 0;
endif
if(!CheckLineOfSight(user,item ))
	SendSysMessage(user,"You can't see that.");
	return 0;
endif
return 1;
endfunction

function TestTool( byref who, byref tool, byref porcentage)
  if (tool.hp && (Random(100)<=porcentage));
  	tool.hp := tool.hp-1;
        SendSysMessage(who,"Your tool "+ tool.desc + " was damaged a little.");
  endif
endfunction