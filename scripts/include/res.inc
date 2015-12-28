use uo;
use os;
use basic;

include "../../pkg/opt/karmafame/karmafame";

const MAX_LOSS_PERCENT	:= 0.5;

function ResurrectMobile( who , by_who := 0 )

	Resurrect( who );
	FixColor( who );
	//MurdererStatLoss( who );

	//more thing to do on res

endfunction


function FixColor( who )

   var newcolor, racepicked := who.title_race;

   if (racepicked=="Elf")
	newcolor := 770;
   elseif (racepicked=="Dark-Elf")
	newcolor := 33877;
   elseif (racepicked=="Goblin")
	newcolor := 34186;
   elseif (racepicked=="Barbarian")
	newcolor := 33804;
   elseif (racepicked=="Dwarf")
	newcolor := 33888;
   elseif (racepicked=="Orc")
	newcolor := 1056;
   elseif (racepicked=="Frost-Elf")
	newcolor := 91;
   else
	newcolor := who.truecolor;
   endif

   who.color := newcolor;

endfunction


function MurdererStatLoss( who )

	var shortc := GetObjProperty( who , "shortmurders" );
	if(!shortc)
		return;
	endif

	if(shortc>4) //then murderer]
		var multiplier := cint(shortc)/100.0;
		if(multiplier > MAX_LOSS_PERCENT)
			multiplier := MAX_LOSS_PERCENT;
		endif
		multiplier := 1.0 - multiplier;

		var str := GetStrength(who) - GetStrengthMod(who);
		var dex := GetDexterity(who) - GetDexterityMod(who);
		var inte := GetIntelligence(who) - GetIntelligenceMod(who);

		str := cint(str * multiplier);
		dex := cint(dex * multiplier);
		inte := cint(inte * multiplier);

		SetBaseStrength(who,str);
		SetBaseDexterity(who,dex);
		SetBaseIntelligence(who,inte);

		AwardFame( who , -250 );
		SendSysmessage( who , "Thy body pays the price for your sins." );
		if( shortc = 5 )
			EraseObjProperty( who , "shortmurders" );
		else
			SetObjProperty( who , "shortmurders" , shortc - 5 );
		endif
	endif

endfunction
