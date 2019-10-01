## Shortest Path Facebook Dataset
This project was developed for the CSE100 Advanced Data-Structures course
## Single-source shortest path problem
Dijkstra's algorithm, conceived by computer scientist Edsger Dijkstra, is a graph search algorithm that solves in single-source shortest path problem for a graph with non-negative edge path costs, producing a shortest path tree. In our implementation we are using Djikstra's algorithm to find the minimum path between weighted edges in a friend graph. The dataset can be found at http://snap.stanford.edu/data
<p align="center">
  <img src="https://upload.wikimedia.org/wikipedia/commons/5/57/Dijkstra_Animation.gif">
</p>

## How to run
```
g++ -std=c++11 src/pathfinder.cpp 
```

## Folder Structure
    ├── data                    # Data of friend connectivity graph
    ├── Reference Solution      # Documentation of correct output files
    ├── Output                  # Sample output to standard out
    ├── Makefile
    └── README.md
