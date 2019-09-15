#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<dirent.h>
#include<dir.h>
#include<process.h>
#include<time.h>
int chk_dt(char *str)
{
        int k,count=0;
        for(k=0;k<strlen(str)-1;k++)
        {
            switch(k)
            {
                case 0:
                if('0'<=str[k]<='3'){count++;}
                case 1:
                if('0'<=str[k]<='1'){count++;}
                case 2:
                if(str[k]=='-'){count++;}
                case 3:
                if('0'<=str[k]<='1'){count++;}
                case 4:
                if('0'<=str[k]<='2'){count++;}
                case 5:
                if(str[k]=='-'){count++;}
                case 6:
                if('0'<=str[k]<='9'){count++;}
                case 7:
                if('0'<=str[k]<='9'){count++;}
                case 8:
                if('0'<=str[k]<='9'){count++;}
                case 9:
                if('0'<=str[k]<='9'){count++;}
            }
        }
        if(count<10)
        {
            return 0;
        }

}
int check(char *dir)
{
    DIR *dp;
    dp=opendir(dir);
    if(dp==NULL)
    {
        printf("Warning!!!Invalid path.\n");
        return -1;
    }
}
void open_dir(char *dir)
{
    char *d;
    int k;
    struct dirent *di;
    DIR *dp;
    dp=opendir(dir);
    if(dp==NULL)
    {
        printf("Cannot open directory.\n");
    }
    printf("Showing all folders in %s : \n\n",dir);
    printf("Serial Number:  Folder Name: \n");
    while((di=readdir(dp))!=NULL)
    {
       d=di->d_name;
       for(k=0;d[k];k++)
       {
           if(k==0)
           {
               printf("%c  ",d[k]);
           }
           else
           {
               printf("%c",d[k]);
           }
       }
       printf("\n");
    }
}
int fcount(char *dirname)
{
    int count=-2;
    struct dirent *dir;
    DIR *dp;
    dp=opendir(dirname);
    if(dp==NULL)
    {
        printf("Cannot open directory.\n");
        return 0;
    }
    while((dir=readdir(dp))!=NULL)
    {
        if((dir->d_name)!=NULL)
        {
            count++;
        }
    }
    return count;
}
typedef struct entry
{
    char date[12];
    char time[12];
    char title[200];
    char body[1000];
}entry;
void addnote()
{
    entry e;
    char pathname[50],dirname[50],*path,*entire_path,*entire_dir,str[50],p[10];
    int i=92,ch,value,f_num;
    printf("\n\t\t\t\t\t\t     ADD MENU\t\t\t\t\t\t\n");
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
        printf("\nPRESS 0 To return\nPRESS 1 To create directory\nPRESS 2 To create file.\n");
        printf("Enter your choice : \n");
        scanf("%d",&ch);
        switch(ch)
        {
        case 0:
            return;
        case 1:
        printf("Enter a valid path name (Finish with %c) \n: ",i);
        fflush(stdin);
        gets(pathname);
        printf("Checking for path\n");
        int k=check(pathname);
        if(k==-1)
        {
            return;
        }
        printf("Total folders in this directory %d : \n",fcount(pathname));
        printf("Enter a directory [dd-mm-yyyy] (Finish with %c) \n: ",i);
        fflush(stdin);
        gets(e.date);
        printf("Checking for access.\n");
        k=chk_dt(e.date);
        if(k==0)
        {
            printf("Invalid entry.\n");
            return;
        }
        sprintf(str,"%d",fcount(pathname)+1);
        entire_dir=strcat(str,e.date);
        path=strcat(pathname,entire_dir);
        value=mkdir(path);
        if(value==0)
        {
            printf("Sub folder has been created.\n");
        }
        else
        {
            printf("This folder already exists.\n");
            return;
        }
        break;
        case 2:
            printf("Enter a valid path name : \n");
            fflush(stdin);
            gets(pathname);
            f_num=fcount(pathname);
            printf("Total folders >>> %d\n",f_num);
            if(f_num==0)
            {
                printf("Cannot create file.\n");
                return;
            }
            else
            {
                int count=0;
                FILE *fp;
                open_dir(pathname);
                char filename[50],s[50],*file,*entire_file;
                struct dirent *dir;
                DIR *dp;
                dp=opendir(pathname);
                if(dp==NULL)
                {
                    printf("Cannot open directory.\n");
                    return;
                }
                printf("Enter folder serial number : ");
                scanf("%d",&value);
                sprintf(str,"%d",value);
                while((dir=readdir(dp))!=NULL)
                {
                    if(strncmp(str,(dir->d_name),1)==0)
                    {
                        count++;
                        entire_dir=strcat(pathname,dir->d_name);
                        printf("Matched folder ->-> %s\n",entire_dir);
                    }
                }
                if(count==0)
                {
                    printf("This folder does not exist.\n");
                    return;
                }
                else
                printf("Enter %c to create file path : ",i);
                scanf("%s",p);
                entire_path=strcat(entire_dir,p);
                sprintf(s,"%d",fcount(entire_path)+1);
                printf("Enter a file name [hh-mm] : \n");
                fflush(stdin);
                gets(filename);
                entire_file=strcat(s,filename);
                file=strcat(entire_path,entire_file);
                fp=fopen(file,"w+");
                if(fp==NULL)
                {
                    return;
                }
                else
                    {
                        printf("Enter title : ");
                        fflush(stdin);
                        gets(e.title);
                        fprintf(fp,"%s",e.title);
                        printf("Enter note : ");
                        fflush(stdin);
                        gets(e.body);
                        fprintf(fp,"%s",e.body);
                    }
                    fclose(fp);
                    return;

            }
    }
}
}
void viewnote()
{
        char pathname[50],dirname[50],*path,*entire_path,*entire_dir;
        char *file,str[50],p[10],q[50];
        int i=92,ch,value,f_num,count=0;
        FILE *fp;
        entry e;
        printf("Enter a valid path name (Finish with %c) \n: ",i);
        fflush(stdin);
        gets(pathname);
        printf("Checking for path\n");
        int k=check(pathname);
        if(k==-1)
        {
            return;
        }
        open_dir(pathname);
        if(fcount(pathname)==0)
        {
            printf("Folder is empty.\n");
            return;
        }
        printf("Enter folder serial number to view : \n");
        scanf("%d",&f_num);
        sprintf(str,"%d",f_num);
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
                    if(strncmp(str,(dir->d_name),1)==0)
                    {
                        count++;
                        entire_dir=strcat(pathname,dir->d_name);
                        printf("Selected folder to view ->-> %s\n",entire_dir);
                    }
                }
                if(count==0)
                {
                    printf("This folder does not exist.\n");
                    return;
                }
                else
                printf("Enter %c to create file path : ",i);
                scanf("%s",p);
                entire_path=strcat(entire_dir,p);
                open_dir(entire_path);
                if(fcount(entire_path)==0)
                {
                    printf("Files not found.\n");
                    return;
                }
                printf("Enter file serial number : \n");
                scanf("%d",&value);
                sprintf(q,"%d",value);
                dp=opendir(entire_path);
                if(dp==NULL)
                {
                    printf("Cannot open folder.\n");
                    return;
                }
                while((dir=readdir(dp))!=NULL)
                {
                    if(strncmp(q,(dir->d_name),1)==0)
                    {
                        file=strcat(entire_path,dir->d_name);
                        printf("Selected file to view ->-> %s\n",file);
                    }
                }
                fp=fopen(file,"r+");
                if(fp==NULL)
                {
                    printf("File cannot be found.\n");
                    return;
                }
                printf("Showing file elements.\n\n");
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
    return 0;
}
