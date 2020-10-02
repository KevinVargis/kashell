#include "builtins.h"
#include "headers.h"

char* prompt(char* path, char* daddydir) {
    char name[1000];
    char yamero[1000];
    char* uname = malloc(1000 * sizeof(char));
    int i, flag = 0;
    // char* ter_name = malloc(100 * sizeof(char));
    char ter_name[1000];

    ter_name[0] = '\0';
    printf("<");

    
    strcpy(yamero, path);
    uname = getlogin();
    strcat(ter_name, uname);
    strcat(ter_name, "@");
    gethostname(name, sizeof(name));
    strcat(ter_name, name);

    printf("\033[1;32m");
    printf("%s", ter_name);
    printf("\033[0m");
    printf(":");

    // strcpy(ter_name, "");
    ter_name[0] = '\0';

    for(i = 0; (daddydir[i] != '\0') && (path[i] != '\0'); i++)
    {
        if(daddydir[i] == path[i])
            flag = 1;
        else
        {
            flag = 0;
            break;
        }
    }
    if((flag == 1) && (strlen(path) >= strlen(daddydir)))
    {   
        strcat(ter_name, "~");
        strcat(ter_name, path + strlen(daddydir));
    }
    else
    {
        // strcat(ter_name, ":");
        strcat(ter_name, path);
    }
    printf("\033[1;34m");
    printf("%s", ter_name);
    printf("\033[0m");
    printf(">");
    // strcat(ter_name, ">");
    // printf("%s\n", ter_name);

    char* in_buf = malloc(1000 * sizeof(char)); 
    size_t in_len = sizeof(in_buf);
    
    long long int yo = getline(&in_buf, &in_len, stdin); 
    // printf("%lld\n", yo);
    if(yo == -1)
    {
        overkill();
        printf("\n");
        exit(0);
    } 
    for(int i = strlen(in_buf)-2; (i >= 0) && (in_buf[i] == ' '); i--)
    { 
        in_buf[i] = '\0';
        // printf("yeet\n");
    }
    return in_buf;
}

char* deepprompt(char* path, char* daddydir) {
    char name[1000];
    char yamero[1000];
    char* uname = malloc(1000 * sizeof(char));
    int i, flag = 0;
    // char* ter_name = malloc(100 * sizeof(char));
    char ter_name[1000];

    ter_name[0] = '\0';
    printf("<");

    
    strcpy(yamero, path);
    uname = getlogin();
    strcat(ter_name, uname);
    strcat(ter_name, "@");
    gethostname(name, sizeof(name));
    strcat(ter_name, name);

    printf("\033[1;32m");
    printf("%s", ter_name);
    printf("\033[0m");
    printf(":");

    // strcpy(ter_name, "");
    ter_name[0] = '\0';

    for(i = 0; (daddydir[i] != '\0') && (path[i] != '\0'); i++)
    {
        if(daddydir[i] == path[i])
            flag = 1;
        else
        {
            flag = 0;
            break;
        }
    }
    if((flag == 1) && (strlen(path) >= strlen(daddydir)))
    {   
        strcat(ter_name, "~");
        strcat(ter_name, path + strlen(daddydir));
    }
    else
    {
        // strcat(ter_name, ":");
        strcat(ter_name, path);
    }
    printf("\033[1;34m");
    printf("%s", ter_name);
    printf("\033[0m");
    printf(">");
    // strcat(ter_name, ">");
    // printf("%s\n", ter_name);

    // char* in_buf = malloc(1000 * sizeof(char)); 
    // size_t in_len = sizeof(in_buf);
    
    // long long int yo = getline(&in_buf, &in_len, stdin); 
    // // printf("%lld\n", yo);
    // if(yo == -1)
    // {
    //     overkill();
    //     printf("\n");
    //     exit(0);
    // } 
    // for(int i = strlen(in_buf)-2; (i >= 0) && (in_buf[i] == ' '); i--)
    // { 
    //     in_buf[i] = '\0';
    //     // printf("yeet\n");
    // }
    // return in_buf;
}
