//////////////////////////////////////////////////////			//
//Help system include							//
//functions here							//
//Icanpage(thechar) //returns if the char can use the page system now	//
//staffcheck() //set the number of online gms and counselors		//
//pagecheck(who, type) //check if who have paged, return  page num or 0 //
//pagewarning(type, message) //send to all staff types the message 	//
//////////////////////////////////////////////////////////////////////////


//globals variables
var counpages := {};
var gmpages := {};

var onlinecounselors;
var onlinestaff;

counpages := GetGlobalProperty("counpages");
gmpages := GetGlobalProperty("gmpages");

function GetStaff()
var staffs:=array;
	foreach player in EnumerateOnlineCharacters()
		if( player.cmdlevel >= 1)
			staffs.append( player );
		endif
	endforeach
return  staffs;
endfunction

function pagecheck(serial, type)

var cserial := CInt(serial);
var retval := 0;
var i;
//type if 1 for gm pages and 2 for counpages

case(CInt(type))
1:	var maxi := gmpages.size();

	for(i := 0; i < maxi; i := i + 1)
		if (cserial == CInt(gmpages[i]))
			retval := i;
			break;
		endif
	endfor


2:	var maxi := counpages.size();
	for(i := 0; i < maxi; i := i + 1)
		if (cserial == CInt(counpages[i]))
			retval := i;
			break;
		endif
	endfor

endcase

return retval;

endfunction


function SendPageToStaff(thepage, who, staffs)

	foreach char in staffs
			SendSysMessage( char, "Page from " + who.name + " ["+ ReadGameClock() +"]: " + thepage);
	endforeach

endfunction