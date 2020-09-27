#ifndef __AMP_H
#define __AMP_H
int back_bois;

struct process
{
    int pid;
    char pname[1500];
    // char status[100];
};

struct process proc_list[1000];

#endif