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
            
            int trunc = 0, append = 0, input = 0, stdo, stdi; 
            for(int j = 0; args[j] != NULL; j++)
                printf("%s ", args[j]);
            printf("\n");
            for(int j = 0; j < i; j++)
            {
                // printf("%s\n", args[j]);
                if(strcmp(args[j], ">>") == 0)
                {
                    append = 1;
                    // printf("a%s\n", args[j+1]);
                    int fd = open(args[j+1], O_WRONLY | O_CREAT | O_APPEND, 0644);
                    // printf("%s\n", args[j+1]);
                    stdo = dup(1);
                    if (fd < 0) {
                        perror("kash");
                        continue;
                    }
                    if (dup2(fd, STDOUT_FILENO) < 0) {
                        perror("kash");
                        continue;
                    }
                    close(fd);
                    for(int z = j+2; z < i; z++)
                    {
                        args[z-2] = args[z];
                    }
                    args[i-2] = NULL;
                    i -= 2;
                    j--;
                }
                else if(strcmp(args[j], ">") == 0)
                {
                    trunc = 1;

                    int fd = open(args[j+1], O_WRONLY | O_CREAT | O_TRUNC, 0644);

                    stdo = dup(1);
                    if (fd < 0) {
                        perror("kash");
                        continue;
                    }
                    if (dup2(fd, STDOUT_FILENO) < 0) {
                        perror("kash");
                        continue;
                    }
                    close(fd);
                    for(int z = j+2; z < i; z++)
                    {
                        args[z-2] = args[z];
                    }
                    args[i-2] = NULL;
                    i -= 2;
                    j--;
                }
                else if(strcmp(args[j], "<") == 0)
                {
                    input = 1;

                    int fd = open(args[j+1], O_RDONLY);

                    stdi = dup(0);

                    if (fd < 0) {
                        perror("kash");
                        continue;
                    }

                    if (dup2(fd, STDIN_FILENO) < 0) {
                        perror("kash");
                        continue;
                    }
                    close(fd);

                    for(int z = j+2; z < i; z++)
                    {
                        
                            args[z-2] = args[z];
                    }
                    args[i-2] = NULL;
                    i -= 2;
                    j--;
                }
                // printf("NULL at %d\n", i);
            }
            // for(int j = 0; args[j] != NULL; j++)
            //     printf("%s ", args[j]);
                //  write(1, "", strlen(""));
            // printf("\n");
            if(strcmp(args[0], "cd") == 0)
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

            if((trunc == 1) || (append == 1))
            {
                dup2(stdo ,STDOUT_FILENO);
                close(stdo);
            }
            if(input == 1)
            {
                dup2(stdi, STDIN_FILENO);
                close(stdi);
            }

        }
    }
}
