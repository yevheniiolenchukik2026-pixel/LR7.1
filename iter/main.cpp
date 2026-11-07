#include <iostream>
#include <iomanip>
#include <ctime>
#include <cstdlib>

using namespace std;

void Create(int** Q, const int rowCount, const int colCount, const int Low, const int High);
void Print(int** Q, const int rowCount, const int colCount);
void Sort(int** Q, const int rowCount, const int colCount);
void Change(int** Q, const int col1, const int col2, const int rowCount);
void Calc(int** Q, const int rowCount, const int colCount, int& S, int& k);

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

    Sort(Q, rowCount, colCount);
    cout << "Sorted matrix:" << endl;
    Print(Q, rowCount, colCount);

    Calc(Q, rowCount, colCount, S, k);
    cout << "S = " << S << endl;
    cout << "k = " << k << endl;
    cout << "Modified matrix:" << endl;
    Print(Q, rowCount, colCount);

    for (i = 0; i < rowCount; i++)
        delete[] Q[i];
    delete[] Q;

    return 0;
}

void Create(int** Q, const int rowCount, const int colCount, const int Low, const int High)
{
    int i, j;

    for (i = 0; i < rowCount; i++)
        for (j = 0; j < colCount; j++)
            Q[i][j] = Low + rand() % (High - Low + 1);
}

void Print(int** Q, const int rowCount, const int colCount)
{
    int i, j;

    cout << endl;
    for (i = 0; i < rowCount; i++)
    {
        for (j = 0; j < colCount; j++)
            cout << setw(5) << Q[i][j];
        cout << endl;
    }
    cout << endl;
}

void Sort(int** Q, const int rowCount, const int colCount)
{
    int i0, i1;

    for (i0 = 0; i0 < colCount - 1; i0++)
        for (i1 = 0; i1 < colCount - i0 - 1; i1++)
            if ((Q[0][i1] > Q[0][i1 + 1])
                ||
                (Q[0][i1] == Q[0][i1 + 1] &&
                 Q[1][i1] < Q[1][i1 + 1])
                ||
                (Q[0][i1] == Q[0][i1 + 1] &&
                 Q[1][i1] == Q[1][i1 + 1] &&
                 Q[2][i1] > Q[2][i1 + 1]))
                Change(Q, i1, i1 + 1, rowCount);
}

void Change(int** Q, const int col1, const int col2, const int rowCount)
{
    int i, tmp;

    for (i = 0; i < rowCount; i++)
    {
        tmp = Q[i][col1];
        Q[i][col1] = Q[i][col2];
        Q[i][col2] = tmp;
    }
}

void Calc(int** Q, const int rowCount, const int colCount, int& S, int& k)
{
    int i, j;

    S = 0;
    k = 0;
    for (i = 0; i < rowCount; i++)
        for (j = 0; j < colCount; j++)
            if (!(Q[i][j] > 0 && Q[i][j] % 2 == 0))
            {
                S += Q[i][j];
                k++;
                Q[i][j] = 0;
            }
}
