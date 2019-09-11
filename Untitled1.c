#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<conio.h>
#include<string.h>
#include<dirent.h>

void addnote();
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
    int ch1;
    entry e;
    FILE *fp;
    DIR *entdir;
    struct dirent *subdirread;
    char buffer1[25]={"./"},buffer2[25]={"./"},ch;
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
        printf("Enter date(dd-mm-yyyy): ");
        gets(e.date);
        fflush(stdin);
    }
    strcat(buffer1,e.date);
    strcat(buffer1,"/");
    if((entdir=opendir(buffer1))==NULL)
    {
        //gonna make a directory here.
    }
    else
    {
        printf("\nSuccessfully opened entry directory!\n");
        if(ch1==1)
        {
            printf("Enter time(hh-mm): ");
            gets(e.time);
        }
        strcat(buffer2,e.date);
        strcat(buffer2,"/");
        strcat(buffer2,e.time);
        if((fp=fopen(buffer2,"rb+"))!=NULL)
        {
            printf("This entry already exists.Use Edit Entry from menu to edit the existing entry or delete the entry first!");
            _getch();
        }
        else
        {
            if((fp=fopen(buffer2,"wb+"))==NULL)
            {
                printf("Unable to create entry!");
                _getch();
                return;
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
            /*while((ch=fgetc(fp))!=EOF)
            {
                putc(ch,stdout);
            }*/
            fclose(fp);
            closedir(entdir);
            _getch();
        }
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
                editnote();
                break;

        default:
            printf("\nWrong choice!");
            break;
        }
        system("cls");
    }
}
