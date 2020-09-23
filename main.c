#include "headers.h"
#include "builtins.h"

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
    getcwd(daddydir, sizeof(daddydir));
    buff  = (char *)calloc(20000, sizeof(char));
    siz = -1;
    back_bois = -1;
    no[0] = -1;
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
    // close(fno);
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
        // memset(parse, 0, sizeof(parse));
        char* cmd[100];
        char cwd[1000];
        getcwd(cwd, sizeof(cwd));
        // strcat(cwd, "/yoo");
        
        parse = prompt(cwd, daddydir);
        // printf("1%s\n", parse);
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
            char* pip[100];
            int pipe_count = 0;
            cmd[p] = strtok(cmd[p], "|");
            while(cmd[p] != NULL)
            {
                // printf("%s\n", parse);
                pip[pipe_count++] = cmd[p];
                cmd[p] = strtok(NULL, "|");
            }
            if(p == k -1)
            {
                strtok(pip[pipe_count-1], "\n");
                pip[pipe_count] = NULL;
            }
        
            // for(int j = 0; pip[j] != NULL; j++)
            // printf("%s %u ", pip[pipe_count-1], pipe_count-1);
            // printf("\n");

            // int pipefds[2*pipe_count];

            // for(int i = 0; i < pipe_count; i++)
            // {
            //     if(pipe(pipefds + i*2) < 0) 
            //     {
            //         perror("pipe");
            //         continue;
            //     }
            // }
            int stdo, stdi;
            stdi = dup(0);
            stdo = dup(1);
            int pipe_fd[2];
            int fpid;
            int fdd = 0;				/* Backup */

            for(int pi = 0; pi < pipe_count - 1; pi++)
            {
                pipe(pipe_fd);
                fpid = fork();
                if(fpid < 0) 
                {
                    perror("pipe");
                    exit(1);
                }
                else if (fpid == 0) 
                {
                    fflush(NULL);
                    dup2(fdd, 0);
                    fflush(NULL);
                    if (pip[pi+1] != NULL) 
                    {
                        dup2(pipe_fd[1], 1);
                    }
                    
                    close(pipe_fd[0]);
                    fflush(NULL);
                    exec(pip[pi], pipe_count);
                    fflush(NULL);
                    // execvp((*pip)[0], *pip);

                    exit(0);
                }
                else 
                {
                    wait(NULL); 		/* Collect childs */
                    close(pipe_fd[1]);
                    // close(fdd);
                    fdd = pipe_fd[0];
                    // pip++;
                }
            }

            dup2(stdo, STDOUT_FILENO);
            dup2(fdd, STDIN_FILENO);
            exec(pip[pipe_count-1], pipe_count);

            dup2(stdi, STDIN_FILENO);
            dup2(stdo, STDOUT_FILENO); 

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
            // }
        }
    }
}
