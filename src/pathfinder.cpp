#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "Graph.hpp"
using namespace std;
/*
 * void usage(char * program_name);
 * Description: Checks if the user netered the correct number of arguments;
 * paramters: program_name - The command line paramter
 * return:  None
 */
void usage(char* program_name) {
    cerr << program_name << " called with incorrect arguments." << endl;
    cerr << "Usage: " << program_name
          << " friendship_pairs_file test_pairs_file output_file"
          << endl;
    exit(-1);
}

/*
 *
 * int main(int argc, char* argv[);
 * Description: Main driver function for the pathfinder program
 * Takes in a graph file and generates a undirected graph. Then
 * it takes a input file to query the longest path, and an out
 * file to print the path two
 * Paramters:   argv[1] - The graph file
 *              argv[2] - The input query file
 *              argv[3] - The output filea
 * Return:  error if there was an error reading in the file
 *          success if the function successfully executed
 */
int main(int argc, char* argv[]) {
  
    if (argc != 4) {
        usage(argv[0]);
    }
  
    char* graph_filename = argv[1];
    char* pairs_filename = argv[2];
    char* output_filename = argv[3];

    Graph g;
    g.loadFromFile(graph_filename); 
    g.printToFile(output_filename , pairs_filename);
}  
