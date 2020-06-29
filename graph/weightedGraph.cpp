#include <cstdio>
#include <limits>
#include <algorithm>
#include <vector>
#include <string>
#include <stack>
#include <unordered_set>
#include <unordered_map>

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

        if (visitedNodes.find(curNode) != visitedNodes.end())
        {
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

// First working version, future refactors will come
void printPrimMCST (vector<string> &vertices, double matrix[29][29])
{

    double mcstCost = 0;

    unordered_set<string> nodesIncludedInMCST;
    unordered_map<string, pair<string, double>> edgeCosts;	// <child, <parent, cost>>
    unordered_map<string, vector<string>> mcst;

    for (string curVertex : vertices)
    {
        edgeCosts.insert(make_pair(curVertex, make_pair("", numeric_limits<double>::max())));
    }
    edgeCosts.begin()->second.second = 0;

    int nVertices = vertices.size();

    while (nodesIncludedInMCST.size() < nVertices)
    {
        // Pick the vertex with the lowest cost, not included in nodesIncludedInMCST
        double minCost = numeric_limits<double>::max();
        string curVertex = "";
        string curVertexParent = "";
        unordered_map<string, pair<string, double>>::iterator it;
        for (it = edgeCosts.begin(); it != edgeCosts.end(); it++)
        {
            if (nodesIncludedInMCST.find(it->first) == nodesIncludedInMCST.end())
            {
                if (it->second.second < minCost)
                {
                    curVertex = it->first;
                    curVertexParent = it->second.first;
                    minCost = it->second.second;
                }
            }
        }
        mcstCost += minCost;


        // Include the selected vertex in the set
        nodesIncludedInMCST.insert(curVertex);
        if (mcst.find(curVertex) == mcst.end())
        {
            mcst.insert(make_pair(curVertex, vector<string>()));
        }
        if(curVertexParent != "")
        {
            mcst.find(curVertex)->second.push_back(curVertexParent);

            if(mcst.find(curVertexParent) == mcst.end())
            {
                mcst.insert(make_pair(curVertexParent, vector<string>()));

            }
            mcst.find(curVertexParent)->second.push_back(curVertex);
        }


        // Update edgeCosts with the new neighbors
        int curVertexIndex = 0;
        for (int i = 0; i < nVertices; i++)
        {
            if (curVertex == vertices[i])
            {
                curVertexIndex = i;
            }
        }

        for (int i = 0; i < 29; i++)
        {
            if (matrix[curVertexIndex][i] != 0 && matrix[curVertexIndex][i] < edgeCosts.find(vertices[i])->second.second)
            {
                edgeCosts.find(vertices[i])->second.first = curVertex;
                edgeCosts.find(vertices[i])->second.second = matrix[curVertexIndex][i];
            }
        }
    }


    // Print the mcst graph
    printf("\nPrim's MCST cost = %.1f\n", mcstCost);
    unordered_map<string, vector<string>>::iterator it;
    for (it = mcst.begin(); it != mcst.end(); it++)
    {
        string curNode = it->first;
        printf("%s\n", curNode.c_str());

        vector<string> neighbors = it->second;
        if (!neighbors.empty())
        {
            printf("\t");
        }
        for(string curNeighbor : neighbors)
        {
            printf("%s ", curNeighbor.c_str());
        }
        printf("\n");
    }

}

// Standard DFS
bool formsCycle (unordered_map<string, vector<string>> &graph, string startVertex, string endVertex)
{
    if(graph.find(startVertex) == graph.end() || graph.find(endVertex) == graph.end())
    {
        return false;
    }

    stack<string> verticesToVisit;
    verticesToVisit.push(startVertex);
    unordered_set<string> visitedVertices;

    while (!verticesToVisit.empty())
    {
        string curVertex = verticesToVisit.top();
        verticesToVisit.pop();
        visitedVertices.insert(curVertex);
        if(curVertex == endVertex)
        {
            return true;
        }

        vector<string> neighbors = graph.find(curVertex)->second;
        for (string curNeighbor : neighbors)
        {
            if (visitedVertices.find(curNeighbor) == visitedVertices.end())
            {
                verticesToVisit.push(curNeighbor);
            }
        }

    }
    return false;

}

void printKruskalMCST (vector<string> &vertices, double matrix[29][29])
{
    double mcstCost = 0;
    int mcstNEdges = 0;
    int nVertices = vertices.size();
    unordered_map<string, vector<string>> mcst;

    // Create a vector with all the edges
    vector<pair<double, pair<string, string>>> edges;
    for(int i = 0; i < 29; i++)
    {
        for(int j = i; j < 29; j++)
        {
            if (matrix[i][j] != 0)
            {
                edges.push_back(make_pair(matrix[i][j], make_pair(vertices[i], vertices[j])));
            }
        }
    }

    // Sort this vector in ascending order, O(n lgn)
    sort(edges.begin(), edges.end());

    // Kruskal's
    vector<pair<double, pair<string, string>>>::iterator it = edges.begin();
    while (mcstNEdges < nVertices - 1)
    {

        double curWeight = it->first;
        string curVertex1 = it->second.first;
        string curVertex2 = it->second.second;

        if (!formsCycle(mcst, curVertex1, curVertex2))
        {
            if(mcst.find(curVertex1) == mcst.end())
            {
                mcst.insert(make_pair(curVertex1, vector<string>()));
            }
            mcst.find(curVertex1)->second.push_back(curVertex2);

            if(mcst.find(curVertex2) == mcst.end())
            {
                mcst.insert(make_pair(curVertex2, vector<string>()));
            }
            mcst.find(curVertex2)->second.push_back(curVertex1);


            mcstCost += curWeight;
            mcstNEdges++;
        }

        it++;
    }


    // Print the mcst graph
    printf("\nKruskal's MCST cost = %.1f\n", mcstCost);
    unordered_map<string, vector<string>>::iterator mcst_it;
    for (mcst_it = mcst.begin(); mcst_it != mcst.end(); mcst_it++)
    {
        string curNode = mcst_it->first;
        printf("%s\n", curNode.c_str());

        vector<string> neighbors = mcst_it->second;
        if (!neighbors.empty())
        {
            printf("\t");
        }
        for(string curNeighbor : neighbors)
        {
            printf("%s ", curNeighbor.c_str());
        }
        printf("\n");
    }

}



double calculateGraphCost(double matrix[29][29])
{
    double graphCost = 0;
    for (int i = 0; i < 29; i++)
    {
        for (int j = i; j < 29; j++)
        {
            graphCost += matrix[i][j];
        }
    }
    return (graphCost);
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

    //printDFS(vertices, adjacencyMatrixGraph, "Madrid");

    //printf("\nInitial graph cost = %.1f\n", calculateGraphCost(adjacencyMatrixGraph));
    printPrimMCST(vertices, adjacencyMatrixGraph);

    printKruskalMCST(vertices, adjacencyMatrixGraph);

}