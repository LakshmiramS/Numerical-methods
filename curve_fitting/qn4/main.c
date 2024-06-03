#include<stdio.h>
#include<math.h>
void LU_decomposition(float array[][6], int len)
//remember that this works only on square matrices.
{
    int n=len;
    for(int k=0;k<n-1;k++)
    {
        //first decide what the pivot equation is
        //write a loop to iterate across the first column and find out which one has the greatest absolute value.
        float max=fabs(array[k][k]);
        int max_index=k;
        for(int row=1+k;row<n;row++)
        {
            if(fabs(array[row][k])>=max)
            {
                max_index=row;
            }
        }
        //if the first row is already the pivot(that is, if it already has the maximum absolute value, then do nothing. otherwise, swap two rows and bring the row with the maximum absolute value to the first row.
        if(max_index==k)
        {
            //do nothing
        }
        else{
            //swap the rows
            for(int m=k;m<n;m++)
            {
                float temp=array[k][m];
                array[k][m]=array[max_index][m];
                array[max_index][m]=temp;
            }
        }
        //now that the pivot equation is decided, lets start the decomposition
        //row 1 is the pivot
        //the following is assuming that n is not equal to 1. the decomposition of a single element matrix is (i suppose) not defined and practically useless.
        //the following code is built to contain both L and U in the same matrix for efficiency of space.
        for(int row=1+k;row<n;row++)
        {
            float factor=array[row][k]/array[k][k];
            for(int col=k;col<n;col++)
            {
                array[row][col]-=factor*array[k][col];
            }
            array[row][k]=factor;
        }
    }
}

//function for forward substitution
//define a d column vector (presumably in the main program) to hold the intermediate values in the process and pass its pointer into the function.

void forward_substitution(float array[][6],float d[],int n)
{
    d[0]=array[0][n];
    for(int i=1;i<n;i++)
    {
        float sum=0;
        for(int j=0;j<i;j++)
        {
            sum+=array[i][j]*d[j];
        }
        d[i]=array[i][n]-sum;
    }
}

//function for back substitution
//define an x column vector (presumably in the main program or in the environment inside of which the function is used) to hold the final values obtained from the  process and pass its pointer into the function.
//also pass the same d column vector into this function.
void back_substitution(float array[][6],float d[],float x[],int n)
{
    x[n-1]=d[n-1]/array[n-1][n-1];
    for(int i=n-2;i>=0;i--)
    {
        float sum=0;
        for(int j=n-1;j>i;j--)
        {
            sum+=array[i][j]*x[j];
        }
        x[i]=(d[i]-sum)/array[i][i];
    }
}
void quadratic_splines(float *x,float *y,int n,float *b,float *a)
{
    a[0]=0;
    for(int i=1;i<n;i++)
    {
       // a[i]=a[i-1]*(x[i]-x[i-1])+((y[i]-y[i-1])/(x[i]-x[i-1]))+((y[i+1]-y[i])/(x[i+1]-x[i]));
        a[i]=(a[i-1]*(x[i]-x[i-1])+b[i-1]-b[i])/(x[i]-x[i+1]);
    }
}
void cubic_splines(float a[][6],float x[])
{
    //in this function i will basically solve for the second derivate terms using LU decomposition. the required function can be extracted later using a suitable algorithm.
    //solve ax=b;
    LU_decomposition(a, 5);
    float intermediate_array[5];
    forward_substitution(a,intermediate_array , 5);
    back_substitution(a, intermediate_array, x, 5);
    
    
}
int main()
{
    //the below 2 arrays will contain the coordinates of the data points.
    //this whole program is built after knowing that there are only 7 data points. to generalise it, 7 can be replaced using n and malloc can be used to define arrays dynamically.
    float  x_i[7]={3.86,5.73,7.34,8.85,11.7,13.8,15.2};
    float y_i[7]={11.55,9.95,12.4,16.2,17.37,16.34,13.63};
    //i am defining the array that contains the n+1 data points within the program. this can be user input if needed by modifying the existing code slightly.
    //create an array a that will contain the leading coefficients of the n quadratics in the interpolation.
        float a[6];
        float b[6];
        for(int i=0;i<6;i++)
        {
            b[i]=(y_i[i+1]-y_i[i])/(x_i[i+1]-x_i[i]);
        }
    //call the quadratic_spline function now. the required curve can be obtained by using a particular algorithm.
        quadratic_splines(x_i, y_i, 6,b, a);
        for(int i=0;i<6;i++)
        {
            //printf("a[%d]=%f\tb[%d]=%f\tc[%d]=%f\n",i+1,a[i],i+1,b[i],i+1,y_i[i]);
            printf("y=%f + %f(x-%f)+%f(x-%f)(x-%f){%f<=x<=%f}\n",y_i[i],b[i],x_i[i],a[i],x_i[i],x_i[i+1],x_i[i],x_i[i+1]);
        }
        printf("\n*********************************************\n");
    

//    //the below code is for cubic splines
    float arr[5][6]={{},{},{},{},{}};
    //filling up arr
    //the following is the n-1 x n-1 matrix(A) appended with the b column vector.
    arr[0][0]=2*(x_i[2]-x_i[0]);
    arr[0][1]=x_i[2]-x_i[1];
    for(int i=1;i<4;i++)
    {
        int j=i-1;
        arr[i][j]=x_i[i+1]-x_i[i];
        arr[i][j+1]=2*(x_i[i+2]-x_i[i]);
        arr[i][j+2]=x_i[i+2]-x_i[i+1];
    }
    arr[4][3]=x_i[5]-x_i[4];
    arr[4][4]=2*(x_i[6]-x_i[4]);
    //entering values for b vector
    for(int i=0;i<5;i++)
    {
        arr[i][5]=(6*(y_i[i+2]-y_i[i+1])/(x_i[i+2]-x_i[i+1]))-(6*(y_i[i+1]-y_i[i])/(x_i[i+1]-x_i[i]));
    }
    float derivatives[5];
    cubic_splines(arr,derivatives);
    //the derivatives array now contains the the second order derivatives requires to uniquely determine the n quadratics .
    for(int i=0;i<5;i++)
    {
        //printf("derivative[%d]=%f\n",i+2,derivatives[i]);
    }
    //update the derivatives array with the initial and final values
    float new_derivatives[7];
    new_derivatives[0]=0.00;
    new_derivatives[6]=0.00;
    for(int i=1;i<6;i++)
    {
        new_derivatives[i]=derivatives[i-1];
    }
    //write code here to print the cubic equations
    for(int i=0;i<6;i++)
    {
        printf("y=%f(%f-x)^3 + %f(x-%f)^3 + %f(%f-x)+%f(x-%f)\n",(new_derivatives[i]/((x_i[i+1]-x_i[i])*6)),x_i[i+1],(new_derivatives[i+1]/((x_i[i+1]-x_i[i])*6)),x_i[i],(y_i[i]/(x_i[i+1]-x_i[i]))-(new_derivatives[i]*(x_i[i+1]-x_i[i])/6),x_i[i+1],(y_i[i+1]/(x_i[i+1]-x_i[i]))-(new_derivatives[i+1]*(x_i[i+1]-x_i[i])/6),x_i[i]);
    }
}
