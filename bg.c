#include "builtins.h"
#include "headers.h"

void add_bg(char *args[], int pid)
{
    back_bois++;
    strcpy(proc_list[back_bois].pname, args[0]);
    for(int i = 1; (args[i] != NULL) && strcmp(args[i], "&"); i++)
    {
        strcat(proc_list[back_bois].pname, " ");
        strcat(proc_list[back_bois].pname, args[i]);
    }
    proc_list[back_bois].pid = pid;

    // char fname[100] = "/proc/";
    // // char xpname[100] = "/proc/";
    // // char execu[100];
    // int blah;
    // char bla[100], status;
    // unsigned long int m;

    // char num[10];
    // sprintf(num, "%d", pid);
    
    // strcat(fname, num);
    // // strcat(xpname, num);
    // printf("pid -- %s\n", num);
    // // int ar = atoi(args[1]);
    // // if(ar == 0)
    // // {
    // //     printf("pinfo: integer argument expected\n");
    // //     return;
    // // }
    // // if(kill(ar, 0) < 0)
    // // {
    // //     perror("pinfo");
    // //     return;
    // // }
    // strcat(fname, "/stat");
    // // strcat(xpname, "/exe");
    // // printf("%s\n", fname);
    // FILE* f = fopen(fname, "r");
    // fscanf(f, "%d %s %c %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %lu", &blah, bla, &status, &blah, &blah, &blah, &blah, &blah, &blah, &blah, &blah, &blah, &blah, &blah, &blah, &blah, &blah, &blah, &blah, &blah, &blah, &blah, &m);
    // printf("Process Status -- %c\n", status);
    // if(status == 'R')
    //     strcpy(proc_list[back_bois].status, "Running");
    // else
    // {
    //     strcpy(proc_list[back_bois].status, "Stopped");
    // }
    
    // printf("Virtual Memory Usage -- %lu\n", m);
    // int len = readlink(xpname, execu, 100);
    // execu[len] = '\0';
    // int bytes = MIN(readlink(xpname, execu, 100), 99);
    
    // if(bytes >= 0)
    //     execu[bytes] = '\0';
    // return bytes;
    // printf("%ld %d\n", strlen(execu), bytes);
    // printf("Executable Path -- %s\n", execu);

    printf("[%d] %d %s\n", back_bois, pid, proc_list[back_bois].pname);
}

void jobs()
{
    for(int i = 1; i <= back_bois; i++)
    {
         char fname[100] = "/proc/";
    // char xpname[100] = "/proc/";
    // char execu[100];
    int blah;
    char bla[100], status;
    unsigned long int m;

    char num[10];
    sprintf(num, "%d", proc_list[i].pid);
    
    strcat(fname, num);
    // printf("pid -- %s\n", num);
    
    strcat(fname, "/stat");
    FILE* f = fopen(fname, "r");
    fscanf(f, "%d %s %c %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %lu", &blah, bla, &status, &blah, &blah, &blah, &blah, &blah, &blah, &blah, &blah, &blah, &blah, &blah, &blah, &blah, &blah, &blah, &blah, &blah, &blah, &blah, &m);
    // printf("Process Status -- %c\n", status);
    if(status == 'R')
        printf("[%d] Running %s [%d]\n", i, proc_list[i].pname, proc_list[i].pid);
    else
    {
        // strcpy(proc_list[back_bois].status, "Stopped");
        printf("[%d] Stopped %s [%d]\n", i, proc_list[i].pname, proc_list[i].pid);
    }
        

    }
}