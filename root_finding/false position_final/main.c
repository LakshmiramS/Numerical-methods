#include<stdio.h>
#include<math.h>
float pu(float t)//function for urban population
{
    //data from question
    float pu_max=75000,pu_min=100000,ku=0.045;
    return pu_max*exp(-ku*t)+pu_min;
}
float ps(float t)//function for sub-urban population
{
    //data from question
    float ps_max=300000,p0=10000,ks=0.08;
    return ps_max/(1+((ps_max/p0)-1)*exp(-ks*t));
}
float y(float t)//function whose root is to be found
{
    return ps(t)-1.2*pu(t);
}
//fucntion for deploying the false position method
//almost everything about this method is the same as bisection except for the way we calculate xr
float falsepoint(float xl,float xu,float tolerance)
{
    
    float xr=xu-((y(xu)*(xl-xu))/(y(xl)-y(xu)));
    float xr_old=xr;
    float error=10;
    int iter=0;
    while(error>tolerance)
    {
        if(y(xr)==0)
        {
            error=0;
            break;
        }
        else if(y(xr)*y(xl)<0)
        {
            xu=xr;
            xr=xu-((y(xu)*(xl-xu))/(y(xl)-y(xu)));
            xr_old=xu;
            float xr_new=xr;
            iter++;
            error=fabs((xr_new-xr_old)/xr_new)*100;
            
        }
        else{
            xl=xr;
            xr=xu-((y(xu)*(xl-xu))/(y(xl)-y(xu)));
            xr_old=xl;
            float xr_new=xr;
            iter++;
            error=fabs((xr_new-xr_old)/xr_new)*100;
            
        }
        printf("iteration %d   error %f\n", iter, error);
       
    }
    return xr;
}
int  main()
{
    float root=falsepoint(10, 100, 0.05);
    printf("root is %f",root);
    printf("urban population is : %f\n",pu(root));
    printf("sub-urban population is : %f\n",ps(root));
}
