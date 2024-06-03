#include <stdlib.h>
#include <stdio.h>
#include <math.h>

// function for swapping values of two variables using pointers.
void swap(float *x, float *y) {
    float t = *x;
    *x = *y;
    *y = t;
}


// function to swap two rows of a 2D array required in the function.(lesser iterations)
// x1 and x2 are the indices of the rows to be exchanged. Numbers after y will only get interchanged
void swap_array(float **array, int x1, int x2, int y, int cols) {
    for (; y <= cols; y++) {
        swap(&array[x1][y], &array[x2][y]);
    }

}

// function to print the 2D array in the proper format. Passing pointer to a 2D array, number of rows and columns
// the coefficients of variables are printed in a single row
void print_array_2D(float **array, int rows, int cols) {

    int i, j;

    for (i = 0; i < rows; i++) {
        printf("\n");
        for (j = 0; j < cols; j++) {
            printf("%f     ", array[i][j]);
        }
    }
}


// function to print the 2D array in the proper format. Passing pointer to a 2D array, number of rows and columns
// the coefficients of variables are printed in a single row
void print_array_1D(float *array, int rows) {
    for (int j = 0; j < rows; j++) {
        printf("%0.10f     ", array[j]);
    }
}


// input values in 1D array
void array_input_1D(float *array, int rows) {
    int i;

    for (i = 0; i < rows; i++) {
        printf("Please enter arr[%d]:", i);
        scanf("%f", &array[i]);
    }
}


// demanding values to be stored in a 2D array, coefficients to be entered.
void array_input_2D(float **array, int rows, int cols) {
    int i, j;

    for (i = 0; i < rows; i++) {
        printf("\n");
        for (j = 0; j < cols; j++) {
            printf("Please enter arr[%d][%d]:", i, j);
            scanf("%f", &array[i][j]);

        }
    }
}


// function of copy array x to y
void copy_array(float**x, float**y, int rows, int cols){
    for(int i=0; i<rows; i++){
        for (int j=0; j<cols; j++){
            y[i][j] = x[i][j];
        }
    }
}


// transpose of matrix
void transpose(float **x, int rows){
    float **other; // defining a double pointer array
    // initializing the 2D array
    // allocating the array using malloc() function
    other = malloc(rows * sizeof *other);
    // array inside an array(2D array) using malloc
    for (int i = 0; i < rows; i++) {
        other[i] = malloc((rows + 1) * sizeof *other[i]);
    }

    for(int j=0; j<rows; j++){
        for(int k=0; k<rows; k++){
            other[j][k]=x[k][j];
        }
    }

    copy_array(other, x, rows, rows);


    for (int i = 0; i < rows; i++) {
        free(other[i]);
    }
    free(other);
}



// calculating the determinant of the array
void determinant(float**array, int size, float power){
    float value=1;

    for(int i=0; i<size; i++){
        value = value * array[i][i];
    }
    value = value * powf(-1, power);
    printf("The value of determinant is: %f", value);
}


// function for LU_decomposition
void LU_decomposition(float **array, int rows, int cols, float pivot){
    int y = 0;
    float power=0;

    // iterating over rows
    // the two equations getting solved belong to the index x1 and x2
    // every time the loop runs, number of coefficients in the overall equations reduces by 1
    for (int x1 = 0; x1 < cols; x1++) {
        int x2 = x1 + 1;

        // calculating the factor and changing the coefficients in the matrix in each 2 equations
        for (int x3 = x2; x3 < rows; x3++) {

            // conditional statement for partial pivoting
            if(fabsf(array[x1][y]) < pivot){

                int index = 0; // index of row to be exchanged
                float max = fabsf(array[x1][y]); // to store and compare the maximum value of the first coefficient

                // loop to calculate max value
                for(int x4 = x2;x4<rows; x4++ ){

                    // max number condition
                    if(fabsf(array[x4][y]) > max){
                        max = fabsf(array[x4][y]);
                        index = x4; // setting the index
                    }
                }

                // swapping the two rows
                swap_array(array, x1, index, y, cols);
                power++;

            }

            // calculating the factor
            float factor = array[x3][y] / array[x1][y];

            // changing the coefficients
            for (int y1 = y; y1 < cols; y1++) {
                array[x3][y1] = array[x3][y1] - (factor * array[x1][y1]);
            }

            // forming the L part of the matrix
            array[x3][x1] = factor;
        }

        y = y + 1;
    }
//    determinant(array, rows, power);
}


// function for back substitution algorithm
// function takes the coefficient array, solution array, number of rows and columns
void back_substitution(float **array, float*sol ,int rows, int cols){

    // setting the variables
    int n = 1; // denotes the number of values to be put back into the equation
    int x1 = rows-1; // index of corresponding row
    int y1 = cols-1; // index corresponding to column

    // calculating the value of xn(last variable and storing it in nth box in the solution array
    sol[cols-2] = array[rows-1][cols-1]/array[rows-1][cols-2];

    // for loop for calculating further variables
    for(; x1>0; x1--) {

        // calculating the RHS for the final division
        float RHS = array[x1-1][y1]; // setting RHS to the constant in the equation
        for (int j = n; j > 0; j--) {
            RHS = RHS - (array[x1 - 1][y1 - j] * sol[y1 - j]);
        }
        // now the eqn looks like ax=b

        // calculating the value of variable and storing it in the solution array
        float soln = RHS / array[x1-1][y1-n-1];
        n++; // increasing n by 1

        // as we move up in the array, number of variables to be put back in the equation increases by 1
        sol[y1 - n] = soln;
    }
}


// function calculates the solutions of real equations from the x 2D matrix and stores it in sol matrix
void calculation_real(float **x, int rows, int cols, float*sol, float pivot){

    // performing LU_decomposition
    LU_decomposition(x, rows, cols, pivot);

//     printf("\nThe LU_decomposed array: ");
//     print_array_2D(x, rows, cols);


    // performing back substitution to get the answers
    back_substitution(x,sol,rows,cols);
}


// printing the complex roots on with 'i'
// in the sol matrix first half contain real part of the solution and other half contains coefficients if 'i'
void print_complex(float*sol, int len){
    for(int i=0; i<(len/2); i++){
        printf("\nx%d = %f + %fi", i+1, sol[i], sol[i+(len/2)]);
    }
}

// function to calculate the inverse of the given matrix
void inverse_calc(float pivot, float **sol, int rows, float **x) {

    // array y will be copied from x and will be used to perform calculation
    float **y; // defining a double pointer array
    // initializing the 2D array
    // allocating the array using malloc() function
    y = malloc(rows * sizeof *y);
    // array inside an array(2D array) using malloc
    for (int i = 0; i < rows; i++) {
        y[i] = malloc((rows + 1) * sizeof *y[i]);
    }


    // calculating the inverse
    for (int j = 0; j < rows; j++) {
        copy_array(x, y, rows, rows);
        for (int k = 0; k < rows; k++) {
            if (k == j) {
                y[k][rows] = 1;
            } else {
                y[k][rows] = 0;
            }
        }

        calculation_real(y, rows, rows + 1, sol[j], pivot);
    }

    transpose(sol, rows);

    for (int i = 0; i < rows; i++) {
        free(y[i]);
    }
    free(y);

}



// function to calculate th solutions of equation with complex coefficients
void complex(float pivot, int var){


    float **array; // defining a double pointer array
    // initializing the 2D array
    // allocating the array using malloc() function
    array = malloc((2 * var) * sizeof *array);
    // array inside an array(2D array) using malloc
    for (int i = 0; i < (2*var); i++) {
        array[i] = malloc(((2*var) + 1) * sizeof *array[i]);
    }


    float sol[2*var];

    float **inp_real; // defining a double pointer array
    // initializing the 2D array
    // allocating the array using malloc() function
    inp_real = malloc(var * sizeof *inp_real);
    // array inside an array(2D array) using malloc
    for (int i = 0; i < var; i++) {
        inp_real[i] = malloc(var * sizeof *inp_real[i]);
    }
    printf("Please enter the real matrix:\n");
    array_input_2D(inp_real, var, var);


    float **inp_complex; // defining a double pointer array
    // initializing the 2D array
    // allocating the array using malloc() function
    inp_complex = malloc(var * sizeof *inp_complex);
    // array inside an array(2D array) using malloc
    for (int i = 0; i < var; i++) {
        inp_complex[i] = malloc(var * sizeof *inp_complex[i]);
    }
    printf("Please enter the imaginary matrix:\n");
    array_input_2D(inp_complex, var, var);


    float **constant; // defining a double pointer array
    // initializing the 2D array
    // allocating the array using malloc() function
    constant = malloc(2 * sizeof *constant);
    // array inside an array(2D array) using malloc
    for (int i = 0; i < 2; i++) {
        constant[i] = malloc(var * sizeof *constant[i]);
    }
    printf("Please enter the constant matrix:\n");
    array_input_2D(constant, 2, var);


    int n=2*var;

    for(int j=0; j<var; j++){
        for(int x=0; x<var; x++){
            array[j][x]=inp_real[j][x];
        }
        for(int x=var; x<n; x++){
            array[j][x]=(-1)*inp_complex[j][x-var];
        }
    }

    // putting all the values in array to be put in for real calculation
    for(int j=var; j<n; j++){
        for(int x=0; x<var; x++){
            array[j][x]=inp_complex[j-var][x];
        }
        for(int x=var; x<n; x++){
            array[j][x]=inp_real[j-var][x-var];
        }
    }

    for(int j=0; j<var; j++){
        array[j][n]=constant[0][j];
    }
    for(int j=var; j<n; j++){
        array[j][n]=constant[1][j-var];
    }

    // solving the equation with real coefficients
    calculation_real(array, 2*var, (2*var)+1, sol, pivot);

    // printing the solutions
    print_complex(sol, 2*var);


    // deallocating the arrays
    for (int i = 0; i < var; i++) {
        free(inp_real[i]);
        free(inp_complex[i]);
    }
    free(inp_real);
    free(inp_complex);
    for (int i = 0; i < 2; i++) {
        free(constant[i]);
    }
    free(constant);
    for (int i = 0; i < (2*var); i++) {
        free(array[i]);
    }
    free(array);
}


// function for matrix multiplication
void matrix_multiplication(float **x, int len, float *constant, float *output){
    for(int i=0; i<len; i++){
        float sum=0;
        for(int j=0; j<len; j++){
            sum = sum + (x[i][j] * constant[j]);
        }
        output[i] = sum;
    }
}



void Ax_equals_to_B(float **x, int rows, float pivot, float *sol, float *constant){

    float **inverse; // defining a double pointer array
    // initializing the 2D array
    // allocating the array using malloc() function
    inverse = malloc(rows * sizeof(*inverse));
    // array inside an array(2D array) using malloc
    for (int i = 0; i < rows; i++) {
        inverse[i] = malloc((rows + 1) * sizeof(float));
    }

    // calculating the inverse
    inverse_calc(pivot, inverse, rows, x);

    // multiplying inverse of A with B
    matrix_multiplication(inverse, rows, constant, sol);


//    // printing the solution
//    print_equation(sol, rows);

    for (int i = 0; i < rows; i++) {
        free(inverse[i]);
    }
    free(inverse);
}
