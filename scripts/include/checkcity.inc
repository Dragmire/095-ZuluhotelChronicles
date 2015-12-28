use os;
use uo;

function CheckCity(item)

  if ( item.x>=1244 && item.y>=1530 && item.x <= 1704 && item.y <= 1758)
      return 1; // Britain
   
    elseif ( item.x>=4379 && item.y>=1045 && item.x <= 4487 && item.y <= 1178)
      return 1; // Moonglow

    elseif ( item.x>=5638 && item.y>=3083 && item.x<=5799 && item.y<=3328)
      return 1; // Papua
    elseif ( item.x>=5799 && item.y>=3121 && item.x<=5822 && item.y<=3327)
      return 1; // Papua
    elseif ( item.x>=5137 && item.y>=3948 && item.x<=5196 && item.y<=4082)
      return 1; // Delucia
    elseif ( item.x>=5196 && item.y>=3923 && item.x<=5322 && item.y<=4085)
      return 1; // Delucia

    elseif ( item.x>=1294 && item.y>=3664 && item.x <= 1506 && item.y <= 3886)
      return 1; // Jhelom
     
    elseif ( item.x>=494 && item.y>=926 && item.x <= 600 && item.y <= 1034)
      return 1; // Yew
     
    elseif ( item.x>=590 && item.y>=796 && item.x <= 670 && item.y <= 886)
      return 1; // Empath Abbey
     
    elseif ( item.x>=2394 && item.y>=370 && item.x <= 2624 && item.y <= 632)
      return 1; // Minoc

    elseif ( item.x>=1794 && item.y>=2638 && item.x <= 2136 && item.y <= 2902)
      return 1; // Trinsic

    elseif ( item.x>=538 && item.y>=2106 && item.x <= 686 && item.y <= 2274)
      return 1; // Skara Brae

    elseif ( item.x>=3646 && item.y>=2040 && item.x <= 3814 && item.y <= 2280)
      return 1; // Magincia

    elseif ( item.x>=3588 && item.y>=2446 && item.x <= 3762 && item.y <= 2690)
      return 1; // Occlo

    elseif ( item.x>=2612 && item.y>=2082 && item.x <= 2772 && item.y <= 2256)
      return 1; // Buccaneers Den

    elseif ( item.x>=3496 && item.y>=1062 && item.x <= 3808 && item.y <= 1400)
      return 1; // Nujelm

    elseif ( item.x>=2794 && item.y>=634 && item.x <= 3026 && item.y <= 1000)
      return 1; // Vesper

    elseif ( item.x>=2206 && item.y>=1116 && item.x <= 2290 && item.y <= 1236)
      return 1; // Cove

    elseif ( item.x>=5120 && item.y>=0 && item.x <= 5374 && item.y <= 254)
      return 1; // Wind

    elseif ( item.x>=5376 && item.y>=1081 && item.x <=6142 && item.y <= 1278)
      return 1; // Green Acres
endif

return 0;
endfunction
