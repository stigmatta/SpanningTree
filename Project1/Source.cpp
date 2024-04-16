#include <iostream>
#include <vector>
#include <map>

#define MAX 9999

using namespace std;

class Node
{
private:
	unsigned int number;
	vector <pair<Node*, unsigned int>> connections;
public:
	Node(unsigned int number) :number(number) {};

	unsigned int GetNumber()const
	{
		return number;
	}

	void AddConnection(Node* node, unsigned int length)
	{
		pair<Node*, unsigned int> connection,connection2;
		connection.first = node;
		connection.second = length;
		connections.push_back(connection);

		connection2.first = this;
		connection2.second = length;
		node->connections.push_back(connection2);
	}

	Node* GetConnectedNode(int index)
	{
		return connections[index].first;
	}

	unsigned int GetConnectionsSize()
	{
		return connections.size();
	}

	unsigned int GetConnectionLength(int index)
	{
		return connections[index].second;
	}

	void ShowConnections()
	{
		if (connections.empty())
			return;
		cout << "Node #" << number << " connections:\n";
		for (const auto& connection : connections)
		{
			cout << "Connected to Node #" << connection.first->GetNumber() << " with length " << connection.second << endl;
		}
	}

};

class Graph
{
private:
	vector <Node*> nodes;
	unsigned int size=0;
public:
	void AddNode(Node* node)
	{
		nodes.push_back(node);
		size++;
	}

	unsigned int GetSize()const
	{
		return size;
	}

	Node* GetNode(int index)
	{
		return nodes[index];
	}

	void ShowAllConnections()
	{
		for(int i = 0;i<nodes.size();i++)
		{
			nodes[i]->ShowConnections();
		}
	}
};

class MinimalSpanningTree
{
private:
	Graph* graph;
	vector <Node*> d;
	vector <Node*> c;
public:
	MinimalSpanningTree(Graph* graph)
	{
		this->graph = graph;
		for (int i = 0; i < graph->GetSize(); i++)
		{
			d.push_back(graph->GetNode(i));
		}
	}
	
	void PrintD()
	{
		cout << "D:\n";
		for (int i = 0; i < d.size(); i++)
			cout << d[i]->GetNumber() << ' ';
		cout << endl;
	}

	void PrintC()
	{
		cout << "C:\n";
		for (int i = 0; i < c.size(); i++)
			cout << c[i]->GetNumber() << ' ';
		cout << endl;
	}

	void Algorithm()
	{

		PrintD();
		PrintC();

		int minimalLength = 0;

		c.push_back(graph->GetNode(0));
		d.erase(d.begin());

		PrintD();
		PrintC();
		while (!d.empty())
		{
			int min = INT_MAX;
			int nodeInd = -1;
			int nodeConnectionInd = -1;
			Node* tempNode = nullptr;

			for (int i = 0; i < c.size(); ++i)
			{
				for (int j = 0; j < c[i]->GetConnectionsSize(); ++j)
				{
					if (min > c[i]->GetConnectionLength(j) && find(c.begin(), c.end(), c[i]->GetConnectedNode(j)) == c.end())
					{
						min = c[i]->GetConnectionLength(j);
						nodeConnectionInd = j;
						tempNode = c[i]->GetConnectedNode(j);
					}
				}
			}

			if (tempNode)
			{
				minimalLength += min;
				c.push_back(tempNode);
				d.erase(remove(d.begin(), d.end(), tempNode), d.end());

				PrintD();
				PrintC();
			}
		}

		cout << "\n\n" << "Minimal length: " << minimalLength;

	}
};

int main()
{
	Graph graph;
	Node* one = new Node(1);
	Node* two = new Node(2);
	Node* three = new Node(3);
	Node* four = new Node(4);
	Node* five = new Node(5);
	Node* six = new Node(6);
	Node* seven = new Node(7);
	Node* eight = new Node(8);
	
	graph.AddNode(one);
	graph.AddNode(two);
	graph.AddNode(three);
	graph.AddNode(four);
	graph.AddNode(five);
	graph.AddNode(six);
	graph.AddNode(seven);
	graph.AddNode(eight);
	

	five->AddConnection(one, 7);
	five->AddConnection(three, 10);
	five->AddConnection(two, 4);
	five->AddConnection(six, 9);
	five->AddConnection(seven, 9);
	five->AddConnection(eight, 8);
	five->AddConnection(four, 10);

	one->AddConnection(two, 11);
	one->AddConnection(three, 7);

	two->AddConnection(six, 12);

	three->AddConnection(four, 6);
	three->AddConnection(eight, 15);

	four->AddConnection(seven, 19);
	four->AddConnection(eight, 11);

	eight->AddConnection(seven, 5);
	seven->AddConnection(six, 10);

	graph.ShowAllConnections();

	MinimalSpanningTree mstree(&graph);
	mstree.Algorithm();
	


}