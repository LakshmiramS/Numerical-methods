#include<stdio.h>
#include<math.h>

//function for integrand
float y(float x)
{
    return 2*cos(2*x);
}
//function for midpoint
float midpoint(int n,float a,float b)//n: partitions,a and b are the limits of integragtion.
{
    float sum=0;float width=(b-a)/n;
    for(int i=0;i<n;i++)
    {
        sum+=y(a+(width*i)+(width/2))*width;
    }
    return sum;
}
//function for trapezoid
float trapezoid(int n,float a,float b)//n: partitions,a and b are the limits of integragtion.
{
    float sum=0;float width=(b-a)/n;
    for(int i=0;i<n;i++)
    {
        sum+=0.5*(y(a+width*i)+y(a+width*(i+1)))*width;
    }
    return sum;
}
//function for simpson
float simpson(int n,float a,float b)//n: partitions,a and b are the limits of integragtion.
{
    float sum=0;float width=(b-a)/n;
    for(int i=0;i<n/2;i++)
    {
        sum+=(width/3)*(y(a+2*i*width)+4*y(a+width*(2*i+1))+y(a+width*(2*i+2)));
    }
    return sum;
}
int main()
{
    float pi=3.142857;
    float actual_value=1;
    
    printf("printing values for midpoint method\n");
    float actual1=fabs((midpoint(2,0,pi/4)-actual_value)/actual_value)*100;//actual error when n=2
    printf("actual error is: %f\n",actual1);
    //calculating actual and relative errors for powers of 2 starting from 4 till 1024.
    for(int i=2;i<11;i++)
    {
        
        float new=midpoint(pow(2,i),0,pi/4);
        float old=midpoint(pow(2,i-1),0,pi/4);
        float actual_error=fabs((new-actual_value)/actual_value)*100;
        float relative_error=fabs((new-old)/old)*100;
        printf("iteration : %d , actual error : %f ,relative error : %f\n",i-1,actual_error,relative_error);
        
        
    }
    printf("\n\n");
    
    
    printf("printing values for trapezoid method\n");
    float actual2=fabs((trapezoid(2,0,pi/4)-actual_value)/actual_value)*100;//actual error when n=2
    printf("actual error is: %f\n",actual2);
    //calculating actual and relative errors for powers of 2 starting from 4 till 1024.
    for(int i=2;i<11;i++)
    {

        float new=trapezoid(pow(2,i),0,pi/4);
        float old=trapezoid(pow(2,i-1),0,pi/4);
        float actual_error=fabs((new-actual_value)/actual_value)*100;
        float relative_error=fabs((new-old)/old)*100;
        printf("iteration : %d , actual error : %f ,relative error : %f\n",i-1,actual_error,relative_error);
        
    }
    printf("\n\n");
    
    
    
    printf("printing values for simpson method\n");
    float actual3=fabs((simpson(2,0,pi/4)-actual_value)/actual_value)*100;//actual error when n=2
    printf("actual error is: %f\n",actual3);
    //calculating actual and relative errors for powers of 2 starting from 4 till 1024.
    for(int i=2;i<11;i++)
    {
        
        float new=simpson(pow(2,i),0,pi/4);
        float old=simpson(pow(2,i-1),0,pi/4);
        float actual_error=fabs((new-actual_value)/actual_value)*100;
        float relative_error=fabs((new-old)/old)*100;
        //printf("iteration : %d , actual error : %f ,relative error : %f\n",i-1,actual_error,relative_error);
        printf("%f\n",relative_error);
    }
}


