#include <iostream>
#include <vector>

using namespace std;

class Matrix
{
public:
    vector<vector<int>> coordinates;

};

Matrix *operator+(const Matrix &a, const Matrix &b)
{
    if (a.coordinates.size() == b.coordinates.size() and a.coordinates[0].size() == b.coordinates[0].size())
    {
        Matrix *c = new Matrix;
        for (int i = 0; i < a.coordinates.size(); ++i)
        {
            vector<int> curRow;
            for (int j = 0; j < a.coordinates[i].size(); ++j)
            {
                curRow.push_back(a.coordinates[i][j] + b.coordinates[i][j]);
            }
            c->coordinates.push_back(curRow);
        }
        return c;
    }
    else
    {
        throw string("Matrices should have equal dimensions");
    }
}

Matrix *operator-(const Matrix &a, const Matrix &b)
{
    if (a.coordinates.size() == b.coordinates.size() and a.coordinates[0].size() == b.coordinates[0].size())
    {
        Matrix *c = new Matrix;
        for (int i = 0; i < a.coordinates.size(); ++i)
        {
            vector<int> curRow;
            for (int j = 0; j < a.coordinates[i].size(); ++j)
            {
                curRow.push_back(a.coordinates[i][j] - b.coordinates[i][j]);
            }
            c->coordinates.push_back(curRow);
        }
        return c;
    }
    else
    {
        throw string("Matrices should have equal dimensions");
    }
}

void printMatrix(const Matrix &matrixToPrint)
{
    for (int i = 0; i < matrixToPrint.coordinates.size(); ++i)
    {
        for (int j = 0; j < matrixToPrint.coordinates[i].size(); ++j)
        {
            cout.width(4); //для форматированного вывода матрицы
            cout << matrixToPrint.coordinates[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

Matrix *operator*(const Matrix &a, const Matrix &b)
{
    if (a.coordinates[0].size() ==
        b.coordinates.size()) //кол-во столбцов первой матрицы должно равняться кол-ву строк второй матрицы
    {
        Matrix *c = new Matrix;

        //заполняем выходную матрицу нулями
        for (int i = 0; i < a.coordinates.size(); ++i)
        {
            vector<int> curRow;
            for (int j = 0; j < b.coordinates[0].size(); ++j)
            {
                curRow.push_back(0);
            }
            c->coordinates.push_back(curRow);
        }

        for (int i = 0; i < a.coordinates.size(); ++i) //цикл по строкам первой матрицы
        {
            for (int j = 0; j < b.coordinates[0].size(); ++j) //цикл по столбцам второй матрицы
            {
                for (int k = 0; k < a.coordinates[0].size(); ++k) //цикл по столбцам первой матрицы
                {
                    c->coordinates[i][j] += a.coordinates[i][k] * b.coordinates[k][j];
                }
            }
        }
        return c;
    }
    else
    {
        throw string("Not valid matrices dimensions");
    }
}

Matrix *operator*(const Matrix &a, const int k)
{
    Matrix *c = new Matrix;

    for (int i = 0; i < a.coordinates.size(); ++i)
    {
        vector<int> curRow;
        for (int j = 0; j < a.coordinates[i].size(); ++j)
        {
            curRow.push_back(a.coordinates[i][j] * k);
        }
        c->coordinates.push_back(curRow);
    }

    return c;
}

void fillMatrix(Matrix *newMatrix)
{
    int n, m, curCoordinate;

    cout << "Input number of coordinates (n x m): ";
    cin >> n >> m;

    cout << "Input coordinates: ";
    for (int i = 0; i < n; ++i)
    {
        cout << "Input " << i + 1 << " row (" << m << " elements): ";
        vector<int> curRow;

        for (int j = 0; j < m; ++j)
        {
            cin >> curCoordinate;
            curRow.push_back(curCoordinate);
        }
        newMatrix->coordinates.push_back(curRow);
    }

}

int main()
{
    Matrix *matrixA = new Matrix;
    Matrix *matrixB = new Matrix;

    fillMatrix(matrixA);
    fillMatrix(matrixB);

    int num;
    cout << "Input number: ";
    cin >> num;

    Matrix *matrixC;

    printMatrix(*matrixA);
    printMatrix(*matrixB);

    cout << "MatrixA + MatrixB = " << endl;
    try
    {
        matrixC = (*matrixA) + (*matrixB);
        printMatrix(*matrixC);
        delete matrixC;
    }
    catch (string &errorMessage)
    {
        cout << errorMessage << endl;
    }

    cout << "MatrixA - MatrixB = " << endl;
    try
    {
        matrixC = (*matrixA) - (*matrixB);
        printMatrix(*matrixC);
        delete matrixC;
    }
    catch (string &errorMessage)
    {
        cout << errorMessage << endl;
    }


    cout << "MatrixA * MatrixB = " << endl;
    try
    {
        matrixC = (*matrixA) * (*matrixB);
        printMatrix(*matrixC);
        delete matrixC;
    }
    catch (string &errorMessage)
    {
        cout << errorMessage << endl;
    }

    cout << "MatrixA * " << num << " = " << endl;
    matrixC = (*matrixA) * num;
    printMatrix(*matrixC);

    delete matrixC;
    delete matrixB;
    delete matrixA;

    return 0;
}
