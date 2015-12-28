function fix_flag(flaghome,fcolor)

  var ev:=struct;
  ev.+type:=EVID_CTF_MAKE_FLAG;
  ev.+source:=flaghome;
  ev.+fcolor:=fcolor;
  var pid:=GetGlobalProperty("#CTFPointManagerPID");
  var proc:=getprocess(pid);
  proc.SendEvent(ev);

endfunction

function game_start()

  var ev:=struct;
  ev.+type:=EVID_CTF_START;
  var pid:=GetGlobalProperty("#CTFPointManagerPID");
  var proc:=getprocess(pid);
  proc.SendEvent(ev);

endfunction

function game_end()

  var ev:=struct;
  ev.+type:=EVID_CTF_END;
  var pid:=GetGlobalProperty("#CTFPointManagerPID");
  var proc:=getprocess(pid);
  proc.SendEvent(ev);

endfunction

function game_capture(who,mcolor)

  var ev:=struct;
  ev.+type:=EVID_CTF_CAPTURE;
  ev.+source:=who;
  ev.+mcolor:=mcolor;
  var pid:=GetGlobalProperty("#CTFPointManagerPID");
  var proc:=getprocess(pid);
  proc.SendEvent(ev);

endfunction