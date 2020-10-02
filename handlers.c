#include "headers.h"
#include "builtins.h"

void cld_exit(int sig)
{
    int pid, status, heh = 0;
    signal(SIGCHLD, cld_exit);
    while ((pid = waitpid(-1, &status, WNOHANG)) != -1)
    {
        int chk = 1;
        if(pid == 0)
            break;
        while(chk <= back_bois)
        {
            if(proc_list[chk].pid == pid)
                break;
            chk++;
        }
        if((WIFEXITED(status)))
        {
            printf("\n%s with pid %d ", proc_list[chk].pname, pid);
            // if (WEXITSTATUS(status) == 0)
                printf("\nexited normally with exit status: %d\n", WEXITSTATUS(status));
            // else
            //     printf("\nexited abnormally\n");
            heh = 1;

        }
        else
        {
            printf("\n%s with pid %d exited abnormally\n", proc_list[chk].pname, pid);
        }
        del_bg(chk);
        // for(int p = chk; p < back_bois; p++)
        // {
        //     proc_list[p].pid = proc_list[p+1].pid;
        //     strcpy(proc_list[p].pname, proc_list[p+1].pname);
        //     // strcpy(proc_list[p].status, proc_list[p+1].status);
        // }
        // back_bois--;
       
    }
    if(heh)
    {
        char cwd[1000];
        getcwd(cwd, 1000);
        deepprompt(cwd, daddydir);
        fflush(stdout);
    }
}

void ctrl_z(int sig)
{
    int pid, status, heh = 0;
    
    // printf("%d %d %d\n", getpid(), kash_id, last_boi.pid);
    if(last_boi.pid != -1)
    {
        // printf("yamero\n");
        back_bois++;
        strcpy(proc_list[back_bois].pname, last_boi.pname);
        proc_list[back_bois].pid = last_boi.pid;
        // kill(last_boi.pid, SIGTTIN);
        setpgid(last_boi.pid, 0);
        kill(last_boi.pid, SIGSTOP);
        // signal(SIGTSTP, SIG_IGN);
        printf("[%d] %d %s\n", back_bois, last_boi.pid, proc_list[back_bois].pname);
        fflush(stdout);
    }
    
    // char cwd[1000];
    // getcwd(cwd, sizeof(cwd));
    // prompt(cwd ,daddydir);
    // main();
    signal(SIGTSTP, ctrl_z);
    return;
}

void ctrl_c(int sig)
{
    int pid, status, heh = 0;
    printf("\n");
        // printf("%d %d %d\n", getpid(), kash_id, last_boi.pid);

    if(last_boi.pid != -1)  // (getpid() != kash_id) && 
    { 
        kill(last_boi.pid, SIGINT);
        // printf("\n");
        // fflush(NULL);
    }
    else
    {
        char cwd[1000];
        getcwd(cwd, 1000);
        deepprompt(cwd, daddydir);
        fflush(stdout);
    }
    
    // signal(SIGTSTP, ctrl_z);
    return;
}
