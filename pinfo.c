#include "pinfo.h"
#include "headers.h"

void pinfo(char* args[])
{
    // int id;
    char fname[100] = "/proc/";
    char xpname[100] = "/proc/";
    char execu[100];
    int blah;
    char bla[100], status;
    unsigned long int m;
    if(args[1] == NULL)
    {
        int id = getpid();
        sprintf(fname + strlen(fname), "%d", id);
        sprintf(xpname + strlen(xpname), "%d", id);
        printf("pid -- %d\n", id);
    }
    else
    {
        // char id = args[1];
        strcat(fname, args[1]);
        strcat(xpname, args[1]);
        printf("pid -- %s\n", args[1]);
        int ar = atoi(args[1]);
        if(ar == 0)
        {
            printf("pinfo: integer argument expected\n");
            return;
        }
        if(kill(ar, 0) < 0)
        {
            perror("pinfo");
            return;
        }
    }
    strcat(fname, "/stat");
    strcat(xpname, "/exe");
    // printf("%s\n", fname);
    FILE* f = fopen(fname, "r");
    fscanf(f, "%d %s %c %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %lu", &blah, bla, &status, &blah, &blah, &blah, &blah, &blah, &blah, &blah, &blah, &blah, &blah, &blah, &blah, &blah, &blah, &blah, &blah, &blah, &blah, &blah, &m);
    printf("Process Status -- %c\n", status);
    printf("Virtual Memory Usage -- %lu\n", m);
    int len = readlink(xpname, execu, 100);
    execu[len] = '\0';
    // int bytes = MIN(readlink(xpname, execu, 100), 99);
    
    // if(bytes >= 0)
    //     execu[bytes] = '\0';
    // return bytes;
    // printf("%ld %d\n", strlen(execu), bytes);
    printf("Executable Path -- %s\n", execu);
}