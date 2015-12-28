/*
 * key.inc - key functions
 */
include "include/client";
include "include/objtype";

var KEYTYPES := { UOBJ_COPPER_KEY,
									UOBJ_GOLD_KEY,
									UOBJ_IRON_KEY,
									UOBJ_MAGIC_KEY,
									UOBJ_RUSTY_IRON_KEY };

/*
 * AllocLockId - allocate a lock ID.
 *
 * Locks are allocated a new lockid when they are created or changed.
 * If a lock's lockid is changed, all old keys will no longer work.
 *
 * TODO: go critical.  The only place this is called is already critical, so...
 */
function AllocLockId()

	set_critical(1);
	var lockid := GetGlobalProperty( "nextlockid" );
	if (!lockid)
		lockid := 1;
	endif
	SetGlobalProperty( "nextlockid", lockid+1 );

	set_critical(0);

	return lockid;
endfunction

// does 'who' have a key matching this lockid?
function FindKey(who, what)

	var lockid := GetObjProperty( what, "lockid" );

	if (!lockid) // not keyed
		return 1;
	endif

	foreach item in EnumerateItemsInContainer( who.backpack )
		if (item.graphic in KEYTYPES)
			if (GetObjProperty( item, "lockid" ) == lockid)
				return item;
			endif
		endif
	endforeach

	return 0;

endfunction