#include "headers.h"
#include "cd.h"

void cd(char* args[], char* daddydir)  //int argc, char* argv[]
{
    char s[1000];
    getcwd(s, 1000);
    // if((strcmp(daddydir, s) == 0) && (strcmp(args[1], "..") == 0))
    // {
    //     int i;
    //     for(i = strlen(s)-1; (s[i] != '/') && (i >= 0); i--)
    //     {
    //     }
    //     s[i] = '\0';
    //     printf("%s\n", s);
    // }
    char lwwd[1000], ter_name[1000];
    strcpy(lwwd, lwd);
    getcwd(lwd, sizeof(lwd));
    int flag = 0;
    for(int i = 0; (daddydir[i] != '\0') && (lwd[i] != '\0'); i++)
    {
        if(daddydir[i] == lwd[i])
            flag = 1;
        else
        {
            flag = 0;
            break;
        }
    }
    if((flag == 1) && (strlen(lwd) >= strlen(daddydir)))
    {   
        strcpy(ter_name, "~");
        strcat(ter_name, lwd + strlen(daddydir));
    }
    else
    {
        // strcat(ter_name, ":");
        strcpy(ter_name, lwd);
    }
    strcpy(lwd, ter_name);
    if(args[1] == NULL)
    {
        if(chdir(daddydir) < 0)
            perror("cd");
    }
    else if(args[1][0] == '~')  // strcmp(args[1], "~") == 0
    {
        if(chdir(daddydir) < 0)
            perror("cd");
        if(args[1][1] != '\0')
        {
            if(chdir(args[1] + 2) < 0)
                perror("cd");
        }
    }
    else if(args[1][0] == '-')  // strcmp(args[1], "~") == 0
    {
        
        printf("%s\n", lwwd);
        if(lwwd[0] == '~')  // strcmp(args[1], "~") == 0
        {
            if(chdir(daddydir) < 0)
                perror("cd");
            if(lwwd[1] != '\0')
            {
                if(chdir(lwwd + 2) < 0)
                    perror("cd");
            }
        }
        else
        {
            if(chdir(lwwd) < 0)
                perror("cd");
        }
        if(args[1][1] != '\0')
        {
            if(chdir(args[1] + 2) < 0)
                perror("cd");
        }
    }
    else
    {
        // printf("%s\n", args[1]);
        if(chdir(args[1]) < 0)
            perror("cd");
    }
    // return(0);
}

