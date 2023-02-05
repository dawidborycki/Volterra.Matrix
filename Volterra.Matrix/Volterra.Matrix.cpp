#include "Volterra.Matrix.h"
#include <chrono>
#include <random>

using namespace std;

double** generateRandomSquareMatrix(int size) {
    // Initialize random number generator
    random_device random_device;
    default_random_engine engine(random_device());

    // Prepare uniform distribution 
    uniform_real_distribution uniform_distribution;

    // Generate matrix
    double** matrix = new double*[size];

    for (int i = 0; i < size; i++) {
        matrix[i] = new double[size];

        for (int j = 0; j < size; j++) {
            matrix[i][j] = uniform_distribution(engine);
        }
    }

    return matrix;
}

void printSquareMatrix(double** matrix, int size) {
    for (int i = 0; i < size; i++) {

        for (int j = 0; j < size; j++) {
            cout << fixed << setprecision(4) << matrix[i][j] << " ";
        }

        cout << endl;
    }
}

double** squareMatrixProduct(double** matrix1, double** matrix2, int size)
{
    double** result = new double*[size];

    for (int i = 0; i < size; i++) {
        result[i] = new double[size];

        for (int j = 0; j < size; j++) {

            result[i][j] = 0;

            for (int k = 0; k < size; k++) {
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }

    return result;
}

void releaseSquareMatrix(double** matrix, int size) {
    for (int i = 0; i < size; i++) {
        delete[] matrix[i];
    }

    delete[] matrix;
}

void simpleTest() {
    const int size = 3;

    double** matrix1 = generateRandomSquareMatrix(size);
    double** matrix2 = generateRandomSquareMatrix(size);

    cout << "Matrix1:" << endl;
    printSquareMatrix(matrix1, size);

    cout << endl << "Matrix2:" << endl;
    printSquareMatrix(matrix2, size);

    cout << endl << "Product:" << endl;
    double** product = squareMatrixProduct(matrix1, matrix2, size);
    printSquareMatrix(product, size);

    releaseSquareMatrix(matrix1, size);
    releaseSquareMatrix(matrix2, size);
    releaseSquareMatrix(product, size);
}

double msElapsedTime(chrono::system_clock::time_point start) {
    auto end = chrono::system_clock::now();

    return chrono::duration_cast<chrono::milliseconds>(end - start).count();
}

chrono::system_clock::time_point now() {
    return chrono::system_clock::now();
}

void performanceTest(int size, int trialCount) {
    double** matrix1, ** matrix2, ** product;

    auto start = now();

    for (int i = 0; i < trialCount; i++) {
        matrix1 = generateRandomSquareMatrix(size);
        matrix2 = generateRandomSquareMatrix(size);

        product = squareMatrixProduct(matrix1, matrix2, size);

        releaseSquareMatrix(matrix1, size);
        releaseSquareMatrix(matrix2, size);
        releaseSquareMatrix(product, size);
    }

    auto elapsedTime = msElapsedTime(start);

    cout << "Matrix size: " << size << "x" << size
        << ", Trial count: " << trialCount 
        << ", Elapsed time [s]: " << fixed << setprecision(2) << elapsedTime / 60 << endl;
}

int main(int argc, char** argv)
{
    //simpleTest();
  
    // Performance testing
    if (argc < 2)
    {
        cout << "Trial count is missing." << endl;
        return 0;
    }

    const int szCount = 5;
    int size[szCount] {100, 200, 300, 400, 500};

    int trialCount = stoi(argv[1]);

    for (int i = 0; i < szCount; i++) {
        performanceTest(size[i], trialCount);
    }

    cout << endl;

	return 0;
}
