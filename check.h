#include<stdlib.h>
#include<string.h>
#include<ctype.h>
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
char *substr(char *str,int start,int end)
{
    int k=-1,index;
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
   int k=0,day,month,year,i,c_digit=0,pos[8]={0,1,3,4,6,7,8,9};
   char *p1,*p2,*p3;
   if(date[2]!='-'||date[5]!='-'||strlen(date)>10)
   {
       return 0;
   }
   for(k=0;k<8;k++)
   {
       if(isdigit(date[pos[k]]))
       {
           c_digit++;
       }
   }
   if(c_digit<8)
   {
       return 0;
   }
   p1=substr(date,0,1);
   p2=substr(date,3,4);
   p3=substr(date,6,9);
   day=atoi(p1);
   month=atoi(p2);
   year=atoi(p3);
   if(day>31||month>12||year>=3000||day<=0||month<=0||year<2000)
   {
       return 0;
   }
   if(month==1||month==3||month==5||month==7||month==8||month==10||month==12)
   {
       if(1<=day&&day<=31)
       {
           return 1;
       }
   }
   else if(month==4||month==6||month==9||month==11)
   {
       if(1<=day&&day<=30)
       {
           return 1;
       }
       else if(day>30)
       {
           return 0;
       }
   }
   else if(month==2)
   {
       i=leapyear(year);
       printf("i=%d\n",i);
       if(i==0)
       {
           if(1<=day&&day<=28)
           {
               return 1;
           }
           else if(day>28)
           {
               return 0;
           }
       }
        else if(i==1)
       {
           if(1<=day&&day<=29)
           {
               return 1;
           }
           else if(day>29)
           {
               return 0;
           }
       }
   }

}

int check_tm(char *time)
{
    int k,c_digit=0,hour,minute,pos[4]={0,1,3,4};
    char *p1,*p2;
    if(time[2]!='-'||strlen(time)>5)
    {
        return 0;
    }
    for(k=0;k<4;k++)
    {
        if(isdigit(time[pos[k]]))
        {
            c_digit++;
        }
    }
    if(c_digit<4)
    {
        return 0;
    }
    p1=substr(time,0,1);
    p2=substr(time,3,4);
    hour=atoi(p1);
    minute=atoi(p2);
    if(hour<=0||hour>12||minute<0||minute>60)
    {
        return 0;
    }
    else
        {
            return 1;
        }
}
