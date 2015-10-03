/*  
basically this is the concept:

have a simple CLI to receive a few parameters

hexchunk -_Process -_Address -Size

_Process will be the process name.

_Address will be a pointer (in this case, an integer representing the address in memory the chunk should be read).

Size will be an integer representing the number of bytes to be read

*/

#include "toolset.h"

CToolset* Toolset;

void main( int Argc, char** Args )
{
	switch ( Argc )
	{
	case 1:
		printf( "missing parameter _Process\n" );
		exit( 1 );
		break;
	case 2:
		printf( "missing parameter _Address\n" );
		exit( 1 );
		break;
	case 3:
		printf( "missing parameter Size\n" );
		exit( 1 );
		break;
	}

	printf("[ hexchunk - a simple hex block reader ]\n\n");

	Toolset = new CToolset ( Args[ 1 ] );

	byte* _Buffer = Toolset->Read( ( (void*)strtol( Args[ 2 ], 0, 16 ) ), atoi( Args[ 3 ] ));

	for (int i = 0; i < atoi( Args[ 3 ] ); ++i)
	{
		if (i % 26 == 0)
			printf("\n");

		if (_Buffer[i] < 16)
			printf("0");

		printf("%X ", _Buffer[i]);
	}
}