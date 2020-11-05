#include <cstring>
#include <iostream>
#include <fstream>

int parser( char * filename )
{
    uint32_t length;
    uint64_t dataLength;
    char type[ 5 ];
    char * data;
    data = NULL;
    memset( type, 0, 5 );
    std::ifstream stream;

    stream.open( filename, std::ios::binary | std::ios::in );

    if( stream.is_open() == false || stream.good() == false )
        std::cout << "Couldn't open media file" << std::endl;

    while( !stream.eof() )
    {
        uint8_t c[ 4 ];
        stream.read( ( char * )c, 4 );
        length = ( uint32_t )c[ 0 ] << 24 | ( uint32_t )c[ 1 ] << 16 | ( uint32_t )c[ 2 ] << 8 | ( uint32_t )c[ 3 ];

        dataLength = 0;

        stream.read( ( char * )type, 4 );

        if( length == 1 )
        {
                uint8_t  c[ 4 ];
                stream.read( ( char * )c, 4 );
                dataLength = ( uint32_t )c[ 0 ] << 24 | ( uint32_t )c[ 1 ] << 16 | ( uint32_t )c[ 2 ] << 8 | ( uint32_t )c[ 3 ] - 16;
        }
        else
        {
            dataLength = length - 8;
        }

        if( strcmp( type, "ftyp" ) == 0 ||
                strcmp( type, "cmov" ) == 0 ||
                strcmp( type, "cmvd" ) == 0 ||
                strcmp( type, "co64" ) == 0 ||
                strcmp( type, "ctts" ) == 0 ||
                strcmp( type, "dcom" ) == 0 ||
                strcmp( type, "dinf" ) == 0 ||
                strcmp( type, "edts" ) == 0 ||
                strcmp( type, "elst" ) == 0 ||
                strcmp( type, "fiel" ) == 0 ||
                strcmp( type, "free" ) == 0 ||
                strcmp( type, "gmhd" ) == 0 ||
                strcmp( type, "hdlr" ) == 0 ||
                strcmp( type, "iods" ) == 0 ||
                strcmp( type, "ipro" ) == 0 ||
                strcmp( type, "junk" ) == 0 ||
                strcmp( type, "mdat" ) == 0 ||
                strcmp( type, "mdhd" ) == 0 ||
                strcmp( type, "mdia" ) == 0 ||
                strcmp( type, "meta" ) == 0 ||
                strcmp( type, "mfra" ) == 0 ||
                strcmp( type, "minf" ) == 0 ||
                strcmp( type, "moof" ) == 0 ||
                strcmp( type, "moov" ) == 0 ||
                strcmp( type, "mvex" ) == 0 ||
                strcmp( type, "mvhd" ) == 0 ||
                strcmp( type, "pict" ) == 0 ||
                strcmp( type, "pnot" ) == 0 ||
                strcmp( type, "rdrf" ) == 0 ||
                strcmp( type, "rmcd" ) == 0 ||
                strcmp( type, "rmcs" ) == 0 ||
                strcmp( type, "rmda" ) == 0 ||
                strcmp( type, "rmdr" ) == 0 ||
                strcmp( type, "rmqu" ) == 0 ||
                strcmp( type, "rmra" ) == 0 ||
                strcmp( type, "rmvc" ) == 0 ||
                strcmp( type, "sinf" ) == 0 ||
                strcmp( type, "skip" ) == 0 ||
                strcmp( type, "smhd" ) == 0 ||
                strcmp( type, "stbl" ) == 0 ||
                strcmp( type, "stco" ) == 0 ||
                strcmp( type, "stsc" ) == 0 ||
                strcmp( type, "stsd" ) == 0 ||
                strcmp( type, "stss" ) == 0 ||
                strcmp( type, "stsz" ) == 0 ||
                strcmp( type, "stts" ) == 0 ||
                strcmp( type, "tkhd" ) == 0 ||
                strcmp( type, "traf" ) == 0 ||
                strcmp( type, "trak" ) == 0 ||
                strcmp( type, "uuid" ) == 0 ||
                strcmp( type, "vmhd" ) == 0 ||
                strcmp( type, "wide" ) == 0 ||
                strcmp( type, "wfex" ) == 0
        )
        {
            std::cout << "Atom = " << type << "  " << dataLength << std::endl;
            stream.ignore( dataLength );

            continue;
        }
    }

    if( stream.is_open() )
        stream.close();

        return 0;
}

int main( int argc, char * argv[] )
{
    if( argc != 2 )
    {
        std::cout << "Please provide a media file" << std::endl;
    }

    parser( argv[ 1 ] );
    return 0;
}
