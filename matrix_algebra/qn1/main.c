//1 write code to dynamically allocate a 2d array.
//2 function for LU decomposition with partial pivoting
//3 solving an equation of type Ax=B using forward substitution and back substitution after decomposition
//4 calculate matrix inverses using the above method.
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
float determinant(float **array,int n)
{
    float det=1;
    for(int i=0;i<n;i++)
    {
        det*=array[i][i];
    }
    return det;
}
//function for LU decomposition with partial pivoting
void LU_decomposition(float **array, int len)
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

void forward_substitution(float **array,float *d,int n)
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
void back_substitution(float **array,float *d,float *x,int n)
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



//function to transpose a pxp square matrix
void square_matrix_transpose(float **array,int p)
{
    for(int row=0;row<p-1;row++)
    {
        //it will suffice if the loops work on one triangular half of the matrix
        for(int col=row+1;col<p;col++)
        {
            float temp=array[row][col];
            array[row][col]=array[col][row];
            array[col][row]=temp;
        }
    }
}


//function for matrix inverse using all the above methods
void matrix_inverse(float **array,float **inverse,int n)
{
    for(int i=0;i<n;i++)
    {
        array[i][n]=0;
    }
    for(int m=0;m<n;m++)
    {
        //augment the matrix's last column with the corresponding column vector from the identity matrix
        array[m][n]=1;
        //pass the augmented array for forward substitution
        //define a d column vector dynamically
        float *d;
        d=malloc(sizeof(float)*n);
        forward_substitution(array, d, n);
        //now pass the array for back substitution
        //now we also need a column vector to store the final answer.but this process is not easy because of the way 2d arrays are built in c.
        //here's what we will do to remedy this: the inverse matrix is structured in such a way that the pointers to the rows will be passed into the function to store the final answer . later the transpose of the matrix can be evaluated and presented as the actual inverse.
        back_substitution(array, d, inverse[m], n);
        
        
        
    }
    //now take the transpose of the matrix.
    square_matrix_transpose(inverse, n);
}


int main()
{
    //the following code is to dynamically allocate a 2d array as per the user definition.
    //in our case rows=columns=n
    int n;
    printf("enter the number of variables\n");
    scanf("%d",&n);
    float **array;
    //array will hold the coefficients of the equations and also the b vector (AX=B)
    array=malloc(n*sizeof(int*));
    for(int i=0;i<n;i++)
    {
        array[i]=malloc((n+1)*sizeof(float));
    }
    float **inverse;
    //inverse wil be a nXn square matrix that holds the inverse of A
    inverse=malloc(n*sizeof(int*));
    for(int i=0;i<n;i++)
    {
        inverse[i]=malloc(n*sizeof(float));
    }
    
    //write code here to input values for array
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            printf("enter value for  array[%d][%d]  ",i+1,j+1);
            scanf("%f",&array[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    //enter values for b vector
    for(int i=0;i<n;i++)
    {
        printf("enter b[%d]  ",i+1);
        scanf("%f",&array[i][n]);
    }
    printf("\n");
    
    //output the values of array or inverse as required.
    
    LU_decomposition(array, n);
    //compute the determinant after lu decomposition
    printf("the determinant is:  %f ",determinant(array,n));
    float *answer;
    answer=malloc(n*sizeof(float));
    float *intermediate_vector;
    intermediate_vector=malloc(n*sizeof(float));
    forward_substitution(array, intermediate_vector, n);
    back_substitution(array, intermediate_vector, answer, n);
    //return the contents of answer.
    printf("the values of the variables are :\n");
    for(int i=0;i<n;i++)
    {
        printf("%f\t",answer[i]);
    }
    printf("\n");
    //free up the memory after usage
    for(int i=0;i<n;i++)
    {
        free(array[i]);
    }
    free(array);
    
    //free up the memory after usage
    for(int i=0;i<n;i++)
    {
        free(inverse[i]);
    }
    free(inverse);
    
    return 0;
}
