#include "pgd16cnv.h"

#include <windows.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>

/**
	BITMAPINFOHEADER Ç©ÇÁ PBMP_FILEHEADER Çê∂ê¨ÇµÇƒäiî[.
	@param dst äiî[êÊ
	@param bi Windows BMP èÓïÒ
	@return P/ECE BMP Ç…ïœä∑Ç≈Ç´Ç»Ç¢èÍçá false
*/
static bool get_pbmp_file_header_to( PBMP_FILEHEADER* dst, BITMAPINFOHEADER const* bi )
{
	if( ( bi->biWidth % 8 == 0 )	// ïùÇÕ8ÉsÉNÉZÉãíPà 
	 && ( bi->biBitCount == 4 || bi->biBitCount == 8 ) // 4bit or 8bit
	 && ( bi->biCompression == BI_RGB ) )	// ñ≥à≥èk
	{
		strncpy( reinterpret_cast< char* >( &dst->head ), "XEBP", 4 );
		dst->bpp = 4;
		dst->mask = ( bi->biBitCount == 8 )? 1 : 0;
		dst->w = static_cast< short >( bi->biWidth );
		dst->h = static_cast< short >( abs( bi->biHeight ) );
		dst->buf_size = ( dst->bpp + dst->mask ) * dst->w * dst->h / 8;
		dst->fsize = sizeof(PBMP_FILEHEADER) + dst->buf_size;
		return true;
	}
	return false;
}

unsigned char* pgd16cnv( BITMAPINFOHEADER const* bi, unsigned char const* bmp )
{
	PBMP_FILEHEADER header;
	if( get_pbmp_file_header_to( &header, bi ) )
	{
		unsigned char* const p = static_cast< unsigned char* >( malloc( header.fsize ) );
		if( p )
		{
			memcpy( p, &header, sizeof(PBMP_FILEHEADER) );
			unsigned char* buf = p + sizeof(PBMP_FILEHEADER);
			unsigned char* mask = buf + header.bpp * header.w * header.h / 8;
			if( bi->biBitCount == 8 )	// 8bit Å® É}ÉXÉNóL/ñ≥16äKí≤
			{
				for( int i = 0; i < header.w * header.h; i++ )
				{
					*buf <<= 4;
					*buf |= ( *bmp & 0xF0 )? 0 : *bmp;
					if( i != 0 && i % 2 == 0 ) { buf++; }
					if( header.mask )
					{
						*mask <<= 1;
						*mask |= ( *bmp & 0xF0 )? 0 : 1;
						if( i != 0 && i % 8 == 0 ) { mask++; }
					}
					bmp++;
				}
			}
			else						// 4bit Å® É}ÉXÉNñ≥16äKí≤
			{
				memcpy( buf, bmp, header.w * header.h / 2 );
			}
			return p;
		}
	}
	return NULL;
}

