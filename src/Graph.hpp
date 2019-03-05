#ifndef GRAPH_HPP
#define GRAPH_HPP
#include <fstream>
#include <iostream>
#include <map>
#include <vector>
#include <stack>
#include <set>
using namespace std;

//Constructor for the node class
class Node {
    public:
        Node(string val);
        vector<Node *> neighbors;
        string key; 
        bool visited;
        Node * parent;
        int dist;
};

//Constructor for the graph class
class Graph {
    private:
        void reset();

        //Set that keep track of nodes that we will reset later
        set<Node *> cache;
        
        //Map that contains all the nodes in the graph
        map<string, Node *>  nodes;
        
        //The shortest path that we will be printing frtom
        stack<Node *> shortestPath;     

        void printShortestPath();

        bool isDigit(string s);

        bool pathfinder(Node* from, Node* to);
    
    public:
        Graph(void);

        ~Graph(void);

        bool loadFromFile(const char* in_filename);

        void socialgathering(vector<string>& invitees, const int& k);

        void printToFile(string outfile, string infile);
    
};

#endif  // GRAPH_HPP
