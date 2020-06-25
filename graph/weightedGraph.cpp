#include <cstdio>
#include <vector>
#include <string>
#include <stack>
#include <unordered_set>

using namespace std;

// Compiled with 'g++ weightedGraph.cpp -o graph' and ran with './graph' on Ubuntu 20.04

bool isAdjacencyMatrixCorrect (double matrix [29][29], int nRows, int nCols)
{
    if (nRows != nCols)
    {
        printf("nRows (%d) is different from nCols (%d)\n", nRows, nCols);
        return false;
    }

    bool isCorrect = true;
    for (int i = 0; i < nRows; i++)
    {
        for (int j = 0; j < nCols; j++)
        {
            if (matrix[i][j] != matrix [j][i])
            {
                printf("%.1f at [%d][%d] is different from %.1f at [%d][%d]\n", matrix[i][j], i, j, matrix[j][i], j, i);
                isCorrect = false;
            }
        }
    }

    return isCorrect;
}

// Let's say all edges have the same weight, I just wanted to write DFS using adjacency matrix
void printDFS(vector<string> &vertices, double matrix [29][29], string startNode)
{

    stack<string> nodesToVisit;
    nodesToVisit.push(startNode);
    unordered_set<string> visitedNodes;

    int verticesSize = vertices.size();

    while (!nodesToVisit.empty())
    {
        string curNode = nodesToVisit.top();
        nodesToVisit.pop();

        if (visitedNodes.find(curNode) != visitedNodes.end()){
        	continue;
        }

        visitedNodes.insert(curNode);
        printf("%s ", curNode.c_str());


        int curNodeIndex = 0;
        for (int i = 0; i < verticesSize; i++)
        {
            if (vertices[i] == curNode)
            {
                curNodeIndex = i;
                break;
            }
        }

        for (int i = 0; i < verticesSize; i++)
        {
            if (matrix[curNodeIndex][i] != 0)
            {
                if(visitedNodes.find(vertices[i]) == visitedNodes.end())
                {
                    nodesToVisit.push(vertices[i]);
                }
            }
        }
    }
    printf("\n");

}


void printPrimMCST (vector<string>& vertices, double[29][29] matrix){

}



int main (int argc, char *argv [])
{
    vector<string> vertices = {	"Madrid", "Toledo",	"Caceres", "Merida", "Segovia", "Zamora",
                                "Vigo", "Coruna", "Burgos", "Leon", "Oviedo", "Vitoria",
                                "Calatayud", "Zaragoza", "Huesca", "Taragona", "Cuenca",
                                "Requena", "Valencia", "Castellon", "Albacete", "Alicante",
                                "Puertollano", "Cordoba", "Sevilla", "Cadiz", "Malaga",
                                "Granada", "Almeria"
                              };

    double adjacencyMatrixGraph [29][29] =
    {
        {0, 73.0, 303.2, 0, 91.2, 0, 0, 0, 0, 0, 0, 0, 231.7, 0, 0, 0, 168.2, 0, 0, 0, 0, 0, 242.6, 0, 0, 0, 0, 0, 0},  // Madrid
        {73, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},    					// Toledo
        {303.2, 0, 0, 73.7, 0, 267.0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},    			// Caceres
        {0, 0, 73.7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},    					// Merida
        {91.2, 0, 0, 0, 0, 210.0, 0, 0, 199.9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},    			// Segovia
        {0, 0, 267.0, 0, 210.0, 0, 259.5, 399, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},    		// Zamora
        {0, 0, 0, 0, 0, 259.5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},    				// Vigo
        {0, 0, 0, 0, 0, 399, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},    					// Coruna
        {0, 0, 0, 0, 199.9, 0, 0, 0, 0, 156.0, 0, 121.2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},    		// Burgos
        {0, 0, 0, 0, 0, 0, 0, 0, 156.0, 0, 123.0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},    			// Leon
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 123.0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},    				// Oviedo
        {0, 0, 0, 0, 0, 0, 0, 0, 121.2, 0, 0, 0, 0, 0, 329.7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},    			// Vitoria
        {231.7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 71.1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},   				// Calatayud
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 71.1, 0, 74.0, 236.0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},    			// Zagagoza
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 329.7, 0, 74.0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},    				// Huesca
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 236.0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},    				// Tarragona
        {168.2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 133.8, 0, 0, 163.8, 0, 0, 0, 0, 0, 0, 0, 0},    		// Cuenca
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 133.8, 0, 68.6, 0, 0, 174.2, 0, 0, 0, 0, 0, 0, 0},    			// Requena
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 68.6, 0, 63.8, 185.3, 125.4, 0, 0, 0, 0, 0, 0, 0},    		// Valencia
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 63.8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},   					// Castellon
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 163.8, 0, 185.3, 0, 0, 166.7, 0, 0, 0, 0, 0, 0, 0},   			// Albacete
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 174.2, 125.4, 0, 166.7, 0, 0, 0, 0, 0, 0, 0, 291.6},   		// Alicante
        {242.6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 106.5, 0, 0, 0, 0, 0},    			// Puertollano
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 106.5, 0, 140.7, 0, 158.6, 207.8, 0},    	// Cordoba
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 140.7, 0, 120.8, 204.8, 0, 0},   			// Sevilla
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 120.8, 0, 0, 0, 0},    				// Cadiz
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 158.6, 204.8, 0, 0, 126.5, 0},    		// Malaga
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 207.8, 0, 0, 126.5, 0, 167.6},    		// Granada
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 291.6, 0, 0, 0, 0, 0, 167.6, 0}     			// Almeria
    };

    printDFS(vertices, adjacencyMatrixGraph, "Madrid");

    printPrimMCST(vertices, adjacencyMatrixGraph);

}