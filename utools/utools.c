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

bool squareCollisionCheck(int x1,int y1,int w1,int h1,int x2,int y2,int w2,int h2)
{
    if(w1 > w2 || h1 > h2)
    {
        int buffer;
        buffer = w2;
        w2 = w1;
        w1 = buffer;

        buffer = h2;
        h2 = h1;
        h1 = buffer;

        buffer = x2;
        x2 = x1;
        x1 = buffer;

        buffer = y2;
        y2 = y1;
        y1 = buffer;
    }
    // Linear programming
    int vertex[4][2] = {{x1,y1},{x1,y1+h1},{x1+w1,y1},{x1+w1,y1+h1}};
    for(int i = 0;i < 4;i++)
    {
        if(vertex[i][0] > x2 && vertex[i][0] < x2 + w2 && vertex[i][1] < y2 + h2 && vertex[i][1] > y2) return true;
    }
    return false;
}