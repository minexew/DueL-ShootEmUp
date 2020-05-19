
#include <stdio.h>
#include <stdlib.h>

#include "gmWP.h"

static FILE* wpFile = NULL;

Function double wOpen ( const char* ccFileName )
{
    wpFile = fopen( ccFileName, "w" );
    return ( wpFile != NULL );
}

Function double wClose ()
{
    if ( wpFile != NULL)
    {
        fclose( wpFile );
        wpFile = NULL;
    }
}

Function double wWriteHeader ()
{
    int i;
    if ( wpFile == NULL )
        return 0;

    i = 0;
    fwrite( "gmWayPt.", 1, 8, wpFile );
    fwrite( &i, 2, 1, wpFile );
    return 1;
}

Function double wStartBank ( double _BankId, double _Count )
{
    bhdr Header;
    if ( wpFile == NULL )
        return 0;
    
    Header.ID = (int)_BankId;
    Header.wpCount = (int)_Count;
    fwrite( &Header, 1, 4, wpFile );
    return 1;
}

Function double wAddPoint ( double _X, double _Y )
{
    WayPoint wp;
    if ( wpFile == NULL )
        return 0;

    wp.x = (int)_X;
    wp.y = (int)_Y;
    fwrite( &wp, 1, 4, wpFile );
    return 1;
}
