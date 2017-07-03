#pragma once

/** @file
	Windows BMP 操作の補助.
	@author zurachu
*/

#include <windows.h>

/**
	ヒープを確保して Windows BMP ファイルを読み込み.
	@param filename BMP ファイル名
	@return 読み込んだヒープ領域（失敗時 NULL）
	@warning 不要になったヒープは free() すること。
*/
unsigned char* Bmp_FileReadAlloc( char const* filename );

/**
	Windows BMP のトップダウン、ボトムアップを入れ替える.
	@param bi Windows BMP 情報
	@param bmp Windows ビットマップ部分
*/
bool Bmp_UpsideDown( BITMAPINFOHEADER* bi, unsigned char* bmp );

