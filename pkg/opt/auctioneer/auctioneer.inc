use uo;
use os;
use util;

include "include/client";
include "include/objtype";
include "include/utility";
include "include/myutil";

const MAX_AUCTIONS_PER_CATEGORY := 12;

var storage := find_or_create_storage( "Auction Storage" );
if (!storage)
	exit;
endif



///////////////////
//  figures out how much gold the auctioneer is holding for the player
///////////////////

function DetermineGoldHeld(acctname)
	var gold_array := GetGlobalProperty("auctioneer_gold");
	if (!gold_array)
		gold_array := dictionary;
	endif

	if (!gold_array.exists (acctname) )
		return 0;
	else
		return CInt(gold_array[acctname]);
	endif
endfunction




///////////////////
//  adds or subtracts gold from a player's account (pass a negative number to subtract).  This
//  function doesn't check the numbers, so its possible to go below 0.
///////////////////

function AddAmountToGoldHeld(acctname, new_amount)
	set_critical(1);
	new_amount := CInt(new_amount);
	var gold_array := GetGlobalProperty("auctioneer_gold");
	if (!gold_array)
		gold_array := dictionary;
	endif

	var gold_amount;
	if (!gold_array.exists (acctname) )
		gold_amount := 0;
	else
		gold_amount := CInt(gold_array[acctname]);
	endif

	gold_array [acctname] := gold_amount + new_amount;
	SetGlobalProperty("auctioneer_gold", gold_array);
	set_critical(0);
endfunction




///////////////////
//  determines the amount of gold the player has available to use (When a player bids on an item, that gold
//  is marked as unavailable)
///////////////////

function DetermineGoldAvailable(acctname)
	var gold_held := DetermineGoldHeld(acctname);
	var gold_reserved := 0;
	foreach category in ListCategoryNames()
		var category_box := find_or_create_item(storage, category, UOBJ_BANKBOX);
		foreach item in ListRootItemsInContainer(category_box)
			var current_high_bidder := GetObjProperty(item, "current_high_bidder");
			if (current_high_bidder && current_high_bidder == acctname)
				gold_reserved := gold_reserved + CInt(GetObjProperty(item, "current_high_bid"));
			endif
		endforeach
	endforeach

	return (gold_held - gold_reserved);
endfunction




///////////////////
//  builds the gump for the category selection menu
///////////////////

function SelectCategory(player)

	syslog("Displaying menu");

	var categories := CreateMenu("What kind of items do you want to look at?");
	foreach category_description in ListCategoryDescriptions()
		AddMenuItem(categories, 0, category_description);
	endforeach
	var cat_select := SelectMenuItem2(player, categories);
	if (!cat_select)
		return 0;
	endif

	var category_names := ListCategoryNames();

	return category_names[cat_select.index];

endfunction




///////////////////
//  returns a listing of the auction category names (behind the scenes names)
///////////////////

function ListCategoryNames()
	return {
		"auc_weapons_general",
		"auc_armor_general",
		"auc_other_general",
	};
endfunction




///////////////////
//  returns a listing of the auction category descriptions (names the player sees)
///////////////////

function ListCategoryDescriptions()
	return {
		"Weapons",
		"Armor",
		"Misc.",
	};
endfunction




///////////////////
//  Checks all the auctions to see if which ones have been completed
///////////////////

function CheckCompletedAuctions()
	start_script(":auctioneer:completeauctions", 0);
endfunction


