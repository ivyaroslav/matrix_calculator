#include <iostream>
#include <cmath>
#include <Windows.h>
#include <ctime>
#include <iomanip>
using namespace std;
int number, answer, size;
int i, j, k, n, determ;
void matrix_input(float matrix[][10], int size);
void matrix_output(float matrix[][10], int  size);
void SaddlePoints(float matrix[][10], int size);
void other(float matrix[][10], int size);
void repeat();
void task1();
void task2();

int main()
{
    do
    {
        SetConsoleOutputCP(1251);
        SetConsoleCP(1251);
        srand((unsigned)time(NULL));

        cout << "Please type in the number of the task: 1 or 2" << endl;
        cin >> number;
        while (number != 1 && number != 2)
        {
            cout << "Wrong value! Type in 1 for the first task, or type in 2 for the second task." << endl;
            cin >> number;
        }
        if (number == 1)
        {
            task1();
            repeat();
            break;
        }
        if (number == 2)
        {
            task2();
            repeat();
            break;
        }

    } while (answer == 1);
}

void matrix_input(float matrix[][10], int size)
{
    int choice;
    cout << " Please choose how would you like to fill in an array, type in 1 for manual fill; 2 for random numbers fill " << endl;
    cin >> choice;
    while (choice != 1 && choice != 2)
    {
        cout << "Wrong value! Type in 1 or 2" << endl;
        cin >> choice;
    }

    if (choice == 1)
    {
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                cout << "Matrix[" << i << "][" << j << "]: ";
                cin >> matrix[i][j];
            }
        }
    }
    else if (choice == 2)
    {
        int min, max;
        cout << "Type in the range of the values (-100,100)" << endl;
        cout << "Min value" << endl;
        cin >> min;
        cout << "Max value" << endl;
        cin >> max;

        while (min < -100 || min>100)
        {
            cout << "Please type in the range bounded by (-100;99)" << endl;
            cout << "Min value" << endl;
            cin >> min;
            cout << "Max value" << endl;
            cin >> max;

        }
        while (max < min || max>100)
        {
            if (max < min)
            {
                cout << "\aUpper limit can't be less than the lower limit\n";
                cout << "Min value" << endl;
                cin >> min;
                cout << "Max value" << endl;
                cin >> max;

            }
            if (max > 100)
            {
                cout << "\aToo much!\n";
                cout << "Min value" << endl;
                cin >> min;
                cout << "Max value" << endl;
                cin >> max;

            }
        }
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                matrix[i][j] = min + rand() % (max - min + 1);
            }
        }
    }
}

void matrix_output(float  matrix[][10], int size)
{
    cout << "    ";
    for (int z = 0; z < size; z++)
    {  //Printing the number of the column
        cout << "(" << z << ") ";
    }
    cout << endl;
    //==============================================
    for (int x = 0; x < size; x++)
    {   //Printing the row
        cout << x << ")|" << setw(3) << matrix[x][0];
        for (int y = 1; y < size; y++)
        {
            cout << setw(5) << matrix[x][y];
        }
        cout << " |\n";
    }
    cout << endl;
}

void task1()
{

    float matrix[10][10];
    int size;
    cout << "Task 1 is to find the saddle points of the matrix" << endl;
    cout << "Please type in the dimensions of a square matrix\n";
    cout << "From 3 to 10:\n";
    cin >> size;
    while (size < 3 || size>10)
    {
        cout << "Wrong value." << endl;
        cin >> size;
    }
    matrix_input(matrix, size);
    cout << "Input matrix" << endl;
    matrix_output(matrix, size);
    SaddlePoints(matrix, size);

}

void SaddlePoints(float matrix[][10], int size)
{
    int saddlePointCount = 0;

    for (int i = 0; i < size; i++)
    {
        int minInRow = matrix[i][0];
        int colIndex = 0;

        // Finding min element in the current row
        for (int j = 0; j < size; j++)
        {
            if (matrix[i][j] < minInRow)
            {
                minInRow = matrix[i][j];
                colIndex = j;
            }
        }

        // Checking if the min element is also the maximum in the column
        int saddlePoint = 1;  
        for (int k = 0; k < size; k++)
        {
            if (matrix[k][colIndex] > minInRow) {
                saddlePoint = 0;  // saddle point not found
                break;
            }
        }
        if (saddlePoint)
        {
            cout << "Saddle point (" << i << ", " << colIndex << "): " << minInRow << endl;
            saddlePointCount++;
        }
    }
    if (saddlePointCount == 0)
    {
        cout << "Saddle points are not found" << endl;
        other(matrix, size);

    }
}

void other(float matrix[][10], int size)
{
    int maxim = 0;
    int sum = 0;
    for (int i = 0; i < size; i++)
    {
        maxim = matrix[i][0];
        if ((i + 1) % 2 != 0) // in case of odd row
        {
            for (int j = 0; j < size; j++)
            {
                if (matrix[i][j] > maxim)
                {
                    maxim = matrix[i][j];
                }
            }
            cout << "The greatest element of " << i + 1 << "th row = " << maxim << endl;
        }
        else // in case of even row
        {
            for (int j = 0; j < size; j++)
            {
                sum += matrix[i][j];
            }
        }

    }
    cout << "Sum of the elements of all even rows in the matrix = " << sum << endl;
}


void subMatrix(float mat[][10], float temp[][10], int p, int q, int n)
{
    int i = 0, j = 0;
    // filling in the minor of a matrix
    for (int row = 0; row < n; row++)
    {
        for (int col = 0; col < n; col++)
        {
            if (row != p && col != q)
            {
                temp[i][j++] = mat[row][col];
                if (j == n - 1)
                {
                    j = 0;
                    i++;
                }
            }
        }
    }
}

int determinantOfMatrix(float matrix[][10], int size)
{
    int determinant = 0;
    if (size == 1) 
    {
        return matrix[0][0]; 
    }
    if (size == 2) 
    {
        return (matrix[0][0] * matrix[1][1]) - (matrix[0][1] * matrix[1][0]); 
    }
    float temp[10][10];
    temp[size][size];
    int sign = 1;
    for (int i = 0; i < size; i++)
    {
        subMatrix(matrix, temp, 0, i, size);
        determinant += sign * matrix[0][i] * determinantOfMatrix(temp, size - 1); 
        sign = -sign;
    }
    return determinant;
}
int identityMatrix(float matrix[][10], int n)
{
    for (i = 0; i < n; i++) 
    {
        for (j = 0; j < 2 * n; j++)
        {
            if (j == (i + n))
            {
                matrix[i][j] = 1;
            }
        }
    }
    return matrix[i][j];
}
void invertedMatrix(float matrix[][10], int n)
{
    float d;
    for (i = n - 1; i > 1; i--) 
    {                          
        if (matrix[i - 1][1] < matrix[i][1])
        {
            for (j = 0; j < n * 2; j++)
            {
                d = matrix[i][j];
                matrix[i][j] = matrix[i - 1][j];
                matrix[i - 1][j] = d;
            }
        }
    }
    for (i = 0; i < n; i++) 
    {
        for (j = 0; j < n * 2; j++) // working with the augmented matrix
        {
            if (j != i)
            {
                d = matrix[j][i] / matrix[i][i];//d - divisor for every row
                for (k = 0; k < n * 2; k++)
                {
                    matrix[j][k] = matrix[j][k] - (matrix[i][k] * d); // element of the inverse matrix = this element - the element of the "lower" row multiplied by the divisor
                }                                      
            }
        }
    }
    for (i = 0; i < n; i++)// transforming the initial matrix into an identity one.
    {
        d = matrix[i][i]; // the divisor by which each element of the augmented matrix will be divided
        for (j = 1; j <= n * 2; j++) //
        {
            matrix[i][j] = matrix[i][j] / d; 
        }
    }
    cout << "Inverse matrix " << endl;
    cout << endl;
    for (i = 0; i < n; i++) 
    {
        for (j = n; j < n * 2; j++)
        {
            cout << "     " << matrix[i][j];
        }
        cout << endl;
    }
}
void task2()
{
    float matrix[10][10] = { 0 };
    cout << "Type in the dimensions of a matrix \n";
    cout << "From 3 to 10:\n";
    cin >> n;
    while (n < 3 || n>10)
    {
        cout << "Wrong value" << endl;
        cin >> n;
    }
    matrix_input(matrix, n);
    determ = determinantOfMatrix(matrix, n); 
    matrix_output(matrix, n);
    identityMatrix(matrix, n);
    invertedMatrix(matrix, n);
    cout << " Determinant = " << determ << endl;

}



void repeat()
{
    cout << "Would you like to run the program again? \n1 - Yes \n2 - No" << endl;
    cin >> answer;
    while (answer != 1 && answer != 2)
    {
        cout << "Wrong value, type 1 or 2" << endl;
        cin >> answer;
    }
    while (answer == 1)
    {
        main();
    }
}