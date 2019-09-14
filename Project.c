#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<dir.h>
#include<dirent.h>
#include<process.h>
#include<time.h>
void addnote();
void viewnote();
int fcount(char *dir_name)
{
     int filecount=-2;
     struct dirent *dir;
     DIR *dp;
     dp=opendir(dir_name);
     if(dp==NULL)
     {
         printf("Cannot open directory.\n");
     }
     while((dir=readdir(dp))!=NULL)
     {
      if((dir->d_name)!=NULL)
          {
              filecount++;
          }
     }
      return filecount;

}
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
    struct dirent *dir;
    entry e;
    DIR *dp;
    FILE *fp;
    int value,in,i=92,ch1,file_count;
    char dirname[50],*entire_dir,*entire_path,*entire_file,s_num[50];
    char path_name[50],filename[50],str[50];
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
        printf("Enter a valid path name(Finish with %c) : ",i);
        fflush(stdin);
        gets(path_name);
        printf("Enter date(dd-mm-yyyy(Finish with %c)): ",i);
        fflush(stdin);
        gets(e.date);
        fflush(stdin);
        entire_dir=strcat(path_name,e.date);
        value=mkdir(entire_dir);
    if(!value)
    {
        printf("Directory has been created.\n");
    }
    else
        {
            printf("This directory already exists.\n");
        }
    if(fcount(entire_dir)==0)
    {
        printf("This directory is empty.\n");
        file_count=fcount(entire_dir);
        printf("Enter a name to create %d-th file [hh-mm] : ",file_count+1);
        sprintf(s_num,"%d",file_count+1);
        fflush(stdin);
        gets(e.time);
        entire_file=strcat(s_num,e.time);
        entire_path=strcat(entire_dir,entire_file);
        fp=fopen(entire_path,"w+");
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
       else
    {
        dp=opendir(entire_dir);
        if(dp==NULL)
        {
            printf("Cannot open directory.\n");
        }
        while((dir=readdir(dp))!=NULL)
        {
            printf("%s\n",dir->d_name);
        }
        file_count=fcount(entire_dir);
        printf("Enter a name to create %d-th file [hh-mm]: ",file_count+1);
        sprintf(s_num,"%d",file_count+1);
        fflush(stdin);
        gets(e.time);
        entire_file=strcat(s_num,e.time);
        entire_path=strcat(entire_dir,entire_file);
        fp=fopen(entire_path,"w+");
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
}
}
void viewnote()
{
    int i=92,in,file_num;
    FILE *fp;
    struct dirent *dir;
    DIR *dp;
    char pathname[50],dirname[50],*entire_path,*entire_dir,str[50],*filename;
    printf("Enter a valid path name(Finish with %c) : ",i);
    fflush(stdin);
    gets(pathname);
    printf("Enter date(dd-mm-yyyy(Finish with %c)): ",i);
    fflush(stdin);
    gets(dirname);
    entire_dir=strcat(pathname,dirname);
    dp=opendir(entire_dir);
    if(dp==NULL)
    {
        printf("Cannot open directory.\n");
    }
    printf("Total %d files showing below >>> \n",fcount(entire_dir));
    while((dir=readdir(dp))!=NULL)
    {
            printf("%s\n",dir->d_name);
    }
    printf("Enter file serial number [Please enter the first digit from left] : ");
    scanf("%d",&file_num);
    sprintf(str,"%d",file_num);
    dp=opendir(entire_dir);
    while((dir=readdir(dp))!=NULL)
    {
        if(strncmp(str,(dir->d_name),1)==0)
        {
            printf("%s\n",dir->d_name);
            filename=dir->d_name;
        }
    }
    entire_path=strcat(entire_dir,filename);
    fp=fopen(entire_path,"r+");
    if(fp==NULL)
    {
        printf("Cannot read file.\n");
    }
    else
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
        }
        fclose(fp);

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
    return 0;
}
