function IsInside (who, sign, item)

	var nwx := getobjproperty (sign, "nwx");
	var nwy := getobjproperty (sign, "nwy");
	var sex := getobjproperty (sign, "sex");
	var sey := getobjproperty (sign, "sey");

	if ( (item.x >= nwx and item.x <= sex) and
	     (item.y >= nwy and item.y <= sey) )
		return 1;
	else
		return 0;
	endif

endfunction
