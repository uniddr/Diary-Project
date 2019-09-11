#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<conio.h>
#include<string.h>

void addnote();
typedef struct entry
{
    char date[12];
    char time[12];
    char title[30];
    char body[1000];
}entry;

void addnote()
{
    system("cls");
    int ch1,ch2;
    entry e;
    FILE *fp;
    char filetitle[255];
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
        strftime(rtime,sizeof(rtime), "%d/%m/%Y", tm_info);
        strcpy(e.date, rtime);
        strftime(rtime,sizeof(rtime), "%H:%M", tm_info);
        strcpy(e.time, rtime);
    }
    else if(ch1==1)
    {
        printf("Enter date: ");
        gets(e.date);
        fflush(stdin);
        printf("\nEnter time: ");
        gets(e.time);
        fflush(stdin);
    }
    printf("Enter note title: ");
    gets(e.title);
    fflush(stdin);
    _getch();
    //if((fp=fopen())
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
