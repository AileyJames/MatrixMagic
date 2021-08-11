

#include <iostream>
#include <stdio.h>
#include<algorithm>
#include<assert.h>
#include <iterator>
#include <fstream>

using namespace std;

int** magicSquare( int n);
void writeMagicSquare(int** magicSquare, int n, string path);
int magicConstant( int n);
int** magicSquareOdd(const int n);
int** magicSquareDoublyEven(const int n);
int** magicSquareSinglyEven(const int n);
void freeMatrix(int** matrix, int n);



int main(int argc, char* argv[]) {

	const int n = atoi(argv[1]);
	if (argc < 2) {
		cout << "Usage: " << argv[0] << " size [output_path]";
		return 1;
	}
	if (n < 3) {
		cout << "Please Ensure the matrix is bigger then 3" << endl;
		return 1;
	}
	int** ms = magicSquare(n);

	const std::string path(argc < 3 ? "matrix.txt" : argv[2]);
	writeMagicSquare(ms, n, path);
	freeMatrix(ms, n);
	return 0;
}


void freeMatrix(int** matrix, int n) {

	for (int i = 0; i < n; i++) {
		delete[] matrix[i];
	}
	delete[] matrix;
}

int** magicSquare(int n) {
	if (n % 2 == 1) {
		return magicSquareOdd(n);
	}
	else if (n % 4 == 0) {
		return magicSquareDoublyEven(n);
	}
	else {
		return magicSquareSinglyEven(n);
	}
}

void writeMagicSquare(int** magicSquare, int n, std::string path) {
	fstream fs;
	fs.open(path, fstream::out);
	if (!fs.fail()) {
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++) {
				fs << magicSquare[i][j];

				if (j < n-1) {
					fs <<  ",";
				}
			}
			fs << endl;
		}
		fs.close();
	}
	else {
		cout << "Error Writing to File: " << path << endl;
	}
	
}

int magicConstant(int n) {
	return n * (n * n + 1) / 2;

}


int** createMatrix(int n) {
	int** result = new int* [n];

	for (int i = 0; i < n; i++) {
		result[i] = new int[n];
		memset(result[i], 0, sizeof(int) * n);
	}
	return result;
}


int** magicSquareOdd(const int n) {
	int value = 0;
	int gridSize = n * n;
	int c = n / 2;
	int r = 0;

	int** result = createMatrix(n);

	while (++value <= gridSize) {
		result[r][c] = value;

		if (r == 0) {
			if (c == n - 1) {
				r++;
			}
			else {
				r = n - 1;
				c++;
			}
		}
		else if (c == n - 1) {
			r--;
			c = 0;
		}
		else if (result[r - 1][c + 1] == 0) {
			r--;
			c++;
		}
		else {
			r++;
		}
	}

	return result;
}



int** magicSquareDoublyEven(int n) {
	int bits = 0b1001011001101001;
    int size = n * n;
    int mult = n / 4;  // how many multiples of 4
	int** result = createMatrix(n);
 
    for (int r=0, i=0; r<n; r++) {
        for (int c=0; c<n; c++, i++) {
            int bitPos = c / mult + (r / mult) * 4;
            result[r][c] = (bits & (1 << bitPos)) != 0 ? i + 1 : size - i;
        }
    }
 
    return result;
}

int** magicSquareSinglyEven(const int n) {

	int size = n * n;
	const int halfN = n / 2;
	int subSquareSize = size / 4;

	int** subSquare = magicSquareOdd(halfN);
	int quadrantFactors[] = { 0, 2, 3, 1 };

	int** result = createMatrix(n);

	for (int r = 0; r < n; r++) {
		for (int c = 0; c < n; c++) {
			int quadrant = (r / halfN) * 2 + (c / halfN);
			result[r][c] = subSquare[r % halfN][c % halfN];
			result[r][c] += quadrantFactors[quadrant] * subSquareSize;
		}
	}

	int nColsLeft = halfN / 2;
	int nColsRight = nColsLeft - 1;

	for (int r = 0; r < halfN; r++) {
		for (int c = 0; c < n; c++) {
			if (c < nColsLeft || c >= n - nColsRight
				|| (c == nColsLeft && r == nColsLeft)) {
				if (c == 0 && r == nColsLeft) {
					continue;
				}

				int tmp = result[r][c];
				result[r][c] = result[r + halfN][c];
				result[r + halfN][c] = tmp;
			}
		}
	}

	freeMatrix(subSquare, halfN);
	return result;
}