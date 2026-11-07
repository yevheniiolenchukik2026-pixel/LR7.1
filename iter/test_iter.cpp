#include <cstdio>
#include <iostream>

#define main program_main
#include "main.cpp"
#undef main

using namespace std;

int Check(const char* name, const int expected, const int actual)
{
    if (expected == actual)
    {
        cout << "PASS  " << name << ": expected " << expected << ", got " << actual << endl;
        return 0;
    }
    cout << "FAIL  " << name << ": expected " << expected << ", got " << actual << endl;
    return 1;
}

int main()
{
    const int rowCount = 8;
    const int colCount = 6;
    int i, j, S, k, failed;
    int** Q;
    char name[32];
    int src[rowCount][colCount] = {
        {  -9,   0,   2,   3,  22,  23 },
        {  -1,   7, -20,  20, -24, -19 },
        {  22, -16,  15,  22,   4, -14 },
        { -15, -13,  13, -18,   9,  22 },
        {  10,   8,   3,  10, -26,  -9 },
        { -10,   4,   9, -10, -25,   9 },
        {  -2, -23, -13,   5, -19, -10 },
        {  -2, -24, -25,  11, -22,   5 }
    };
    int expected[rowCount][colCount] = {
        {  0,  0,  2,  0, 22,  0 },
        {  0,  0,  0, 20,  0,  0 },
        { 22,  0,  0, 22,  4,  0 },
        {  0,  0,  0,  0,  0, 22 },
        { 10,  8,  0, 10,  0,  0 },
        {  0,  4,  0,  0,  0,  0 },
        {  0,  0,  0,  0,  0,  0 },
        {  0,  0,  0,  0,  0,  0 }
    };

    Q = new int* [rowCount];
    for (i = 0; i < rowCount; i++)
    {
        Q[i] = new int[colCount];
        for (j = 0; j < colCount; j++)
            Q[i][j] = src[i][j];
    }

    S = 0;
    k = 0;
    failed = 0;

    Calc(Q, rowCount, colCount, S, k);

    failed += Check("Calc sum S", -257, S);
    failed += Check("Calc count k", 37, k);
    for (i = 0; i < rowCount; i++)
        for (j = 0; j < colCount; j++)
        {
            snprintf(name, sizeof(name), "Calc Q[%d][%d]", i, j);
            failed += Check(name, expected[i][j], Q[i][j]);
        }

    for (i = 0; i < rowCount; i++)
        delete[] Q[i];
    delete[] Q;

    if (failed == 0)
        cout << endl << "ALL TESTS PASSED" << endl;
    else
        cout << endl << "FAILED: " << failed << endl;

    return failed;
}
