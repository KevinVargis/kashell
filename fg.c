#include "builtins.h"
#include "headers.h"

void fg(int pno)
{
    if((pno > back_bois) || (pno < 1))
        printf("fg: invalid job number\n");
    else
    {
        signal(SIGTTOU, SIG_IGN);
        signal(SIGTTIN, SIG_IGN);
        tcsetpgrp(0, getpgid(proc_list[pno].pid));
        kill(proc_list[pno].pid, SIGCONT);
        waitpid(getpgid(proc_list[pno].pid), NULL, WUNTRACED);
        tcsetpgrp(0, getpgid(0));
        signal(SIGTTOU, SIG_DFL);
        signal(SIGTTIN, SIG_DFL);
        del_bg(pno);
    }
}