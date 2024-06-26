#ifndef GRAPH_H
#define GRAPH_H
#include<vector>
#include<iostream>
using namespace std;

struct vertex;
struct adjVertex{
    vertex *v;
    
};

struct vertex{

    string name;
    bool visited = false;
    int distance = 0;
    vector<adjVertex> adj;
    vertex(const string& name) : name(name) {} // Add this constructor so I can statically push_back

};

class Graph
{
    public:
        void addEdge(string v1, string v2);
        void addVertex(string name);
        void displayEdges();
        void breadthFirstTraverse(string startVertex);//was sourceVertex
        vector<string> findReachableCitiesWithinDistanceK(string source, int k);
        vector<vertex *> getVertices() { return vertices; }

    private:
        vector<vertex*> vertices;
};

#endif // GRAPH_H
