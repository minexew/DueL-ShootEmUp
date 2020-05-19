
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

#include "gmWP.h"

WayPoint* BankData = NULL;
unsigned BankCount = 0;
long fLen = 0;
FILE* wpFile = NULL;

fhdr FileHeader;
bhdr BankHeader;

int CheckHeader ()
{
    return ( memcmp( FileHeader.iHdr, "gmWayPt.", 8 ) == 0 && FileHeader.verif == 0 );
}

Function double Open ( const char* ccFileName )
{
    wpFile = fopen( ccFileName, "r" );
    if ( wpFile == NULL )
        return 0;
    else
    {
        fseek( wpFile, 0, SEEK_END );
        fLen = ftell( wpFile );
        return 1;
    }
}

Function double Close ()
{
    if ( wpFile != NULL)
    {
        fclose( wpFile );
        wpFile = NULL;
    }
}

Function double ReadBank ( double _BankId )
{
    unsigned Bank;
    
    if ( wpFile == NULL )  // is da file open'd?
        return 0;
    Bank = (unsigned)_BankId;
    fseek( wpFile, 0, SEEK_SET );  // jump to start
    fread( &FileHeader, 1, 10, wpFile );
    if ( !CheckHeader() ) return 0;
    while ( ftell( wpFile ) < fLen )
    {
        fread( &BankHeader, 1, 4, wpFile );
        if ( BankHeader.ID == Bank )
        {
            BankData = malloc( BankHeader.wpCount * sizeof(WayPoint) );
            BankCount = fread( BankData, sizeof(WayPoint), BankHeader.wpCount, wpFile );
            return 1;
        }
        else
            fseek( wpFile, BankHeader.wpCount * sizeof(WayPoint), SEEK_CUR );
    }
    
    return 0;
}

Function double GetCount()
{
    return BankCount;
}

Function double GetX( double i )
{
    return BankData[ (int)i ].x;
}

Function double GetY( double i )
{
    return BankData[ (int)i ].y;
}

/*Function void HelloWorld ()
{
    MessageBox (0, "Hello World from DLL!\n", "Hi", MB_ICONINFORMATION);
}*/


BOOL APIENTRY DllMain (HINSTANCE hInst     /* Library instance handle. */ ,
                       DWORD reason        /* Reason this function is being called. */ ,
                       LPVOID reserved     /* Not used. */ )
{
    switch (reason)
    {
        case DLL_PROCESS_ATTACH:
            break;

        case DLL_PROCESS_DETACH:
            if ( wpFile != NULL )
                fclose( wpFile );
            break;

        case DLL_THREAD_ATTACH:
            break;

        case DLL_THREAD_DETACH:
            break;
    }

    /* Returns TRUE on success, FALSE on failure */
    return TRUE;
}
