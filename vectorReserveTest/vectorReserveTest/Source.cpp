#include<iostream>
#include<vector>

using namespace std;

int main()
{
	vector<int> foo{ 1,2,3,4,5 };
	foo.reserve(4);

	foo.pop_back();
	foo.pop_back();
	foo[4] = 4;

	cout << foo[0] << ' ' << foo[1] << ' ' << foo[2] << ' ' << foo[3] << ' ' << foo[4];
	return 0;
}