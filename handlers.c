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
        printf("Press <Enter> to continue\n");
}

void ctrl_z(int sig)
{
    int pid, status, heh = 0;
    // printf("yo\n");
    if((getpid() != kash_id) && (last_boi.pid != -1))
    {
        back_bois++;
        strcpy(proc_list[back_bois].pname, last_boi.pname);
        proc_list[back_bois].pid = last_boi.pid;
        kill(last_boi.pid, SIGTTIN);
        kill(last_boi.pid, SIGTSTP);
        printf("[%d] %d %s\n", back_bois, last_boi.pid, proc_list[back_bois].pname);
    }
    // signal(SIGTSTP, ctrl_z);
    return;
}

void ctrl_c(int sig)
{
    int pid, status, heh = 0;
    printf("\n");
    if((getpid() != kash_id) && (last_boi.pid != -1))
    {
        kill(last_boi.pid, SIGINT);
        // printf("\n");
        // fflush(NULL);
    }
    // signal(SIGTSTP, ctrl_z);
    return;
}
