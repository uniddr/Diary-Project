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
    char pathname[50],*path,s[10],*entire_dir,*filename;
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
                dp=opendir(pathname);
                printf("\nShowing folders in %s : \n",pathname);
                printf("Serial number:   Folder name:   \n");
                while((dir=readdir(dp))!=NULL)
                {
                    f++;
                    printf("%d   %s\n",f+1,dir->d_name);
                }
                printf("Enter serial number to create file : ");
                scanf("%d",&value);
                dp=opendir(pathname);
                while((dir=readdir(dp))!=NULL)
                {
                    k++;
                    if(k==value)
                    {
                        entire_dir=strcat(pathname,dir->d_name);
                        break;
                    }
                }
                printf("\nEnter %c to create file in %s : ",i,entire_dir);
                fflush(stdin);
                gets(s);
                filename=strcat(entire_dir,s);
                printf("Enter a file name [hh-mm] : ");
                fflush(stdin);
                gets(e.time);
                char *entire_file=strcat(filename,e.time);
                FILE *fp;
                fp=fopen(entire_file,"w+");
                if(fp==NULL)
                {
                    printf("Cannot open file.\n");
                    return;
                }
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
     char pathname[50],*path,s[10],*entire_dir,*filename;
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
                    printf("%d   %s\n",f+1,dir->d_name);
                }
                printf("Enter folder serial to view file : \n");
                scanf("%d",&input);
                dp=opendir(pathname);
                while((dir=readdir(dp))!=NULL)
                {
                    k++;
                    if(k==input)
                    {
                        path=strcat(pathname,dir->d_name);
                        break;
                    }
                }
                printf("Enter %c to view files in %s : ",i,path);
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
                    printf("%d   %s\n",count+1,dir->d_name);
                }
                printf("Enter file serial to view file : \n");
                scanf("%d",&input);
                dp=opendir(entire_dir);
                k=-2;
                while((dir=readdir(dp))!=NULL)
                {
                    k++;
                    if(k==input)
                    {
                        filename=strcat(entire_dir,dir->d_name);
                        break;
                    }
                }
                FILE *fp;
                fp=fopen(filename,"r+");
                if(fp==NULL)
                {
                    printf("Cannot read file.\n");
                    return;
                }
                printf("Showing file elements : \n");
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
        printf("\n\t\t\t\t     1   >>   Add Record\t\t\t\t\t\t  \n");
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
