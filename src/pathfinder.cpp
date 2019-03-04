#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "Graph.hpp"

using namespace std;

void usage(char* program_name) {
  cerr << program_name << " called with incorrect arguments." << endl;
  cerr << "Usage: " << program_name
       << " friendship_pairs_file test_pairs_file output_file"
       << endl;
  exit(-1);
}

int main(int argc, char* argv[]) {
  
  if (argc != 4) {
    usage(argv[0]);
  }
  

  char* graph_filename = argv[1];
  char* pairs_filename = argv[2];
  char* output_filename = argv[3];

  //TODO   
 /* You can call the pathfinder function from here */
 Graph g;
 g.loadFromFile(graph_filename); 
// g.pathfinder(g.nodes.at("3") , g.nodes.at("12"));
 //g.printToFile("mysolout" , "file1.txt");
// g.reset();
// g.pathfinder(g.nodes.at("3") , g.nodes.at("12"));
// g.printShortestPath();        
// g.reset();
 //g.pathfinder(g.nodes.at("0"), g.nodes.at("0"));
  g.printToFile(output_filename , pairs_filename);
}  
