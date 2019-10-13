#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int leapyear(int year)
{
    if(year%4==0)
    {
        if(year%100==0)
        {
            if(year%400==0)
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }
        else
        {
            return 0;
        }
    }
    else
    {
        return 0;
    }
}
char *strdiv(char *str,int start,int end)
{
    int k=-1,index=start;
    char *p=(char*)malloc(20);
    for(index=start;index<end+1;index++)
    {
        k++;
        p[k]=str[index];
    }
    p[k+1]='\0';
    return p;

}
int check_dt(char *date)
{
   int day,month,year,i,count=0;
   char *p1,*p2,*p3;
   p1=strdiv(date,0,1);
   p2=strdiv(date,3,4);
   p3=strdiv(date,6,strlen(date-1));
   day=atoi(p1);
   month=atoi(p2);
   year=atoi(p3);
   printf("%d %d %d\n",day,month,year);
   if(day==0||month==0||year==0)
   {
       return 0;
   }
   else if(day>31||month>12||year>=3000)
   {
       return 0;
   }
   i=leapyear(year);
   if(month==1||month==3||month==5||month==7||month==8||month==10||month==12)
       {
           if(1<=day<=31)
           {
                 count++;
                 return count;
           }
           return 0;
       }
       else if(month==4||month==6||month==9||month==1)
       {
           if(1<=day<=30)
           {
               count++;
               return count;
           }
           return 0;
       }
       else if(month==2)
       {
           if(i==0)
       {
           if(1<=day<=28)
           {
               count++;
               return count;
           }
           return 0;
       }
       else if(i==1)
       {
           if(1<=day<=29)
           {
               count++;
               return count;
           }
           return 0;
       }
       }
}
int check_tm(char *time)
{
    int hour,minute;
    char *p1,*p2;
    p1=strdiv(time,0,1);
    p2=strdiv(time,3,4);
    hour=atoi(p1);
    minute=atoi(p2);
    if(hour==0||minute==0)
    {
        return 0;
    }
    if(1<=hour<=12&&0<=minute<=60)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
int main()
{
    int value;
    char str[20];
    printf("Enter date : ");
    gets(str);
    value=check_dt(str);
    printf("%d\n",value);
    if(value==0)
    {
        printf("**** ***.\n");
    }
    else
    {
        printf("Date has been entered successfully!!!\n");
    }
    printf("Enter time : ");
    gets(str);
    value=check_tm(str);
    printf("%d\n",value);
    if(value==0)
    {
        printf("**** ***.\n");
    }
    else
    {
        printf("Time has been entered successfully!!!\n");
    }
    return 0;
}
