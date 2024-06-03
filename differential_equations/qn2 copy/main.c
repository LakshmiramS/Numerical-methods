#include<stdio.h>
#include<math.h>
double f(double x,double y)
{
    return -100000*y+99999*exp(-x);
}
void euler(double h,double xi,double xf,double yi)
{
    if(xi==xf)
    {
        //do nothing
    }
    else{
        double y=yi+f(xi, yi)*h;
        printf("%lf\n",y);
        if(xi+h<=xf)
        {
            euler(h, xi+h, xf, y);
        }
    }
}
//function for implicit euler
void imp_euler(float h,float xi,float xf,float yi)
{
    float a=100000,b=99999;
    if(xi==xf)
    {
        //do nothing
    }
    else{
        float  y=(yi+b*exp(-xi-h))/(1+a);
        printf("%f\n",y);
        if(xi+h<=xf)
        {
            imp_euler(h, xi+h, xf, y);
        }
    }
}

int main()
{
    euler(0.00002, 0, 2, 0);
    printf("*******************************************************************\n");
    imp_euler(0.1, 0, 2, 0);
}
