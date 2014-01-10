#include "stdafx.h"
#include "scanfolder.h"

void dfsFolder(const char* folderPath, const char* extent)
{

	 _finddata_t files; 

	 int File_Handle; 

	 int i=0;  

	 char path[100];

	 sprintf(path, "%s*%s", folderPath, extent);

	 File_Handle = _findfirst(path, &files); 

	 if(File_Handle==-1) 
	 {  
		 printf("error\n"); 
		 return ; 
	 } 
	 do 
	 {  
		 printf("%s \n",files.name); 
		 sprintf(path, "%s%s", folderPath, files.name);
		 openAndReadFile(path);
		 i++;
	 } while(!_findnext(File_Handle,&files)); 
	 _findclose(File_Handle);  
	 printf("Find %d files\n",i);  

}

void openAndReadFile(const char* fileName)
{
	int ch;
	FILE* fp;
	printf("open the file %s \n", fileName);
	fp = fopen(fileName, "r");
	if (fp == NULL)
	{
		return;
	}
	while ((ch = getc(fp)) != EOF)
	{
		printf("%x ", ch);
	}
	fclose(fp);
	printf("\n");
}