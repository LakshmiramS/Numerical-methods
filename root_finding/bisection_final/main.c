#include<stdio.h>
#include<math.h>
//function for function
float function(float x)
{
    float w=2500,e=50000000,i=30000,l=600;
    return (w/(120*e*i*l))*(-pow(x,5)+2*pow(l,2)*pow(x,3)-pow(l,4)*x);
}
//function for derivative
float y(float x)
{
    int l=600,e=50000,i=30000,w=2500;
    return w*(-pow(x,4)*5 + 6*pow(l,2)*pow(x,2)-pow(l,4))/(120*e*i*l);
}
float bisect(float xl,float xu,float tolerance)
{
    
    float xr=(xl+xu)/2;
    float error=fabs((xl-xu)/(2*xr))*100;
    int iter=0;
    while(error>tolerance)
    {
        if(y(xr)==0)
        {
            break;
        }
        else if(y(xr)*y(xl)<0)
        {
            xu=xr;
            xr=(xl+xu)/2;
            iter++;
            error=fabs((xl-xu)/(2*xr))*100;
            
        }
        else{
            xl=xr;
            xr=(xl+xu)/2;
            iter++;
            error=fabs((xl-xu)/(2*xr))*100;
            
        }
        //printf("iteration %d   error %f\n", iter, error);
        printf("%f\n",error);
    }
    return xr;
}
int  main()
{
    float root=bisect(250, 300, 0.05);
    printf("root is %f\n",root);
    printf("the maximum elongation is: %f",function(root));
}
