#include <iostream> 
#include <stdio.h>
#include <thread>
#include <mutex>
#include <atomic>
#include <stdlib.h>
#include <time.h>
#include <iomanip>
#include <math.h>
#include <vector>

using namespace std;

#define EXIT_SUCCESS 0 
#define size 2


int counter = 0;
int limit = 10;
mutex mtx;

void threadAction(int id);
void multrow(vector<vector<int>> &matrix3,vector<vector<int>> matrix1,vector<vector<int>> matrix2,int row);
void print_matrix(vector<vector<int>> matrix,int digits);

int main()
{
	srand((unsigned)time(0));
	cout << "===========================================================" << endl;
    cout << "\tThreads" << endl;
    cout << "===========================================================" << endl << endl;

	vector<int> row_zeroes(size,0);

    thread threads[size];

    vector<vector<int>> matrix1;
	matrix1.reserve(size);
	for(int i = 0; i < size;i++)
	{
		matrix1.push_back(row_zeroes);
		for(int j = 0; j < size;j++)
		{
			matrix1[i][j] = rand()%limit;
		}
	}

	cout << endl << "MATRIX1; " << endl;
	int digits = log10(limit);
	print_matrix(matrix1,digits);


	vector<vector<int>> matrix2;
	matrix2.reserve(size);
	for(int i = 0; i < size;i++)
	{
		matrix2.push_back(row_zeroes);
		for(int j = 0; j < size;j++)
		{
			matrix2[i][j] = rand()%limit;
		}
	}

	cout << endl << "MATRIX2; " << endl;
	print_matrix(matrix2,digits);

	vector<vector<int>> matrix3;
	matrix3.reserve(size);
	for(int i = 0; i < size;i++)
	{
		matrix3.push_back(row_zeroes);
		threads[i] = thread(multrow, ref(matrix3),matrix1,matrix2,i);
	}

	for (int i = 0; i < size; ++i) {
        threads[i].join();
    }
	

	cout << endl << "MATRIX1 x MATRIX2" << endl;
	print_matrix(matrix3,digits);


	
	return EXIT_SUCCESS;
}




int mult(vector<vector<int>> matrix1, vector<vector<int>> matrix2, int i, int j)
{
	int val = 0;
	for(int k = 0; k < size; k++)
	{
		val += matrix1[i][k] * matrix2[k][j];
	}
	return val;
}



void multrow(vector<vector<int>> &matrix3,vector<vector<int>> matrix1,vector<vector<int>> matrix2,int row)
{
	for(int j = 0; j < size;j++)
	{
		matrix3[row][j] = mult(matrix1,matrix2,row,j);	
	}
}

void print_matrix(vector<vector<int>> matrix, int digits)
{
	for(int i = 0; i < size;i++)
	{
		for(int j = 0; j < size;j++)
		{
			cout << setw(digits+2) << matrix[i][j] << " " ;
		}
		cout << endl;
	}
}

// Multiplicación de matrices en paralelo



