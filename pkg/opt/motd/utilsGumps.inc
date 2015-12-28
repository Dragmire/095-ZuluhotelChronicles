//
// Gump Utils
//
// Copyright 2003 Jouni Airaksinen, mintus@bluecave.net
//

use uo;

function SendStringAsHtmlWindow(who, text, title := "Message Of The Day")
  var data := array(
  "page 0",    
//  "nomove",  
  "nodispose", 
//  "noclose", 
//  "resizepic 50 50 2520 320 325",
  "resizepic 50 50 2520 320 325", //background
  "text 127 108 1152 0",
  "htmlgump 130 136 361 149 1 1 1"
  );
  var lines := array(
  title,
  text
  );
  
  return SendDialogGump( who, data, lines );
endfunction
