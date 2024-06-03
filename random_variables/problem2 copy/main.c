#include<stdio.h>
#include<math.h>
#include<stdlib.h>
//function to generate n random variables between 0 and 1
float random_number(float a,float b)
{
    return a+(b-a)*((float)rand()/(float)RAND_MAX);
}
//function to print the n values of the set X
//let u1_i denote the ith element of the set U1
//let u2_i denote the ith element of the set U2
void X(int n)
{
    for(int i=0;i<n;i++)
    {
        float u1=random_number(0.00, 1.00);
        float u2=random_number(0.00, 1.00);
        printf("%f\n",sqrt(fabs(-2*log(u1)))*cos(2*M_PI*u2));
        
    }
}


//planning on directly evaluating x_i using the formulas in hand
int main()
{
    srand(0);
    X(10000);
}
