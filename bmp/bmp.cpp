#include "bmp.h"

#include <windows.h>
#include <cstdio>
#include <cstdlib>

unsigned char* Bmp_FileReadAlloc( char const* filename )
{
	FILE* fp = fopen( filename, "rb" );
	if( fp )
	{
		BITMAPFILEHEADER bf;
		fread( &bf, 1, sizeof(BITMAPFILEHEADER), fp );
		if( !strncmp( reinterpret_cast< char* >( &bf.bfType ), "BM", 2 ) )
		{
			unsigned char* const p = static_cast< unsigned char* >( malloc( bf.bfSize ) );
			if( p )
			{
				fseek( fp, 0, SEEK_SET );
				fread( p, 1, bf.bfSize, fp );
				fclose( fp );
				return p;
			}
		}
		fclose( fp );
	}
	return NULL;
}

bool Bmp_UpsideDown( BITMAPINFOHEADER* bi, unsigned char* bmp )
{
	int const byte_per_line = ( ( bi->biBitCount * bi->biWidth / 8 ) + 3 ) & ~3;
	int const height = abs( bi->biHeight );
	int const bmp_size = byte_per_line * height;
	unsigned char* const temp = static_cast< unsigned char* >( malloc( bmp_size ) );
	if( temp )
	{
		memcpy( temp, bmp, bmp_size );
		for( int y = height - 1; y >= 0; y-- )
		{
			memcpy( bmp, temp + byte_per_line * y, byte_per_line );
			bmp += byte_per_line;
		}
		free( temp );
		bi->biHeight = -bi->biHeight;
		return true;
	}
	return false;
}

