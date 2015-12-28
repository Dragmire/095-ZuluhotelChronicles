use uo;

function GetModAmount( magery ) 

    var mod_amount := Random(10) + (magery/6);
    return mod_amount;

endfunction

function GetModDuration( magery )

    var duration := 60 + ((magery / 15) * 60);
    return (duration);

endfunction

function CanMod(who, stat)

	var mod;

	case (stat)
        	"str": mod := "#ss";
        	"dex" : mod := "#dd";
        	"int" : mod := "#ii";
        	"ar"  : mod := "#aa";
        	"p"  : mod := "#pp";
	endcase

	if (getobjproperty(who, mod))
        	return 0;
	else
        	return 1;
	endif

endfunction

function DoTempMod(who, stat, amt, duration)

	var mod;

	case (stat)
        	"str": 
			mod := "#ss";
			SetStrengthMod(who, GetStrengthMod(who) + amt);
        	"dex" : 
			mod := "#dd";
			SetDexterityMod(who, GetDexterityMod(who) + amt);
        	"int" : 
			mod := "#ii";
			SetIntelligenceMod(who, GetIntelligenceMod(who) + amt);
        	"ar"  : 
			mod := "#aa";
			who.ar_mod := who.ar_mod + amt;
		"p"   :
			mod := "#pp";
			who.paralyzed := 1;
	endcase

	SetObjProperty(who,mod,1);

	var parms := {};
	parms[2] := who;
	parms[1] := stat;
	parms[3] := amt;
	parms[4] := duration;

	start_script("::/misc/unmod", parms);

endfunction
