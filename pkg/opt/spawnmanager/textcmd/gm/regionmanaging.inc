////////////////////////////////////////////////////////////////////
////	This include may scare when seem the first time :)	////
////	Most of it is gump building and datafile managing. 	////
////	Also, there's some communication with the region 	////
////	  managers.						////
////		Adriano Iank, <aiank@convoy.com.br>		////
////////////////////////////////////////////////////////////////////

global regionfile;
global regions := array;
	
function BuildRegionsGump()

	local res;
	local region, elem;
	local pagesize, pagenum, pagelocation;
	local invalidnum;
	local keepgoing := 1;
	
	repeat
	
		data := {"Select region."};
		layout := {
			"page 0",
			"noclose",
			"nodispose",
			"resizepic 0 0 5120 280 250",
			"text 20 15 600 0",
			"button 20 220 2460 2461 1 0 -1",
			"button 100 220 242 241 1 0 0",
			"page 1"
		};

		pagesize := 0;
		pagenum := 2; 
		region := 0;
		invalidnum := 0;

		foreach elem in regions
			region := region + 1;
			if(elem.valid)
				pagesize := pagesize + 1;
				if(pagesize > 5)
					pagesize := 1;
					layout.append("button 230 220 5601 5605 0 " + pagenum);
					layout.append("page " + pagenum);
					layout.append("button 200 220 5603 5607 0 " + (pagenum-1));
					pagenum := pagenum + 1;
				endif			
				pagelocation := 20+(30*pagesize);
				layout.append("button 20 " + pagelocation + " 210 211 1 0 " + region);
				data.append(elem.name);
				layout.append("text 45 " + pagelocation + " 600 " + (region-invalidnum));
			else
				invalidnum := invalidnum + 1;
			endif
		endforeach	
		
		res := SendDialogGump(me, layout, data);
		
		if(res[0]!=0)
			BuildSingleRegionGump(res[0]);
		else
			keepgoing := 0;
		endif
		
	until(!keepgoing or !me.ip);
	
endfunction

function load_region_specs()

	regionfile := OpenDataFile("regions");
	if(!regionfile)
		regionfile := CreateDataFile("regions", DF_KEYTYPE_INTEGER);
	endif
	local keys := regionfile.Keys();
	local elem;
	local region := struct;
	region.+fromx;
	region.+fromy;
	region.+groups;
	region.+name;
	region.+respawntime;
	region.+tospawn;
	region.+tox;
	region.+toy;
	region.+valid;
	region.groups := array;
	
	foreach key in keys
		elem := regionfile.FindElement(key);
		region.fromx := elem.GetProp("FromX");
		region.fromy := elem.GetProp("FromY");
		region.groups := elem.GetProp("Group");
		region.name := elem.GetProp("Name");
		region.respawntime := elem.GetProp("RespawnTime");
		region.tospawn := elem.GetProp("ToSpawn");
		region.tox := elem.GetProp("ToX");
		region.toy := elem.GetProp("ToY");
		region.valid := 1;
		regions[key] := region;
	endforeach
	
endfunction	

function BuildSingleRegionGump(region)

	local res;
	local pagesize, pagelocation;
	local regiontmp := struct;
	local save := 0;
	local keepgoing := 1;
	regiontmp.+fromx;
	regiontmp.+fromy;
	regiontmp.+groups;
	regiontmp.+name;
	regiontmp.+respawntime;
	regiontmp.+tospawn;
	regiontmp.+tox;
	regiontmp.+toy;
	regiontmp.+valid;
	local shiftpos, topleft, bottomright;
	
	if(region > 0)
		regiontmp.name := regions[region].name;
		regiontmp.fromx := regions[region].fromx;
		regiontmp.fromy := regions[region].fromy;
		regiontmp.groups := regions[region].groups;
		regiontmp.respawntime := regions[region].respawntime;
		regiontmp.tospawn := regions[region].tospawn;
		regiontmp.tox := regions[region].tox;
		regiontmp.toy := regions[region].toy;
		topleft := 1;
		bottomright := 1;
		regiontmp.valid := 1;
	else
		regiontmp.name := "Not defined";
		regiontmp.fromx := 0;
		regiontmp.fromy := 0;
		regiontmp.groups := array;
		regiontmp.respawntime := 10;
		regiontmp.tospawn := 0;
		regiontmp.tox := 0;
		regiontmp.toy := 0;
		topleft := 0;
		bottomright := 0;
		regiontmp.valid := 0;
	endif
		
	repeat
	
		data := {"Region name:",
			regiontmp.name,
			"Top left position:",
			regiontmp.fromx,
			regiontmp.fromy,
			"Bottom right position:",
			regiontmp.tox,
			regiontmp.toy,
			"Respawn time (minutes):",
			regiontmp.respawntime,
			"Amount to spawn:",
			regiontmp.tospawn,
			"Groups:",
			"Enabled/Disable",
			"Delete region",
			"Go to"
		};
		layout := {
			"page 0",
			"noclose",
			"nodispose",
			"resizepic 0 0 5120 420 45",
			"text 20 15 600 0",
			"text 200 15 600 1",
			"button 390 15 210 211 1 0 1",
			"resizepic 0 45 5120 420 285",
			"text 20 60 600 2",
			"text 200 60 600 3",
			"text 250 60 600 4",
			"text 20 90 600 5",
			"text 200 90 600 6",
			"text 250 90 600 7",
			"text 20 120 600 8",
			"text 200 120 600 9",
			"text 20 150 600 10",
			"text 200 150 600 11",
			"text 20 180 600 12",
			"text 20 210 600 13",
			"text 20 240 600 14",
			"text 20 270 600 15",
			"button 390 60 210 211 1 0 2",
			"button 390 90 210 211 1 0 3",
			"button 390 120 210 211 1 0 4",
			"button 390 150 210 211 1 0 5",
			"button 390 180 210 211 1 0 6",
			"button 390 210 210 211 1 0 7",
			"button 390 240 210 211 1 0 8",
			"button 390 270 210 211 1 0 9",
			"button 250 300 239 240 1 0 10",
			"button 350 300 242 241 1 0 0"
		};
		
		res := SendDialogGump(me, layout, data);
		case(res[0])
			1:	regiontmp.name := GetNewProp(regiontmp.name, "name", "str");
			2:	local newpos := GetNewPosition("top left");
				if(newpos)
					regiontmp.fromx := newpos.x;
					regiontmp.fromy := newpos.y;
					topleft := 1;
				endif
			3:	local newpos := GetNewPosition("bottom right");
				if(newpos)
					regiontmp.tox := newpos.x;
					regiontmp.toy := newpos.y;
					bottomright := 1;
				endif
			4:	regiontmp.respawntime := GetNewProp(regiontmp.respawntime, "respawn time", "int");
			5:	regiontmp.tospawn := GetNewProp(regiontmp.tospawn, "# to spawn", "int");
			6:	ShowGroups(regiontmp.groups);
			7:	set_enabled_disabled(region);
			8:	DeleteRegion(region);
				keepgoing := 0;
			9:	local result := build_goto_gump(regiontmp);
				if(result < 0)
					SendSysMessage(me, "Canceled");
				elseif(result == 0)
					SendSysMessage(me, "Could not go to location.");
				endif
			10:	if(topleft and bottomright) //Position validation
					if(regiontmp.fromx > regiontmp.tox)
						shiftpos := regiontmp.fromx;
						regiontmp.fromx := regiontmp.tox;
						regiontmp.tox := shiftpos;
					endif
					if(regiontmp.fromy > regiontmp.toy)
						shiftpos := regiontmp.fromy;
						regiontmp.fromy := regiontmp.toy;
						regiontmp.toy := shiftpos;
					endif
					save := 1;
					keepgoing := 0;
				else
					SendSysMessage(me, "You must define the positions.");
				endif	
			default:
				keepgoing := 0;
		endcase
			
	until(!keepgoing or !me.ip);

	if(save)
		if(region > 0)
			if(!GetGlobalProperty("#regiondefs"+region))
				BuildRegionManager(regiontmp, region);
			endif
		else
			regiontmp.valid := 1;
			region := 1;
			local keys := regionfile.Keys();
			local lastkey := 0;
			foreach key in keys
				if(key > lastkey + 1)
					region := lastkey + 1;
					break;
				else
					region := key + 1;
					lastkey := key;
				endif
			endforeach
			BuildRegionManager(regiontmp, region);
		endif
		regions[region] := regiontmp;
		SaveRegionSettings(region);
	endif
		
endfunction

function GetGroupName(group)

	if((group < 1) or (!group) or (!groups[group].valid))
		return ("Invalid group.");
	endif
	
	return (groups[group].name);
	
endfunction

function GetNewProp(oldpropval, propname, proptype)

	local newprop;
	case (proptype)
	"int":
		newprop := Cint(SendTextEntryGump(me, "Enter new "+propname+".",TE_CANCEL_ENABLE,TE_STYLE_NUMERICAL, 180, "Old value was "+oldpropval));
	"str":
		newprop := CStr(SendTextEntryGump(me, "Enter new "+propname+".",TE_CANCEL_ENABLE,TE_STYLE_NORMAL, 50, "Old value was "+oldpropval));
	endcase
	
	if(!newprop)
		return oldpropval;
	else
		return newprop;
	endif
	
endfunction

function GetNewPosition(posname)

	SendSysMessage(me, "Target the "+posname+" position.");
	return(TargetCoordinates(me));
	
endfunction

function BuildRegionManager(regiontmp, region)
			
	local manager;
	local xrange := regiontmp.tox - regiontmp.fromx + 1;
	local yrange := regiontmp.toy - regiontmp.fromy + 1;
	local xrdm;
	local yrdm;
	local newz;
	repeat
		sleepms(10);
		xrdm := regiontmp.fromx + RandomInt(xrange);
		yrdm := regiontmp.fromy + RandomInt(yrange);
		newz := GetWorldHeight(xrdm,yrdm);
		manager := CreateItemAtLocation(xrdm, yrdm, newz, 0xa348, 1);
	until (manager);
	ReserveItem(manager);
	SetObjProperty(manager, "ActualNum", 0);
	SetObjProperty(manager, "Enabled", 1);
	SetObjProperty(manager, "RegionNum", region);
	manager.decayat := 0;
	ReleaseItem(manager);

endfunction

function SaveRegionSettings(region)

	local regionelem := regionfile.FindElement(region);
	if(!regionelem)
		Syslog("[Spawnmanager] Could not find "+region+" entry in regions.txt.");
		regionelem := regionfile.CreateElement(region);
		if(!regionelem)
			Syslog("[Spawnmanager] Could not create region element: "+regionelem.errortext);
		endif
	endif
	
	regionelem.SetProp("ToSpawn", regions[region].tospawn);
	regionelem.SetProp("FromX", regions[region].fromx);
	regionelem.SetProp("FromY", regions[region].fromy);
	regionelem.SetProp("ToX", regions[region].tox);
	regionelem.SetProp("ToY", regions[region].toy);
	regionelem.SetProp("Name", regions[region].name);
	regionelem.SetProp("RespawnTime", regions[region].respawntime);
	regionelem.SetProp("Group", regions[region].groups);
	
	UnloadDataFile("regions");

	local regionmanagerpid := Cint(GetGlobalProperty("#regiondefs"+region));
	local process := GetProcess(regionmanagerpid);
	local ev := struct;
	ev.+type;
	ev.type := 0x0002; //EV_UPDATE
	process.SendEvent(ev);
	
endfunction

function set_enabled_disabled(region)

	if(region < 0)
		SendSysMessage(me, "Region is not yet operational.");
		return;
	endif
	
	local regionmanagerpid := Cint(GetGlobalProperty("#regiondefs"+region));
	local process := GetProcess(regionmanagerpid);
	local ev := struct;
	ev.+type;
	ev.+source;
	ev.type := 0x0004; //EV_ENABLE_DISABLE
	ev.source := me;
	process.SendEvent(ev);
	
endfunction

function DeleteRegion(region)

	if(region < 0)
		SendSysMessage(me, "Region is not yet operational.");
		return;
	endif
	
	regions[region].valid := 0;
	local regionmanagerpid := Cint(GetGlobalProperty("#regiondefs"+region));
	local process := GetProcess(regionmanagerpid);
	local ev := struct;
	ev.+type;
	ev.type := 0x0005; //EV_REGION_DELETED
	process.SendEvent(ev);
	regionfile.DeleteElement(region);
			
endfunction
	
function build_goto_gump(regiondefs)

	data := {"Top Left", "Center", "Bottom Right", "Random"};
	layout := {"page 0",
			"noclose",
			"nodispose",
			"resizepic 0 0 5120 150 180",
			"text 20 30 600 0",
			"text 20 60 600 1",
			"text 20 90 600 2",
			"text 20 120 600 3",
			"button 120 30 210 211 1 0 1",
			"button 120 60 210 211 1 0 2",
			"button 120 90 210 211 1 0 3",
			"button 120 120 210 211 1 0 4",
			"button 75 150 242 241 1 0 0"
		};
			
	local res := SendDialogGump(me, layout, data);
	local loc := struct;
	loc.+x;
	loc.+y;
	loc.+z;
	local rndincx := 0;
	local rndincy := 0;
	local tries := 0;
	
	case (res[0])
		1:	loc.x := regiondefs.fromx;
			loc.y := regiondefs.fromy;
		2:	loc.x := Cint((regiondefs.fromx + regiondefs.tox)/2);
			loc.y := Cint((regiondefs.fromy + regiondefs.toy)/2);
		3:	loc.x := regiondefs.tox;
			loc.y := regiondefs.toy;
		4:	loc.x := Cint((regiondefs.fromx + regiondefs.tox)/2);
			loc.y := Cint((regiondefs.fromy + regiondefs.toy)/2);
			rndincx := regiondefs.tox - regiondefs.fromx; 
			rndincy := regiondefs.toy - regiondefs.fromy; 
		default:
			return -1;
	endcase
	
	repeat
		loc.x := loc.x + (Cint(rndincx/2) - RandomInt(rndincx+1));
		loc.y := loc.y + (Cint(rndincy/2) - RandomInt(rndincy+1));
		loc.z := GetWorldHeight(loc.x, loc.y);
		rndincx := rndincx + 1;
		rndincy := rndincy + 1;
		tries := tries + 1;
	until(MoveCharacterToLocation(me, loc.x, loc.y, loc.z, 0) or tries > 4);
	
	if(tries > 4)
		return 0;
	else
		return 1;
	endif
	
endfunction	

function GetGroup()

	data := { "Select the group:" };
	layout := {
			"page 0",
			"noclose",
			"nodispose",
			"resizepic 0 0 5120 280 280",
			"text 20 15 600 0",
			"button 20 250 242 241 1 0 -1",
			"page 1"
		};

	local pagesize := 0;
	local pagenum := 2; 
	local group := 0;
	local invalidnum := 0;
	local pagelocation;
	foreach elem in groups
		group := group + 1;
		if(elem.valid)
			pagesize := pagesize + 1;
		else
			invalidnum := invalidnum + 1;
			continue;
		endif
		if(pagesize > 5)
			pagesize := 1;
			layout.append("button 230 210 5601 5605 0 " + pagenum);
			layout.append("page " + pagenum);
			layout.append("button 200 210 5603 5607 0 " + (pagenum-1));
			pagenum := pagenum + 1;
		endif			
		pagelocation := 20+(30*pagesize);
		layout.append("button 20 " + pagelocation + " 210 211 1 0 " + group);
		data.append(elem.name);
		layout.append("text 45 " + pagelocation + " 600 " + (group-invalidnum));
	endforeach
	
	local res := SendDialogGump(me, layout, data);
		
	return(res[0]);
	
endfunction	

function ShowGroups(byref groups)

	local res;
	local pagelocation, pagesize, pagenum, pos;
	
	repeat
	
		data := {"Select group to erase."};
		layout := {
			"page 0",
			"noclose",
			"nodispose",
			"resizepic 0 0 5120 280 280",
			"text 20 15 600 0",
			"button 20 250 2460 2461 1 0 -1",
			"button 200 250 239 240 1 0 0",
			"page 1"
		};

		pagesize := 0;
		pagenum := 2; 
		pos := 1;
		foreach group in groups
			pagesize := pagesize + 1;
			if(pagesize > 5)
				pagesize := 1;
				layout.append("button 230 210 5601 5605 0 " + pagenum);
				layout.append("page " + pagenum);
				layout.append("button 200 210 5603 5607 0 " + (pagenum-1));
				pagenum := pagenum + 1;
			endif			
			pagelocation := 20+(30*pagesize);
			layout.append("button 20 " + pagelocation + " 210 211 1 0 " + pos);
			data.append(GetGroupName(group));
			layout.append("text 45 " + pagelocation + " 600 " + pos);
			pos := pos + 1;
		endforeach
	
		res := SendDialogGump(me, layout, data);
		
		if(res[0] < 0)
			local newgroup := GetGroup();
			if(newgroup > 0)
				groups.append(newgroup);
			endif
		elseif(res[0] > 0)
			local auxarray array;
			auxarray := groups;
			auxarray.erase(res[0]);
			groups := auxarray;
		endif
		
	until(!res[0] or !me.ip);
	
endfunction