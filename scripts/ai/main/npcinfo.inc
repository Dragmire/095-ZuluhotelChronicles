function imalooter(npctemplate)

	var cfg := ReadConfigFile("::npcdesc");
	if (cfg[npctemplate].noloot) return 0; else return 1; endif

endfunction

function imanundead(npctemplate)

	var cfg := ReadConfigFile("::npcdesc");
	var undead := cfg[npctemplate].undead;
	if (!undead) return 0; else return undead; endif

endfunction

function HasNoCorpse(npctemplate)

	var cfg := ReadConfigFile("::npcdesc");
	if (cfg[npctemplate].nocorpse) return 1; else return 0; endif

endfunction

//good npcs use this function to determine what they should attack
function IsHostile(mob)

	if ( (!mob.npctemplate) or ( mob.script = "tamed" ) )
		return 0; 
	endif

	var cfg := ReadConfigFile("::npcdesc");
	if (cfg[mob.npctemplate].hostile) return 1; else return 0; endif

endfunction

//aggro npcs use this function to determine what they should attack
function IsGood(mob)

	if ( (!mob.npctemplate) or ( mob.script = "tamed" ) )
		return 1;
	endif

	if ( mob.script = "humuc" or mob.script = "merchant" or mob.script = "playervendor" )
		return 0;
	endif

	var cfg := ReadConfigFile("::npcdesc");
	if ( cfg[mob.npctemplate].alignment = "good" ) return 1; else return 0; endif


endfunction
