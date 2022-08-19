#include "utools.h"
#include <stdlib.h>
//#include <unistd.h>

char* rootPath[128];

void initUtools(int argc,char** argv)
{
    realpath(argv[0],rootPath);
}