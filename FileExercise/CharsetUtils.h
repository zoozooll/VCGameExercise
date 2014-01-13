#include "stdafx.h"

#pragma once


void printfCharAsHex(const char *string);

//代码转换:从一种编码转为另一种编码 
int code_convert(char *from_charset,char *to_charset,const char *inbuf,size_t* inlen,char *outbuf,size_t* outlen) ;

void getEncoding(const char* file, char * output);

void getEncodingFromFile(FILE *file, char * output);