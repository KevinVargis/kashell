#include "headers.h"
#include "pwd.h"

void pwd()
{
    char s[100];
    if(getcwd(s, 100) < 0)
        perror("pwd");
    printf("%s\n", s);
}