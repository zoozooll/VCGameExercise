#include "CharsetUtils.h"
#include "stdafx.h"
#include "iconv.h"
#include "uchardet.h"

#define BUFFER_SIZE_CHARDED 65536

int code_convert(char *from_charset,char *to_charset,const char *inbuf,size_t* inlen,char *outbuf,size_t* outlen) 
{ 
	iconv_t cd; 
	int rc; 
	//char **pout = &outbuf; 

	cd = iconv_open(to_charset,from_charset); 
	if (cd==0) return -1; 
	memset(outbuf,0,*outlen); 
	if (iconv(cd, &inbuf, inlen, &outbuf, outlen) == -1) return -1; 
	iconv_close(cd); 
	return 0; 
} 

void printfCharAsHex(const char *string)
{
	do
	{
		printf("%02x ", *string);
		string++;
	}while(*string != '\0');
	
	printf("\n");
}

/*
ansi.txt:       c4      e3      77
unicode.txt:    ff      fe      60
ubigendian.txt: fe      ff      4f
utf8.txt:       ef      bb      bf
*/
void getEncoding(const char* file, char * result)
{
	 FILE *fp = fopen(file, "r");

    unsigned char *buf1 = (unsigned char*)malloc(sizeof(unsigned char)*3);

    int i;

    if(fp == NULL)

    {
        printf("open file [%s] failed.\n", file);
        return;
    }
    fread(buf1, sizeof(unsigned char), 3, fp);
    fclose(fp);

    if (buf1[0] == 0xEF && buf1[1] == 0xBB && buf1[2] == 0xBF)
	{
		result = "UTF-8";
	}
	else if (buf1[0] == 0xff && buf1[1] == 0xfe)
	{
		result = "unicode";
	}
	else if (buf1[0] == 0xfe && buf1[1] == 0xff)
	{
		result = "unicode-bigendian";
	}
	else 
	{
		result = "ANSI";
	}

    free(buf1);
}

void getEncodingFromFile(FILE *fp, char * result)
{
	/*fseek(stream, 0, SEEK_SET);
	unsigned char *buf1 = (unsigned char*)malloc(sizeof(unsigned char)*3);

    int i;

    if(stream == NULL)

    {
        return;
    }
    fread(buf1, sizeof(unsigned char), 3, stream);

	printf("%x %x %x\n", buf1[0], buf1[1], buf1[2]);

    if (buf1[0] == 0xEF && buf1[1] == 0xBB && buf1[2] == 0xBF)
	{
		sprintf(result, "%s","UTF-8");
	}
	else if (buf1[0] == 0xff && buf1[1] == 0xfe)
	{
		sprintf(result, "%s","unicode");
	}
	else if (buf1[0] == 0xfe && buf1[1] == 0xff)
	{
		sprintf(result, "%s","unicode-bigendian");
	}
	else 
	{
		sprintf(result, "%s","ANSI");
	}
	fseek(stream, 0, SEEK_SET);
    free(buf1);*/

	uchardet_t handle = uchardet_new();
	char *buffer = (char*)malloc(sizeof(char)*BUFFER_SIZE_CHARDED);
    while (!feof(fp))
    {
        size_t len = fread(buffer, 1, BUFFER_SIZE_CHARDED, fp);
        int retval = uchardet_handle_data(handle, buffer, len);
        if (retval != 0)
        {
            fprintf(stderr, "Handle data error.\n");
            exit(0);
        }
    }
    uchardet_data_end(handle);

    const char * charset = uchardet_get_charset(handle);
    if (*charset)
    	//printf("%s\n", charset);
		sprintf(result, "%s",charset);
	else
		//printf("ascii/unknown\n");
		sprintf(result, "%s","ascii/unknown\n");
	fseek(fp, 0, SEEK_SET);
	free(buffer);
    uchardet_delete(handle);
}
