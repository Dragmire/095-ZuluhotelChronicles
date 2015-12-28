use uo;
use os;

include "include/objtype";
include "include/client";

function RemoveCamouflage( thief )

 	thief.color := GetObjProperty(thief, "cmfc");
	thief.graphic := GetObjProperty(thief, "cmfg");
	thief.name := GetObjProperty(thief, "cmfn");

	EraseObjProperty(thief, "cmfc");
	EraseObjProperty(thief, "cmfg");
	EraseObjProperty(thief, "cmfn");


	var storage := findsa(thief);
	var hair := GetEquipmentByLayer(thief, LAYER_HAIR );
	DestroyItem(hair);

	hair := GetEquipmentByLayer(thief, LAYER_BEARD );
	DestroyItem(hair);

	var itm;

	foreach itm in EnumerateItemsInContainer(storage)
	     EquipItem(thief, itm);
	endforeach

endfunction


function findsa( character )
    var worldbank := disguisesa();

    var bank_obj_name := "Disguises of " + character.serial;
    var bankbox := FindRootItemInStorageArea( worldbank, bank_obj_name );

    if (!bankbox)
        bankbox := CreateRootItemInStorageArea( worldbank, bank_obj_name, UOBJ_BANKBOX );
    endif

        // should never happen.  FIXME make sure and document that fact
    if (!bankbox)
        print( "Unable to find or create disguise area for " + character.serial );
    endif
   
    return bankbox;
endfunction




function disguisesa()
    var bank := FindStorageArea( "Disguise Storage" );
    if (!bank)
        bank := CreateStorageArea( "Disguise Storage" );
    endif

    if (!bank)
        print( "Unable to open or create disguise storage!" );
    endif
    return bank;
endfunction