#include <iostream>
#include "Graph.h"


int main() {
    
    int numberOfGraphs;
    cin >> numberOfGraphs;

    for (int i = 0; i < numberOfGraphs; ++i) {

        int numberVertices;
        cin >> numberVertices;
        Graph graph(numberVertices);

        for (int j = 1; j <= numberVertices; ++j) {

            int numberNeighbors;
            cin >> numberNeighbors;
            int* neighborsTable = new int[numberNeighbors];

            for (int l = 0; l < numberNeighbors; ++l) {
                cin >> neighborsTable[l];
            }
            graph.addEdges(j, numberNeighbors, neighborsTable);
            delete[] neighborsTable;
        }

        cout << "This is your graph " << i + 1 << ": " << endl ;
        graph.printGraph();
        cout << "\n" << "Gradual sequence : ";
        graph.printGradualSequence();
        cout << "Number of cohesion : " << graph.getNumberOfCohesion() << endl;
        cout << "Is bipartiteness : " << graph.bipartiteness() << endl;
        //graph.printEccentricities();
        //cout << "?" << endl;
        //cout << "?" << endl;
        cout << "Vertices colours using greedy algorithm : ";
        graph.printColoring();
        cout << "Vertices colours using LF algorithm : ";
        graph.printLF();
        //graph.printSLF();
        //cout << "?" << endl;
        //cout << "?" << endl;
        cout << "The number of the graph complement's edges : " << graph.getNumComplementEdges() << endl;
    }

    return 0;
}
