/*
Matamoros, Corbin
CMPS 3013 - Prof Simpson
Project 2 - STL Vector Problem
1/29/2019
This program will read from a file through std::cin an N x N and n x n matrix,
where 0 < n =< N. It will output by std::cout how many times the smaller matrix
is found in the larger matrix per orientation (smaller matrix will be rotated
by 90, 180, and 270 degrees and compared to the larger matrix for containment). 
Time complexity is, worst case, O(n^2) if all elements in an n x n matrix are
compared. Execution time, according to the UVA website, is 0.020. 
*/

#include<iostream>
#include<vector>

using namespace std;

void fillMatrices(vector<vector<char>> &lgMatrix, vector<vector<char>> &smMatrix, int lgMatrixSize, int smMatrixSize);
int compareAt0(vector<vector<char>> &lgMatrix, vector<vector<char>> &smMatrix);
int compareAt90(vector<vector<char>> &lgMatrix, vector<vector<char>> &smMatrix);
int compareAt180(vector<vector<char>> &lgMatrix, vector<vector<char>> &smMatrix);
int compareAt270(vector<vector<char>> &lgMatrix, vector<vector<char>> &smMatrix);

int main()
{
	//the variables ending with 'Res' contain the number of instances the small matrix
	//was discovered in the large matrix per orientation
	int largeMatrixSize, smallMatrixSize, zeroRes, ninetyRes, oneeightyRes, twoseventyRes;

	cin >> largeMatrixSize >> smallMatrixSize;

	vector<vector<char>> largeMatrix, smallMatrix;

	while (largeMatrixSize != 0 && smallMatrixSize != 0)
	{
		//resize 2D matrices to fit incoming data from input file
		largeMatrix.resize(largeMatrixSize, vector<char>(largeMatrixSize));
		smallMatrix.resize(smallMatrixSize, vector<char>(smallMatrixSize));

		//fill small and large matrices from the input file. Small matrix is filled
		//at 0-degree orientation
		fillMatrices(largeMatrix, smallMatrix, largeMatrixSize, smallMatrixSize);

		//compare small matrix in all four orientations for instances in large matrix
		zeroRes = compareAt0(largeMatrix, smallMatrix);
		ninetyRes = compareAt90(largeMatrix, smallMatrix);
		oneeightyRes = compareAt180(largeMatrix, smallMatrix);
		twoseventyRes = compareAt270(largeMatrix, smallMatrix);

		//output results for all four of the small matrices' orientations
		cout  << zeroRes << ' ' << ninetyRes << ' ' << oneeightyRes << ' ' << twoseventyRes << '\n';

		cin >> largeMatrixSize >> smallMatrixSize;
		//matrices must be cleared, otherwise resizing doesn't affect the entire
		//matrix
		largeMatrix.clear();
		smallMatrix.clear();
	}
	return 0;
}

/*
	Name:		fillMatrices
	Parameters: lgMatrix, smMatrix, lgMatrixSize, and smMatrixSize
	Output:		none
	Purpose:	fill the 2D vectors lgMatrix and smMatrix with values from the intput file
	Notes:		both 2D vectors are passed by reference
*/
void fillMatrices(vector<vector<char>> &lgMatrix, vector<vector<char>> &smMatrix, int lgMatrixSize, int smMatrixSize)
{
	for (int i = 0; i < lgMatrixSize; i++)
	{
		for (int j = 0; j < lgMatrixSize; j++)
		{
			cin >> lgMatrix[i][j];
		}
	}

	for (int i = 0; i < smMatrixSize; i++)
	{
		for (int j = 0; j < smMatrixSize; j++)
		{
			cin >> smMatrix[i][j];
		}
	}
}

/*
	Name:		compareAt0
	Parameters:	lgMatrix and smMatrix
	Output:		foundOne
	Purpose:	Search the lgMatrix for any instances of smMatrix
	Notes:		Enter this link (https://youtu.be/eePTdvDptYQ) into your browser's search bar for a full explaination
				of function. But, in short, this function search the large matrix for any	
				occurances of the small matrix.
*/
int compareAt0(vector<vector<char>> &lgMatrix, vector<vector<char>> &smMatrix)
{
	int j = 0, k, m = 0, n = 0, matChecker = 0, counter = 0, duplicateChecker = 0, foundOne = 0;
	
	//l "lowers" the small matrix down the lgMatrix
	for (int l = 0; l <= lgMatrix.size() - smMatrix.size(); l++)
	{
		//i slides the small matrix across the lgMatrix
		for (int i = 0; i <= lgMatrix.size() - smMatrix.size(); i++)
		{
			k = l;
			j = i;
			m = 0;
			n = 0;
			counter = 0;
			//will run through all rows with 'k'
			while (counter < smMatrix.size())
			{
				//will run through all columns with 'j'
				while (n < smMatrix.size() && lgMatrix[k][j] == smMatrix[m][n])
				{
					j++;
					n++;
					matChecker++;
					duplicateChecker++;
				}
				//if two elements do not match, quit searching row
				if (matChecker != smMatrix.size())
				{
					matChecker = 0;
					duplicateChecker = 0;
					counter = smMatrix.size();
				}
				//if all elements match, quit searching row and document discovery in 'foundOne'
				else if (duplicateChecker == (smMatrix.size() * smMatrix.size()))
				{
					foundOne++;
					matChecker = 0;
					duplicateChecker = 0;
					counter = smMatrix.size();
				}
				//otherwise, all elements in current row have matched, so move to the next row
				else
				{
					k++;
					m++;
					j = i;
					n = 0;
					matChecker = 0;
					counter++;
				}
			}
		}
	}
	return foundOne;
}

/*
Name:		compareAt90
Parameters:	lgMatrix and smMatrix
Output:		foundOne
Purpose:	Search the lgMatrix for any instances of smMatrix
Notes:		Enter this link (https://youtu.be/oZzJEvOqvSQ) into your browser's search bar for a full explaination
			of function. But, in short, this function search the large matrix for any	
			occurances of the small matrix.
*/
int compareAt90(vector<vector<char>> &lgMatrix, vector<vector<char>> &smMatrix)
{
	int j = 0, k, m = 0, n = 0, matChecker = 0, counter = 0, duplicateChecker = 0, foundOne = 0;

	//l "lowers" the small matrix down the lgMatrix
	for (int l = 0; l <= lgMatrix.size() - smMatrix.size(); l++)
	{
		//i slides the small matrix across the lgMatrix
		for (int i = 0; i <= lgMatrix.size() - smMatrix.size(); i++)
		{
			k = l;
			j = i;
			m = smMatrix.size() - 1;
			n = 0;
			counter = 0;
			//will run through all rows with 'k'
			while (counter < smMatrix.size())
			{
				//will run through all columns with 'j'
				while (m > -1 && lgMatrix[k][j] == smMatrix[m][n])
				{
					j++;
					m--;
					matChecker++;
					duplicateChecker++;
				}
				//if two elements do not match, quit searching row
				if (matChecker != smMatrix.size())
				{
					matChecker = 0;
					duplicateChecker = 0;
					counter = smMatrix.size();
				}
				//if all elements match, quit searching row and document discovery in 'foundOne'
				else if (duplicateChecker == (smMatrix.size() * smMatrix.size()))
				{
					foundOne++;
					matChecker = 0;
					duplicateChecker = 0;
					counter = smMatrix.size();
				}
				//otherwise, all elements in current row have matched, so move to the next row
				else
				{
					k++;
					n++;
					j = i;
					m = smMatrix.size() - 1;
					matChecker = 0;
					counter++;
				}
			}
		}
	}
	return foundOne;
}

/*
Name:		compareAt180
Parameters:	lgMatrix and smMatrix
Output:		foundOne
Purpose:	Search the lgMatrix for any instances of smMatrix
Notes:		Enter this link (https://youtu.be/oZzJEvOqvSQ) into your browser's search bar for a full explaination
			of function. But, in short, this function search the large matrix for any	
			occurances of the small matrix.
*/
int compareAt180(vector<vector<char>> &lgMatrix, vector<vector<char>> &smMatrix)
{
	int j = 0, k, m = 0, n = 0, matChecker = 0, counter = 0, duplicateChecker = 0, foundOne = 0;

	//l "lowers" the small matrix down the lgMatrix
	for (int l = 0; l <= lgMatrix.size() - smMatrix.size(); l++)
	{
		//i slides the small matrix across the lgMatrix
		for (int i = 0; i <= lgMatrix.size() - smMatrix.size(); i++)
		{
			k = l;
			j = i;
			m = smMatrix.size() - 1;
			n = smMatrix.size() - 1;
			counter = 0;
			//will run through all rows with 'k'
			while (counter < smMatrix.size())
			{
				//will run through all columns with 'j'
				while (n > -1 && lgMatrix[k][j] == smMatrix[m][n])
				{
					j++;
					n--;
					matChecker++;
					duplicateChecker++;
				}
				//if two elements do not match, quit searching row
				if (matChecker != smMatrix.size())
				{
					matChecker = 0;
					duplicateChecker = 0;
					counter = smMatrix.size();
				}
				//if all elements match, quit searching row and document discovery in 'foundOne'
				else if (duplicateChecker == (smMatrix.size() * smMatrix.size()))
				{
					foundOne++;
					matChecker = 0;
					duplicateChecker = 0;
					counter = smMatrix.size();
				}
				//otherwise, all elements in current row have matched, so move to the next row
				else
				{
					k++;
					m--;
					j = i;
					n = smMatrix.size() - 1;
					matChecker = 0;
					counter++;
				}
			}
		}
	}
	return foundOne;
}

/*
Name:		compareAt270
Parameters:	lgMatrix and smMatrix
Output:		foundOne
Purpose:	Search the lgMatrix for any instances of smMatrix
Notes:		Enter this link (https://youtu.be/oZzJEvOqvSQ) into your browser's search bar for a full explaination
			of function. But, in short, this function search the large matrix for any	
			occurances of the small matrix.
*/
int compareAt270(vector<vector<char>> &lgMatrix, vector<vector<char>> &smMatrix)
{
	int j = 0, k, m = 0, n = 0, matChecker = 0, counter = 0, duplicateChecker = 0, foundOne = 0;

	//l "lowers" the small matrix down the lgMatrix
	for (int l = 0; l <= lgMatrix.size() - smMatrix.size(); l++)
	{
		//i slides the small matrix across the lgMatrix
		for (int i = 0; i <= lgMatrix.size() - smMatrix.size(); i++)
		{
			k = l;
			j = i;
			m = 0;
			n = smMatrix.size() - 1;
			counter = 0;
			//will run through all rows with 'k'
			while (counter < smMatrix.size())
			{
				//will run through all columns with 'j'
				while (m < smMatrix.size() && lgMatrix[k][j] == smMatrix[m][n])
				{
					j++;
					m++;
					matChecker++;
					duplicateChecker++;
				}
				//if two elements do not match, quit searching row
				if (matChecker != smMatrix.size())
				{
					matChecker = 0;
					duplicateChecker = 0;
					counter = smMatrix.size();
				}
				//if all elements match, quit searching row and document discovery in 'foundOne'
				else if (duplicateChecker == (smMatrix.size() * smMatrix.size()))
				{
					foundOne++;
					matChecker = 0;
					duplicateChecker = 0;
					counter = smMatrix.size();
				}
				//otherwise, all elements in current row have matched, so move to the next row
				else
				{
					k++;
					n--;
					j = i;
					m = 0;
					matChecker = 0;
					counter++;
				}
			}
		}
	}
	return foundOne;
}