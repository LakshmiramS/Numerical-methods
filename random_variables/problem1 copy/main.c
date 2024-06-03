#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<time.h>

//function for generating a random number between a and b both inclusive
float random_number(float a,float b)
{
    return a+(b-a)*((float)rand()/(float)RAND_MAX);
}
//function for pi_n
float pi_n(float n)
{
    float inside_circle=0;
    for(int i=0;i<n;i++)
    {
        float x=random_number(0.00,1.00);
        float y=random_number(0.00,1.00);
        if(pow(x,2)+pow(y,2)<=1)
        {
            inside_circle++;
        }
    }
    return (inside_circle/n)*4;
}
//function to return the madhava series
float madhava_n(float n)
{
    float sum=0;
    for(int i=1;i<=n;i++)
    {
        sum+=pow(-1,i+1)/(2*i-1);
    }
    return sum*4;
}
int main()
{
    srand(200);
    float pi = M_PI;
    for(int i=1;i<8;i++)
    {
        float approx_pi=pi_n(pow(10,i));
        float absolute_error=fabs((approx_pi-pi)/pi)*100;
        float absolute_error_madhava=fabs((madhava_n(pow(10,i))-pi)/pi)*100;
        //printf("approximate pi : %f absolute error : %f\n",approx_pi,absolute_error);
        printf("%f\n",absolute_error_madhava);
        
        
    }
}
