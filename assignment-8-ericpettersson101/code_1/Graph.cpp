#include "Graph.hpp"
#include <vector>
#include <queue>
#include <iostream>
#include <algorithm>
using namespace std;

void Graph::addVertex(string name) {
    vertices.push_back(new vertex{name});
}

void Graph::addEdge(string v1, string v2) {
    vertex *vertex1, *vertex2  = nullptr;

    // Find the vertices in the graph
    for (auto &v : vertices) {
        if (v->name == v1) vertex1 = v;
        if (v->name == v2) vertex2 = v;
    }

    // Add an edge if both vertices exist in the graph
        vertex1->adj.push_back(adjVertex{vertex2}); // Add the adjacency to vertex1's list
        vertex2->adj.push_back(adjVertex{vertex1}); // Add the adjacency to vertex1's list


}

void Graph::displayEdges() {
    for(auto & v : vertices) {
        cout << v->name << " --> ";

        for(auto & adj : v->adj) {
            cout << adj.v->name << " ";
        }
        cout << endl;
    }
}


void Graph::breadthFirstTraverse(string sourceVertex) {
    // Reset all vertices to unvisited
    vertex *start = nullptr;
    for(auto &v : vertices) {
        if(v->name == sourceVertex) {
            start = v;
        }
    }


    if(start) {
        queue<vertex*> q;
        start->visited = true;
        q.push(start);

        cout << "Starting vertex (root): " << start->name << "-> ";
        while (!q.empty()) {
            vertex *current = q.front(); q.pop();

            for (auto &adj : current->adj) {
                if (!adj.v->visited) {

                    adj.v->visited = true;
                    adj.v->distance = current->distance + 1;
                    q.push(adj.v); // Ensure this is within the if statement
                    
                    cout << adj.v->name << "(" << adj.v->distance << ") ";
                }
            }
        }
        cout << "\n\n"; //for test cases
    } 
}
vector<string> Graph::findReachableCitiesWithinDistanceK(string source, int k) {
    vector<string> reachableCities;
    queue<vertex*> q;
    vertex *start = nullptr;
    // Reset all vertices to unvisited
    for (auto &v : vertices) {
        if (v->name == source) {
            start = v;
        }
    }


    if (start) {
        start->visited = true;
        q.push(start);

        while (!q.empty()) {
            vertex *current = q.front();
            q.pop();

            for (auto &adj : current->adj) {
                if (!adj.v->visited) {
                    adj.v->visited = true;
                    adj.v->distance = current->distance + 1;
                    if (adj.v->distance == k) {
                        reachableCities.push_back(adj.v->name);
                    }
                    q.push(adj.v);
                }
            }
        }
    }
    sort(reachableCities.begin(), reachableCities.end(), greater<string>());
    return reachableCities;
    
}