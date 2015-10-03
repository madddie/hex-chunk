#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>

#pragma warning( disable: 4996)

class CToolset
{
protected:

	HWND Window;

	HANDLE Process;

	int PID;

	char _WindowTitle[128];

	char _ConsoleTitle[256];

public:

	CToolset( char* _Process )
	{
		Process = Get( _Process, &PID );

		sprintf( _WindowTitle, "PID: %X - Process: %s\n", PID, _Process );

		SetConsoleTitleA( _WindowTitle );
	}

	HANDLE Get( char* Process, int* _PID )
	{
		HANDLE Snapshot = CreateToolhelp32Snapshot( TH32CS_SNAPPROCESS, 0 );

		PROCESSENTRY32 Processes;

		Processes.dwSize = sizeof( PROCESSENTRY32 );

		do if ( !strcmp( Processes.szExeFile, Process ) )
		{

			*_PID = Processes.th32ProcessID;

			return OpenProcess( PROCESS_ALL_ACCESS, 0, Processes.th32ProcessID );

		} while ( Process32Next( Snapshot, &Processes ) );

		return INVALID_HANDLE_VALUE;
	}

	/* reads a region in the processes memory at the interpreted size and returns a pointer to the newly allocated space/return buffer */
	byte* Read(void* _Address, int Size)
	{
		void* _ReturnRegion = malloc(Size);

		ReadProcessMemory(Process, _Address, _ReturnRegion, Size, 0);

		return (byte*)_ReturnRegion;
	}
};