

function drop_anchor()

// assumes that var me = npc::self



var cfg := ReadConfigFile("npcdesc");

var dstart := cfg[me.npctemplate].dstart;
var psub := cfg[me.npctemplate].psub;

if (!psub)
        psub := 10;
endif

if (dstart)
       SetAnchor(me.x, me.y, dstart, psub);
endif

endfunction