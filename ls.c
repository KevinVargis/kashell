#include "ls.h"
#include "headers.h"

char old[100], name[100], tim[100];
int l;
extern int optind;

void print_perm(char* path, char* args[], char* daddydir)
{
    struct stat sfile;  
    // struct passwd* uid = getpwuid(sfile.st_uid);
    // struct group* gid = getgrgid(sfile.st_gid);
    
    // if(l == 0)
    // printf("hoi\n");
    // chk = mkdir(argv[3], 0700);         // chk will tell us if the dir is already created
    // chdir(path);
    
    char s[100];
    if(getcwd(s, 100) < 0)
        perror("pwd");
    if(args != NULL)
    {
        if(args[optind][0] == '/')
            strcpy(s, args[optind]);
        else if(args[optind][0] == '~')
        {
            strcpy(s, daddydir);
            strcat(s, args[optind]+1);
        }
        else
        {
            strcat(s,"/");
            strcat(s, args[optind]);
        }
    }
    strcat(s,"/");
    strcat(s, path);
    // printf("%s\n", s);
    // printf("%s\n", path);
    if(stat(s,&sfile)==-1)    // getting permissions of directory using stat
    {
        perror("Error opening directory");
    }
    else
    {   
        // printing permisson details
        if(l == 1)
        {
            struct passwd* uid = getpwuid(sfile.st_uid);
            struct group* gid = getgrgid(sfile.st_gid);
            write(1, (S_ISDIR(sfile.st_mode))? "d":"-", strlen((S_ISDIR(sfile.st_mode))? "d":"-"));
            write(1, (sfile.st_mode & S_IRUSR)? "r":"-", strlen((sfile.st_mode & S_IRUSR)? "r":"-"));
            write(1, (sfile.st_mode & S_IWUSR)? "w":"-", strlen((sfile.st_mode & S_IWUSR)? "w":"-"));
            write(1, (sfile.st_mode & S_IXUSR)? "x":"-", strlen((sfile.st_mode & S_IXUSR)? "x":"-"));
            write(1, (sfile.st_mode & S_IRGRP)? "r":"-", strlen((sfile.st_mode & S_IRGRP)? "r":"-"));
            write(1, (sfile.st_mode & S_IWGRP)? "w":"-", strlen((sfile.st_mode & S_IWGRP)? "w":"-"));
            write(1, (sfile.st_mode & S_IXGRP)? "x":"-", strlen((sfile.st_mode & S_IXGRP)? "x":"-"));
            write(1, (sfile.st_mode & S_IROTH)? "r":"-", strlen((sfile.st_mode & S_IROTH)? "r":"-"));
            write(1, (sfile.st_mode & S_IWOTH)? "w":"-", strlen((sfile.st_mode & S_IWOTH)? "w":"-"));
            write(1, (sfile.st_mode & S_IXOTH)? "x":"-", strlen((sfile.st_mode & S_IXOTH)? "x ":"- "));   
            // printf("1\n");
            printf("%5ld", sfile.st_nlink);
            // printf("1\n");
            printf("%10s", uid -> pw_name);
            // printf("1\n");
            printf("%17s\t", gid -> gr_name);
            // printf("1\n");
            printf("%12ld\t", sfile.st_size);
            // printf("1\n");
            const time_t timz = sfile.st_mtime;
            // char timo[100];
            strftime(tim, 36, "%d.%m.%Y %H:%M:%S", localtime(&timz));
            printf("%20s  ", tim);
        }

        if(S_ISDIR(sfile.st_mode))
        {
            printf("\033[1;34m");
            printf("%20s  ", name);
            printf("\033[0m");
        }
        else
            printf("%20s  ", name);
        
        printf("\n");
    }
    // chdir(old);
    // if(getcwd(s, 100) < 0)
    //     perror("pwd");
    // printf("%s\n", s);
}

void ls(char* args[], int argc, char* daddydir)
{
    extern char *optarg;
    int a = 0, m;
    l = 0;
	// extern int optind;
    struct dirent* dir;
    char* path;
    char pathdef[] = ".", s[200];
    DIR* dp;

    optind = 1;
    if(getcwd(old, 100) < 0)
        perror("pwd");

    // printf("%d\n", optind);
    while ((m = getopt(argc, args, "la")) != -1)
    {
        if(m == 'l')
            l = 1;
        if(m == 'a')
            a = 1;
    }
    // printf("%d %d\n", optind, argc);

    if(optind == argc) 
    {	
		path = pathdef;
        // printf("%s", path);
        printf("%s:\n", path);
        dp = opendir(path);
        if(dp == NULL)
        {
            perror("ls");
            // return;
        }
        else
        {
            while(dir = readdir(dp))
            {
                // printf("%s ", dir -> d_name);
                strcpy(name, dir -> d_name);
                if((name[0] != '.') || (a == 1))
                {
                    print_perm(dir -> d_name, NULL, daddydir);
                    // if(l == 1)
                    //     print_perm(dir -> d_name);
                    // else
                    //     printf("%s\n", dir -> d_name);
                }
            }
            closedir(dp);
        }
        printf("\n");
	}
    else
    {
        while(optind < argc)
        {
            if(args[optind][0] == '~')
            {
                strcpy(s, daddydir);
                printf("hai\n");
                strcat(s, args[optind]+1);
                printf("hai2\n");
            }
            path = s;
            printf("%s:\n", path);
            dp = opendir(path);
            if(dp == NULL)
            {
                perror("ls");
                // return;
            }
            else
            {
                while(dir = readdir(dp))
                {
                    // printf("%s ", dir -> d_name);
                    strcpy(name, dir -> d_name);
                    if((name[0] != '.') || (a == 1))
                    {
                        print_perm(dir -> d_name, args, daddydir);
                    }
                }
                closedir(dp);
            }
            printf("\n");
            optind++;
        }
    }

    
    return;
}