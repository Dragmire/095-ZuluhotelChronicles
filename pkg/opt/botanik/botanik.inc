function counttree(leaves)

  var treecount:=0,cfg:=ReadConfigFile("tree"),restype:=0;

  foreach item in ListItemsNearLocation(CInt(leaves.x),CInt(leaves.y),CInt(leaves.z),3)
    restype:=cfg[item.objtype].product;
    if (restype) treecount:=treecount+1; endif
  endforeach

  return treecount;

endfunction

function fixtree(tree,regrow,amt)
SetObjProperty(tree,"amt",amt);
SetObjProperty(tree,"death",0);
start_script("regrow",{tree,regrow});
endfunction

function DestroyTree(me, tree)
if (YesNo(me,"Destroy it?")) DestroyItem(tree); endif
endfunction