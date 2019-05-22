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

void fillLgMatrix(vector<vector<char>> &lgMatrix, int lgMatrixSize);
void fillSmallMatrix(vector<vector<char>> &smMatrix0, vector<vector<char>> &smMatrix90, vector<vector<char>> &smMatrix180, vector<vector<char>> &smMatrix270, int smMatrixSize);
int compareSm2Lg(vector<vector<char>> &lgMatrix, vector<vector<char>> &smMatrix);

int main()
{
	//the variables ending with 'Res' contain the number of instances the small matrix
	//was discovered in the large matrix per orientation
	int largeMatrixSize, smallMatrixSize, zeroRes, ninetyRes, oneeightyRes, twoseventyRes;

	cin >> largeMatrixSize >> smallMatrixSize;

	vector<vector<char>> largeMatrix, smallMatrix0, smallMatrix90, smallMatrix180, smallMatrix270;

	while (largeMatrixSize != 0 && smallMatrixSize != 0)
	{
		//resize 2D matrices to fit incoming data from input file
		largeMatrix.resize(largeMatrixSize, vector<char>(largeMatrixSize));
		smallMatrix0.resize(smallMatrixSize, vector<char>(smallMatrixSize));
		smallMatrix90.resize(smallMatrixSize, vector<char>(smallMatrixSize));
		smallMatrix180.resize(smallMatrixSize, vector<char>(smallMatrixSize));
		smallMatrix270.resize(smallMatrixSize, vector<char>(smallMatrixSize));

		//fill the large matrix and all four small matrices
		fillLgMatrix(largeMatrix, largeMatrixSize);
		fillSmallMatrix(smallMatrix0, smallMatrix90, smallMatrix180, smallMatrix270, smallMatrixSize);

		//compare all small matrices for appearances in the large matrix
		zeroRes = compareSm2Lg(largeMatrix, smallMatrix0);
		ninetyRes = compareSm2Lg(largeMatrix, smallMatrix90);
		oneeightyRes = compareSm2Lg(largeMatrix, smallMatrix180);
		twoseventyRes = compareSm2Lg(largeMatrix, smallMatrix270);

		//output instances of small matrices in large matrix
		cout << zeroRes << ' ' << ninetyRes << ' ' << oneeightyRes << ' ' << twoseventyRes << '\n';

		cin >> largeMatrixSize >> smallMatrixSize;

		//matrices must be cleared, otherwise resizing doesn't affect the entire
		//matrix
		largeMatrix.clear();
		smallMatrix0.clear();
		smallMatrix90.clear();
		smallMatrix180.clear();
		smallMatrix270.clear();
	}
	return 0;
}

/*
	Name:		fillLargeMatrix
	Parameters: lgMatrix and lgMatrixSize
	Output:		none
	Purpose:	fill the 2D vector lgMatrix with values from the input file
	Notes:		the 2D vector is passed to the function by reference
*/
void fillLgMatrix(vector<vector<char>> &lgMatrix, int lgMatrixSize)
{
	for (int i = 0; i < lgMatrixSize; i++)
	{
		for (int j = 0; j < lgMatrixSize; j++)
		{
			cin >> lgMatrix[i][j];
		}
	}
}
/*
	Name:		fillSmallMatrix
	Parameters: smMatrix0, smMatrix90, smMatrix180, smMatrix270, and smMatrixSize
	Output:		none
	Purpose:	fill the 2D vectors that represent smMatrix with values from the input file
	Notes:		all 2D vectors are passed by reference
*/
void fillSmallMatrix(vector<vector<char>> &smMatrix0, vector<vector<char>> &smMatrix90, vector<vector<char>> &smMatrix180, vector<vector<char>> &smMatrix270, int smMatrixSize)
{
	int k = 0, l = smMatrixSize - 1, m = smMatrixSize - 1, n = smMatrixSize - 1, p = smMatrixSize - 1, q = 0;
	for (int i = 0; i < smMatrixSize; i++)
	{
		for (int j = 0; j < smMatrixSize; j++)
		{
			//fills small matrix at 0-degree orientation
			cin >> smMatrix0[i][j];

			//filling the 90-orientation matrix
			smMatrix90[k][l] = smMatrix0[i][j];
			k++;

			//filling the 180-orientation matrix
			smMatrix180[m][n] = smMatrix0[i][j];
			n--;

			//filling the 270-orientation matrix
			smMatrix270[p][q] = smMatrix0[i][j];
			p--;
		}
		k = 0;
		l--;
		m--;
		n = smMatrixSize - 1;
		p = smMatrixSize - 1;
		q++;
	}
}

/*
	Name:		compareSm2Lg
	Parameters:	lgMatrix and smMatrix
	Output:		foundOne
	Purpose:	Search the lgMatrix for any instances of smMatrix
	Notes:		Enter this link (https://youtu.be/eePTdvDptYQ) into your 
				browser's search bar for a full explaination of function. 
				But, in short, this function search the large matrix for any	
				occurances of the small matrix.
*/
int compareSm2Lg(vector<vector<char>> &lgMatrix, vector<vector<char>> &smMatrix)
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
				//if unmatching elements found, quit searching row
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