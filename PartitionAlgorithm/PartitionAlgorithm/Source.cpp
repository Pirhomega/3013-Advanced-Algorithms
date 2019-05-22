//Corbin Matamoros's Partition Program that he totally did not copy from
//the material provided in class...

#include<iostream>
#include<vector>

using namespace std;

void partition(vector<int> &vec1);

int main()
{
	vector<int> vec1;

	vec1.resize(25);
	srand(123123);

	//fills the vector with random numbers between 0 and 50
	for (int i = 0; i < vec1.size(); i++)
	{
		vec1[i] = rand() % 50;
		cout << vec1[i] << " ";
	}
	cout << '\n';
	partition(vec1);//partition function call

	//outputs contents of vector after partition call
	for (int i = 0; i < vec1.size(); i++)
	{
		cout << vec1[i] << " ";
	}

	return 0;
}

void partition(vector<int> &vec1)
{
	int x = vec1.back(), i = -1, temp;

	for (int j = 0; j < vec1.size(); j++)
	{
		//if currect element is larger than pivot, swap with j-th element
		if (vec1[j] <= x)
		{
			i++;
			temp = vec1[i];
			vec1[i] = vec1[j];
			vec1[j] = temp;
		}
	}
	//these three put the pivot in between the two partitions created above
	temp = vec1[i + 1];
	vec1[i + 1] = vec1.back();
	vec1.back() = temp;
}