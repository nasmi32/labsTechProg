#include <iostream>
#include <vector>

using namespace std;

class Vector
{
public:
    vector<int> coordinates;
};

Vector *operator+(const Vector &a, const Vector &b)
{
    if (a.coordinates.size() == b.coordinates.size())
    {
        Vector *c = new Vector; //создаем результирующий объект в куче, но тогда дальше придется следить за его использованием
        for (int i = 0; i < a.coordinates.size(); ++i)
        {
            c->coordinates.push_back(a.coordinates[i] + b.coordinates[i]);
        }

        return c;
    }
    else
    {
        cout << "Vectors should have equal length" << endl;
    }
}

Vector operator-(const Vector &a, const Vector &b)
{
    if (a.coordinates.size() == b.coordinates.size())
    {
        Vector c;
        for (int i = 0; i < a.coordinates.size(); ++i)
        {
            c.coordinates.push_back(a.coordinates[i] - b.coordinates[i]);
        }

        return c;
    }
    else
    {
        cout << "Vectors should have equal length" << endl;
    }

}

Vector operator*(const Vector &a, const int n)
{
    Vector c;
    for (int i = 0; i < a.coordinates.size(); ++i)
    {
        c.coordinates.push_back(a.coordinates[i] * n);
    }
    return c;
}

int operator*(const Vector &a, const Vector &b)
{
    if (a.coordinates.size() == b.coordinates.size())
    {
        int result = 0;
        for (int i = 0; i < a.coordinates.size(); ++i)
        {
            result += a.coordinates[i] * b.coordinates[i];
        }
        return result;
    }
    else
    {
        cout << "Vectors should have equal length" << endl;
    }
}

void printVector(const Vector &vectorToPrint)
{
    for (int i = 0; i < vectorToPrint.coordinates.size(); ++i)
    {
        cout << vectorToPrint.coordinates[i] << " ";
    }
    cout << endl;
}

void fillVector(Vector *newVector)
{
    int n, curCoordinate;

    cout << "Input number of coordinates: ";
    cin >> n;

    cout << "Input coordinates: ";
    for (int i = 0; i < n; ++i)
    {
        cin >> curCoordinate;
        newVector->coordinates.push_back(curCoordinate);
    }

}

int main()
{
    Vector *vectorA = new Vector;
    Vector *vectorB = new Vector;

    fillVector(vectorA);
    fillVector(vectorB);

    Vector *vectorC;
    vectorC = (*vectorA) + (*vectorB);
    cout << "VectorA + VectorB = ";
    printVector(*vectorC);
    delete vectorC;

    Vector vectorD;
    vectorD = (*vectorA) - (*vectorB);
    cout << "VectorA - VectorB = ";
    printVector(vectorD);

    vectorD = (*vectorA) * 5;
    cout << "VectorA * 5 = ";
    printVector(vectorD);

    cout << "VectorA * VectorB = " << (*vectorA) * (*vectorB);

    delete vectorB;
    delete vectorA;

    return 0;
}