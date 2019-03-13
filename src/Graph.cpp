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

//Constructor initialzes everything
Node::Node(string val){
    this->key = val;
    this->visited = false;
    this->parent = NULL;
    this->dist = -1;
}

Graph::Graph(void)  {
}
//Destructor
Graph::~Graph(void) {
}

/*
 * bool Graph::loadFromFile(const char * in_filename);
 * Description: This function will load the graph and generate the graph.
 * It reads the file one line at a time. 
 * Paramaters:  const char* in_filename - The name of the file being read from
 * Return:  True - The file was successfull read
 *          False - There was an error reading the file
 */
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
    //Do the same thing for the second paramter
    if(nodes.find(record[1]) == nodes.end()){
        Node *n2 = new Node(record[1]);
        this->nodes.insert(pair<string, Node *>(record[1] , n2));
    }
    
    //Insert the nodes into the hashmap
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

/*
 * void Graph::printToFile(string out_file, string in_file);
 * Description: THis method will read the input from infile and then print
 * the shortest path to outfile. If the line read is not a valid number than
 * it will skip over it. If there is no path then it will print a new line
 * Paramters:   out_file - The name of the outfile
 *              in_file - The name of the in file
 * Return:      None
 */
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
 
    //Get the shortest path from the nodes
    Node * from = nodes.at(record[0]);
    Node * to = nodes.at(record[1]);
    bool inpath =  pathfinder(from, to);

    //If there is no path then print a new line
    if(inpath == false){
        outfile << "\n";
        reset(); //Reset the graph for the next query
        continue;
    }    

    //Dequeue from shortest path stack and print it to the files
    while(!shortestPath.empty()){
      Node * top = shortestPath.top();
      shortestPath.pop();
      outfile << top->key; //Print the key to file
      //Only print space if not the last element in the shortest path
      if(!shortestPath.empty()){
          outfile << " ";
      }
    }  

    //Reset the graph for the next query
    reset();
    outfile << "\n";
    }
}

/*
 * void Graph::reset();
 * Description: Function that resets the values of each node so we can perform
 * the next query
 * Paramters:   None
 * return:      None
 */
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
/*
 * Helper method that displays that prints out the nodes
 */
void Graph::printShortestPath(){
  while(!(shortestPath.empty())){
    Node * curr = shortestPath.top();
    shortestPath.pop();
    cout << curr->key << endl;
  }
}

/*
 * bool graph:: pathfinder(Node * from, Node * to);
 * Description: Function taht calculates the shortest path between from and to
 * paramters:   Node * to - The node we are starting at
 *              Node * from - The destination Node
 * Return:      true if the path exists, false otherwise
 */
bool Graph::pathfinder(Node* from, Node* to) {
  
  //Enqueue the first element  
  queue<Node *> tovisit;
  stack<Node *> returnVal;
  from->dist = 0;
  cache.insert(from);  //keep track of nodes that we will reset later
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
    for(size_t i =0; i < curr->neighbors.size(); i++){
      if(curr->neighbors[i]->dist == -1){
        curr->neighbors[i]->parent = curr;
        curr->neighbors[i]->dist = curr->dist + 1;
        cache.insert(curr->neighbors[i]); //Keep track of nodes we will reset
        tovisit.push(curr->neighbors[i]);
      } 
    }   
  }   
  return false;  
}

/*
 * bool Graph::isDigit(stirng s);
 * Description: Checks if a string has only digits
 * parmaters:   s - The string we will be checking
 * Return;  True - The string is a digit
 *          False - The string is not a digit
 */
bool Graph::isDigit(string s){
  for(size_t i =0; i < s.size(); i++){
    if(isdigit(s[i]) == false){
      return false;
    }
  }
  return true;
}


//DFS Helper Function
static bool traversal( Node * node, map<string, int> * degree, int k){
  node->visited = true;

  //Iterate through all of nodes neighbors 
  for( int i =0; i < node->neighbors.size(); i++){
    //If the degree is less than k then we decrement by one
    if((*degree)[node->key] < k ){
      (*degree)[node->neighbors[i]->key]--; 
    }   
    
    //Do DFS
    if(node->neighbors[i]->visited == false){
      if(traversal(node->neighbors[i], degree, k)) (*degree)[node->key]--;
    }
  }
  return ((*degree)[node->key] < k);
}

/* Implement social gathering*/
void Graph::socialgathering(map<string, int> *  degrees, Node * startVertex, const int& k) {
  traversal(startVertex, degrees, k);
}

//Generates a map of the number of degrees to a string
bool Graph::genDegree(const char * in_filename, map<string, int> * degree){

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
        degree->insert(pair<string, int>(record[0], 0));
    }
    //Do the same thing for the second paramter
    if(nodes.find(record[1]) == nodes.end()){
        Node *n2 = new Node(record[1]);
        this->nodes.insert(pair<string, Node *>(record[1] , n2));
        degree->insert(pair<string, int>(record[1], 0));
    }
    
    //Insert the nodes into the hashmap
    Node * curr = nodes[record[0]];
    Node * dest = nodes[record[1]];
    curr->neighbors.push_back(dest);
    dest->neighbors.push_back(curr);

    //Increment the count of hashmap
    (*degree)[record[0]] = (*degree)[record[0]] + 1;
    (*degree)[record[1]] = (*degree)[record[1]] + 1;

  }
  
  if (!infile.eof()) {
    cerr << "Failed to read " << in_filename << "!\n";
    return false;
  }

  infile.close();
  return true;
}

bool Graph::socialHelper(Node * curr, int k){

  curr->visited = true;
      
  //Iterate through the graph
  for(size_t i = 0; i < curr->neighbors.size(); i++){       



  }


}

