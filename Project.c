#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<conio.h>
#include<string.h>
#include<dirent.h>
#include<sys/stat.h>
#include<errno.h>

typedef struct entry
{
    char date[12];
    char time[12];
    char title[200];
    char body[1000];
}entry;

void addnote()
{
    system("cls");
    int ch,i;
    entry e;
    FILE *fp;
    DIR *entdir;
    struct dirent *subdirread;
    char dirname[25]={"./Notes/"},filename[25]={"./Notes/"},c;
    printf("\n\t\t\t\t\t\tADD MENU\t\t\t\t\t  \n");
    printf("\t\t\t\t--------------------------------------------\t\t\t\t  ");
    printf("\n\t\t\t\t 0   >>   To use system date and time\t\t\t\t\t\t  ");
    printf("\n\t\t\t\t 1   >>   To use custom date and time\t\t\t\t\t\t  \n");
    printf("\n\t\t\t\t Enter your choice:  ");
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
        fflush(stdin);
        printf("Enter date(dd-mm-yyyy): ");
        gets(e.date);
        fflush(stdin);
    }
    if((entdir=opendir(dirname))==NULL)
    {
        if((mkdir(dirname))==-1)
        {
            printf("Error handling path! ");
            return;
        }
    }
    closedir(entdir);
    strcat(dirname,e.date);
    strcat(dirname,"/");
    if((entdir=opendir(dirname))==NULL)
    {
        if(!(mkdir(dirname)))
        {
            printf("Directory successfully created!");
            entdir=opendir(dirname);
        }
        else
        {
            printf("Failed to create directory!");
        }
    }
    printf("\nSuccessfully opened entry directory!\n");
    if(ch==1)
    {
        printf("Enter time(hh-mm): ");
        gets(e.time);
    }
    strcat(filename,e.date);
    strcat(filename,"/");
    strcat(filename,e.time);
    if((fp=fopen(filename,"rb+"))!=NULL)
    {
        printf("This entry already exists.Use Edit Option from menu to edit the existing entry or delete the entry first!\n\nPress any key to go back to main menu");
        _getch();
    }
    else
    {
        if((fp=fopen(filename,"wb+"))==NULL)
        {
            printf("Unable to create entry!");
            _getch();
            return;
        }
        printf("Enter title: ");
        fflush(stdin);
        gets(e.title);
        for(i=0;i<strlen(e.title);i++)
        {
            c=e.title[i];
            c=c+4;
            c=c^150;
            e.title[i]=c;
        }
        fputs(e.title,fp);
        fputs("\n",fp);
        for(i=0;i<strlen(e.title);i++)
        {
            fputs("-",fp);
        }
        fputs("---\n",fp);
        printf("\nEnter the note: ");
        fflush(stdin);
        gets(e.body);
        for(i=0;i<strlen(e.body);i++)
        {
            c=e.body[i];
            c=c+4;
            c=c^150;
            e.body[i]=c;
        }
        fputs(e.body,fp);
        fclose(fp);
        closedir(entdir);
        printf("\n\nEntry created successfully! Press any key to go back to main menu ");
        _getch();
    }
}
void viewnote()
{
    system("cls");
    int f=0,ch;
    long int choice;
    char pathname[50]={"./Notes/"},name[500][15],choice_check[20],*choice_remain;
    struct dirent *dir;
    DIR *dp;
    printf("\n\t\t\t\t\t\t     VIEW MENU\t\t\t\t\t  \n");
    printf("\t\t\t\t    --------------------------------------------\t\t\t\t  ");
    if((dp=opendir(pathname))==NULL)
    {
        printf("\n\n\n\nCannot open directory to view.Press any key to go back to main menu.\n");
        fflush(stdin);
        _getch();
        return;
    }
    printf("\n\t\t\t\t     SN:   Name:\t\t\t\t\t\t  \n");
    while((dir=readdir(dp))!=NULL)
    {
        if((strcmp(dir->d_name,"..")!=0)&&(strcmp(dir->d_name,".")!=0))
        {
            strcpy(name[f],dir->d_name);
            printf("\n\t\t\t\t     %d.   %s",f+1,name[f]);
            f++;
        }
    }
    if(f==0)
    {
        printf("No folder found.\n");
        return;
    }
    closedir(dp);
    while(1)
    {
        fflush(stdin);
        printf("\n\n\t\t\t\t     Enter serial no. of date to view : ");
        fgets(choice_check,20,stdin);
        errno=0;
        choice=strtol(choice_check,&choice_remain,10);
        if((errno==ERANGE)||(choice==0 && errno!=0)||(choice_remain==choice_check)||(*choice_remain!='\n'))
        {
            perror("Error!  ");
            printf("Press any key to go back to main menu.\n");
            fflush(stdin);
            _getch();
            return;
        }
        if((choice<=f)&&(choice>=1))
        {
            break;
        }
        else
        {
            fflush(stdin);
            printf("\n\t\t\t\t     Wrong choice! ");
            printf("Press any key to choose again.");
            _getch();
        }
    }
    strcat(pathname,name[choice-1]);
    strcat(pathname,"/");
    dp=opendir(pathname);
    if(dp==NULL)
    {
        printf("\n\t\t\t\t     Cannot open folder.\n");
        return;
    }
    system("cls");
    f=0;
    printf("\n\t\t\t\t     SN:  Name:   \n");
    while((dir=readdir(dp))!=NULL)
    {
        if((strcmp(dir->d_name,"..")!=0)&&(strcmp(dir->d_name,".")!=0))
        {
            strcpy(name[f],dir->d_name);
            printf("\n\t\t\t\t     %d.   %s",f+1,name[f]);
            f++;
        }
    }
    if(f==0)
    {
        printf("\n\t\t\t\t     No file found.\n");
        return;
    }
    closedir(dp);
    while(1)
    {
        fflush(stdin);
        printf("\n\n\t\t\t\t     Enter serial no. of time to view : ");
        fgets(choice_check,20,stdin);
        errno=0;
        choice=strtol(choice_check,&choice_remain,10);
        if((errno==ERANGE)||(choice==0 && errno!=0)||(choice_remain==choice_check)||(*choice_remain!='\n'))
        {
            printf("Error!  ");
            printf("Press any key to go back to main menu.\n");
            fflush(stdin);
            _getch();
            return;
        }
        if((choice<=f)&&(choice>=1))
        {
            break;
        }
        else
        {
            fflush(stdin);
            printf("\n\t\t\t\t     Wrong choice! ");
            printf("Press any key to choose again.");
            _getch();
        }
    }
    strcat(pathname,name[choice-1]);
    FILE *fp;
    if((fp=fopen(pathname,"rb+"))==NULL)
    {
        printf("\n\n\t\t\t\t     Cannot read file.\n");
        return;
    }
    system("cls");
    printf("\n\n\t\t\t\t     Showing file elements : \n\n");
    {
        while(1)
        {
            if((ch=fgetc(fp))!=EOF)
            {
                if((ch!='\n')&&(ch!='-'))
                {
                    ch=ch^150;
                    ch=ch-4;
                }
                putc(ch,stdout);
            }
            else
            {
                break;
            }
        }
        fclose(fp);
    }
    fflush(stdin);
    printf("\n\nPress any key to go back to main menu ");
    _getch();
}
void editnote()
{
    system("cls");
    entry e;
    int f=0,ch;
    long int choice;
    char pathname[50]={"./Notes/"},name[500][15],choice_check[20],*choice_remain;
    struct dirent *dir;
    DIR *dp;
    printf("\n\t\t\t\t\t\t     EDIT MENU\t\t\t\t\t  \n");
    printf("\t\t\t\t    --------------------------------------------\t\t\t\t  ");
    if((dp=opendir(pathname))==NULL)
    {
        printf("\n\n\n\nCannot open directory to view.Press any key to go back to main menu.\n");
        fflush(stdin);
        _getch();
        return;
    }
    printf("\n\t\t\t\t     SN:   Name:\t\t\t\t\t\t  \n");
    while((dir=readdir(dp))!=NULL)
    {
        if((strcmp(dir->d_name,"..")!=0)&&(strcmp(dir->d_name,".")!=0))
        {
            strcpy(name[f],dir->d_name);
            printf("\n\t\t\t\t     %d.   %s",f+1,name[f]);
            f++;
        }
    }
    if(f==0)
    {
        printf("No folder found.\n");
        return;
    }
    closedir(dp);
    while(1)
    {
        fflush(stdin);
        printf("\n\n\t\t\t\t     Enter serial no. of date to view : ");
        fgets(choice_check,20,stdin);
        errno=0;
        choice=strtol(choice_check,&choice_remain,10);
        if((errno==ERANGE)||(choice==0 && errno!=0)||(choice_remain==choice_check)||(*choice_remain!='\n'))
        {
            perror("Error");
            printf("Press any key to go back to main menu.\n");
            fflush(stdin);
            _getch();
            return;
        }
        if((choice<=f)&&(choice>=1))
        {
            break;
        }
        else
        {
            fflush(stdin);
            printf("\n\t\t\t\t     Wrong choice! ");
            printf("Press any key to choose again.");
            _getch();
        }
    }
    strcat(pathname,name[choice-1]);
    strcat(pathname,"/");
    dp=opendir(pathname);
    if(dp==NULL)
    {
        printf("\n\t\t\t\t     Cannot open folder.\n");
        return;
    }
    system("cls");
    f=0;
    printf("\n\t\t\t\t     SN:  Name:   \n");
    while((dir=readdir(dp))!=NULL)
    {
        if((strcmp(dir->d_name,"..")!=0)&&(strcmp(dir->d_name,".")!=0))
        {
            strcpy(name[f],dir->d_name);
            printf("\n\t\t\t\t     %d.   %s",f+1,name[f]);
            f++;
        }
    }
    if(f==0)
    {
        printf("\n\t\t\t\t     No file found.\n");
        return;
    }
    closedir(dp);
    while(1)
    {
        fflush(stdin);
        printf("\n\n\t\t\t\t     Enter serial no. of time to view : ");
        fgets(choice_check,20,stdin);
        errno=0;
        choice=strtol(choice_check,&choice_remain,10);
        if((errno==ERANGE)||(choice==0 && errno!=0)||(choice_remain==choice_check)||(*choice_remain!='\n'))
        {
            printf("Error!");
            printf("Press any key to go back to main menu.\n");
            fflush(stdin);
            _getch();
            return;
        }
        if((choice<=f)&&(choice>=1))
        {
            break;
        }
        else
        {
            fflush(stdin);
            printf("\n\t\t\t\t     Wrong choice! ");
            printf("Press any key to choose again.");
            _getch();
        }
    }
    strcat(pathname,name[choice-1]);
    FILE *fp;
    if((fp=fopen(pathname,"rb"))==NULL)
    {
        printf("\n\n\t\t\t\t     Could not open file! Press any key to return to main menu.\n");
        _getch();
        return;
    }
    fclose(fp);
    if((fp=fopen(pathname,"wb+"))==NULL)
    {
        printf("\n\n\t\t\t\t     Could not edit file! Press any key to return to main menu.\n");
        _getch();
        return;
    }
    system("cls");
    printf("Enter title: ");
        fflush(stdin);
        gets(e.title);
        fputs(e.title,fp);
        fputs("\n",fp);
        for(int i=0;i<strlen(e.title);i++)
        {
            fputs("-",fp);
        }
        fputs("---\n",fp);
        printf("\nEnter the note: ");
        fflush(stdin);
        gets(e.body);
        fputs(e.body,fp);
        fclose(fp);


    fflush(stdin);
    printf("\n\nPress any key to go back to main menu ");
    _getch();
}
void deletenote()
{
    system("cls");
    entry e;
    int f=0,ch,i;
    long int choice;
    char pathname[50]={"./Notes/"},name[500][15],choice_check[20],*choice_remain;
    struct dirent *dir;
    DIR *dp;
    printf("\n\t\t\t\t\t\t     DELETE MENU\t\t\t\t\t  \n");
    printf("\t\t\t\t    --------------------------------------------\t\t\t\t  ");
    if((dp=opendir(pathname))==NULL)
    {
        printf("\n\n\n\nCannot open directory to view.Press any key to go back to main menu.\n");
        fflush(stdin);
        _getch();
        return;
    }
    printf("\n\t\t\t\t     SN:   Name:\t\t\t\t\t\t  \n");
    while((dir=readdir(dp))!=NULL)
    {
        if((strcmp(dir->d_name,"..")!=0)&&(strcmp(dir->d_name,".")!=0))
        {
            strcpy(name[f],dir->d_name);
            printf("\n\t\t\t\t     %d.   %s",f+1,name[f]);
            f++;
        }
    }
    if(f==0)
    {
        printf("No folder found.\n");
        return;
    }
    closedir(dp);
    while(1)
    {
        fflush(stdin);
        printf("\n\n\t\t\t\t     Enter serial no. of date to view : ");
        fgets(choice_check,20,stdin);
        errno=0;
        choice=strtol(choice_check,&choice_remain,10);
        if((errno==ERANGE)||(choice==0 && errno!=0)||(choice_remain==choice_check)||(*choice_remain!='\n'))
        {
            perror("Error");
            printf("Press any key to go back to main menu.\n");
            fflush(stdin);
            _getch();
            return;
        }
        if((choice<=f)&&(choice>=1))
        {
            break;
        }
        else
        {
            fflush(stdin);
            printf("\n\t\t\t\t     Wrong choice! ");
            printf("Press any key to choose again.");
            _getch();
        }
    }
    strcat(pathname,name[choice-1]);
    strcat(pathname,"/");
    dp=opendir(pathname);
    if(dp==NULL)
    {
        printf("\n\t\t\t\t     Cannot open folder.\n");
        return;
    }
    system("cls");
    f=0;
    printf("\n\t\t\t\t     SN:  Name:   \n");
    while((dir=readdir(dp))!=NULL)
    {
        if((strcmp(dir->d_name,"..")!=0)&&(strcmp(dir->d_name,".")!=0))
        {
            strcpy(name[f],dir->d_name);
            printf("\n\t\t\t\t     %d.   %s",f+1,name[f]);
            f++;
        }
    }
    if(f==0)
    {
        printf("\n\t\t\t\t     No file found.\n");
        return;
    }
    closedir(dp);
    while(1)
    {
        fflush(stdin);
        printf("\n\n\t\t\t\t     Enter serial no. of time to view : ");
        fgets(choice_check,20,stdin);
        errno=0;
        choice=strtol(choice_check,&choice_remain,10);
        if((errno==ERANGE)||(choice==0 && errno!=0)||(choice_remain==choice_check)||(*choice_remain!='\n'))
        {
            perror("Error");
            printf("Press any key to go back to main menu.\n");
            fflush(stdin);
            _getch();
            return;
        }
        if((choice<=f)&&(choice>=1))
        {
            break;
        }
        else
        {
            fflush(stdin);
            printf("\n\t\t\t\t     Wrong choice! ");
            printf("Press any key to choose again.");
            _getch();
        }
    }
    strcat(pathname,name[choice-1]);
    FILE *fp;
    if((fp=fopen(pathname,"rb"))==NULL)
    {
        printf("\n\n\t\t\t\t     Could not find file! Press any key to return to main menu.\n");
        _getch();
        return;
    }
    fclose(fp);
    if((i=remove(pathname))==0)
    {
        printf("\n\n\t\t\t     Entry deleted successfully! Press any key to return to main menu.\n");
        _getch();
        return;
    }
    else
    {
        printf("\n\n\t\t\t\t     Unable to delete entry! Press any key to return to main menu.\n");
        _getch();
        return;
    }
}

int main(int argc,char *argv[])
{
    int t,j,c;
    while(1)
    {
        printf("\n\t\t\t--------------------------------------------\t\t\t\t  ");
        printf("\n\n\t\t\t\tWelcome To Your Own Personal Diary\t\t\t\t  \n");
        printf("\n\t\t\t--------------------------------------------\t\t\t\t  ");
        printf("\n\t\t\t\t\t Main Menu\t\t\t\t\t  \n");
        printf("\n\t\t\t 0   >>   Exit Program\t\t\t\t\t\t  ");
        printf("\n\t\t\t 1   >>   Add Record\t\t\t\t\t\t  ");
        printf("\n\t\t\t 2   >>   View Record\t\t\t\t\t\t  ");
        printf("\n\t\t\t 3   >>   Edit Record\t\t\t\t\t\t  ");
        printf("\n\t\t\t 4   >>   Delete Record\t\t\t\t\t\t  \n");
        printf("\n\t\t\t Enter your choice:  ");
        scanf("%d",&c);

        switch(c)
        {
        case 0:
            system("cls");
            printf("\n\n\t\t\t\t\tThank you for using the software! \n\n\n\n");
            exit(1);

        case 1:
            addnote();
            break;

        case 2:
            viewnote();
            break;

        case 3:
            editnote();
            break;

        case 4:
            deletenote();
            break;

        default:
            printf("\n\t\t\t\t     Wrong choice! ");
            printf("Press any key to choose again.");
            _getch();
            fflush(stdin);
            break;
        }
        system("cls");
    }
}
