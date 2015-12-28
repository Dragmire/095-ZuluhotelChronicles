////////////////////////////////////////////////////////////////////
////	These functions are used to manage the groups.		////
////	Each function is complicated enough to deserve a 	////
////	  comment, so that's what will be done... soon :p	////
////		Adriano Iank, <aiank@convoy.com.br>		////
////////////////////////////////////////////////////////////////////

global groupfile;
global groups := array;

function BuildGroupsGump()
	
	local group;
	local elem;
	local name;
	local pagelocation, pagesize, pagenum;
	local res;
	local invalidnum;
	local keepgoing := 1;
	
	repeat
	
		data := { "Select the group:" };
		layout := {
			"page 0",
			"noclose",
			"nodispose",
			"resizepic 0 0 5120 280 240",
			"text 20 15 600 0",
			"button 20 210 2460 2461 1 0 -1",
			"button 100 210 242 241 1 0 0",
			"page 1"
		};

		pagesize := 0;
		pagenum := 2; 
		group := 0;
		invalidnum := 0;
		foreach elem in groups
			group := group + 1;
			if(elem.valid)
				pagesize := pagesize + 1;
				if(pagesize > 5)
					pagesize := 1;
					layout.append("button 230 210 5601 5605 0 " + pagenum);
					layout.append("page " + pagenum);
					layout.append("button 200 210 5603 5607 0 " + (pagenum-1));
					pagenum := pagenum + 1;
				endif			
				name := elem.name;
				pagelocation := 20+(30*pagesize);
				layout.append("button 20 " + pagelocation + " 210 211 1 0 " + group);
				data.append(name);
				layout.append("text 45 " + pagelocation + " 600 " + (group-invalidnum));
			else
				invalidnum := invalidnum + 1;
			endif
		endforeach
	
		res := SendDialogGump(me, layout, data);
		if(res[0]=0)
			keepgoing := 0;
		else
			BuildSingleGroupGump(res[0]);
		endif
		
	until(!keepgoing or !me.ip);
	
endfunction

function BuildSingleGroupGump(group)

	local name;
	local pagelocation, pagesize, pagenum, templatenum, res;
	local templates;
	local keepgoing := 1;
	local save := 0;
	
	local grouptmp := struct;
	grouptmp.+name;
	grouptmp.+spawn;
	grouptmp.+valid;
	grouptmp.valid := 1;
	
	if(group > 0)
		grouptmp.name := groups[group].name;
		grouptmp.spawn := groups[group].spawn;
	else
		local lastkey := 0;
		group := 1;
		foreach key in (groupfile.Keys())
			if(key > (lastkey + 1))
				group := lastkey + 1;
				break;
			else
				group := key + 1;
				lastkey := key;
			endif
		endforeach
		grouptmp.name := "Click to select group name:";
		grouptmp.spawn := array;
	endif
		
	repeat
	
		data := {grouptmp.name,"Select template to erase.","Erase group."};
		layout := {
			"page 0",
			"nodispose",
			"resizepic 0 0 5120 280 45",
			"text 20 15 600 0",
			"button 250 15 210 211 1 0 -1",
			"resizepic 0 45 5120 280 265",
			"text 20 60 600 1",
			"text 20 250 600 2",
			"button 30 280 2460 2461 1 0 -2",
			"button 150 250 210 211 1 0 -3",
			"button 210 280 239 240 1 0 -4",
			"button 120 280 242 241 1 0 0",
			"page 1"
		};

		pagesize := 0;
		pagenum := 2;
		templatenum := 0;
		
		foreach template in (grouptmp.spawn)
			pagesize := pagesize + 1;
			templatenum := templatenum + 1;
			if(pagesize > 5)
				pagesize := 1;
				layout.append("button 230 250 5601 5605 0 " + pagenum);
				layout.append("page " + pagenum);
				layout.append("button 200 250 5603 5607 0 " + (pagenum-1));
				pagenum := pagenum + 1;
			endif			
			
			pagelocation := 65+(30*pagesize);
			layout.append("button 20 " + pagelocation + " 210 211 1 0 " + templatenum);
			data.append(template);
			layout.append("text 45 " + pagelocation + " 600 " + (templatenum+2));
		endforeach
	
		res := SendDialogGump(me, layout, data);
		if(res[0]=-1)
			grouptmp.name := SendTextEntryGump(me, "Enter group name.",TE_CANCEL_ENABLE,TE_STYLE_NORMAL, 50, "");
		elseif(res[0]=-2)	//Logical removal
			AddTemplateToGroup(grouptmp.spawn);
		elseif(res[0]=-3)
			grouptmp.valid := 0;
			keepgoing := 0;
			save := 1;
		elseif(res[0]=-4)
			groups[group] := grouptmp;
			keepgoing := 0;
			save := 1;
		elseif(res[0]>0)
			local auxarray array;
			auxarray := grouptmp.spawn;
			auxarray.erase(res[0]);
			grouptmp.spawn := auxarray;
		else
			keepgoing := 0;
		endif
	
	until(!keepgoing or !me.ip);
	
	if(save)
		SaveGroupSettings();
	endif
	
endfunction

function load_groups_specs()

	groupfile := OpenDataFile("datagroups");
	if(!groupfile)
		groupfile := CreateDataFile("datagroups", DF_KEYTYPE_INTEGER);
	endif
	
	local elem;
	local keys := groupfile.Keys();
	local group := struct;
	group.+name;
	group.+spawn;
	group.+valid;
	
	foreach key in keys
		elem := groupfile.FindElement(key);
		group.name := elem.GetProp("Name");
		group.spawn := elem.GetProp("spawn");
		group.valid := 1;
		groups[key] := group;
	endforeach
	
endfunction
	
function AddTemplatetoGroup(byref spawnarray)

	local template;
	template := SendTextEntryGump(me, "Enter template to be added to group.",TE_CANCEL_ENABLE,TE_STYLE_NORMAL, 50, "");
	if(template)
		spawnarray.append(template);
	else
		SendSysMessage(me, "Canceled");
	endif	
	
endfunction

function SaveGroupSettings()

	groupfile := CreateDataFile("datagroups", DF_KEYTYPE_INTEGER);
	local auxposition := 1;
	local elem, group;
	
	foreach group in groups
		if (group.valid)
			elem := groupfile.CreateElement(auxposition);
			elem.SetProp("Name", group.name);
			elem.SetProp("spawn", group.spawn);
		else
			groupfile.DeleteElement(auxposition);
		endif
		auxposition := auxposition + 1;
	endforeach

	UnloadDataFile("datagroups");

	local groupmanagerpid := Cint(GetGlobalProperty("#groupmanagerpid"));
	local process := GetProcess(groupmanagerpid);
	local ev := struct;
	ev.+type;
	ev.type := 0x0002; //EV_UPDATE
	process.SendEvent(ev);
	
endfunction
