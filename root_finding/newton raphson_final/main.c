#include<stdio.h>
#include<math.h>
float y(float x)//function oracle
{
    return ((4-x)*exp(-0.5*x))-2;
}
float y_(float x)//derivative oracle
{
    return 0.5*(x-6)*exp(-0.5*x);
}
float nr(float x,int iter,float tolerance)//nr stands for newton raphson
{
   int iter_max=10000;
   if(iter<iter_max)//ensuring my computer doesnt fry in case the sequence diverges!
   {
       float xr_old=x;//this notation makes it easier for understanding the error formula
       if(y(x)==0)
       {
           return xr_old;
       }
       else
       {
           //avoiding division by 0
           if(y_(xr_old)==0)
           {
               printf("division by 0 error\n");
               return -1;
           }
           else
           {
               float xr_new=xr_old-(y(xr_old)/y_(xr_old));
               iter++;
               float error=fabs((xr_new-xr_old)/xr_new)*100;
               printf("iteration: %d root: %f error: %f\n",iter,xr_new,error);
               if(error<=tolerance)
               {
                   return xr_new;
               }
               else{
                  return nr(xr_new, iter, tolerance);
               }
               
           }
       }
   }
   else{
       printf("the sequence is divergent");
       return -1;
   }
    
    
}
int main()
{
    printf("the most approximate root when n=2 is : %f\n", nr(2,0,0.05));
    printf("the most approximate root when n=6 is : %f\n", nr(6,0,0.05));
    printf("the most approximate root when n=8 is : %f\n", nr(8,0,0.05));
}
