//A mass balance for a pollutant in a well-mixed lake can be
//written as
//Vdc =W−Qc−kV√c dt
//Given the parameter values V = 1 × 106m3, Q = 1 × 105 m3/yr, W = 1 × 106 g/yr, and k = 0.25 m0.5/g0.5/yr, use the modified secant method to solve for the steady-state concentration. Employ an initial guess of c = 4 g/m3 and δ = 0.5. Perform three iterations and determine the percent relative error after the third iteration.
#include<stdio.h>
#include<math.h>
float y(float c)//function oracle
{
    float v=pow(10,6),q=v/10,w=v,k=0.25;
    return w-q*c-k*v*(sqrt(c));
}
float ms(float c,int iter,float tolerance)//ms stands for modified secant
{
    float del=0.5;
    float iter_max=1000;//again, precaution for the case of divergence.
    float xr_old=c;
    if(y(xr_old)==0)
    {
        return xr_old;
    }
    else
    {
        if(iter<iter_max)
        {
            float temp=y(xr_old+del)-y(xr_old);//introducing a temporary variable after realising that this quantity is required quite a few times.
            if(temp!=0)
            {
                float xr_new=xr_old-((y(xr_old))/((temp)/del));
                iter++;
                float error=fabs((xr_new-xr_old)/xr_new)*100;
                printf("iteration:  %d root : %f error: %f\n",iter,xr_new,error);
                if(error<tolerance)
                {
                    return xr_new;
                }
                else{
                    return ms(xr_new, iter, tolerance);
                }
            }
            else{
                printf("divergent");
                return -1;
            }
        }
        else{
            printf("divergent\n");
            return -1;
        }
    }
}
int main()
{
    printf("the most approximate root is : %f", ms(4,0,0.005));
}
