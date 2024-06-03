#include<stdio.h>
#include<math.h>
//function for integrand
double y(double x)
{
    return pow(x,-x);
}
//function for midpoint
double midpoint(int n,double a,double b)//n: partitions,a and b are the limits of integragtion.
{
    double sum=0;double width=(b-a)/n;
    for(int i=0;i<n;i++)
    {
        sum+=y(a+(width*i)+(width/2))*width;
    }
    return sum;
}
//function for trapezoid
double trapezoid(int n,double a,double b)//n: partitions,a and b are the limits of integragtion.
{
    double sum=0;double width=(b-a)/n;
    for(int i=0;i<n;i++)
    {
        sum+=0.5*(y(a+width*i)+y(a+width*(i+1)))*width;
    }
    return sum;
}
//function for simpson
double simpson(int n,double a,double b)//n: partitions,a and b are the limits of integragtion.
{
    double sum=0;double width=(b-a)/n;
    for(int i=0;i<n/2;i++)
    {
        sum+=(width/3)*(y(a+2*i*width)+4*y(a+width*(2*i+1))+y(a+width*(2*i+2)));
    }
    return sum;
}
int main()
{
    double sum=0;
    for(int i=0;i<6;i++)
    {
        sum+=pow(i,-i);
    }
    double actual_value=sum;//the RHS of the equality
    
    printf("printing values for midpoint method\n");
    for(int i=1;i<11;i++)
    {
        double actual_error=fabs((midpoint(pow(2,i),0,1)-actual_value)/(actual_value))*100;
        //printf("iterations : %d ,actual error: %lf\n",i,actual_error);
        printf("%lf\n",actual_error);
    }
    printf("\n\n");
    
    printf("printing values for trapezoid method\n");
    for(int i=1;i<11;i++)
    {
        double actual_error=fabs((trapezoid(pow(2,i),0,1)-actual_value)/(actual_value))*100;
       // printf("iterations : %d ,actual error: %lf\n",i,actual_error);
        printf("%lf\n",actual_error);
    }
    printf("\n\n");
    
    printf("printing values for simpson method\n");
    for(int i=1;i<11;i++)
    {
        double actual_error=fabs((simpson(pow(2,i),0,1)-actual_value)/(actual_value))*100;
        //printf("iterations : %d ,actual error: %lf\n",i,actual_error);
        printf("%lf\n",actual_error);
    }
    printf("\n\n");
}
