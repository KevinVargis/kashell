#include "headers.h"
#include "builtins.h"

void exec(char pip[], int pipe_count)
{
    char* args[200];
    memset(args, 0, sizeof(args));
    // for(int j = 0; args[j] != NULL; j++)
        // printf("1%s ", pip);
    pip = strtok(pip, " \t");
    int i = 0, forkReturn;
    while(pip != NULL)
    {
        // printf("%s\n", parse);
        args[i++] = pip;
        pip = strtok(NULL, " \t");
    }
    // if(p == k -1)
    // {
    //     strtok(args[i-1], "\n");
    //     args[i] = NULL;
    // }
    // printf("A\n");
    // printf("\n");
    // printf("A\n");
    
    if(strcmp(args[0], "\n") == 0)
    {
        return;
    }
    
    int trunc = 0, append = 0, input = 0, stdo, stdi; 
    // for(int j = 0; args[j] != NULL; j++)
    //     printf("%s ", args[j]);
    // printf("\n");
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
    // bgc = 0;
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
        // printf("xhaxha\n");
    }
    else if(strcmp(args[0], "setenv") == 0)
    {
        
        if(i <= 1)
            printf("setenv: Too few arguments\n");
        else if(i == 2)
        {
            if(setenv(args[1],"", 1) < 0)
                perror("setenv");
        }
        else if(i == 3)
        {
            if(setenv(args[1], args[2], 1) < 0)
                perror("setenv");
            // else
            //     printf("yoyo\n");
        }
        else
            printf("setenv: Too many arguments\n");
        // printf("%d\n", i);
        
    }
    else if(strcmp(args[0], "unsetenv") == 0)
    {
        if(i <= 1)
            printf("unsetenv: Too few arguments\n");
        else if(i == 2)
        {
            if(unsetenv(args[1]) < 0)
                perror("unsetenv");
        }
        else
            printf("unsetenv: Too many arguments\n");
        
        
    }
    else if(strcmp(args[0], "jobs") == 0)
    {
        jobs();
    }
    else if(strcmp(args[0], "kjob") == 0)
    {
        if(i <= 2)
            printf("kjob: Too few arguments\n");
        else if(i == 3)
            kjob(args);
        else
            printf("kjob: Too many arguments\n");
    }
    else if(strcmp(args[0], "fg") == 0)
    {
        int pno = atoi(args[1]);
        if(i <= 1)
            printf("fg: Too few arguments\n");
        else if(i == 2)
            fg(pno);
        else
            printf("fg: Too many arguments\n");
    }
    else if(strcmp(args[0], "bg") == 0)
    {
        int pno = atoi(args[1]);
        if(i <= 1)
            printf("bg: Too few arguments\n");
        else if(i == 2)
            bg(pno);
        else
            printf("bg: Too many arguments\n");
    }
    else if(strcmp(args[0], "overkill") == 0)
    {
        if(i <= 0)
            printf("overkill: Too few arguments\n");
        else if(i == 1)
            overkill();
        else
            printf("overkill: Too many arguments\n");
    }
    else if(strcmp(args[0], "quit") == 0)
    {
        if(i <= 0)
            printf("quit: Too few arguments\n");
        else if(i == 1)
        {
            overkill();
            exit(0);
        }
        else
            printf("quit: Too many arguments\n");
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
            {
                perror(args[0]);
                // bgc = 1;
                kill(getpid(), SIGKILL);
            }
                     
            // kill(getpid(), SIGKILL);
        }
        else
        {
            // sleep(1);
            // if(bgc == 2)
            // {
                add_bg(args, forkReturn);
                // back_bois++;
                // strcpy(proc_list[back_bois].pname, args[0]);
                // proc_list[back_bois].pid = forkReturn;
                // printf("[%d] %d %s\n", back_bois+1, forkReturn, proc_list[back_bois].pname);
            // }
        }
    }
    else if(strcmp(args[0], "history") != 0)
    {
        forkReturn = fork();
        last_boi.pid = forkReturn;
        strcpy(last_boi.pname, args[0]);
        for(int i = 1; (args[i] != NULL) && strcmp(args[i], "&"); i++)
        {
            strcat(last_boi.pname, " ");
            strcat(last_boi.pname, args[i]);
        }
        
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
    // printf("%d\n", bgc);
    fflush(NULL);
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
    
    // no[0] = siz;
    // close(fno);
    
    // fno = open(hisnopath, O_WRONLY | O_TRUNC);
    // write(fno, no, sizeof(no));
    
    // // fclose(fhis);
    // fhis = fopen(hispath, "w");
    // for(int i = ((siz-19) > 0 ? (siz-19) : 0); i <= siz; i++)
    // {
    //     fputs(hist[i%20], fhis);
    //     // printf("%d %s", i%5, hist[i%5]);
    // }
    // fclose(fhis);

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
    // printf("HEY HEY HEY\n");
    return;
}