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
#include <queue>
using namespace std;

Node::Node(string val){
    this->key = val;
    this->visited = false;
    this->parent = NULL;
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
        Node *n = new Node(record[0]);
        nodes.insert(pair<string, Node *>(record[0] , n));
    }

    if(nodes.find(record[1]) == nodes.end()){
        Node *n2 = new Node(record[1]);
        this->nodes.insert(pair<string, Node *>(record[1] , n2));
    }
    
    //Inserting neighbor into the key node
    Node * curr = nodes[record[0]];
    Node * dest = nodes[record[1]];
    curr->neighbors.push_back(dest);

  }

  if (!infile.eof()) {
    cerr << "Failed to read " << in_filename << "!\n";
    return false;
  }

  infile.close();
  return true;
}

/* Implement pathfinder*/
bool Graph::pathfinder(Node* from, Node* to) {
    queue<Node *> tovisit;
    tovisit.push(from);
    
    while(!tovisit.empty()){
   
        Node * curr = tovisit.front();
        tovisit.pop();
        curr->visited = true;     
        
        cout << "popping " << curr->key << "From the queue" << endl;    

        if(curr == to){
            cout << "We found the node" << endl;
            while(curr->parent){
                cout << curr-> key << endl;
                curr = curr->parent;
            }
            return true;
        }    
        
            //Enqueue the unvisited neighbor nodes
            for(int i =0; i < curr->neighbors.size(); i++){
                if(curr->neighbors[i]->visited == false){
                    tovisit.push(curr->neighbors[i]);
                    curr->neighbors[i]->parent = curr;
                 }        
            }   

   
     }   

    return true;  
}

/* Implement social gathering*/
//TODO
void Graph::socialgathering(vector<string>& invitees, const int& k) {
}

