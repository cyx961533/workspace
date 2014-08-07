//============================================================================
// Name        : DijkstraAlgorithm.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <queue>
#include <list>
#include <set>
#include <limits>
#include "Node.hpp"

//#include <boost>

using namespace std;
//using namespace boost;

struct ComparePair {
	bool operator() (const Node &a, const Node &b ) const {
		float t1 = a.distance;
		float t2 = b.distance;
 		return t1 > t2;
	}
};

/*	Node temp(3,1214);
	Q.push(temp);
	temp.set(1,23245);
	Q.push(temp);
	temp.set(2,2);
	Q.push(temp);

	while(!Q.empty()) {
		Node temp = Q.top();
		Q.pop();
		cout << "Node:" << temp.id << " Weight:" << temp.distance << endl;
	}
*/

/*	adjacencyList[0].push_back(make_pair(1,232));
    cout << "Debug 00:: *(adjacencyList[0].begin).first: " << (*adjacencyList[0].begin()).first << endl;
*/

void traversalDijkstra(int numberOfNodes, int src, int dst, vector< list < pair<int, float> > > adjacencyList, list<int> traverseList, const string outputLocation) {

	set< pair<float,int> >                             Q;
	vector< float >                                    d(numberOfNodes);
	list< pair<int, float> >                           S;                           // pair<node, minDistance>

	vector< list<int> > shortestPaths(numberOfNodes);
	int prevFixedNodeList[numberOfNodes];

	// Distance of all nodes from source
	for(int i=0; i<numberOfNodes; i++){
		if(i != src) {
			d[i] = numeric_limits<float>::max();
		}
		else {
			d[i] = 0;
		}
	}

	// Dijkstra Algorithm
	Q.insert(make_pair(0,src));
	prevFixedNodeList[src] = src;

	while(Q.size()!=0) {
		float minDist = Q.begin()->first;
		int nextHop   = Q.begin()->second;

		//cout << "Debug 11: Next hop=" << nextHop.id << endl;
		Q.erase(Q.begin());
		S.push_back(make_pair(nextHop, minDist));

		// Build path for each fixed vertex
		for (list<int>::iterator it = shortestPaths[prevFixedNodeList[nextHop]].begin(); it != shortestPaths[prevFixedNodeList[nextHop]].end(); it++) {
			cout << "Debug 22:: " << *it << endl;
		    shortestPaths[nextHop].push_back(*it);
		}
		shortestPaths[nextHop].push_back(nextHop);

		list < pair<int, float> >::iterator listIt = adjacencyList[nextHop].begin();
		for(; listIt != adjacencyList[nextHop].end(); listIt++) {
			//cout<< "Debug 11: for (*listIt).first:" << (*listIt).first << " (*listIt).second:" << (*listIt).second << "d[(*listIt).first]" << d[(*listIt).first] << endl;
			float prevMin = d[(*listIt).first];
			float couldBeMin = d[nextHop] + (*listIt).second;
			if( prevMin > couldBeMin) {
				d[(*listIt).first] = couldBeMin;
				Q.erase(make_pair(prevMin, (*listIt).first));
				//cout << "Debug 11: Hop to be pushed:" << (*listIt).first << endl;
				Q.insert(make_pair(couldBeMin, (*listIt).first));
				prevFixedNodeList[(*listIt).first] = nextHop;
			}
		}
	}

    string traversalFileName = outputLocation + "/AllFaces/traversalDetails.txt";
    ofstream traversalFilePtr;
    traversalFilePtr.open(traversalFileName.c_str());

	// Print the shortest distance for each other vertex
	for(int i=0; i<numberOfNodes; i++) {

		//cout << "Shortest distance from source:" << src << " to vertex:" << i << " =" << d[i] << endl;
		//cout << " Size: " << shortestPaths[i].size() << " Path taken: " ;

		traversalFilePtr << "Shortest distance from source:" << src << " to vertex:" << i << " =" << d[i] << endl;
		traversalFilePtr << " Size: " << shortestPaths[i].size() << " Path taken: " ;

		for(list<int>::iterator it = shortestPaths[i].begin(); it != shortestPaths[i].end(); it++){
			//cout << *it << "-" ;
			traversalFilePtr << *it << "-" ;
		}
		traversalFilePtr << endl;
	}
}
