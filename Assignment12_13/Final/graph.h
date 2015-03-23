////////////////////////////////////////////////////////////////////////////////////////
//		Group Members:	Josh Reinoehl, Cole Marlar, Michael Bretherick
//		Assignment 12:	Shortest Path Algorithm
//		Description:	Receives data points to create a graph of vertices and then makes
//						use of a shortest path algorithm based on vertices selected by 
//						the user.
//							
////////////////////////////////////////////////////////////////////////////////////////
#include<iostream>
#include<fstream>
#include<climits>
#include"LinkedList.h"
#include"queue.h"
using namespace std;

#ifndef GRAPH_H
#define GRAPH_H


class graph
{
private:
	class vertex
	{
	public:
		vertex();
		~vertex();
		void reset();
		int num;
		int pathVal;
		int lastChanged;
		LinkedList<int> vertexList;
	};
	int size;
	vertex * vertices;
	int * lastPath;

public:
	graph();
	graph(istream&);
	~graph();
	void setSize(istream&);
	void build(istream&);
	void reset();
	bool shortestPathU(int a,int b);
	int getSize();
	int* getPath();
	void print(ostream&);

};


////////////////////////////////////////////////////////////////////////////////////////
//		Vertex Constructor/Destructor
////////////////////////////////////////////////////////////////////////////////////////
graph::vertex::vertex()
{
	num	= NULL;
	pathVal	= INT_MAX;
	lastChanged = -1;
}

graph::vertex::~vertex()
{
	vertexList.~LinkedList();
}


////////////////////////////////////////////////////////////////////////////////////////
//		Function Actions:	Reinitializes a vertex to be used with new data points.
////////////////////////////////////////////////////////////////////////////////////////
void graph::vertex::reset()
{
	pathVal = INT_MAX;
	lastChanged = -1;
}

graph::graph()
{
	size = 0;
}

void graph::setSize(istream& in)
{
	in >> size;//first line is number of vertices
	vertices = new vertex[size];
	lastPath = new int[size];
}
////////////////////////////////////////////////////////////////////////////////////////
//		Graph Constructor/Destructor
////////////////////////////////////////////////////////////////////////////////////////

graph::graph(istream& in)
{
	in >> size;//first line is number of vertices
	vertices = new vertex[size];
	lastPath = new int[size];
}

graph::~graph()
{
	if ( size > 0 ) 
	{
		delete [] vertices;  
		size = 0;
	}
}

////////////////////////////////////////////////////////////////////////////////////////
//		Function Actions:	Creates and fills the graph to be used.
////////////////////////////////////////////////////////////////////////////////////////
void graph::build(istream& in)
{
	int e;
	for(int c = 0; c < size; c++)
		vertices[c].num = c;
	for(int c = 0; c < size; c++)
	{
		in >> e;
		for(; e != -1; in >> e)
			vertices[c].vertexList.Insert(e);
	}
}

////////////////////////////////////////////////////////////////////////////////////////
//		Function Actions:	Reinitializes a graph to be used with new data points.
////////////////////////////////////////////////////////////////////////////////////////
void graph::reset()
{
	for(int c = 0; c < size; c++)
	{
		vertices[c].reset();
		lastPath[c] = -1;
	}
}

////////////////////////////////////////////////////////////////////////////////////////
//		Function Actions:	Algorithim that performs the search for the shortest path.
////////////////////////////////////////////////////////////////////////////////////////
bool graph::shortestPathU(int a,int b)
{
	int * path = new int[size];
	int temp = -1, eye = a, cursor = -1, dest = b;	//temp will be the points to hit from a to b
	bool flag = true;
	queue<int> que(size);
	for(int c = 0; c < size; c++)
	path[c] = -1;
	reset();

	vertices[a].pathVal = 0;
	while ( eye != b )		//Checks if the current eye is equal to the destination.
	{
		if(!vertices[eye].vertexList.Empty())		//Checks if the eye points to any other vertices.
		{
			vertices[eye].vertexList.GoToBeginning();
			cursor = temp = vertices[eye].vertexList.AtCursor();
			do		//Loops over all vertices the current eye points to.
			{
				if ( (vertices[eye].pathVal+1) < vertices[cursor].pathVal )		//Changes the total path value of a vertex if path from eye is not larger.
				{
					vertices[cursor].pathVal = (vertices[eye].pathVal + 1);
					vertices[cursor].lastChanged = eye;
					que.push(cursor);
				}
				vertices[eye].vertexList.GoToNext();
				cursor = vertices[eye].vertexList.AtCursor();
			}
			while (temp != cursor);
		}

		if ( !que.isEmpty() )
			eye = que.pop();
		else
			return false;
	}
    
	int swapT;
	for(int c = 0; c < size && flag; c++)	//Traces path from destination back to original eye.
	{
		if(dest != -1)
		{
			path[c] = dest;    
			dest = vertices[dest].lastChanged;
		}
		else
			flag = false;
	}
	for(int c = 0, r = size-1; c < r; c++, r--)	
	{
		swapT = path[c];
		path[c] = path[r];
		path[r] = swapT;
	}
	for(int c = 0; c < size-1; c++)
	{
		if(path[c] == -1)
		{
			for(int r = 0; r < size-1; r++)
				path[r] = path[r+1];
			path[size-1] = -1;
		}
	}
	for(int c = 0; c < size; c++)
		lastPath[c] = path[c];

	return true;
}

////////////////////////////////////////////////////////////////////////////////////////
//		Function Actions:	Returns total vertices in current graph data.
////////////////////////////////////////////////////////////////////////////////////////
int graph::getSize()
{
	return size;
}

////////////////////////////////////////////////////////////////////////////////////////
//		Function Actions:	Returns the shortest path of the last two data points entered.
////////////////////////////////////////////////////////////////////////////////////////
int* graph::getPath()
{
	return lastPath;
}

////////////////////////////////////////////////////////////////////////////////////////
//		Function Actions:	Prints each point of the graph along with all points they are
//							pointing to.
////////////////////////////////////////////////////////////////////////////////////////
void graph::print(ostream& out)
{
	for(int c = 0, temp = 0; c < size; c++)
	{
		out << c + 1 << ':';
		if(!vertices[c].vertexList.Empty())
		{
			vertices[c].vertexList.GoToBeginning();
			temp = vertices[c].vertexList.AtCursor();
			
			do
			{
				
				out << (vertices[c].vertexList.AtCursor())+1;
				out << ' ';
				vertices[c].vertexList.GoToNext();
			}
			while(vertices[c].vertexList.AtCursor() != temp);
		}
		out << endl;
	} 
}

#endif