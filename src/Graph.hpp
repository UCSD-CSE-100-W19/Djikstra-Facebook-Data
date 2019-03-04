#ifndef GRAPH_HPP
#define GRAPH_HPP
#include <fstream>
#include <iostream>
#include <map>
#include <vector>
#include <stack>
#include <set>
using namespace std;

class Node {
    public:
        Node(string val);
        vector<Node *> neighbors;
        string key; 
        bool visited;
        Node * parent; //The node that added it onto the list
        int dist;
};


class Graph {
 protected:
  //MAYBE ADD CLASS DATA STRUCTURE(S) HERE

 public:
  set<Node *> cache;
  map<string, Node *>  nodes;
  Graph(void);
  

  stack<Node *> shortestPath;     
  ~Graph(void);

  //MAYBE ADD SOME MORE METHODS HERE SO AS TO ANSWER QUESTIONS IN YOUR PA
	
  /* YOU CAN MODIFY THIS IF YOU LIKE , in_filename : THE INPUT FILENAME */

  bool loadFromFile(const char* in_filename);

  bool pathfinder(Node* from, Node* to);
    
  void socialgathering(vector<string>& invitees, const int& k);

  void printToFile(string outfile, string infile);
    
  void reset();

  void printShortestPath();

  bool isDigit(string s);

};




#endif  // GRAPH_HPP
