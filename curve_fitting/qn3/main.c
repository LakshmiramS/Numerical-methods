#include<stdio.h>
#include<stdlib.h>
#include<math.h>
float coefficient(int n,float *x,float *y)
{
    if(n==0)
    {
        return y[0];
    }
    else if(n==1)
    {
        return (y[0]-y[1])/(x[0]-x[1]);
    }
    else{
        return (coefficient(n-1, x,y)-coefficient(n-1, x+1, y+1))/(x[0]-x[n]);
    }
}
int main()
{
    int n=6;
    //n is the degree of the interpolating polynomial.
    float x[]={3.56,5.2,7.75,9.2,12.3,14.23,15.4};
    //float x[]={15.13,13.6,8.9,6.3};
    float y[]={12.4,10,12.84,16.5,17.25,15.7,13.17};
    //float y[]={13.33,16.35,15.8,10.1};
    //now print the coefficients
    for(int i=0;i<=n;i++)
    {
        printf("%f",coefficient(i, x, y));
        for(int j=0;j<i;j++)
        {
            printf("(x-%f)",x[j]);
        }
        printf(" + ");
    }
    

}
