// FileExercise.cpp : �������̨Ӧ�ó������ڵ㡣
//
//
#include "stdafx.h"
//#include "scanfolder.h"
//
//#include "iconv.h"
//
//int _tmain(int argc, _TCHAR* argv[])
//{
//	dfsFolder("E:\\����������ǧ�꣨�Ŵ���\\",".txt");
//	//dfsFolder("E:\\Java\\jre6\\",".txt");
//	getchar();
//	return 0;
//}
//

#include "iconv.h"
#define OUTLEN 255
int u2g(char *inbuf,size_t inlen,char *outbuf,size_t outlen) ;
int g2u(char *inbuf,size_t inlen,char *outbuf,size_t outlen) ;
void printfCharAsHex(char *string);

int  main() 
{ 
	char in_utf8[] = {0xe6, 0xad, 0xa3, 0xe5, 0x9c, 0xa8, 0xe5, 0xae, 0x89, 0xe8, 0xa3, 0x85, '\0'}; 
	char in_gb2312[] = {0xd5, 0xfd, 0xd4, 0xda, 0xb0, 0xb2, 0xd7, 0xb0, '\0'}; 
	char out[OUTLEN]; 

	//unicode��תΪgb2312�� 
	int rc = u2g(in_utf8,strlen(in_utf8),out,OUTLEN); 
	printf("unicode-->gb2312 out=\n");
	printfCharAsHex(out);
	//gb2312��תΪunicode�� 
	rc = g2u(in_gb2312,strlen(in_gb2312),out,OUTLEN); 
	printf("gb2312-->unicode out=\n");
	printfCharAsHex(out);
	getchar();
	return 0;
} 
//����ת��:��һ�ֱ���תΪ��һ�ֱ��� 
int code_convert(char *from_charset,char *to_charset,const char *inbuf,size_t* inlen,char *outbuf,size_t* outlen) 
{ 
	iconv_t cd; 
	int rc; 
	char **pout = &outbuf; 

	cd = iconv_open(to_charset,from_charset); 
	if (cd==0) return -1; 
	memset(outbuf,0,*outlen); 
	if (iconv(cd, &inbuf, inlen, pout, outlen) == -1) return -1; 
	iconv_close(cd); 
	return 0; 
} 
//UNICODE��תΪGB2312�� 
int u2g(char *inbuf,size_t inlen,char *outbuf,size_t outlen) 
{ 
	return code_convert("utf-8","gb2312",inbuf,&inlen,outbuf,&outlen); 
} 
//GB2312��תΪUNICODE�� 
int g2u(char *inbuf,size_t inlen,char *outbuf,size_t outlen) 
{ 
	return code_convert("gb2312","utf-8",inbuf,&inlen,outbuf,&outlen);

}
void printfCharAsHex(char *string)
{
	do
	{
		printf("%02x ", *string);
		string++;
	}while(*string != '\0');
	
	printf("\n");
}
