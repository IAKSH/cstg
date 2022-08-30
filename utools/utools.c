#include "utools.h"
#include <stdlib.h>
#include <string.h>
//#include <unistd.h>

char rootPath[128];

static int getFileNameIndex(const char* path);

void initUtools(int argc,char** argv)
{
    // this shit didn't work
    //realpath(*argv,rootPath);
    strcpy(rootPath, argv[0]);
    char* p = &rootPath[getFileNameIndex(argv[0])];
    *p = '\0';
}

static int getFileNameIndex(const char* path)
{
    int index = 0;
    int length = strlen(path);
    for(int i = 0;i < length;i++)
    {
        static const char aimdChar = '/';
        //if(strcmp(&path[i],&aimdChar) == 0)
        if(path[i] == aimdChar)
        {
            index = i;
        }
    }
    return index;
}