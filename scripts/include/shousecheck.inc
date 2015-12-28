use uo;
use os;
use util;

//function shousecheck(item)
//
//  local element, nwx, nwy, sex, sey;
//  local cfgfile := ReadConfigFile("::stathouses");
//  local entries := GetConfigStringKeys(cfgfile);
//  foreach listing in entries
//    element :=  cfgfile[listing];
//      nwx:= element.nwx;
//      nwy:= element.nwy;
//      sex:= element.sex;
//      sey:= element.sey;
//
//    if((item.x >= nwx) and (item.x <= sex) and (item.y >= nwy) and (item.y <= sey))
//      return 1;
//      break;
//    endif
//  endforeach
//
//endfunction  

function shousecheck(item)

var nwx, nwy, sex, sey;

   foreach sign in ListItemsNearLocationOfType(item.x, item.y, item.z, 30, 0x7060)

      nwx:= (getobjproperty (sign,"nwx"));
      nwy:= (getobjproperty (sign,"nwy"));
      sex:= (getobjproperty (sign,"sex"));
      sey:= (getobjproperty (sign,"sey"));

    if((item.x >= nwx) and (item.x <= sex) and (item.y >= nwy) and (item.y <= sey))
      return 1;
      break;
    endif
  endforeach
endfunction 