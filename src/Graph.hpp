#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include <map>
#include <vector>

using namespace std;

class Node {
    public:
        Node(string val);
        vector<Node *> neighbors;
        string key; 
        bool visited;
        Node * parent; //The node that added it onto the list
};


class Graph {
 protected:
  //MAYBE ADD CLASS DATA STRUCTURE(S) HERE

 public:
  map<string, Node *>  nodes;
  Graph(void);

  ~Graph(void);

  //MAYBE ADD SOME MORE METHODS HERE SO AS TO ANSWER QUESTIONS IN YOUR PA
	
  /* YOU CAN MODIFY THIS IF YOU LIKE , in_filename : THE INPUT FILENAME */

  bool loadFromFile(const char* in_filename);

  bool pathfinder(Node* from, Node* to);
    
  void socialgathering(vector<string>& invitees, const int& k);

};




#endif  // GRAPH_HPP
