#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "helper.c"


void regression(int no_of_terms, int no_of_points, float *array_x, float *array_y, float *coefficient_soln)
{
    float **array_2D; // defining a double pointer array
    // initializing the 2D array
    // allocating the array using malloc() function
    array_2D = malloc(no_of_terms * sizeof (*array_2D));
    // array inside an array(2D array) using malloc
    for (int i = 0; i < no_of_terms; i++) {
        array_2D[i] = malloc((no_of_terms+1) * sizeof (float));
    }

    float coefficients[2*no_of_terms - 1];


    // coefficients of a0, a1, ...
    for(int i=0; i < 2*no_of_terms - 1; i++){
        float sum=0;
        for(int j=0; j < no_of_points; j++){
            sum += powf(array_x[j], (float)i);
        }
        coefficients[i] = sum;
    }
//    print_array_1D(coefficients, 2*no_of_terms - 1);



    // constants RHS of the equations
    for(int i=0; i < no_of_terms; i++){
        float sum=0;
        for (int j = 0; j < no_of_points ; ++j) {
            sum += (array_y[j] * powf(array_x[j], (float)i));
        }
        array_2D[i][no_of_terms] = sum;
    }



    // forming A while solving Ax=B
    for(int i=0; i < no_of_terms; i++){
        for(int j=0; j < no_of_terms; j++){
            array_2D[i][j] = coefficients[i+j];
        }
    }



//    printf("\n");
    array_2D[0][0] = (float)no_of_points;
//    print_array_2D(array_2D, no_of_terms, no_of_terms);



    calculation_real(array_2D, no_of_terms, no_of_terms+1, coefficient_soln, (float)0.05);





    // deallocating the array
    for (int i = 0; i < no_of_terms; i++) {
        free(array_2D[i]);
    }
    free(array_2D);
}


void multiple_linear_regression(int no_of_points, int eqn_terms, float **array_x, float array_y[], float *coefficient_soln)
{
    float **array_2D; // defining a double pointer array
    // initializing the 2D array
    array_2D = malloc(eqn_terms * sizeof (*array_2D));
    for (int i = 0; i < eqn_terms; i++) {
        array_2D[i] = malloc(eqn_terms * sizeof (float));
    }

    for(int i=0; i<eqn_terms; i++){
        for(int j=i; j<eqn_terms; j++){
            float sum = 0;
            for(int k=0; k<no_of_points; k++){
                sum += array_x[i][k] * array_x[j][k];
            }
            array_2D[i][j] = array_2D[j][i] = sum;
        }
    }


    float constants[eqn_terms];
    for(int i=0; i<eqn_terms; i++){
        float sum=0;
        for(int j = 0; j < no_of_points; ++j){
            sum += array_x[i][j] * array_y[j];
        }
        constants[i] = sum;
    }

//    print_array_1D(constants, eqn_terms);

//    print_array_2D(array_2D, eqn_terms, eqn_terms);

    Ax_equals_to_B(array_2D, eqn_terms, (float)0.05, coefficient_soln, constants);



    // deallocating the array
    for (int i = 0; i < eqn_terms; i++) {
        free(array_2D[i]);
    }
    free(array_2D);
}


float predict_lrgr(float x, float *coefficient_soln, int no_of_terms){
    float y = 0;
    for(int i = 0; i < no_of_terms; i++){
        y = y + (coefficient_soln[i]*powf(x, (float)i));
    }
    return y;
}

void print_mrgr(float *coefficient_soln, int eqn_terms){
    printf("y = ");
    printf("%f ", coefficient_soln[0]);
    for(int i=1; i<eqn_terms; i++){
        printf("+ %f x%d ", coefficient_soln[i], i);
    }
}


float mrgr_error_Sr(int no_of_points, float *array_x[], float array_y[], float *coefficient_soln)
{
    float Sr=0;
    for(int i=0; i<no_of_points; i++){
        float e = array_y[i] - (coefficient_soln[0] + (coefficient_soln[1]*array_x[1][i]) + (coefficient_soln[2]*array_x[2][i]));
        Sr += powf(e, 2);
    }
    return Sr;
}


float correlation_coeff();


int main() {

//    // Question 1
//    int no_of_terms = 2;
//
//    int no_of_points = 5;
//
//    float crude_x[] = {(float) 0.5, 1, 2, 3, 4};
//    float crude_y[] = {(float) 10.4, (float) 5.8, (float) 3.3, (float) 2.4, 2};
//
//
//    float array_x[no_of_points];
//    float array_y[no_of_points];
//
//    for (int i = 0; i < no_of_points; i++) {
//        array_y[i] = sqrtf(crude_y[i]);
//        array_x[i] = 1 / sqrtf(crude_x[i]);
//    }
//
//    float coefficient_soln[no_of_terms];
//
//    regression(no_of_terms, no_of_points, array_x, array_y, coefficient_soln);
//
//    float a, b;
//    b = 1 / coefficient_soln[0];
//    a = coefficient_soln[1] * b;
//
//    printf("a: %f\nb: %f", a, b);
//
//
//    float crudex = (float) 1.6;
//    float x = 1 / sqrtf(crudex);
//
//    float y = predict_lrgr(x, coefficient_soln, no_of_terms);
//    float crudey = powf(y, 2);
//    printf("\ny estimate for 1.6 is %f", crudey);


    // Question 2
    int no_of_points = 9;
    int eqn_terms = 3;

    float coefficient_soln[eqn_terms];


    float **array_x; // defining a double pointer array
    // initializing the 2D array
    // allocating the array using malloc() function
    array_x = malloc(eqn_terms * sizeof (*array_x));
    // array inside an array(2D array) using malloc
    for (int i = 0; i < no_of_points; i++) {
        array_x[i] = malloc(no_of_points * sizeof (float));
    }


    for(int i=0; i<no_of_points; i++){
        array_x[0][i] = 1;
    }

    float array_x1[] = {0, 1, 1, 2,2, 3, 3, 4, 4};
    float array_x2[] = {0, 1, 2, 1, 2, 1, 2, 1, 2};
    float array_y[] = {15.1, 17.9, 12.7, 25.6, 20.5, 35.1, 29.7, 45.4, 40.2};

    array_x[1] = array_x1;
    array_x[2] = array_x2;


    multiple_linear_regression(no_of_points, eqn_terms, array_x, array_y, coefficient_soln);

    print_mrgr(coefficient_soln, eqn_terms);

    float sr = mrgr_error_Sr(no_of_points, array_x, array_y, coefficient_soln);
    float standard_error_estimate = powf(sr/((float)no_of_points - 3), (float)0.5);
    printf("\nThe Standard error of estimate is : %f.", standard_error_estimate);


    // deallocating the array
    for (int i = 0; i < no_of_points; i++) {
        free(array_x[i]);
    }
    free(array_x);

}