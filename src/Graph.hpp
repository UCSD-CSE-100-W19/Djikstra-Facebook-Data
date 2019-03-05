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

    public:
        set<Node *> cache;
        map<string, Node *>  nodes;
        Graph(void);
  

        stack<Node *> shortestPath;     
        ~Graph(void);

        bool loadFromFile(const char* in_filename);

        bool pathfinder(Node* from, Node* to);
    
        void socialgathering(vector<string>& invitees, const int& k);

        void printToFile(string outfile, string infile);
    

        void printShortestPath();

        bool isDigit(string s);
};




#endif  // GRAPH_HPP
