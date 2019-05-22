/*
Matamoros, Corbin
3013 Data Structures and Algorithms, Prof. Simpson
Project 1 - Vector Practice
1/23/2019
This program will input a set of problems solved by each of three students and 
output which student solved the most problems the others haven't and what those
problems were. Problems solved by all three students are tracked in an array,
where indexes are associated with the problem number. 
The time complexity of this algorithm is O(n) without the sort algorithm, O(n*logn) 
with it.
*/

#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

void resetTracker(int tracker[]);
void fillStudentVectors(vector<int> &student, int tracker[]);
void checkForDuplicates(vector<int> &student, int tracker[]);
void printWinner(vector<int> &student, int caseNumber, int winner);
void printWinners(vector<int> &student1st, vector<int> &student2nd, int caseNumber, int _1stPlace1, int _1stPlace2);
void threeWayTie(vector<int> &student1st, vector<int> &student2nd, vector<int> student3rd, int caseNumber);

int main()
{
	int problemSets, problemsSolved;
	vector<int> student1, student2, student3;

	/*to track solved problems, the problem # associated with an element 
	/(problem 39 is associated with index 39) will be incremented*/
	int tracker[10001];

	//-------------------------------------------------------------------------
	//								INPUT
	//-------------------------------------------------------------------------
	
	/*NOTE: each vector will be declared with one extra index that 
	will hold the sum of problems solved uniquely by the student*/
	cin >> problemSets;

	for (int j = 0; j < problemSets; j++)
	{
		resetTracker(tracker);
		
		cin >> problemsSolved;//first input per line is # of problems stud solved
		student1.resize(problemsSolved + 1);
		student1[0] = problemsSolved;//store solved probs in 0
		fillStudentVectors(student1, tracker);//call function to fill vector

		cin >> problemsSolved;
		student2.resize(problemsSolved + 1);
		student2[0] = problemsSolved;
		fillStudentVectors(student2, tracker);

		cin >> problemsSolved;
		student3.resize(problemsSolved + 1);
		student3[0] = problemsSolved;
		fillStudentVectors(student3, tracker);

		//will run to eliminate problems solved by more than one student
		checkForDuplicates(student1, tracker);
		checkForDuplicates(student2, tracker);
		checkForDuplicates(student3, tracker);


		//---------------------------------------------------------------------
		//									OUTPUT
		//---------------------------------------------------------------------

		//if student 1 had most unique problems
		if (student1.front() > student2.front() && student1.front() > student3.front())
			printWinner(student1, j + 1, 1);
		
		//if student 2 had most unique problems
		else if (student2.front() > student3.front())
			printWinner(student2, j+1, 2);
				
		//if student 3 had most unique problems
		else if (student3.front() > student1.front())
			printWinner(student3, j+1, 3);
		
		//if all three students tie
		else if (student1.front() == student2.front() && student2.front() == student3.front())
			threeWayTie(student1, student2, student3, j + 1);
		
		//if student1 and student 2 tie
		else if (student1.front() == student2.front())
			printWinners(student1, student2, j + 1, 1, 2);

		//if student 2 and student 3 tie
		else if (student2.front() == student3.front())
			printWinners(student2, student3, j + 1, 2, 3);

		//if student 1 and student 3 tie
		else if (student1.front() == student3.front())
			printWinners(student1, student3, j + 1, 1, 3);
	}
	return 0;
}

/*
	Name:		resetTracker
	Parameters: tracker (array)
	Output:		none
	Purpose:	set all elements in tracker array to zero
*/
void resetTracker(int tracker[])
{
	for (int i = 0; i < 1001; i++)
	{
		tracker[i] = 0;
	}
}

/*
	Name:		fillStudentVectors
	Parameters: student (vector) and tracker (array)
	Output:		none
	Purpose:	read in values from an input file and place them into a vector
				as well as update the tracker array
	Notes:		both student and tracker arrays are passed by reference
*/
void fillStudentVectors(vector<int> &student, int tracker[])
{
	for (int i = 1; i < student.size(); i++)
	{
		cin >> student[i];
		tracker[student[i]]++;//increment associated index in tracker
	}
}

/*
	Name:		checkForDuplicates
	Parameters: student (vector) and tracker (array)
	Output:		none
	Purpose:	check the student vector against the tracker array. If an
				element in tracker array is greater than 1, the associated
				problem has been solved by more than one student. That problem
				number is wiped in the student vector and student[0] is updated
	Notes:		both student and tracker arrays are passed by reference. 
				Flagging an element instead of erasing avoids increasing time
				complexity.
*/
void checkForDuplicates(vector<int> &student, int tracker[])
{
	for (int i = 1; i < student.size(); i++)
	{
		if (tracker[student[i]] > 1)//check if problem has been solved
		{
			student[i] = -1;//flags for output of vector later on
			student[0] -= 1;//decreases # of student's unique problems by 1
		}
	}
}

/*
	Name:		printWinner
	Parameters: student (vector), caseNumber, and winner
	Output:		none
	Purpose:	print, per case, the student who solved the most unique problems, 
				the number of unique problems, and the problems they solved
	Notes:		student array is passed by reference.
*/
void printWinner(vector<int> &student, int caseNumber, int winner)
{
	sort(student.begin() + 1, student.end());

	cout << "Case #" << caseNumber << ":\n" << winner << " " << student[0] << " ";
	for (int i = 1; i < student.size(); i++)
	{
		if (student[i] != -1)//check for flag. If found, don't print
			cout << student[i] << " ";
	}
	cout << '\n';
}

/*
	Name:		printWinners
	Parameters: student1st (vector), student2nd (vector), caseNumber, and _1stPlace
	Output:		none
	Purpose:	print the two students who tied solving the most unique problems,
				the number of unique problems, and the problems they solved
	Notes:		student arrays are passed by reference.
*/
void printWinners(vector<int> &student1st, vector<int> &student2nd, int caseNumber, int _1stPlace1, int _1stPlace2)
{
	sort(student1st.begin() + 1, student1st.end());
	sort(student2nd.begin() + 1, student2nd.end());

	cout << "Case #" << caseNumber << ":\n" << _1stPlace1 << " " << student1st[0] << " ";
	for (int i = 1; i < student1st.size(); i++)
	{
		if (student1st[i] != -1)//check for flag. If found, don't print
			cout << student1st[i] << " ";
	}
	cout << '\n' << _1stPlace2 << " " << student2nd[0] << " ";
	for (int i = 1; i < student2nd.size(); i++)
	{
		if (student2nd[i] != -1)//check for flag. If found, don't print
			cout << student2nd[i] << " ";
	}
	cout << '\n';
}

/*
	Name:		threeWayTie
	Parameters: student1st (vector), student2nd (vector), and caseNumber
	Output:		none
	Purpose:	print all three students who tied solving the most unique problems,
				the number of unique problems, and the problems they solved
	Notes:		student arrays are passed by reference.
*/
void threeWayTie(vector<int> &student1st, vector<int> &student2nd, vector<int> student3rd, int caseNumber)
{
	sort(student1st.begin() + 1, student1st.end());
	sort(student2nd.begin() + 1, student2nd.end());
	sort(student3rd.begin() + 1, student3rd.end());

	cout << "Case #" << caseNumber << ":\n" << "1 " << student1st[0] << " ";
	for (int i = 1; i < student1st.size(); i++)
	{
		if (student1st[i] != -1)//check for flag. If found, don't print
			cout << student1st[i] << " ";
	}
	cout << '\n' << "2 " << student2nd[0] << " ";
	for (int i = 1; i < student2nd.size(); i++)
	{
		if (student2nd[i] != -1)//check for flag. If found, don't print
			cout << student2nd[i] << " ";
	}
	cout << '\n' << "3 " << student3rd[0] << " ";
	for (int i = 1; i < student3rd.size(); i++)
	{
		if (student3rd[i] != -1)//check for flag. If found, don't print
			cout << student3rd[i] << " ";
	}
	cout << '\n';
}