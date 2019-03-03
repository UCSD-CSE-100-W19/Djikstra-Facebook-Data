#include "Graph.hpp"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <limits>
#include <set>
#include <sstream>
#include <string>
#include <utility>
#include <map>
using namespace std;

Node::Node(String val){
    this->key = insert;
    this->visited = false;
}

Graph::Graph(void)  {
    //Initialize the graph


}

Graph::~Graph(void) {
}


/* Add a node to the graph representing person with id idNumber and add a connection between two nodes in the graph. */
//TODO

 
/* Read in relationships from an inputfile to create a graph */

bool Graph::loadFromFile(const char* in_filename) {
  ifstream infile(in_filename);

  while (infile) {
    string s;
    if (!getline(infile, s)) break;

    istringstream ss(s);
    vector<string> record;

    while (ss) {
      string s;
      if (!getline(ss, s, ' ')) break;
      record.push_back(s);
    }

    if (record.size() != 2) {
      continue;
    }

    
    //If node does not exist in the graph then create a new reference to it
    if(nodes.find(record[0]) == nodes.end()){
        cout << "creating a new node for" << record[0] << endl;
        Node *n = new Node(record[0]);
   //     nodes.insert(record[0] , n);
    }

    if(nodes.find(record[1]) == nodes.end()){
        cout << "Creating a new node for" << record[1] << endl;
        Node *n2 = new Node(record[1]);
     //   nodes.insert(record[1], n2);
    }


  }

  if (!infile.eof()) {
    cerr << "Failed to read " << in_filename << "!\n";
    return false;
  }

  infile.close();
  return true;
}

/* Implement pathfinder*/
//TODO 
bool Graph::pathfinder(Node* from, Node* to) {
    return true;  
}

/* Implement social gathering*/
//TODO
void Graph::socialgathering(vector<string>& invitees, const int& k) {
}

