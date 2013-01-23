/*************************************************************************** 
 dll_invoker.c - example program used with Guid Generator Library
 
     	this program loads the "Generator.dll" library and invokes exposed methods,
		writes the output to the console and terminates.
 
 ***************************************************************************/

// ----------[Definitions]----------
#define WIN32_LEAN_AND_MEAN

// ----------[Includes]----------

#include <windows.h> /// Windows DLL Loading Routines
#include <stdio.h>  // Input/Output
#include <stdlib.h> // EXIT_SUCCESS & EXIT_FAILURE

// ----------[Global Constants]----------

const wchar_t * GeneratorDll = TEXT( "Generator.dll" );

const char * GenerateGuidFunc = "_Generate@0";
const char * EmptyGuidFunc = "_Empty@0";
const char * FromStringAFunc = "_FromStringA@4";
const char * FromStringWFunc = "_FromStringW@4";

const char * GuidOutputFormat = "{%08x-%04x-%04x-%02x%02x-%02x%02x%02x%02x%02x%02x}";

const wchar_t * GuidWideStringToConvert = TEXT( "{FADDEC2A-B4C1-47A4-8065-14C038E4AD67}" );
const char * GuidAsciiStringToConvert = "{FADDEC2A-B4C1-47A4-8065-14C038E4AD67}";

// ----------[Local Prototypes]----------

void DisplayGuid( GUID );
void DisplayEmptyGuid();
void DisplayGeneratedGuid();
void DisplayWideParsedGuid();
void DisplayAsciiParsedGuid();

void Initialize();
void ShutDown();
void Execute();

// ----------[External Prototypes]----------

typedef GUID ( __stdcall *GetGUID ) ();
typedef GUID ( __stdcall *ParseWideGUID ) ( const wchar_t * );
typedef GUID ( __stdcall *ParseAsciiGUID ) ( const char * );

// ----------[Global Variables]----------

HINSTANCE hLibInst = 0;
int nDisplayCount = 100;

// ----------[Entry Point]----------

int main( int argc, char *argv[] )
{
	Initialize();

	Execute();

	ShutDown();
}

// ----------[Functions]----------

void Initialize()
{
	hLibInst = 
		LoadLibrary( GeneratorDll );
}

void ShutDown()
{
	if( hLibInst != NULL )
	{
		FreeLibrary( hLibInst );
	}

	exit ( EXIT_SUCCESS );
}

void Execute()
{
	int index;

	DisplayEmptyGuid();

	for( index = 0; index < nDisplayCount; index++ )
	{
		DisplayGeneratedGuid();
	}

	DisplayWideParsedGuid();
	DisplayAsciiParsedGuid();

	getchar();
}

void DisplayGeneratedGuid()
{
	GetGUID _newGuid = 
		( GetGUID ) GetProcAddress( hLibInst, GenerateGuidFunc );

	GUID newGuid = _newGuid();

	DisplayGuid( newGuid );
}

void DisplayEmptyGuid()
{
	GetGUID _emptyGuid = 
		( GetGUID ) GetProcAddress( hLibInst, EmptyGuidFunc );

	GUID newGuid = _emptyGuid();

	DisplayGuid( newGuid );
}

void DisplayWideParsedGuid()
{
	ParseWideGUID _parseGuid = 
		( ParseWideGUID ) GetProcAddress( hLibInst, FromStringWFunc );

	GUID newGuid = _parseGuid( GuidWideStringToConvert );

	DisplayGuid( newGuid );
}

void DisplayAsciiParsedGuid()
{
	ParseAsciiGUID _parseGuid = 
		( ParseAsciiGUID ) GetProcAddress( hLibInst, FromStringAFunc );

	GUID newGuid = _parseGuid( GuidAsciiStringToConvert );

	DisplayGuid( newGuid );
}

static char * ConvertGuidToString( const GUID * guid )
{
	static char output[ 39 ];
	static size_t len;

	if( len == 0 )
	{
		len = sizeof( output );
		ZeroMemory( &output, len );
	}

	sprintf_s
	(
		output,
		len,
		GuidOutputFormat,
		guid->Data1, guid->Data2, guid->Data3,
		guid->Data4[ 0 ], guid->Data4[ 1 ], guid->Data4[ 2 ], guid->Data4[ 3 ], 
		guid->Data4[ 4 ], guid->Data4[ 5 ], guid->Data4[ 6 ], guid->Data4[ 7 ]
	);

	return output;
}

static void DisplayGuid( GUID guid )
{
	printf( "%s\n", ConvertGuidToString( &guid ) );
}