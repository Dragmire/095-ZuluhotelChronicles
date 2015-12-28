use uo;
use cfgfile;
use util;
use os;

function GetHitZone(defender)
	//This function assumes that the 'Chance' totals in
	//armrzone.cfg all add up to 100.

	var armrzones := ReadConfigFile("::armrzone");

	//last_num stores the max roll for that zone
	var last_num := 0;
	var max_num := 0;

	//Roll determines the layer we hit.
	//In the future, we may want to have anatomy affect this.
	var roll := RandomInt(100)+1;
	foreach zone_name in GetConfigStringKeys(armrzones)
		var zone := armrzones[zone_name];
		last_num := max_num;
		max_num := last_num+zone.Chance;
		if ( roll > last_num && roll <= max_num  )
			return zone_name;
		endif
		sleepms(2);
	endforeach
endfunction

function GetEquipInArmorZone(mobile, zone_name)
	var itemdesc_cfg := ReadConfigFile(":*:itemdesc");
	var equip_list := array;
	foreach item in ListEquippedItems(mobile)
		var item_info := itemdesc_cfg[item.objtype];
		if ( zone_name in GetConfigStringArray(item_info, "Coverage") )
			equip_list.Append(item);
		endif
		sleepms(2);
	endforeach
	
	return equip_list;
endfunction

function SortEquipment(byref equip_list)
	var layer_cfg := ReadConfigFile("::layerprotect");

	var sorted_list := array;
	foreach item in equip_list
		var layer_info := layer_cfg[item.layer];
		sleepms(2);
	endforeach

	return sorted_list;
endfunction
