#pragma once
#include<iostream>
#include<vector>
#include<map>
#include<set>
#include<queue>
#include<stdexcept>

using namespace std;

//C++11 equivalents of #typedef
using graph = vector< 
						priority_queue< 
							pair<int, int>, 
							vector<pair<int, int>>, 
							greater<pair<int, int>>> 
					>;
using MST = vector<pair<int, int>>;
using forest = set < vector<pair<int, int>>>;

class graphMaker
{
	bool isDirected, isWeighted, isDense, hasWeights;
	char dummy;
	int from, to, numNodes, numEdges = 0, mapCounter = 0;
	forest MSTs;
	set <int> nodes;
	map<int, int> nodeConverter;//maps data set values to custom identifiers
	graph G;//holds nodes and edges of graph
	MST tree;//holds the MST of the graph
public:
	graphMaker();
	~graphMaker();
	void findMSTs();
	void printMSTs();
private:
	void insertionCrossroad();
	void insertEdgeDefault();
	void insertEdgeWeighted();
	void insertEdgeUnweighted();
	void graphProperties();
//----------------------------------------------
	void PrimsAlgorithm();
};

