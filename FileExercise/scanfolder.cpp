#include "stdafx.h"
#include "scanfolder.h"
#include "CharsetUtils.h"

#define BUFFER_SIZE 1024

static int g2u(char *inbuf,size_t inlen,char *outbuf,size_t outlen) ;

void dfsFolder(const char* folderPath, const char* extent)
{

	 _finddata_t files; 

	 int File_Handle; 

	 int i=0;  

	 char path[100];

	 sprintf(path, "%s\\*%s", folderPath, extent);

	 File_Handle = _findfirst(path, &files); 

	 if(File_Handle==-1) 
	 {  
		 printf("error\n"); 
		 return ; 
	 } 
	 do 
	 {  
		 printf("%s \n",files.name); 
		 //sprintf(path, "%s%s", folderPath, files.name);
		 openAndReadFile(folderPath, files.name);
		 i++;
	 } while(!_findnext(File_Handle,&files)); 
	 _findclose(File_Handle);  
	 printf("Find %d files\n",i);  

}

void openAndReadFile(const char* folderPath, const char* fileName)
{
	//int ch;
	FILE *infp, *outfp;
	char charset[50], outTemp[BUFFER_SIZE], inPath[250], outPath[250];
	sprintf(inPath, "%s\\%s", folderPath, fileName);
	infp = fopen(inPath, "r");
	
	
	char *buf = (char*)malloc(sizeof(char)*BUFFER_SIZE);	// the buffer of iostream.
	if (infp == NULL)
	{
		return;
	}

	//while ((ch = getc(fp)) != EOF)
	//{
	//	printf("%x ", ch);
	//	//putchar(ch);
	//}

	getEncodingFromFile(infp,charset);
	if (!strcmp(charset, "UTF-8"))
	{
		return;
	}
	sprintf(outPath, "%s_utf\\%s", folderPath, fileName);
	outfp = fopen(outPath, "w");
	while(fgets(buf, BUFFER_SIZE, infp) != NULL)
	{
		
		//printf(buf);
		g2u(buf, (size_t)strlen(buf),outTemp, BUFFER_SIZE);
		fputs(outTemp, outfp);
	}
	fclose(infp);
	fclose(outfp);
	free(buf);
	printf("\n");
}

//GB2312Âë×ªÎªUNICODEÂë 
static int g2u(char *inbuf,size_t inlen,char *outbuf,size_t outlen) 
{ 
	return code_convert("gb2312","utf-8",inbuf,&inlen,outbuf,&outlen);

}