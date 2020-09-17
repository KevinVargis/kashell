#include "headers.h"
#include "cd.h"

void cd(char* args[], char* daddydir)  //int argc, char* argv[]
{
    char s[100];
    getcwd(s, 100);
    // if((strcmp(daddydir, s) == 0) && (strcmp(args[1], "..") == 0))
    // {
    //     int i;
    //     for(i = strlen(s)-1; (s[i] != '/') && (i >= 0); i--)
    //     {
    //     }
    //     s[i] = '\0';
    //     printf("%s\n", s);
    // }
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
    else
    {
        // printf("%s\n", args[1]);
        if(chdir(args[1]) < 0)
            perror("cd");
    }
    // return(0);
}

