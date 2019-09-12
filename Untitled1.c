#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<dir.h>
#include<dirent.h>
#include<process.h>
#include<time.h>
void addnote();
void viewnote();
typedef struct entry
{
    char date[12];
    char time[12];
    char title[100];
    char body[1000];
}
entry;
void addnote()
{
      system("cls");
      int ch1,i=92,value;
      entry e;
      FILE *fp;
      char pathname[50],*entire_path,*entire_dir;

    printf("\n\t\t\t\t\t\t     ADD MENU\t\t\t\t\t  \n");
    printf("\t\t\t\t    --------------------------------------------\t\t\t\t  ");
    printf("\n\t\t\t\t     0   >>   To use system date and time\t\t\t\t\t\t  ");
    printf("\n\t\t\t\t     1   >>   To use custom date and time\t\t\t\t\t\t  \n");
    printf("\n\t\t\t\t     Enter your choice:  ");
    scanf("%d",&ch1);
    if(ch1==0)
    {
        time_t timer;
        char rtime[12]="";
        struct tm* tm_info;

        time(&timer);//retrieves the system date+time
        tm_info = localtime(&timer);//returns a convertible system date+time
        strftime(rtime,sizeof(rtime), "%d-%m-%Y", tm_info);
        strcpy(e.date, rtime);
        strftime(rtime,sizeof(rtime), "%H:%M", tm_info);
        strcpy(e.time, rtime);
    }
    else if(ch1==1)
    {
        fflush(stdin);
        printf("Enter date(dd-mm-yyyy(Finish with %c)): ",i);
        gets(e.date);
        fflush(stdin);
    }
      printf("Please enter path name (Finish with %c): ",i);
      gets(pathname);
      entire_dir=strcat(pathname,e.date);
      value=mkdir(entire_dir);
      if(!value)
      {
          printf("This directory has been created.\n");
      }
      else
        {
            printf("This entry already exists.Use Edit Entry from menu to edit the existing entry or delete the entry first!");
        }
                if(ch1==1)
        {
            printf("Enter time(hh-mm): ");
            fflush(stdin);
            gets(e.time);
        }
        entire_path=strcat(entire_dir,e.time);
        fp=fopen(entire_path,"w");
        if(fp==NULL)
        {
            printf("Cannot open file.\n");
        }
            printf("Enter title: ");
            fflush(stdin);
            gets(e.title);
            fputs(e.title,fp);
            fputs("\n",fp);
            printf("Enter the note: ");
            fflush(stdin);
            gets(e.body);
            fputs(e.body,fp);
            rewind(fp);


}
void viewnote()
{
     int i=92;
     struct dirent *dir_name;
     FILE *fp;
     DIR *dp;
     char pathname[50],filename[50];
     printf("Enter path name (Finish with %c): ",i);
     fflush(stdin);
     gets(pathname);
     dp=opendir(pathname);
     if(dp==NULL)
     {
         printf("This directory does not exist.\n");
     }
     else
     {
         printf("Files exist in %s : \n",pathname);
         while((dir_name=readdir(dp))!=NULL)
         {
             printf("%s\n",dir_name->d_name);
         }
     }
     printf("Enter file name : ");
     gets(filename);
     fp=fopen(strcat(pathname,filename),"r");
     if(fp==NULL)
     {
         printf("File does not exist.\n");
     }
     printf("Success!!!File has been found.\n");
     rewind(fp);

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
        system("cls");
    }
    return 0;
}

