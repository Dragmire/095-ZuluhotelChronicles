/////////////////////////////////////////////
//
//  Shinigami's GumpUtil v1.02 (2000/04/29)
//    (some nice Functions for Gumps)
//
//  Author:    Shinigami
//  eMail:     Shinigami@gmx.net
//  Languages: English/German
//
/////////////////////////////////////////////

/////////////////
// Installation
/////////////////
//
// Move it to /pol/scripts/include and use it in your script:
//   Include "include/gumputil";

//////////////
// Functions
//////////////
//
// GumpTextWidth(gumptext)           // Returns the Width of GumpText
// GumpTextWidthFast(gumptext)       // Returns the Width of GumpText
// GumpTextLeft(gumptext, x, width)  // Returns the X-Value (Left-Alignment)
// GumpTextRight(gumptext, x, width) // Returns the X-Value (Right-Alignment)
// GumpTextMid(gumptext, x, width)   // Returns the X-Value (Mid-Alignment)
//
//   Parameters:
//     gumptext - a String
//     x        - X-Value from the Textbox
//     width    - Width from the Textbox
//
// Create_ScrollBar(x, y, height, pages, page, layout) // Shows a Scrollbar
//
//   Parameters:
//     x,y    - X-/Y-Value of the left-top Corner
//     height - Height
//     pages  - Number of Pages
//     page   - Actual Page Number
//     layout - Contains the actual Gump Layout
//   Returns:
//     Updated "layout"

//////////////////////
// Original Location
//////////////////////
//
// www.egroups.com
//
//   www.egroups.com/files/pol-scriptforum/Includes/gumputil.zip

///////////////////////////////////////////////////////////////////////////////

//////////////
// Constants
//////////////

var c34:=CChr(34);

var length:={ };
       length.+chars:={
         "",                   // Dummy (for Speed...)
         "|",                  //  2
         "`',.;:",             //  3
         c34+"!",              //  4
         "il1[]",              //  5
         "bcejot”ö(){}=",      //  6
         "adfpqrszI„ä~",       //  7
         "ghnuvy?ü <>-",       //  8
         "xJ578$?ß+",          //  9
         "kCE2369^/*",         // 10
         "mwABDFOPŽÄ™Ö40%",    // 11
         "GLNQSZ#",            // 12
         "HRT&_",              // 13
         "KšÜUY",              // 14
         "X",                  // 15
         "V",                  // 16
         "M",                  // 18
         "W",                  // 21
       };
       length.+charsf:=        // Space as Filler is not allowed
         "|||||||||||||||"+    //  2
         "`',.;::::::::::"+    //  3
         c34+"!!!!!!!!!!!!!!"+ //  4
         "il1[]]]]]]]]]]]"+    //  5
         "bcejot”ö(){}==="+    //  6
         "adfpqrszI„ä~~~~"+    //  7
         "ghnuvy?ü <>----"+    //  8
         "xJ578$?ß+++++++"+    //  9
         "kCE2369^/******"+    // 10
         "mwABDFOPŽÄ™Ö40%"+    // 11
         "GLNQSZ#########"+    // 12
         "HRT&___________"+    // 13
         "KšÜUYYYYYYYYYYY"+    // 14
         "XXXXXXXXXXXXXXX"+    // 15
         "VVVVVVVVVVVVVVV"+    // 16
         "MMMMMMMMMMMMMMM"+    // 18
         "WWWWWWWWWWWWWWW";    // 21
       length.+width:={
          2, 3, 4, 5, 6, 7, 8, 9, 10, 11,
          12, 13, 14, 15, 16, 18, 21
       };

//////////////
// Functions
//////////////

// Returns the Width of GumpText

function GumpTextWidth(gumptext)
  var start_i:=len(length.chars);
  var points:=0;
  var j;

  for (j:=len(gumptext); j>0; j:=j-1)
    var i:=start_i;
    while ((i>0) && (!length.chars[i][CStr(gumptext[j])]))
      i:=i-1;
    endwhile;
    if (i>0) // siehe Speed-Dummy
      points:=points+length.width[i-1];
    else
      syslog("GumpTextWidth: Unknown Character = '"+gumptext[j]+"'");
    endif
  endfor

  return (points);
endfunction

// Returns the Width of GumpText

function GumpTextWidthFast(gumptext)
  var points:=0;
  var j;

  for (j:=len(gumptext); j>0; j:=j-1)
    var i:=find(length.charsf, gumptext[j], 1)-1;
    if (i>=0)
      points:=points+length.width[CInt(i/15)+1];
    else
      syslog("GumpTextWidthFast: Unknown Character = '"+gumptext[j]+"'");
    endif
  endfor

  return (points);
endfunction

// Returns the X-Value (Left-Alignment)

function GumpTextLeft(gumptext, x, width)
  return (x);
endfunction

// Returns the X-Value (Right-Alignment)

function GumpTextRight(gumptext, x, width)
  return (x+(width-GumpTextWidthFast(gumptext)));
endfunction

// Returns the X-Value (Mid-Alignment)

function GumpTextMid(gumptext, x, width)
  return (x+CInt((width-GumpTextWidthFast(gumptext))/2));
endfunction

//////////////////////////////////////////////////
// Create_ScrollBar - Erzeugt einen Scrollbalken
//////////////////////////////////////////////////

function Create_ScrollBar(x, y, height, pages, page, layout)
  if (pages>1)
    var x_str:=CStr(x)+" ";
    var button_x_str:="button "+x_str;
    var gumppic_x_str:="gumppic "+x_str;
    var page_before:=" 0 "+CStr(page-1);
    var page_next:=" 0 "+CStr(page+1);

    var y_mark;
    if (pages==page)
      y_mark:=y+height-46;
      layout.append(gumppic_x_str+CStr(y_mark-7)+" 256");
    else
      y_mark:=y+CInt((height-67)/(pages-1))*(page-1)+21;
      layout.append(gumppic_x_str+CStr(y_mark)+" 256");
    endif
    layout.append("gumppic "+CStr(x+1)+" "+CStr(y_mark)+" 254");

    var y_bkg;
    var y_bkg_end;
    if (page>1)
      y_bkg_end:=y+21;
      for (y_bkg:=y_mark-32; y_bkg>y_bkg_end; y_bkg:=y_bkg-32)
        layout.append(button_x_str+CStr(y_bkg)+" 256 256"+page_before);
      endfor;
      layout.append(button_x_str+CStr(y_bkg_end)+" 256 256"+page_before);
      layout.append(button_x_str+CStr(y)+" 250 251"+page_before);
    else
      layout.append(gumppic_x_str+CStr(y)+" 250");
    endif
    if (page<pages)
      y_bkg_end:=y+height-21-32;
      for (y_bkg:=y_mark+25; y_bkg<y_bkg_end; y_bkg:=y_bkg+32)
        layout.append(button_x_str+CStr(y_bkg)+" 256 256"+page_next);
      endfor;
      layout.append(button_x_str+CStr(y_bkg_end)+" 256 256"+page_next);
      layout.append(button_x_str+CStr(y+height-21)+" 252 253"+page_next);
    else
      layout.append(gumppic_x_str+CStr(y+height-21)+" 252");
    endif
  endif

  return (layout);
endfunction