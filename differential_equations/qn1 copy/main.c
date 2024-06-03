#include<stdio.h>
#include<math.h>
#include<time.h>
//function that evaluates the derivative
float f(float x,float y)
{
    return y*pow(x,3)-1.5*y;
}
//function for euler's method
void euler(float h,float xi,float xf,float yi)
{
    if(xi==xf)
    {
        //do nothing
    }
    else{
        float y=yi+f(xi, yi)*h;
        printf("%f\n",y);
        if(xi+h<=xf)
        {
            euler(h, xi+h, xf, y);
        }
    }
}
//function for heun's method
void heun(float h,float xi,float xf,float yi)
{
    if(xi==xf)
    {
        //do nothing
    }
    else{
        float y_int=yi+f(xi, yi)*h;
        float y=yi+(f(xi,yi)+f(xi+h,y_int))*h/2;
        printf("%f\n",y);
        if(xi+h<=xf)
        {
            heun(h, xi+h, xf, y);
        }
    }
}
//function for midpoint's method
void midpoint(float h,float xi,float xf,float yi)
{
    if(xi==xf)
    {
        //do nothing
    }
    else{
        float y_int=yi+f(xi, yi)*h/2;
        float y=yi+f(xi+h/2,y_int)*h;
        printf("%f\n",y);
        if(xi+h<=xf)
        {
            midpoint(h, xi+h, xf, y);
        }
    }
}
//function for fourth order RK method
void fourth_RK(float h,float xi,float xf,float yi)
{
    if(xi==xf)
    {
        //do nothing
    }
    else{
        float k1=f(xi, yi);
        float k2=f(xi+h/2,yi+k1*h/2);
        float k3=f(xi+h/2,yi+k2*h/2);
        float k4=f(xi+h,yi+k3*h);
        float y=yi+(k1+2*k2+2*k3+k4)*h/6;
        printf("%f\n",y);
        if(xi+h<=xf)
        {
            fourth_RK(h, xi+h, xf, y);
        }
    }
}
int main()
{
    float xi=0,xf=2,h=0.5,yi=1;
    clock_t euler_start=clock();
    euler(h, xi, xf, yi);
    clock_t euler_end=clock();
    float euler_time=(float)(euler_end-euler_start)/(CLOCKS_PER_SEC);
    printf("time taken for euler's method is %f\n",euler_time);
    printf("*********************************************************************\n");
    clock_t heun_start=clock();
    heun(h, xi, xf, yi);
    clock_t heun_end=clock();
    float heun_time=(float)(heun_end-heun_start)/(CLOCKS_PER_SEC);
    printf("time taken for heun's method is %f\n",heun_time);
    printf("*********************************************************************\n");
    clock_t midpoint_start=clock();
    midpoint(h, xi, xf, yi);
    clock_t midpoint_end=clock();
    float midpoint_time=(float)(midpoint_end-midpoint_start)/(CLOCKS_PER_SEC);
    printf("time taken for midpoint method is %f\n",midpoint_time);
    printf("*********************************************************************\n");
    clock_t fourthRK_start=clock();
    fourth_RK(h, xi, xf, yi);
    clock_t fourthRK_end=clock();
    float fourthRK_time=(float)(fourthRK_end-fourthRK_start)/(CLOCKS_PER_SEC);
    printf("time taken for fouth order RK method is %f\n",fourthRK_time);
    printf("*********************************************************************\n");
}
