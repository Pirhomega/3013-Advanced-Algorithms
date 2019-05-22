/*
Matamoros, Corbin
3013 Advanced Structures & Algorithms
Mr. Simpson
4/11/2019
This program will allow users to create and modify any type 
of graph (directed, undirected, psuedo, mixed, etc).
*/

#include<iostream>
#include<vector>
#include<queue>
#include "graphMaker.h"

using namespace std;

int main()
{
	try 
	{
		graphMaker graph1;
		graph1.findMSTs();
		graph1.printMSTs();
	}
	catch (const invalid_argument& e) {cerr << e.what() << '\n';}


	return 0;
}