#include "prompt.h"
#include "cd.h"
#include "pwd.h"
#include "echo.h"
#include "ls.h"
#include "pinfo.h"
#include "headers.h"
#include "amp.h"

void cld_exit(int sig)
{
    int pid, status, heh = 0;
    signal(SIGCHLD, cld_exit);
    while ((pid = waitpid(-1, &status, WNOHANG)) != -1)
    {
        int chk = 0;
        if(pid == 0)
            break;
        while(chk <= back_bois)
        {
            if(proc_list[chk].pid == pid)
                break;
            chk++;
        }
        printf("%s with pid %d exited normally\n", proc_list[chk].pname, pid);
        heh = 1;
    }
    if(heh)
        printf("Press <Enter> to continue\n");
}

int main()
{
    char daddydir[1000];
    getcwd(daddydir, sizeof(daddydir));
    char* cmd[] = {"./cd"};
    char* buff  = (char *)calloc(20000, sizeof(char));
    char hist[20][1000];
    FILE* fhis;
    int siz = -1, no[1];
    no[0] = -1;
    char hispath[200], hisnopath[200];
    strcpy(hispath, daddydir);
    strcat(hispath, "/history.txt");
    strcpy(hisnopath, daddydir);
    strcat(hisnopath, "/histno.txt");
    int fno = open(hisnopath, O_RDWR);
    if(fno < 0)
    {
        fno = open(hisnopath, O_RDWR | O_CREAT, 0700);
        write(fno, no, sizeof(no));
        fhis = fopen(hispath, "w");
    }
    else
    {
        read(fno, no, sizeof(no));
        fhis = fopen(hispath, "r");
    }

    // printf("%d\n", no[0]);
    siz = no[0];

    for(int i = ((siz-19) > 0 ? (siz-19) : 0); i <= siz; i++)
        fgets(hist[i%20], 100, fhis);    
    fclose(fhis);

    signal(SIGCHLD, cld_exit);

    printf("\n");
    printf("\033[1;33m");
    printf("\t\t$ Welcome to kash! $\n");
    printf("\033[0m");
    printf("\n");
    // read(fhis, buff, sizeof(buff));
    // buff = strtok(buff, "\n");
    // int cnt = 0;
    // while(buff != NULL)
    // {
    //     // printf("%s\n", parse);
    //     hist[cnt++] = buff;
    //     buff = strtok(NULL, "\n");
    //     printf("%s", hist[cnt-1]);
    // }
    // strtok(hist[cnt-1], "\n");
    // hist[cnt] = NULL;
    // for(int i = 0, i <= siz; i++)


    while (1)
    {
        char* parse;
        char* cmd[100];
        char cwd[1000];
        getcwd(cwd, sizeof(cwd));
        // strcat(cwd, "/yoo");
    
        parse = prompt(cwd, daddydir);
        siz++;
        strcpy(hist[siz%20], parse);
        // strcat(hist[siz%20]);
        parse = strtok(parse, ";");
        int k = 0;
        while(parse != NULL)
        {
            // printf("%s\n", parse);
            cmd[k++] = parse;
            parse = strtok(NULL, ";");
        }
        for(int p = 0; p < k; p++)
        {
            char* args[20];
            cmd[p] = strtok(cmd[p], " \t");
            int i = 0, forkReturn;
            while(cmd[p] != NULL)
            {
                // printf("%s\n", parse);
                args[i++] = cmd[p];
                cmd[p] = strtok(NULL, " \t");
            }
            if(p == k -1)
            {
                strtok(args[i-1], "\n");
                args[i] = NULL;
            }
            // printf("A\n");
            // printf("\n");
            // printf("A\n");

            if(strcmp(args[0], "\n") == 0)
            {
                continue;
            }
            else if(strcmp(args[0], "cd") == 0)
            {
                if(i <= 2)
                    cd(args, daddydir);
                else
                {
                    printf("cd: Wrong number of arguments\n");
                }
            }
            else if(strcmp(args[0], "pwd") == 0)
            {
                pwd();
            }
            else if(strcmp(args[0], "echo") == 0)
            {
                echo(args);
            }
            else if(strcmp(args[0], "ls") == 0)
            {
                ls(args, i, daddydir);
            }
            else if(strcmp(args[0], "pinfo") == 0)
            {
                pinfo(args);
            }
            else if(strcmp(args[i-1], "&") == 0)
            {
                i--;
                args[i] = NULL;
                forkReturn = fork();
                setpgid(0, 0);
                if(forkReturn < 0)
                    perror("Couldnt create fork");
                else if(forkReturn == 0)
                {
                    if(execvp(args[0], args) < 0)
                        perror(args[0]);
                    // kill(getpid(), SIGKILL);
                }
                else
                {
                    back_bois++;
                    strcpy(proc_list[back_bois].pname, args[0]);
                    proc_list[back_bois].pid = forkReturn;
                    printf("[%d] %d %s\n", back_bois+1, forkReturn, proc_list[back_bois].pname);
                }
            }
            else if(strcmp(args[0], "history") != 0)
            {
                forkReturn = fork();
                if(forkReturn < 0)
                    perror("Couldnt create fork");
                else if(forkReturn == 0)
                {
                    if(execvp(args[0], args) < 0)
                        perror(args[0]);
                    kill(getpid(), SIGKILL);
                }
                else
                {
                    wait(NULL);
                }
            }
            
            // // char yo[1000];
            // strcpy(yo, args[0]);
            // strcat(yo, "\n");
            // hist[siz%20] = yo;

            // strcpy(hist[siz%20], args[0]);
            // strcat(hist[siz%20], "\n");
            
            
            
            // printf("ha\n");
            // printf("ha\n");
            if(strcmp(args[0], "history") == 0)
            {
                if(args[1] == NULL)
                {
                    for(int i = ((siz-9) > 0 ? (siz-9) : 0); i <= siz; i++)
                        printf("%s", hist[i%20]);
                }
                else
                {
                    int ar = atoi(args[1]);
                    // printf("%s %d\n", args[1], ar);

                    if(ar == 0)
                        printf("history: Invalid Arguments\n");
                    else if(ar > 20)
                        printf("history: Only 20 entries stored\n");
                    else
                    {
                        for(int i = ((siz-ar+1) > 0 ? (siz-ar+1) : 0); i <= siz; i++)
                            printf("%s", hist[i%20]);
                    }
                }
            }
            // for(int i = ((siz-4) > 0 ? (siz-4) : 0); i <= siz; i++)
            //     printf("%s", hist[i%20]);
            printf("\n");
            no[0] = siz;
            close(fno);
            
            fno = open(hisnopath, O_WRONLY | O_TRUNC);
            write(fno, no, sizeof(no));
            
            // fclose(fhis);
            fhis = fopen(hispath, "w");
            for(int i = ((siz-19) > 0 ? (siz-19) : 0); i <= siz; i++)
            {
                fputs(hist[i%20], fhis);
                // printf("%d %s", i%5, hist[i%5]);
            }
            fclose(fhis);
        }
        // for(int j = 0; j < i; j++)
        //     printf("%s\n", args[j]);
        
        
        
        // args[0] = cmd[0];
        //     args[i+1] = args[i];
        //     args[i] = daddydir;
        //     i++;
        // strcat(arg[0], ".c");
    }
}
