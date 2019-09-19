#define MAX_SIZE 1000
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<dirent.h>
#include<dir.h>
#include<process.h>
#include<time.h>
typedef struct information
{
    char date[12];
    char time[12];
    char title[50];
    char body[1000];
}entry;
void addnote()
{
    int i=92,c,ch,k=-2,key,value,count=-2,f=-3;
    entry e;
    char pathname[50],*path,s[10],*entire_dir,*filename,*file,*di[100];
    printf("\n\t\t\t\t\t\t     ADD MENU\t\t\t\t\t  \n");
    printf("\t\t\t\t    --------------------------------------------\t\t\t\t  ");
    printf("\n\t\t\t\t     0   >>   To use system date and time\t\t\t\t\t\t  ");
    printf("\n\t\t\t\t     1   >>   To use custom date and time\t\t\t\t\t\t  \n");
    printf("\n\t\t\t\t     Enter your choice:  ");
    scanf("%d",&ch);
    if(ch==0)
    {
        time_t timer;
        char rtime[12]="";
        struct tm* tm_info;

        time(&timer);
        tm_info = localtime(&timer);
        strftime(rtime,sizeof(rtime), "%d-%m-%Y", tm_info);
        strcpy(e.date, rtime);
        strftime(rtime,sizeof(rtime), "%H-%M", tm_info);
        strcpy(e.time, rtime);
    }
    else if(ch==1)
    {
    printf("\nPRESS 0 To return to Main Menu\nPRESS 1 To create directory\nPRESS 2 To create file\n");
    printf("Enter an option : ");
    scanf("%d",&c);
    switch(c)
    {
    case 0:
        return;
        break;
    case 1:
         printf("\nPRESS 0 To exit\nPRESS any key To continue\n");
         printf("Press a key (INT) : ");
         scanf("%d",&key);
         while(key!=0)
         {
              printf("Enter a valid pathname(Finish with %c) : ",i);
              fflush(stdin);
              gets(pathname);
              printf("Enter date [dd-mm-yyyy](Finish with %c) : ",i);
              fflush(stdin);
              gets(e.date);
              path=strcat(pathname,e.date);
              value=mkdir(path);
              if(value==0)
              {
                  printf("Directory has been created.\n");
                  printf("\nPRESS 0 To exit\nPRESS any key To continue\n");
                  printf("Press a key (INT) : ");
                  scanf("%d",&key);
              }
              else
                {
                    printf("This directory already exists.\n");
                    printf("\nPRESS 0 To exit\nPRESS any key To continue\n");
                    printf("Press a key (INT) : ");
                    scanf("%d",&key);
                }

         }
         return;
         break;
    case 2:
        printf("Enter a valid path name(Finish with %c) : \n",i);
        fflush(stdin);
        gets(pathname);
        struct dirent *dir;
        DIR *dp;
        dp=opendir(pathname);
        if(dp==NULL)
        {
            printf("Cannot open directory.\n");
            return;
        }
        else
        {
            while((dir=readdir(dp))!=NULL)
            {
                count++;
            }
            if(count==0)
            {
                printf("Cannot create file.First create a sub folder.\n");
                return;
            }
            else
            {
                printf("\nPRESS 1 To create file in existing directories\nPRESS 2 To create a new directory.\n");
                printf("Enter your choice : ");
                scanf("%d",&c);
                switch(c)
                {
            case 1:
                dp=opendir(pathname);
                printf("\nShowing folders in %s : \n",pathname);
                printf("Serial number:   Folder name:   \n");
                while((dir=readdir(dp))!=NULL)
                {
                    f++;
                    if(f>-1)
                    {
                        di[f]=(char*)malloc(MAX_SIZE);
                        if(di[f]==NULL)
                        {
                            printf("Not enough spaces for storing folders.\n");
                            return;
                        }
                        strcpy(di[f],dir->d_name);
                        printf("%d   %s\n",f+1,di[f]);
                    }
                }
                printf("Enter serial number to create file : ");
                scanf("%d",&value);
                printf("Selected folder to create file is %s : \n",di[value-1]);
                printf("\nEnter %c to create file : ",i);
                fflush(stdin);
                gets(s);
                entire_dir=strcat(di[value-1],s);
                file=strcat(pathname,entire_dir);
                break;
            case 2:
                printf("Enter date[dd-mm-yyyy](Finish with %c) : \n",i);
                fflush(stdin);
                gets(e.date);
                file=strcat(pathname,e.date);
                value=mkdir(file);
                if(value==0)
                {
                    printf("Directory has been created.\n");
                }
                else
                    {
                        printf("This directory already exists.\n");
                        return;
                    }
                    break;
                }
                printf("Enter a file name [hh-mm] : ");
                fflush(stdin);
                gets(e.time);
                filename=strcat(file,e.time);
                FILE *fp;
                fp=fopen(filename,"w+");
                if(fp==NULL)
                {
                    printf("Cannot open file.\n");
                    return;
                }
                printf("Success!!!File has been created.\n");
                printf("Enter title : ");
                fflush(stdin);
                gets(e.title);
                printf("Enter note : ");
                fflush(stdin);
                gets(e.body);
                fclose(fp);

            }

        }

    }
    }
}
void viewnote()
{
     int i=92,input,k=-2,value,count=-3,f=-3;
     char pathname[50],*di[100],s[10],*entire_dir,*file[100],*path,*filename;
     printf("Enter a valid pathname(Finish with %c) : ",i);
     fflush(stdin);
     gets(pathname);
     struct dirent *dir;
     DIR *dp;
     dp=opendir(pathname);
     if(dp==NULL)
     {
         printf("Cannot open directory to view.\n");
         return;
     }
     printf("Showing folders in %s \n\n",pathname);
     printf("Serial number:   Folder name:   \n");
     while((dir=readdir(dp))!=NULL)
                {
                    f++;
                    if(f>-1)
                    {
                        di[f]=(char*)malloc(MAX_SIZE);
                        if(di[f]==NULL)
                        {
                            printf("Not enough spaces for storing folders.\n");
                            return;
                        }
                        strcpy(di[f],dir->d_name);
                        printf("%d   %s\n",f+1,di[f]);
                    }
                }
                if(f==-1)
                {
                    printf("No folder found.\n");
                    return;
                }
                printf("Enter folder serial to view file : \n");
                scanf("%d",&input);
                printf("Selected folder to view is %s : \n",di[input-1]);
                path=strcat(pathname,di[input-1]);
                printf("\nEnter %c to view files in %s : ",i,path);
                fflush(stdin);
                gets(s);
                entire_dir=strcat(path,s);
                dp=opendir(entire_dir);
                if(dp==NULL)
                {
                    printf("Cannot open folder.\n");
                    return;
                }
                printf("Serial number:   Folder name:   \n");
                while((dir=readdir(dp))!=NULL)
                {
                    count++;
                    if(count>-1)
                    {
                        file[count]=(char*)malloc(MAX_SIZE);
                        if(file[count]==NULL)
                        {
                            printf("Not enough spaces for storing files.\n");
                            return;
                        }
                        strcpy(file[count],dir->d_name);
                        printf("%d   %s\n",count+1,file[count]);
                    }
                }
                if(count==-1)
                {
                    printf("No file found.\n");
                    return;
                }
                printf("Enter file serial to view file : \n");
                scanf("%d",&input);
                printf("\nSelected file to view is %s : \n",file[input-1]);
                filename=strcat(entire_dir,file[input-1]);
                FILE *fp;
                fp=fopen(filename,"r+");
                if(fp==NULL)
                {
                    printf("Cannot read file.\n");
                    return;
                }
                printf("\nFile has been found.\nShowing file elements : \n\n");
                {
                    while(1)
                    {
                        char ch=fgetc(fp);
                        if(feof(fp))
                        {
                            break;
                        }
                        putchar(ch);

                    }
                    fclose(fp);
                }


}

int main(int argc,char *argv[])
{
    int t,j,c;
    while(1)
    {
        printf("\n\t\t\t\t    --------------------------------------------\t\t\t\t  ");
        printf("\n\n\t\t\t\t\t  Welcome To Your Own Personal Diary\t\t\t\t  \n");
        printf("\n\t\t\t\t    --------------------------------------------\t\t\t\t  ");
        printf("\n\t\t\t\t\t\t     Main Menu\t\t\t\t\t  \n");
        printf("\n\t\t\t\t     0   >>   Exit Program\t\t\t\t\t\t  ");
        printf("\n\t\t\t\t     1   >>   Add Record\t\t\t\t\t\t\t  ");
        printf("\n\t\t\t\t     2   >>   View Record\t\t\t\t\t\t  \n");
        printf("\n\t\t\t\t     Enter your choice:  ");
        scanf("%d",&c);

        switch(c)
        {
        case 0:
            exit(1);

        case 1:
            addnote();
            break;
        case 2:
            viewnote();
            break;
        default:
            printf("\nWrong choice!");
            break;
        }
    }
}
