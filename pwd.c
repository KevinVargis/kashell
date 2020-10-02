#include "headers.h"
#include "pwd.h"

void pwd()
{
    char s[1000];
    if(getcwd(s, 1000) < 0)
        perror("pwd");
    printf("%s\n", s);
}