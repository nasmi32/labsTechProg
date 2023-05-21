#include <iostream>
#include <vector>

using namespace std;

class Vector;

class Matrix
{
private:
    vector<vector<int>> coordinates;

    friend class Vector;

public:
    void fill()
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
            this->coordinates.push_back(curRow);
        }

    }

    void print()
    {
        for (int i = 0; i < this->coordinates.size(); ++i)
        {
            for (int j = 0; j < this->coordinates[i].size(); ++j)
            {
                cout.width(4); //для форматированного вывода матрицы
                cout << this->coordinates[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }

    Matrix operator+(const Matrix &b)
    {
        if (this->coordinates.size() == b.coordinates.size() and this->coordinates[0].size() == b.coordinates[0].size())
        {
            Matrix c;
            for (int i = 0; i < this->coordinates.size(); ++i)
            {
                vector<int> curRow;
                for (int j = 0; j < this->coordinates[i].size(); ++j)
                {
                    curRow.push_back(this->coordinates[i][j] + b.coordinates[i][j]);
                }
                c.coordinates.push_back(curRow);
            }
            return c;
        }
        else
        {
            throw string("Matrices should have equal dimensions");
        }
    }

    Matrix operator-(const Matrix &b)
    {
        if (this->coordinates.size() == b.coordinates.size() and this->coordinates[0].size() == b.coordinates[0].size())
        {
            Matrix c;
            for (int i = 0; i < this->coordinates.size(); ++i)
            {
                vector<int> curRow;
                for (int j = 0; j < this->coordinates[i].size(); ++j)
                {
                    curRow.push_back(this->coordinates[i][j] - b.coordinates[i][j]);
                }
                c.coordinates.push_back(curRow);
            }
            return c;
        }
        else
        {
            throw string("Matrices should have equal dimensions");
        }
    }

    Matrix operator*(const Matrix &b)
    {
        if (this->coordinates[0].size() ==
            b.coordinates.size()) //кол-во столбцов первой матрицы должно равняться кол-ву строк второй матрицы
        {
            Matrix c;

            //заполняем выходную матрицу нулями
            for (int i = 0; i < this->coordinates.size(); ++i)
            {
                vector<int> curRow;
                for (int j = 0; j < b.coordinates[0].size(); ++j)
                {
                    curRow.push_back(0);
                }
                c.coordinates.push_back(curRow);
            }

            for (int i = 0; i < this->coordinates.size(); ++i) //цикл по строкам первой матрицы
            {
                for (int j = 0; j < b.coordinates[0].size(); ++j) //цикл по столбцам второй матрицы
                {
                    for (int k = 0; k < this->coordinates[0].size(); ++k) //цикл по столбцам первой матрицы
                    {
                        c.coordinates[i][j] += this->coordinates[i][k] * b.coordinates[k][j];
                        //printMatrix(*c);
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

    Matrix operator*(const int k)
    {
        Matrix c;

        for (int i = 0; i < this->coordinates.size(); ++i)
        {
            vector<int> curRow;
            for (int j = 0; j < this->coordinates[i].size(); ++j)
            {
                curRow.push_back(this->coordinates[i][j] * k);
            }
            c.coordinates.push_back(curRow);
        }

        return c;
    }

    Vector operator*(
            const Vector &vector); //прототип, потому что функция будет определена ниже после полного определения класса Вектор
};

class Vector
{
private:
    vector<int> coordinates;

    friend Vector Matrix::operator*(const Vector &vector);

public:
    void fill()
    {
        int n, curCoordinate;

        cout << "Input number of coordinates: ";
        cin >> n;

        cout << "Input coordinates: ";
        for (int i = 0; i < n; ++i)
        {
            cin >> curCoordinate;
            this->coordinates.push_back(curCoordinate);
        }

    }

    void print()
    {
        for (int i = 0; i < this->coordinates.size(); ++i)
        {
            cout << this->coordinates[i] << " ";
        }
        cout << endl;
    }

    Vector operator+(const Vector &b)
    {
        if (this->coordinates.size() == b.coordinates.size())
        {
            Vector c;
            for (int i = 0; i < this->coordinates.size(); ++i)
            {
                c.coordinates.push_back(this->coordinates[i] + b.coordinates[i]);
            }

            return c;
        }
        else
        {
            throw string("Vectors should have equal length");
        }
    }

    Vector operator-(const Vector &b)
    {
        if (this->coordinates.size() == b.coordinates.size())
        {
            Vector c;
            for (int i = 0; i < this->coordinates.size(); ++i)
            {
                c.coordinates.push_back(this->coordinates[i] - b.coordinates[i]);
            }

            return c;
        }
        else
        {
            throw string("Vectors should have equal length");
        }

    }

    Vector operator*(const int n)
    {
        Vector c;
        for (int i = 0; i < this->coordinates.size(); ++i)
        {
            c.coordinates.push_back(this->coordinates[i] * n);
        }
        return c;
    }

    int operator*(const Vector &b)
    {
        if (this->coordinates.size() == b.coordinates.size())
        {
            int result = 0;
            for (int i = 0; i < this->coordinates.size(); ++i)
            {
                result += this->coordinates[i] * b.coordinates[i];
            }
            return result;
        }
        else
        {
            throw string("Vectors should have equal length");
        }
    }

    Vector operator*(const Matrix &matrix)
    {
        if (this->coordinates.size() == matrix.coordinates.size())
        {
            Vector result;
            for (int i = 0; i < matrix.coordinates[0].size(); ++i)
            {
                int curMul = 0;
                for (int j = 0; j < this->coordinates.size(); ++j)
                {
                    curMul += this->coordinates[j] * matrix.coordinates[j][i];
                }
                result.coordinates.push_back(curMul);
            }
            return result;
        }
        else
        {
            throw string("Not valid matrix's dimensions");
        }
    }
};

//функция расположена здесь так как она работает с классом вектор (использует его атрибуты)
Vector Matrix::operator*(const Vector &vector)
{
    if (this->coordinates[0].size() == vector.coordinates.size())
    {
        Vector result;
        for (int i = 0; i < this->coordinates.size(); ++i)
        {
            int curMul = 0;
            for (int j = 0; j < this->coordinates[i].size(); ++j)
            {
                curMul += this->coordinates[i][j] * vector.coordinates[j];
            }
            result.coordinates.push_back(curMul);
        }
        return result;
    }
    else
    {
        throw string("Not valid matrix's dimensions");
    }
}

int main()
{
    Matrix matrixA;
    Matrix matrixB;
    matrixA.fill();
    matrixB.fill();

    Vector vectorA;
    Vector vectorB;
    vectorA.fill();
    vectorB.fill();

    matrixA.print();
    matrixB.print();
    vectorA.print();
    vectorB.print();

    cout << "MatrixA * VectorA = ";
    try
    {
//        Vector result;
//        result = matrixA * vectorA;
//        result.print();
        (matrixA * vectorA).print();
    }
    catch (string &errorMessage)
    {
        cout << errorMessage << endl;
    }

    cout << "VectorA * MatrixA = ";
    try
    {
        Vector result;
        result = vectorA * matrixB;
        result.print();
    }
    catch (string &errorMessage)
    {
        cout << errorMessage << endl;
    }

    cout << "VectorA * VectorB = ";
    try
    {
        int result;
        result = vectorA * vectorB;
        cout << result << endl;
    }
    catch (string &errorMessage)
    {
        cout << errorMessage << endl;
    }

    cout << "MatrixA * MatrixB = " << endl;
    try
    {
        Matrix result;
        result = matrixA * matrixB;
        result.print();
    }
    catch (string &errorMessage)
    {
        cout << errorMessage << endl;
    }

    return 0;
}
