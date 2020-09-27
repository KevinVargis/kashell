#include "builtins.h"
#include "headers.h"

void kjob(char *args[])
{
    int sig, pno;
    pno = atoi(args[1]);
    sig = atoi(args[2]);
    if(kill(proc_list[pno].pid, sig) < 0)
        perror("kjob");
}