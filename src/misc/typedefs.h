#pragma once

typedef unsigned char uint_8;
typedef unsigned short uint_16;
typedef unsigned int uint_32;
typedef unsigned long long uint_64;

/*
│ 180
┤

╢
╖
╕
╣
║
╗
╝
╜
╛
┐
└

┬
├
┼

╟
╚
╔
╩
╦
╠
═
╬



╙
╘
╒
╓
╙
╘
╫
╪
┘
┌
▉
▄

*/

char[] M_constToArray(const char* str){
	uint_8* charPtr = (uint_8*)str;
  	uint_16 index = D_CursorPosition;
  	char chr[128];
  	while(*charPtr != 0){
    	switch (*charPtr) {
      		case '│':
      			chr[i] = (char)180;
      		default:
      			chr[i] = *charPtr;
    	}
    	charPtr++;
  	}
  	return chr;
}