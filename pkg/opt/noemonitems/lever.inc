use uo;
use os;
use cfgfile;

include "lever";
include "include/random";

function RandomBool()

	var dice:=Random(99) + 1;
	if (dice>50)
		return 0;
	else
		return 1;
	endif

endfunction

function CreateNewCombination(who, itemcontroller)

	var links:=GetObjProperty(itemcontroller,"AllLevers");
	if (!links)
			return;
	endif

	var obj;
	var n;
	var numlinks:=len(links);
	var combinations:={};

	for (n:=1;n<=numlinks;n:=n+1)
		combinations.Append( RandomBool() );

		obj := SystemFindObjectBySerial(CInt(links[n]));
		if (!obj)
			return;
		endif
		obj.color:=0;
		EraseObjProperty(obj,"status");
	endfor



	SetObjProperty(itemcontroller,"Combinations",combinations); //Stores Right Combinations
	SendSysMessage(who,"New random combination created.");

endfunction