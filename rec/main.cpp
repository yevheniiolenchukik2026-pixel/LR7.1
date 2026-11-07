#include <iostream>
#include <iomanip>
#include <ctime>
#include <cstdlib>

using namespace std;

void Create(int** Q, const int rowCount, const int colCount, const int Low, const int High, int i = 0, int j = 0);
void Print(int** Q, const int rowCount, const int colCount, int i = 0, int j = 0);
void Sort(int** Q, const int rowCount, const int colCount, int i0 = 0, int i1 = 0);
void Change(int** Q, const int col1, const int col2, const int rowCount, int i = 0);
void Calc(int** Q, const int rowCount, const int colCount, int& S, int& k, int i = 0, int j = 0);

int main()
{
    int Low, High, rowCount, colCount, S, k, i;
    int** Q;

    srand((unsigned)time(NULL));

    Low = -26;
    High = 23;
    rowCount = 8;
    colCount = 6;
    S = 0;
    k = 0;

    Q = new int* [rowCount];
    for (i = 0; i < rowCount; i++)
        Q[i] = new int[colCount];

    Create(Q, rowCount, colCount, Low, High);
    cout << "Initial matrix:" << endl;
    Print(Q, rowCount, colCount);
    cout << endl;

    Sort(Q, rowCount, colCount);
    cout << "Sorted matrix:" << endl;
    Print(Q, rowCount, colCount);
    cout << endl;

    Calc(Q, rowCount, colCount, S, k);
    cout << "S = " << S << endl;
    cout << "k = " << k << endl;
    cout << "Modified matrix:" << endl;
    Print(Q, rowCount, colCount);
    cout << endl;

    for (i = 0; i < rowCount; i++)
        delete[] Q[i];
    delete[] Q;

    return 0;
}

void Create(int** Q, const int rowCount, const int colCount, const int Low, const int High, int i, int j)
{
    Q[i][j] = Low + rand() % (High - Low + 1);
    if (j < colCount - 1)
        Create(Q, rowCount, colCount, Low, High, i, j + 1);
    else if (i < rowCount - 1)
        Create(Q, rowCount, colCount, Low, High, i + 1, 0);
}

void Print(int** Q, const int rowCount, const int colCount, int i, int j)
{
    cout << setw(5) << Q[i][j];
    if (j < colCount - 1)
        Print(Q, rowCount, colCount, i, j + 1);
    else
    {
        cout << endl;
        if (i < rowCount - 1)
            Print(Q, rowCount, colCount, i + 1, 0);
    }
}

void Sort(int** Q, const int rowCount, const int colCount, int i0, int i1)
{
    if ((Q[0][i1] > Q[0][i1 + 1])
        ||
        (Q[0][i1] == Q[0][i1 + 1] &&
         Q[1][i1] < Q[1][i1 + 1])
        ||
        (Q[0][i1] == Q[0][i1 + 1] &&
         Q[1][i1] == Q[1][i1 + 1] &&
         Q[2][i1] > Q[2][i1 + 1]))
        Change(Q, i1, i1 + 1, rowCount);

    if (i1 < colCount - i0 - 2)
        Sort(Q, rowCount, colCount, i0, i1 + 1);
    else if (i0 < colCount - 2)
        Sort(Q, rowCount, colCount, i0 + 1, 0);
}

void Change(int** Q, const int col1, const int col2, const int rowCount, int i)
{
    int tmp;

    tmp = Q[i][col1];
    Q[i][col1] = Q[i][col2];
    Q[i][col2] = tmp;

    if (i < rowCount - 1)
        Change(Q, col1, col2, rowCount, i + 1);
}

void Calc(int** Q, const int rowCount, const int colCount, int& S, int& k, int i, int j)
{
    if (i == 0 && j == 0)
    {
        S = 0;
        k = 0;
    }

    if (!(Q[i][j] > 0 && Q[i][j] % 2 == 0))
    {
        S += Q[i][j];
        k++;
        Q[i][j] = 0;
    }

    if (j < colCount - 1)
        Calc(Q, rowCount, colCount, S, k, i, j + 1);
    else if (i < rowCount - 1)
        Calc(Q, rowCount, colCount, S, k, i + 1, 0);
}
