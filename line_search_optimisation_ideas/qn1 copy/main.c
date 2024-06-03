#include<stdio.h>
#include<math.h>
float f(float x)
{
    //return 4*x-1.8*pow(x,2)+1.2*pow(x,3)-0.3*pow(x,4);
    //return -sqrt(1+pow(x,2));
    //return -pow(x,4);
    //return -pow(x,4)-2*pow(x,3)-8*pow(x,2)-5*x;
    return 1+x*1.19175359259-(9.81*pow(x,2))/(1250*pow(0.64278760968,2));
}
float f_1(float x)
{
    //return 4-3.6*x+3.6*pow(x,2)-1.2*pow(x,3);
//    return -(x)/(sqrt(1+pow(x,2)));
    //return -4*pow(x,3);
    return -4*pow(x,3)-6*pow(x,2)-16*x-5;
}
float f_2(float x)
{
    //return -3.6+7.2*x-3.6*pow(x,2);
    //return -pow((1+pow(x,2)),-1.5);
    //return -12*pow(x,2);
    return -12*pow(x,2)-12*x-16;
    
}

   
//function takes in xl,xu,tolerance,error of the current iteration and returns x_opt after error<tolerance.to minimise function evalutations, pass on the value of f(x_opt) of the current iteration to the next one.
void golden_search(float xl,float xu,float tolerance,float *x_opt,float *y_opt)
{
    float r= (sqrt(5)-1)/2;//r is the golden ratio.
    //float r= (float)2/3;
    float d=r*(xu-xl);
    float error=(1-r)*fabs((xu-xl)/(*x_opt))*100;
    if(error>=tolerance)
    {
        float x_o=0,y_o=0;
        if(*x_opt>(xl+xu)/2)
        {
            x_o=xu-d;
            y_o=f(x_o);
            if(*y_opt>y_o)
            {
                //maxima lies in the second interval
                //x_opt is x_opt
                golden_search(x_o, xu, tolerance, x_opt, y_opt);
            }
            else{
                float temp=*x_opt;
                *x_opt=x_o;
                *y_opt=y_o;
                golden_search(xl, temp, tolerance, x_opt, y_opt);
            }
        }
        else{
             x_o=xl+d;
             y_o=f(x_o);
            if(*y_opt>y_o)
            {
                //maxima lies in the second interval
                //x_opt is x_opt
                golden_search(xl, x_o, tolerance, x_opt, y_opt);
            }
            else{
                float temp=*x_opt;
                *x_opt=x_o;
                *y_opt=y_o;
                golden_search(temp,xu, tolerance, x_opt, y_opt);
            }
            
        }
        //error=(1-r)*fabs((xu-xl)/(x_opt))*100;
        
    }
    else{
        //do nothing.
    }
}
//function for parabolic interpolation
//this function takes in x0,x1,x2. it evaluates x3. now x0=x1,x1=x2 and x2=x3.repeat this process for n iterations.
void parabolic_interpolation(float x0,float x1,float x2,float* x_opt,int n)
{
    if(n>0)
    {
        //is there a nice way to evalute cyclic summations and products?
        float num=f(x0)*(pow(x1,2)-pow(x2,2))+f(x1)*(pow(x2,2)-pow(x0,2))+f(x2)*(pow(x0,2)-pow(x1,2));
        float den=2*(f(x0)*(x1-x2)+f(x1)*(x2-x0)+f(x2)*(x0-x1));
        *x_opt=num/den;
        //update the values
        parabolic_interpolation(x1, x2, *x_opt, x_opt, n-1);
    }
}
//function for newton
//print the results of every iteration as graphs may be needed.
//need the 1st and 2nd derivate functions.
//it takes x0, tolerance and repeats the process till relative error <tolerance
void newton(float x0,float tolerance,float* x_opt)
{
    *x_opt=x0-(f_1(x0))/(f_2(x0));
    float error=fabs((*x_opt-x0)/(*x_opt))*100;
    printf("%f\n",*x_opt);
    if(error>tolerance)
    {
        newton(*x_opt, tolerance, x_opt);
    }
    else{
        //do nothing
    }
}
int main()
{
    float xl=0,xu=60;
    float r= (sqrt(5)-1)/2;//r is the golden ratio.
   // float r= (float)2/3;
    float a=xl+r*(xu-xl);
    float b=f(a);
    float* x_opt=&a,*y_opt=&b;
    golden_search(xl, xu, 1.0, x_opt,y_opt);
    printf("%f\n\n",*x_opt);
//    float dummy=0;
//    float* x_opt_parabola=&dummy;
//    parabolic_interpolation(-2,-1,1, x_opt_parabola, 10);
//    printf("%f\n\n",*x_opt_parabola);
//    float* x_opt_newton=&dummy;
//    newton(-1,1.0,x_opt_newton);
//    printf("the final value is %f\n",*x_opt_newton);
}

