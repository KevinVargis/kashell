#include <stdio.h>  
#include <fcntl.h>
#include <time.h>  
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>

#ifndef __BUI_H
#define __BUI_H
char daddydir[1000];
char* buff;
char hist[20][1000];
FILE* fhis;
int siz, no[1];
char hispath[200], hisnopath[200];
int fno;
#endif