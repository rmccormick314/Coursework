#include <iostream>
#include <random>
#include "omp.h"

using std::cout;
using std::endl;

// Matrix size (we are using square matrices here for simplicity)
// Modify this value if you want for tests (actually recommended)
// But your code should be working with the default value (I will test with relatively large values)
const int SIZE = 4096;

// Declare your functions here
void matrixMultiplyBasic(double* A, double* B, double* C, double* result);

void matrixMultiplyVersion2(double* A, double* B, double* C, double* result);
void matrixMultiplyVersion3(double* A, double* B, double* C, double* result);
void matrixMultiplyVersion4(double* A, double* B, double* C, double* result);
void matrixMultiplyVersion5(double* A, double* B, double* C, double* result);

void transpose(double *A, double *B, int n);
void solution(double* A, double* B, double* C, double* result);

int main(int argc, char* argv[])
{
    // This program takes an algorithm version as command-line parameter
    // Right now there is just 1 (default matrix multiplication)
    // The different versions of your code should use different numbers: 2, 3, ...
    int algoVersion;
    if (argc != 2)
    {
        cout << "Error: You need to specify an algorithm version" << endl;
        return 1;
    }
    algoVersion = atoi(argv[1]);

    // Declare and allocate the matrices
    // Note that we represent 2-D matrices using 1-D arrays
    // You don't need to change this code
    double* matrixA = new double[SIZE * SIZE];
    double* matrixB = new double[SIZE * SIZE];
    double* matrixC = new double[SIZE * SIZE];
    double* matrixResult = new double[SIZE * SIZE];

    // Create a random number generator
    // You should not modify this code
    std::mt19937_64 gen(4815162342);
    std::uniform_real_distribution<double> genReal(0.0, 1.0);

    // Fill matrices A, B and C with random numbers
    // You should not modify the random numbers generation
    // Feel free to change the arrays if you want though
    for (int i = 0; i < SIZE; ++i)
    {
        for (int j = 0; j < SIZE; ++j)
        {
            matrixA[i * SIZE + j] = genReal(gen);
            matrixB[i * SIZE + j] = genReal(gen);
            matrixC[i * SIZE + j] = genReal(gen);
        }
    }

    // We use a switch here to be able to test the different versions of the algorithm without commenting/recompiling/etc. every time
    switch (algoVersion)
    {
        case 1:
        {
            // Base version of the algorithm
            // Use the function below as a blueprint to make your different optimized versions
            // Use the same "pattern" for the other cases: start timer, computation, stop timer, print time, break
            cout << "Running Version 1 of Algorithm..." << endl;
            double start = omp_get_wtime();
            matrixMultiplyBasic(matrixA, matrixB, matrixC, matrixResult);
            double stop = omp_get_wtime();
            cout << "Execution time Version 1: " << stop - start << " s" << endl;
            break;
        }
        //
        // Add your versions here
        //
        case 2:
        {
            cout << "Running Version 2 of Algorithm..." << endl;
            double start = omp_get_wtime();
            matrixMultiplyVersion2(matrixA, matrixB, matrixC, matrixResult);
            double stop = omp_get_wtime();
            cout << "Execution time Version 2: " << stop - start << " s" << endl;
            break;
        }

        case 3:
        {
            cout << "Running Version 3 of Algorithm..." << endl;
            double start = omp_get_wtime();
            matrixMultiplyVersion3(matrixA, matrixB, matrixC, matrixResult);
            double stop = omp_get_wtime();
            cout << "Execution time Version 3: " << stop - start << " s" << endl;
            break;
        }

        case 4:
        {
            cout << "Running Version 4 of Algorithm..." << endl;
            double start = omp_get_wtime();
            matrixMultiplyVersion3(matrixA, matrixB, matrixC, matrixResult);
            double stop = omp_get_wtime();
            cout << "Execution time Version 4: " << stop - start << " s" << endl;
            break;
        }

        case 5:
        {
            cout << "Running Version 5 of Algorithm..." << endl;
            double start = omp_get_wtime();
            matrixMultiplyVersion3(matrixA, matrixB, matrixC, matrixResult);
            double stop = omp_get_wtime();
            cout << "Execution time Version 5: " << stop - start << " s" << endl;
            break;
        }

        default:
        {
            cout << "Error: Unknown algorithm version" << endl;
            return 1;
        }
    }

    // Free the allocated memory
    delete[] matrixA;
    delete[] matrixB;
    delete[] matrixC;
    delete[] matrixResult;

    return 0;
}

// Write your functions below

// Version 1, basic matrix multiplication
// Use as a blueprint for your different optimized versions
void matrixMultiplyBasic(double* A, double* B, double* C, double* result)
{
#pragma omp parallel for
    for (int i = 0; i < SIZE; ++i)
    {
        for (int j = 0; j < SIZE; ++j)
        {
            for (int k = 0; k < SIZE; ++k)
            {
                result[i * SIZE + j] = A[i * SIZE + k] * B[k * SIZE + j] + C[i * SIZE + j];
            }
        }
    }
}

//
// Add your functions here
// E.g., matrixMultiplyVersion2, Version3, etc.
//
void matrixMultiplyVersion2(double* A, double* B, double* C, double* result)
{
    #pragma omp parallel for schedule(dynamic) collapse(2) num_threads(8)
    for (int i = 0; i < SIZE; ++i)
    {
        for (int j = 0; j < SIZE; ++j)
        {
            #pragma omp simd
            for (int k = 0; k < SIZE; ++k)
            {
                result[i * SIZE + j] = A[i * SIZE + k] * B[k * SIZE + j] + C[i * SIZE + j];
            }
        }
    }
}

void transpose(double *A, double *B, int n) {
    int i,j;
    for(i=0; i<n; i++) {
        for(j=0; j<n; j++) {
            B[j*n+i] = A[i*n+j];
        }
    }
}

void matrixMultiplyVersion3(double* A, double* B, double* C, double* result)
{
    double *B2 = (double*)malloc(sizeof(double)*SIZE*SIZE);
    transpose(B, B2, SIZE);

    #pragma omp parallel for schedule(dynamic) collapse(2) num_threads(8)
    for (int i = 0; i < SIZE; ++i)
    {
        for (int j = 0; j < SIZE; ++j)
        {
            #pragma omp simd
            for (int k = 0; k < SIZE; ++k)
            {
                result[i * SIZE + j] = A[i * SIZE + k] * B2[k * SIZE + j] + C[i * SIZE + j];
            }
        }
    }

    free(B2);
}

void matrixMultiplyVersion4(double* A, double* B, double* C, double* result)
{
    double *B2 = (double*)malloc(sizeof(double)*SIZE*SIZE);
    transpose(B, B2, SIZE);

    int CHUNK = 8;
    int i, j, k;

    #pragma omp parallel num_threads(8)
    for (i = 0; i < SIZE; ++i)
    {
        #pragma omp for nowait schedule(dynamic) private(i, j, k)
        for (j = 0; j < SIZE; ++j)
        {
            #pragma omp simd
            for (k = 0; k < SIZE; ++k)
            {
                result[i * SIZE + j] = A[i * SIZE + k] * B2[k * SIZE + j] + C[i * SIZE + j];
            }
        }
    }

    free(B2);
}

void matrixMultiplyVersion5(double* A, double* B, double* C, double* result)
{

}
