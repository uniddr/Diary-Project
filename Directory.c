#include<stdio.h>
#include<dirent.h>
#include<errno.h>
#include<string.h>

int main()
{
    DIR *folder;
    struct dirent *dirstrc;
    char spc[255];
    folder=opendir("D:/Backup New 2k19/CodeBlocks/share/File");
    if(folder==NULL)
    {
        printf("Error message: ");
        switch(errno)
        {
        case ENOTDIR:
            printf("Not a directory!");
        case EACCES:
            printf("No permission!");
        case ENOFILE:
            printf("No such file or directory!");
        case EINVAL:
            printf("Invalid argument!");
        }
    }
    if(folder==NULL)
    {
        puts("\nunable to open directory.");
    }
    else
    {
        puts("\nopen successful!");
    }
    while(dirstrc=readdir(folder))
    {
        strcpy(spc,(dirstrc->d_name));
        printf("\n%s   ",spc);
    }
    closedir(folder);
    return 0;
}
