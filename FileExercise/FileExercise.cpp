// FileExercise.cpp : 定义控制台应用程序的入口点。
//
//
#include "stdafx.h"
#include "scanfolder.h"

int _tmain(int argc, _TCHAR* argv[])
{
	//dfsFolder("E:\\世界上下五千年（古代卷）\\",".txt");
	dfsFolder("D:\\test",".txt");
	getchar();
	return 0;
}

//#ifndef VERSION
//#define VERSION "Unknown"
//#endif
//#define BUFFER_SIZE 65536
//
//char buffer[BUFFER_SIZE];
//
//void detect(FILE * fp)
//{
//    uchardet_t handle = uchardet_new();
//
//    while (!feof(fp))
//    {
//        size_t len = fread(buffer, 1, BUFFER_SIZE, fp);
//        int retval = uchardet_handle_data(handle, buffer, len);
//        if (retval != 0)
//        {
//            fprintf(stderr, "Handle data error.\n");
//            exit(0);
//        }
//    }
//    uchardet_data_end(handle);
//
//    const char * charset = uchardet_get_charset(handle);
//    if (*charset)
//    	printf("%s\n", charset);
//	else
//		printf("ascii/unknown\n");
//	
//    uchardet_delete(handle);
//}
//
//void show_version()
//{
//    printf("\n");
//    printf("uchardet Command Line Tool\n");
//    printf("Version %s\n", VERSION);
//    printf("\n");
//    printf("Author: %s\n", "BYVoid");
//    printf("Bug Report: %s\n", "http://code.google.com/p/uchardet/issues/entry");
//    printf("\n");
//}
//
//void show_usage()
//{
//    show_version();
//    printf("Usage:\n");
//    printf(" uchardet [Options] [File]\n");
//    printf("\n");
//    printf("Options:\n");
//    printf(" -v, --version         Print version and build information.\n");
//    printf(" -h, --help            Print this help.\n");
//    printf("\n");
//}
//
//int main(int argc, char ** argv)
//{
//
//    FILE * f;
//
//    f = fopen("D:\\test\\japanese_text.txt", "r");
//    if (f == NULL)
//    {
//        fprintf(stderr, "Cannot open file.\n");
//        return 1;
//    }
//
//
//    detect(f);
//
//    fclose(f);
//	getchar();
//    return 0;
//}

