#include "headers.h"
#include "echo.h"

void echo(char* args[])
{
    int i = 1;
    while(args[i] != NULL)
    {
        printf("%s ", args[i]);
        i++;
    }
    printf("\n");
}