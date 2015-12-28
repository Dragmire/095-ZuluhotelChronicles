use cfgfile;
use basic;

function open_door(door)

    var doordesc := ReadConfigFile(":doors:itemdesc");

    var xmod := CInt(doordesc[door.objtype].xmod);
    var ymod := CInt(doordesc[door.objtype].ymod);

    var newx := (door.x + xmod);
    var newy := (door.y + ymod);
    var newz := door.z;

    var opengraphic := GetObjProperty(door, "opengraphic");
    if ((!opengraphic) || (opengraphic == ""))
        opengraphic := door.graphic + 1;
    endif

    door.graphic := opengraphic;
    door.movable := 1;
    MoveItemToLocation(door, newx, newy, newz, MOVEITEM_FORCELOCATION);   
    door.movable := 0;

endfunction

function close_door(door)

    var doordesc := ReadConfigFile(":doors:itemdesc");

    var xmod := CInt(doordesc[door.objtype].xmod);
    var ymod := CInt(doordesc[door.objtype].ymod);

    var newx := (door.x - xmod);
    var newy := (door.y - ymod);
    var newz := (door.z);

    door.graphic := door.objtype;
    door.movable := 1;
    MoveItemToLocation(door, newx, newy, newz, MOVEITEM_FORCELOCATION);
    door.movable := 0;

endfunction