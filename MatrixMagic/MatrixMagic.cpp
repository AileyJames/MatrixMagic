
#include "MatrixMagic.h"

//vectors
//created matrix class
//Unit testing in C++: Google Test
//GnuGet alot of libraries

int main(int argc, char* argv[]) {
	//Please give the size and name of file. 
	if (argc < 2) {
		cout << "Usage: " << argv[0] << " size [output_path]";
		return 1;
	}
	const int n = atoi(argv[1]);
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
	int** x = createMatrix(n);

	for (int i1 = 0; i1 < n; i1++) {
		for (int j1 = 0; j1 < n; j1++)
		{
			const int i = i1 + 1;
			const int j = j1 + 1;

			x[i1][j1] = n * abs((i + j - 1 + (n/2)) % n) + abs((i + 2*j - 2) % n) + 1;
		}
	}

	return x;
}

int** magicSquareDoublyEven(int n) {
	//every 1 in the binary is where you hit the countup zone. 
	int bits = 0b1001011001101001;
    int size = n * n;
    int mult = n / 4;  // how many multiples of 4
	int** result = createMatrix(n);
 
    for (int r=0, i=0; r<n; r++) {
        for (int c=0; c<n; c++, i++) {
            int bitPos = c / mult + (r / mult) * 4;
			const int countUpZone = (bits & (int)pow(2, bitPos));
            result[r][c] = countUpZone != 0 ? i + 1 : size - i;
        }
    }
 
    return result;
}

int** magicSquareSinglyEven(const int n) {

	// The process for solving a singly even magic square consists of decomposing it into odd 
	// magic squares and applying transformations to them.  We can always do this because a
	// singly even magic square has a rank of 2n but not 4n, which means rank / 2 is always an
	// odd number.

	int size = n * n;
	const int halfN = n / 2;
	int subSquareSize = size / 4;

	// Get the odd magic square that's to form the quadrants of this one, and ensure
	// we have the factors for each quadrant for transforming these odd sub-squares.
	int** subSquare = magicSquareOdd(halfN);
	int quadrantFactors[] = { 0, 2, 3, 1 };

	int** result = createMatrix(n);

	// Go through the first transformation, which consists of picking up values for the right
	// quadrant and scaling them appropriately.  
	for (int r = 0; r < n; r++) {
		for (int c = 0; c < n; c++) {
			int quadrant = (r / halfN) * 2 + (c / halfN);
			result[r][c] = subSquare[r % halfN][c % halfN];
			result[r][c] += quadrantFactors[quadrant] * subSquareSize;
		}
	}

	int nColsLeft = halfN / 2;
	int nColsRight = nColsLeft - 1;

	// The last step consists of swapping out key values in the quadrants.  
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