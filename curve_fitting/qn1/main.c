#include<stdio.h>
#include<math.h>
void linear_regression(float *x, float *y,int n,float *a0,float *a1)
{
    //here n is the number of data points
    float Sx=0,Sy=0,Sxy=0,Sx2=0;
    for(int i=0;i<n;i++)
    {
        Sx+=x[i];
        Sy+=y[i];
        Sxy+=x[i]*y[i];
        Sx2+=pow(x[i],2);
    }
    *a1=(n*Sxy-Sx*Sy)/(n*Sx2-pow(Sx,2));
    *a0=(Sy-(*a1)*Sx)/n;
}

int main()
{
    float a0,a1;
    float x[5]={1.41421,1.00,0.707106,0.577350,0.5};
    float y[5]={3.22490,2.408318,1.81659,1.549193,1.41421};
    float *p1=&a0;
    float *p2=&a1;
    linear_regression(x, y, 5, p1, p2);
    float b=1/a0;
    float a=a1/a0;
    printf("%f,%f",a0,a1);
    printf("the required values are %f and %f\n",a,b);
    printf("the predicted value of the function at x=1.6 is %f\n",a0+a1*1.6);
    
    //input data points after transformation here
    //the required function is y=a0+a1*x
    //substitute the value of x from question to find out the predicted value of y(x).
}
