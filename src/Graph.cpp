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
#include <stack>
#include <vector>
using namespace std;

Node::Node(string val){
    this->key = val;
    this->visited = false;
    this->parent = NULL;
    this->dist = -1;
}

Graph::Graph(void)  {
    //Initialize the graph


}

Graph::~Graph(void) {
}


/* Add a node to the graph representing person with id idNumber and add a connection between two nodes in the graph. */
 
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
    
    //Inserting the nodes 
    Node * curr = nodes[record[0]];
    Node * dest = nodes[record[1]];
    curr->neighbors.push_back(dest);
    dest->neighbors.push_back(curr);
  }

  if (!infile.eof()) {
    cerr << "Failed to read " << in_filename << "!\n";
    return false;
  }

  infile.close();
  return true;
}

//This will print to the outfile
void Graph::printToFile(string out_file, string in_filename){
    ifstream infile(in_filename);
    ofstream outfile(out_file);   
 
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
   
    
    bool dig1 = isDigit(record[0]);
    bool dig2 = isDigit(record[1]);

 
    //Check if they are not numbers
    if(dig1 == false || dig2 ==false){
        continue;
    }

    //Check if the node even exists in the map
    if(nodes.find(record[0]) == nodes.end() || nodes.find(record[1]) == nodes.end()){
        outfile << "\n";
        reset();
        continue;
    }
 
    Node * from = nodes.at(record[0]);
    Node * to = nodes.at(record[1]);
  bool inpath =  pathfinder(from, to);

    if(inpath == false){
        outfile << "\n";
        reset();
        continue;
    }    

    //Write to the file
    while(!shortestPath.empty()){
        Node * top = shortestPath.top();
        shortestPath.pop();
        outfile << top->key;
        //Only print space if not the last element in the shortest path
        if(!shortestPath.empty()){
            outfile << " ";
        }
    }

    //Reset the graph
    reset();
    outfile << "\n";
   }
}

void Graph::reset(){
    std::set<Node *>::iterator it = cache.begin();
    while(it != cache.end()){
        Node * curr = *it;
        curr->dist = -1;
        curr->parent = NULL;
        it++;
    }
    cache.clear(); 
    shortestPath = stack<Node *>();

}

void Graph::printShortestPath(){
    while(!(shortestPath.empty())){
        Node * curr = shortestPath.top();
        shortestPath.pop();
        cout << curr->key << endl;
    }
}

/* Implement pathfinder*/
bool Graph::pathfinder(Node* from, Node* to) {
    
    queue<Node *> tovisit;
    stack<Node *> returnVal;
    from->dist = 0;
    cache.insert(from);
    cache.insert(to);
    tovisit.push(from);
    
    while(!tovisit.empty()){
   
        Node * curr = tovisit.front();
        tovisit.pop();
        
        if(curr == to){
            while(curr->parent){
                returnVal.push(curr);
                curr = curr->parent;
            }

            returnVal.push(from);            
            shortestPath = returnVal;

            return true;
        }    
            //Enqueue the unvisited neighbor nodes
            for(int i =0; i < curr->neighbors.size(); i++){
                    if(curr->neighbors[i]->dist == -1){
                        curr->neighbors[i]->parent = curr;
                        curr->neighbors[i]->dist = curr->dist + 1;
                       // visited.push_back(curr->neighbors[i]); //Keeping track
                        cache.insert(curr->neighbors[i]);
                        tovisit.push(curr->neighbors[i]);
                    } 
            }   
     }   
    return false;  
}

bool Graph::isDigit(string s){
    for(int i =0; i < s.size(); i++){
        if(isdigit(s[i]) == false){
            return false;
        }
    }
    return true;
}

/* Implement social gathering*/
//TODO
void Graph::socialgathering(vector<string>& invitees, const int& k) {
}

