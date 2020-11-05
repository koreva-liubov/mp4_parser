#include <cstring>
#include <iostream>
#include <fstream>

uint32_t uint32BE(uint8_t* string) {
    return ((string[0] & 0xff) << 24 | (string[1] & 0xff) << 16 | (string[2] & 0xff) << 8 | string[3] & 0xff) << 0;
}

int parser( char * filename )
{
    uint32_t length;
    uint64_t dataLength;
    char type[ 5 ];
    char * data;
    data = NULL;
    memset( type, 0, 5 );
    std::ifstream stream;
    int track_count = 0;

    stream.open( filename, std::ios::binary | std::ios::in );

    if( stream.is_open() == false || stream.good() == false )
        std::cout << "Couldn't open media file" << std::endl;

    while( !stream.eof() )
    {
        uint8_t c[ 4 ];

        // Read atom length
        stream.read( ( char * )c, 4 );
        length = uint32BE((uint8_t*)c);

        dataLength = length - 8;

        // Read atom name
        stream.read( ( char * )type, 4 );

        if( strcmp( type, "trak" ) == 0 )
        {
            track_count++;
            std::cout << "Atom " << type << ", length: " << length << std::endl;
            continue;
        }

        // Nested atoms
        if( strcmp( type, "moov" ) == 0 ||
                strcmp( type, "mdia" ) == 0 ||
                strcmp( type, "minf" ) == 0 ||
                strcmp( type, "stbl" ) == 0 ||
                strcmp( type, "stsd" ) == 0
        )
        {
            std::cout << "Atom " << type << ", length: " << length << std::endl;
            continue;
        }

        if( strcmp( type, "mp4a" ) == 0 || strcmp( type, "avc1" ) == 0 || strcmp( type, "ac-3" ) == 0 )
        {
            stream.ignore( dataLength );
            std::cout << "Atom " << type << ", length: " << length  << " for track number " << track_count << std::endl;
            continue;
        }

         if( strcmp( type, "ftyp" ) == 0 ||
                strcmp( type, "mvhd" ) == 0 ||
                strcmp( type, "iods" ) == 0 ||
                strcmp( type, "mdat" ) == 0 ||
                strcmp( type, "tkhd" ) == 0 ||
                strcmp( type, "edts" ) == 0 ||
                strcmp( type, "mdhd" ) == 0 ||
                strcmp( type, "hdlr" ) == 0 ||
                strcmp( type, "hglr" ) == 0 ||
                strcmp( type, "vmhd" ) == 0 ||
                strcmp( type, "dinf" ) == 0 ||
                strcmp( type, "smhd" ) == 0 ||
                strcmp( type, "dref" ) == 0 ||
                strcmp( type, "stts" ) == 0 ||
                strcmp( type, "ctts" ) == 0 ||
                strcmp( type, "gmhd" ) == 0 ||
                strcmp( type, "stss" ) == 0 ||
                strcmp( type, "stsc" ) == 0 ||
                strcmp( type, "stsz" ) == 0 ||
                strcmp( type, "tmcd" ) == 0 ||
                strcmp( type, "stco" ) == 0 ||
                strcmp( type, "udta" ) == 0 ||
                strcmp( type, "cmov" ) == 0 ||
                strcmp( type, "cmvd" ) == 0 ||
                strcmp( type, "c064" ) == 0 ||
                strcmp( type, "dcom" ) == 0 ||
                strcmp( type, "elst" ) == 0 ||
                strcmp( type, "fiel" ) == 0 ||
                strcmp( type, "ipro" ) == 0 ||
                strcmp( type, "junk" ) == 0 ||
                strcmp( type, "meta" ) == 0 ||
                strcmp( type, "mfra" ) == 0 ||
                strcmp( type, "moof" ) == 0 ||
                strcmp( type, "mvex" ) == 0 ||
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
                strcmp( type, "traf" ) == 0 ||
                strcmp( type, "uuid" ) == 0 ||
                strcmp( type, "wide" ) == 0 ||
                strcmp( type, "wfex" ) == 0 ||            
                strcmp( type, "free" ) == 0
        )
        {
            std::cout << "Atom " << type << ", length: " << length << std::endl;
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
