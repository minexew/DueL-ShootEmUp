
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "gmWP.h"

static FILE* File;
static long fLen, Hash, HashT, BuffLen;
static char Buffer[256];

const static unsigned long HashPattern = 0x4B01F95A;

unsigned long HashBuffer( const char* Buffer )
{
    long i, BuffLen = strlen( Buffer );
    HashT = 0;
    for ( i = 0; i < BuffLen; i++ ) 
        HashT += i * Buffer[i];
    
    return HashT ^ HashPattern;
}

void EncodeBuffer( char* Buffer )
{
    long i;
    BuffLen = strlen( Buffer );
    for ( i = 0; i < BuffLen; i++ )
        Buffer[i] ^= 0xCA;
}

Function double SafeSave( const char* ccFileName, const char* ccData )
{
    strcpy( Buffer, ccData );
    
    File = fopen( ccFileName, "w" );
    if ( File == NULL )
        return 0;

    BuffLen = strlen( Buffer );
    Hash = HashBuffer( Buffer );
    EncodeBuffer( Buffer );
    
    fwrite( &Hash, 4, 1, File );
    fwrite( Buffer, 1, BuffLen, File );
    fclose( File );
    return 1;
}

Function const char* SafeLoad( const char* ccFileName, const char* ccDefault )
{
    File = fopen( ccFileName, "r" );
    if ( File == NULL )
        return ccDefault;
    
    fseek( File, 0, SEEK_END );
    fLen = ftell( File );
    if ( fLen < 4 )
        return ccDefault;
    fseek( File, 0, SEEK_SET );
    fread( &Hash, 4, 1, File );
    Buffer[ fread( Buffer, 1, fLen - 4, File ) ] = 0;
    fclose( File );
    
    EncodeBuffer( Buffer );
    if ( Hash != HashBuffer( Buffer ) )
        return ccDefault;
    
    return Buffer;
}
