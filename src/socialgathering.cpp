#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "Graph.hpp"
#include <algorithm>

using namespace std;

//Helper method that sorts a map

//Helper method that wrotes to the file
static bool writeFile(map<string, int> * degree, char * out_file, int k){

  ofstream outfile(out_file);   

  vector<int> s;

  //Add all the degrees that are greater than or equal to k
  for( auto const &x : *degree){
    if(x.second >= k){
      s.push_back(std::stoi(x.first));
    }
  } 

  //Sort the vector
  sort(s.begin(), s.end());

  //Print to the file
  for(auto x : s){
    outfile << x;
    outfile << "\n";
  }
  outfile.close();
  return true;
}

static void printDegrees(map<string, int> * degrees){
  for(auto const& x : *degrees){
    cout << "key: " << x.first << " : " << x.second << endl;
  }

}

void usage(char* program_name) {
  cerr << program_name << " called with incorrect arguments." << endl;
  cerr << "Usage: " << program_name
       << " friendship_pairs_file k_value output_file"
       << endl;
  exit(-1);
}

int main(int argc, char* argv[]) {
  if (argc != 4) {
    usage(argv[0]);
  }
  char* graph_filename = argv[1];
  char* output_filename = argv[3];
  istringstream ss(argv[2]);
  int k = std::stoi( argv[2]);

  //Load the graph from the file
  map<string, int> degree;
  Graph g;
    
  g.genDegree(graph_filename, &degree);

  g.socialgathering(&degree, g.nodes["0"], k );
  
  //Run k core algorithm to reduce the degree values
  for( auto const &x : g.nodes ){
    if( x.second->visited == false){
     g.socialgathering(&degree, x.second, k);
    }
  }  

  writeFile(&degree, argv[3] , k);
  
}
