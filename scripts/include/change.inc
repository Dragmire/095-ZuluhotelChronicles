///////////////////////////////////////////////////////////
// Change.inc
//
// Functions that turn on/off lightsources.
//
// Creator: Oroborous
// Contact: mkow@sympatico.ca
//
// Created: Dec-2000
///////////////////////////////////////////////////////////

use uo;
use os;
use cfgfile;

function Change(byref who, byref item)
	var cfg := ReadConfigFile(":*:itemdesc");
	var elem := FindConfigElem( cfg, item.objtype);
	var elemg := FindConfigElem( cfg, item.graphic);
	
	if (elem.staff > who.cmdlevel)
		return;
	endif

	// Handle duration stuff.
	var duration := GetObjProperty(item, "Duration");
	if (!duration and duration != 0)
		duration := elemg.Duration * 60; // Convert to minutes.
	endif
	
	if (duration <= 0 and !elemg.LightLit)
		return 0;
	endif
	
	// If script already running, kill it.  If not, start it.
	var pid := GetObjProperty(item, "DurationPID");
	if (pid)
		var proc := GetProcess(pid);
		if (proc)
			proc.kill();
			EraseObjProperty(item, "DurationPID");
		endif
	else
		SetObjProperty(item, "Duration", duration);
		
		var params := array;
		params.append(who);
		params.append(item);
		start_script(":lighting:duration", params);
	endif
		
	// Change the graphic, etc...
	if (item.graphic = item.objtype)
		if (elem.changesnd)
	  		PlaySoundEffect(who , elem.changesnd);
		endif
		item.graphic := elem.change;
	else
		if (elem.originsnd)
			PlaySoundEffect(who , elem.originsnd );
		endif
		item.graphic := item.objtype;
	endif
endfunction

///////////////////////////////////////////////////////////
// Purpose: Forces a change in the items graphic.
// Params: 	who			Ref to mobile or 0.
//			item		Red to item.
// Returns: N/A
///////////////////////////////////////////////////////////
function ForceChange(byref who, byref item)
	var cfg := ReadConfigFile(":*:itemdesc");
	var elem := FindConfigElem( cfg, item.objtype);
			
	if (item.graphic = item.objtype)
		if (elem.changesnd and who)
	  		PlaySoundEffect(who , elem.changesnd);
		endif
		item.graphic := elem.change;
	else
		if (elem.originsnd and who)
			PlaySoundEffect(who , elem.originsnd);
		endif
		item.graphic := item.objtype;
	endif
endfunction