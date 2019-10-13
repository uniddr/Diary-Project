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
int check_dt(char *str)
{
   int v1,v2,v3,i,count=0;
   char *p1,*p2,*p3;
   p1=strdiv(str,0,1);
   p2=strdiv(str,3,4);
   p3=strdiv(str,6,9);
   v1=atoi(p1);
   v2=atoi(p2);
   v3=atoi(p3);
   if(v1==0||v2==0||v3==0)
   {
       return 0;
   }
   else if(v1>31||v2>12||v3>3000)
   {
       return 0;
   }
   i=leapyear(v3);
   if(v2==1||v2==3||v2==5||v2==7||v2==8||v2==10||v2==12)
       {
           if(1<=v1<=31)
           {
                 count++;
                 return count;
           }
           return 0;
       }
       else if(v2==4||v2==6||v2==9||v2==1)
       {
           if(1<=v1<=30)
           {
               count++;
               return count;
           }
           return 0;
       }
       else if(v2==2)
       {
           if(i==0)
       {
           if(1<=v1<=28)
           {
               count++;
               return count;
           }
           return 0;
       }
       else if(i==1)
       {
           if(1<=v1<=29)
           {
               count++;
               return count;
           }
           return 0;
       }
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
        printf("Success!!!");
    }
    return 0;
}
