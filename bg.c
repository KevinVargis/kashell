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

    printf("[%d] %d %s\n", back_bois, pid, proc_list[back_bois].pname);
}

void del_bg(int pno)
{
    for(int p = pno; p < back_bois; p++)
    {
        proc_list[p].pid = proc_list[p+1].pid;
        strcpy(proc_list[p].pname, proc_list[p+1].pname);
        // strcpy(proc_list[p].status, proc_list[p+1].status);
    }
    back_bois--;
}

void bg(int pno)
{
    if((pno > back_bois) || (pno < 1))
        printf("fg: invalid job number\n");
    else
    {
        kill(proc_list[pno].pid, SIGCONT);
    }
}

void overkill()
{
    // printf("%d\n", back_bois);
    while (back_bois > 0)
    {
        // printf("%d\n", back_bois);
        if(kill(proc_list[back_bois].pid, 9) < 0)
            perror("overkill");
    }
}

void jobs()
{
    for(int i = 1; i <= back_bois; i++)
    {
         char fname[1000] = "/proc/";
    // char xpname[100] = "/proc/";
    // char execu[100];
    int blah;
    char bla[1000], status;
    unsigned long int m;

    char num[10];
    sprintf(num, "%d", proc_list[i].pid);
    
    strcat(fname, num);
    // printf("pid -- %s\n", num);
    
    strcat(fname, "/stat");
    FILE* f = fopen(fname, "r");
    fscanf(f, "%d %s %c %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %lu", &blah, bla, &status, &blah, &blah, &blah, &blah, &blah, &blah, &blah, &blah, &blah, &blah, &blah, &blah, &blah, &blah, &blah, &blah, &blah, &blah, &blah, &m);
    // printf("Process Status -- %c\n", status);
    if(status == 'T')
        printf("[%d] Stopped %s [%d]\n", i, proc_list[i].pname, proc_list[i].pid);
    else
    {
        // strcpy(proc_list[back_bois].status, "Stopped");
        printf("[%d] Running %s [%d]\n", i, proc_list[i].pname, proc_list[i].pid);
    }
        

    }
}