#pragma once

/** @file
	Windows BMP から16階調 P/ECE BMP に変換.
	@author zurachu
*/

#include <windows.h>

/**
	P/ECE BMP ヘッダ構造体.
	include/Piece_Bmp.h より引用。
	各要素に入る値は、16階調用に拡張したものとなる。
*/
typedef struct {
	DWORD	head;		///< HEADER   'PBEX'
	DWORD	fsize;		///< ファイル長 （BYTE単位）
	BYTE	bpp;		///< bit深度  （4）
	BYTE	mask;		///< マスクのbit深度  （0/1）
	short	w;			///< X幅		8ピクセル単位厳守
	short	h;			///< Y高さ
	DWORD	buf_size;	///< BMPサイズ	（BYTE単位）
}PBMP_FILEHEADER;

/**
	ヒープを確保して、Windows BMP から16階調 P/ECE BMP に変換したデータを格納.
	@param bi Windows BMP 情報
	@param bmp Windows ビットマップ部分（メモリにはトップダウンで配置）
	@return 格納したヒープ領域（失敗時 NULL）
	@warning 不要になったヒープは free() すること。
*/
unsigned char* pgd16cnv( BITMAPINFOHEADER const* bi, unsigned char const* bmp );

