#include "graphMaker.h"


//will create the graph specified in input file
graphMaker::graphMaker()
{
	cin >> dummy;//read in graph direction indicator (if directed or undirected graph)
	switch (dummy)
	{
	case 'Y':case 'y': isDirected = true; cout << "Graph is directed\n"; break;
	case 'N':case 'n': isDirected = false; cout << "Graph is undirected\n"; break;
	default:
		throw invalid_argument("invalid argument in input file. Use 'Y', 'N', or their lowercase equivalents");
		break;
	}
	cin >> dummy;//read in weighted indicator (if graph is weighted or not)
	switch (dummy)
	{
	case 'Y':case 'y': isWeighted = true; cout << "Graph is weighted\n"; break;
	case 'N':case 'n': isWeighted = false; cout << "Graph is unweighted\n"; break;
	default:
		throw invalid_argument("invalid argument in input file. UUse 'Y', 'N', or their lowercase equivalents");
		break;
	}
	cin >> dummy;//read in variable asking if weights are included in input
	switch (dummy)
	{
	case 'Y':case 'y': hasWeights = true; cout << "Input file has weights\n"; break;
	case 'N':case 'n': hasWeights = false; cout << "Input file has no weights\n"; break;
	default:
		throw invalid_argument("invalid argument in input file. UUse 'Y', 'N', or their lowercase equivalents");
		break;
	}

	//resize the graph 2D vector
	cin >> numNodes;
	G.resize(numNodes);
	insertionCrossroad();
	if (isDense)
		cout << "Graph has been constructed and is dense\n";
	else
		cout << "Graph has been constructed and is sparse\n";
	cout << "There are " << numNodes << " nodes and " << numEdges << " edges.\n";
}

void graphMaker::findMSTs()
{
	while (!nodes.empty())
	{
		PrimsAlgorithm();
	}
}

void graphMaker::printMSTs()
{
	for (auto i : MSTs)
	{
		for (auto j : i)
		{
			cout << j.first << ' ';
		}
		cout << '\n';
	}
}

//-----------------------------------------------------------------------------
//							PRIVATE FUNCTIONS
//-----------------------------------------------------------------------------

//Function will determine which edge-insertion function should run based on the
//parameters read in at the beginning of the input file. 
//If the graph is weighted and has weights noted in the input file,
//'insertEdgeWeighted' runs. If the graph is weighted but doesn't have weights
//in the input file, 'insertEdgeUnweighted' runs. Otherwise, 
//'insertEdgeDefault' runs.
void graphMaker::insertionCrossroad()
{
	if (isWeighted && hasWeights)
		insertEdgeWeighted();
	else if (isWeighted && !hasWeights)
		insertEdgeUnweighted();
	else
		insertEdgeDefault();
}

//function will
//input into the 2D vector 'graph' all the edges. E.G.
//if there is an edge between node 4 and 7, a pair of number 7
//and INT_MAX will be pushed to the 4th row of 'graph'
void graphMaker::insertEdgeDefault()
{
	//the condition for the while loop keeps 'from' and 'to' from being equal
	//This class won't support loops in graphs.
	while (cin >> from >> to)
	{
		if (from != to)
		{
			//runs if 'from' nor 'to' are in the nodeConverter map
			if (nodeConverter.find(from) == nodeConverter.end() && nodeConverter.find(to) == nodeConverter.end())
			{
				nodeConverter[from] = mapCounter;
				nodes.insert(mapCounter);
				mapCounter++;
				nodeConverter[to] = mapCounter;
				nodes.insert(mapCounter);
				mapCounter++;
			}
			//runs if 'from' isn't in the map but 'to' is
			else if (nodeConverter.find(from) == nodeConverter.end() && nodeConverter.find(to) != nodeConverter.end())
			{
				nodeConverter[from] = mapCounter;
				nodes.insert(mapCounter);
				mapCounter++;
			}
			//runs if 'to' isn't in the map but 'from' is
			else if (nodeConverter.find(from) != nodeConverter.end() && nodeConverter.find(to) == nodeConverter.end())
			{
				nodeConverter[to] = mapCounter;
				nodes.insert(mapCounter);
				mapCounter++;
			}
			G[nodeConverter[from]].push(make_pair(nodeConverter[to], INT_MAX));
			numEdges++;//counts number of edges in graph
			
		}
	}
}

//function that will insert all the edges of a graph and the weights
//associated with them. The weights have to be included in the input file for
//this method to run. Otherwise, your graph will be all screwed up.
void graphMaker::insertEdgeWeighted()
{
	int weight;
	while (cin >> from >> to >> weight)
	{
		if (from != to)
		{
			//runs if 'from' nor 'to' are in the nodes map
			if (nodeConverter.find(from) == nodeConverter.end() && nodeConverter.find(to) == nodeConverter.end())
			{
				nodeConverter[from] = mapCounter;
				nodes.insert(mapCounter);
				mapCounter++;
				nodeConverter[to] = mapCounter;
				nodes.insert(mapCounter);
				mapCounter++;
			}
			//runs if 'from' isn't in the map but 'to' is
			else if (nodeConverter.find(from) == nodeConverter.end() && nodeConverter.find(to) != nodeConverter.end())
			{
				nodeConverter[from] = mapCounter;
				nodes.insert(mapCounter);
				mapCounter++;
			}
			//runs if 'to' isn't in the map but 'from' is
			else if (nodeConverter.find(from) != nodeConverter.end() && nodeConverter.find(to) == nodeConverter.end())
			{
				nodeConverter[to] = mapCounter;
				nodes.insert(mapCounter);
				mapCounter++;
			}
			G[nodeConverter[from]].push(make_pair(nodeConverter[to], weight));
			numEdges++;//counts number of edges in graph
		}
	}
}

//Function that is customized to read in 'from' and 'to' values from an input
//file just like the 'insertEdgeDefault' function. However, weights are
//selected based on a pre-determined equation.
void graphMaker::insertEdgeUnweighted()
{
	int weight;
	while (cin >> from >> to)
	{
		if (from != to)
		{
			//determine the weight of the edge
			weight = abs(from - to) % 10;

			//runs if 'from' nor 'to' are in the nodeConverter map
			if (nodeConverter.find(from) == nodeConverter.end() && nodeConverter.find(to) == nodeConverter.end())
			{
				nodeConverter[from] = mapCounter;
				nodes.insert(mapCounter);
				mapCounter++;
				nodeConverter[to] = mapCounter;
				nodes.insert(mapCounter);
				mapCounter++;
			}
			//runs if 'from' isn't in the map but 'to' is
			else if (nodeConverter.find(from) == nodeConverter.end() && nodeConverter.find(to) != nodeConverter.end())
			{
				nodeConverter[from] = mapCounter;
				nodes.insert(mapCounter);
				mapCounter++;
			}
			//runs if 'to' isn't in the map but 'from' is
			else if (nodeConverter.find(from) != nodeConverter.end() && nodeConverter.find(to) == nodeConverter.end())
			{
				nodeConverter[to] = mapCounter;
				nodes.insert(mapCounter);
				mapCounter++;
			}
			G[nodeConverter[from]].push(make_pair(nodeConverter[to], weight));
			numEdges++;//counts number of edges in graph
		}
	}
}

void graphMaker::graphProperties()
{
	if (numEdges > numNodes*2)
		isDense = true;
	else
		isDense = false;
}

void graphMaker::PrimsAlgorithm()
{
	int root = rand() % nodes.size(), weight = 0, prev;

	if (nodes.find(root) == nodes.end())
		root = *nodes.end();
	cout << root << '\n';
	pair<int, int> current;
	nodes.erase(root);//delete root node value from set
	tree.push_back(make_pair(root, weight));//push root and weight (0) to tree

	current = G[root].top();//current is now the least-weighted node adjacent to the root
	prev = root;

	//goes to current node's row in 'G' and grabs the first element.
	//if that node is still in the set 'nodes' and the path from the current
	//node to it is the shortest path available, remove from set and add to
	//tree
	while (nodes.find(current.first) != nodes.end() && current.second <= G[current.first].top().second)
	{
		cout << "Found the shortest weighted edge between " << current.first << " and " << prev << '\n';
		prev = current.first;
		nodes.erase(prev);
		tree.push_back(current);
		current = G[current.first].top();
	}
	if (tree.size() <= 1)
	{
		nodes.insert(prev);
		tree.clear();
		cout << "Tree was 1 in size. Quitting in hopes of finding a better tree.\n";
	}
	else
	{
		cout << "Completed a sub tree!\n";
		MSTs.insert(tree);
		tree.clear();
	}
}

graphMaker::~graphMaker()
{
}

//So I keep getting dereferencing error in Prim's algorithm. Try a robust method of
//choosing a node to start at when creating a tree. 