#include <iostream>
#include <stdio.h>
#include<algorithm>
#include<assert.h>
#include <iterator>
#include <fstream>
using namespace std;

int** magicSquare(int n);
void writeMagicSquare(int** magicSquare, int n, string path);
int magicConstant(int n);
int** magicSquareOdd(const int n);
int** magicSquareDoublyEven(const int n);
int** magicSquareSinglyEven(const int n);
void freeMatrix(int** matrix, int n);