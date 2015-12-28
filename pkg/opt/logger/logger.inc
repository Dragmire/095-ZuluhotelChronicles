use os;
use uo;

include "include/eventid";

var buffer := {};

function LogLine( byref line )
	if( len( buffer ) >= 0 )
		buffer.append( CStr( line ) );
	else
		buffer:={ CStr( line ) };
	endif
endfunction

function LogCommit( byref file )
	var manager := getprocess( CInt(GetGlobalProperty( "#LoggerPID" )) );
	if( manager )
		manager.SendEvent( { file + ".log", buffer } );
	else
		syslog( "Logger: no logger is listening." );
	endif
	buffer := {};
endfunction

/*
LogLine("Today is a good day, this is said.");
LogLine("My name is, my name is, my name is Staff.");
LogCommit("staff");
*/