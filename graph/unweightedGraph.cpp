#include <cstdio>
#include <climits>
#include <algorithm>
#include <vector>
#include <stack>
#include <deque>
#include <unordered_set>
#include <unordered_map>

using namespace std;

// Compiled using 'g++ unweightedGraph.cpp -o graph' and executed using './graph' on Ubuntu 20.04
// SpanishCitiesGraph.png was used as the test graph


void printDFS (unordered_map<string, vector<string>> &graph, string startNode)
{
    printf("\nDFS:\n");
    if (graph.count(startNode) == 0)
    {
        throw invalid_argument("startNode is not in the graph");
    }

    stack<string> nodesToVisit;
    nodesToVisit.push(startNode);
    unordered_set<string> visitedNodes;

    while (!nodesToVisit.empty())
    {
        string curNode = nodesToVisit.top();
        nodesToVisit.pop();

        if (visitedNodes.count(curNode))
        {
            continue;
        }

        visitedNodes.insert(curNode);
        printf("%s ", curNode.c_str());

        for (string neighbor : graph.find(curNode)->second)
        {
            if (visitedNodes.find(neighbor) == visitedNodes.end())
            {
                nodesToVisit.push(neighbor);
            }
        }
    }
    printf("\n%ld nodes\n", visitedNodes.size());
    printf("\n");
}

void printDFS(int matrix [29][29]){
    
}


void printBFS (unordered_map<string, vector<string>> &graph, string startNode)
{
    printf("\nBFS:\n");
    if (graph.count(startNode) == 0)
    {
        throw invalid_argument("startNode is not in the graph");
    }

    deque<string> nodesToVisit;
    nodesToVisit.push_back(startNode);
    unordered_set<string> visitedNodes;

    while (!nodesToVisit.empty())
    {
        string curNode = nodesToVisit.front();
        nodesToVisit.pop_front();

        if(visitedNodes.count(curNode))
        {
            continue;
        }

        visitedNodes.insert(curNode);
        printf("%s ", curNode.c_str());

        for (string neighbor : graph.find(curNode)->second)
        {
            if (!visitedNodes.count(neighbor))
            {
                nodesToVisit.push_back(neighbor);
            }
        }
    }
    printf("\n%ld nodes\n", visitedNodes.size());
    printf("\n");
}

void printShortestRoute (unordered_map<string, vector<string>> &graph, string startNode, string endNode)
{
    if (graph.count(startNode) == 0)
    {
        throw invalid_argument("startNode is not in the graph");
    }
    if (graph.count(endNode) == 0)
    {
        throw invalid_argument("endNode is not in the graph");
    }

    printf("Shortest route from %s to %s:\n", startNode.c_str(), endNode.c_str());

    deque<string> nodesToVisit;
    nodesToVisit.push_back(startNode);
    unordered_map<string, string> traces;   // key: child, value: parent
    traces.insert(make_pair(startNode, ""));

    //unordered_set<string> visitedNodes;

    while (!nodesToVisit.empty())
    {
        string curNode = nodesToVisit.front();
        nodesToVisit.pop_front();

        if (curNode == endNode)
        {
            vector<string> reversedPath;
            string curTrace = curNode;

            while(curTrace != "")
            {
                reversedPath.push_back(curTrace);
                curTrace = traces.find(curTrace)->second;
            }

            reverse(reversedPath.begin(), reversedPath.end());

            for (string str : reversedPath)
            {
                printf("%s ", str.c_str());
            }
            printf("\n\n");
            return;
        }

        for (string neighbor : graph.find(curNode)->second)
        {
            if (traces.find(neighbor) == traces.end())
            {
                nodesToVisit.push_back(neighbor);
                traces.insert(make_pair(neighbor, curNode));
            }
        }
    }
}

bool hasCycle (unordered_map<string, vector<string>> &graph)
{

    deque<string> nodesToVisit;
    nodesToVisit.push_back(graph.begin()->first);
    unordered_set<string> visitedNodes;

    while(!nodesToVisit.empty())
    {
        string curNode = nodesToVisit.front();
        nodesToVisit.pop_front();
        visitedNodes.insert(curNode);

        if (visitedNodes.find(curNode) != visitedNodes.end())
        {
            return true;
        }

        for(string neighbor : graph.find(curNode)->second)
        {
            if (visitedNodes.find(neighbor) == visitedNodes.end())
            {
                nodesToVisit.push_back(neighbor);
            }
        }
    }

    return false;
}

bool isAdjacencyMatrixCorrect (int matrix [29][29], int nRows, int nCols)
{
    if (nRows != nCols)
    {
        printf("nRows (%d) is different from nCols (%d)\n", nRows, nCols);
        return false;
    }

    for (int i = 0; i < nRows; i++)
    {
        for (int j = 0; j < nCols; j++)
        {
            if (matrix[i][j] != matrix [j][i])
            {
                printf("%d at [%d][%d] is different from %d at [%d][%d]\n", matrix[i][j], i, j, matrix[j][i], j, i);
                return false;
            }
        }
    }

    return true;
}

// It doesn't make much sense to implement Prim on an unweighted graph but it's useful for me to practice
unordered_map<string, vector<string>> primMST (unordered_map<string, vector<string>> &graph)
{

    // This is the graph we'll return
    unordered_map<string, vector<string>> mcst;

    // Set to keep track of the already included vertices in the mst
    unordered_set<string> includedVertices;
    // Map with the updated weights of the edges connecting neighbors to the included vertices
    unordered_map<string, pair<string, int>> edgesWeights; //newVertex, parent, weight
    int nVertices = 0;

    // Fill in edgesWeights with the vertices in graph and set the initial weight to infinite
    unordered_map<string, vector<string>>::iterator it;
    for (it = graph.begin(); it != graph.end(); it++)
    {
        nVertices++;
        edgesWeights.insert(make_pair(it->first, make_pair("", INT_MAX)));
    }
    // Except for the first vertex, whichever it is
    edgesWeights.begin()->second.second = 0;

    // While there are still vertices to connect
    while (includedVertices.size() < nVertices)
    {
        int minWeight = INT_MAX;
        string selectedVertex = "";
        string selectedVertexParent = "";

        // Find the not-yet-connected vertex with the minimum weight. In this scenario, all the weights are 1
        unordered_map<string, pair<string, int>>::iterator it;
        for(it = edgesWeights.begin(); it != edgesWeights.end(); it++)
        {
            if(includedVertices.find(it->first) == includedVertices.end())
            {
                if (it->second.second < minWeight)
                {
                    selectedVertex = it->first;
                    selectedVertexParent = it->second.first;
                    minWeight = it->second.second;
                }
            }
        }

        // Incude it in the set
        includedVertices.insert(selectedVertex);

        // And add the edge to the returning graph
        mcst.insert(make_pair(selectedVertex, vector<string>()));
        if(selectedVertexParent != "")
        {
            mcst.find(selectedVertex)->second.push_back(selectedVertexParent);
            mcst.find(selectedVertexParent)->second.push_back(selectedVertex);
        }
        
        // Update the edges' weights of the new neighbors
        vector<string> neighbors = graph.find(selectedVertex)->second;
        for(string neighbor : neighbors)
        {
            edgesWeights.find(neighbor)->second.first = selectedVertex;
            edgesWeights.find(neighbor)->second.second = 1;
        }

    }


    return mcst;
}

void printGraph(unordered_map<string, vector<string>> &graph)
{

    unordered_map<string, vector<string>>::iterator it;
    for (it = graph.begin(); it != graph.end(); it++)
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

int main (int argc, char *argv [])
{

    unordered_map<string, vector<string>> unweightedGraph =
    {
        {"Madrid", {"Segovia", "Calatayud", "Cuenca", "Puertollano", "Toledo", "Caceres"}},
        {"Toledo", {"Madrid"}},
        {"Caceres", {"Madrid", "Merida", "Zamora"}},
        {"Merida", {"Caceres"}},
        {"Segovia", {"Madrid", "Zamora", "Burgos"}},
        {"Zamora", {"Segovia", "Caceres", "Vigo", "Coruna"}},
        {"Vigo", {"Zamora"}},
        {"Coruna", {"Zamora"}},
        {"Burgos", {"Segovia", "Leon", "Vitoria"}},
        {"Leon", {"Burgos", "Oviedo"}},
        {"Oviedo", {"Leon"}},
        {"Vitoria", {"Burgos", "Huesca"}},
        {"Calatayud", {"Madrid", "Zaragoza"}},
        {"Zaragoza", {"Huesca", "Tarragona", "Calatayud"}},
        {"Huesca", {"Zaragoza", "Vitoria"}},
        {"Tarragona", {"Zaragoza"}},
        {"Cuenca", {"Madrid", "Requena", "Albacete"}},
        {"Requena", {"Cuenca", "Alicante", "Valencia"}},
        {"Valencia", {"Castellon", "Requena", "Albacete", "Alicante"}},
        {"Castellon", {"Valencia"}},
        {"Albacete", {"Cuenca", "Valencia", "Alicante"}},
        {"Alicante", {"Valencia", "Requena", "Albacete", "Almeria"}},
        {"Puertollano", {"Madrid", "Cordoba"}},
        {"Cordoba", {"Puertollano", "Sevilla", "Malaga", "Granada"}},
        {"Sevilla", {"Cordoba", "Cadiz", "Malaga"}},
        {"Cadiz", {"Sevilla"}},
        {"Malaga", {"Granada", "Cordoba", "Sevilla"}},
        {"Granada", {"Cordoba", "Malaga", "Almeria"}},
        {"Almeria", {"Granada", "Alicante"}}
    };

    int adjacencyMatrixGraph [29][29] =
    {
        {0, 1, 1, 0, 1,     0, 0, 0, 0, 0,      0, 0, 1, 0, 0,      0, 1, 0, 0, 0,      0, 0, 1, 0, 0,      0, 0, 0, 0},    // Madrid
        {1, 0, 0, 0, 0,     0, 0, 0, 0, 0,      0, 0, 0, 0, 0,      0, 0, 0, 0, 0,      0, 0, 0, 0, 0,      0, 0, 0, 0},    // Toledo
        {1, 0, 0, 1, 0,     1, 0, 0, 0, 0,      0, 0, 0, 0, 0,      0, 0, 0, 0, 0,      0, 0, 0, 0, 0,      0, 0, 0, 0},    // Caceres
        {0, 0, 1, 0, 0,     0, 0, 0, 0, 0,      0, 0, 0, 0, 0,      0, 0, 0, 0, 0,      0, 0, 0, 0, 0,      0, 0, 0, 0},    // Merida
        {1, 0, 0, 0, 0,     1, 0, 0, 1, 0,      0, 0, 0, 0, 0,      0, 0, 0, 0, 0,      0, 0, 0, 0, 0,      0, 0, 0, 0},    // Segovia

        {0, 0, 1, 0, 1,     0, 1, 1, 0, 0,      0, 0, 0, 0, 0,      0, 0, 0, 0, 0,      0, 0, 0, 0, 0,      0, 0, 0, 0},    // Zamora
        {0, 0, 0, 0, 0,     1, 0, 0, 0, 0,      0, 0, 0, 0, 0,      0, 0, 0, 0, 0,      0, 0, 0, 0, 0,      0, 0, 0, 0},    // Vigo
        {0, 0, 0, 0, 0,     1, 0, 0, 0, 0,      0, 0, 0, 0, 0,      0, 0, 0, 0, 0,      0, 0, 0, 0, 0,      0, 0, 0, 0},    // Coruna
        {0, 0, 0, 0, 1,     0, 0, 0, 0, 1,      0, 1, 0, 0, 0,      0, 0, 0, 0, 0,      0, 0, 0, 0, 0,      0, 0, 0, 0},    // Burgos
        {0, 0, 0, 0, 0,     0, 0, 0, 1, 0,      1, 0, 0, 0, 0,      0, 0, 0, 0, 0,      0, 0, 0, 0, 0,      0, 0, 0, 0},    // Leon

        {0, 0, 0, 0, 0,     0, 0, 0, 0, 1,      0, 0, 0, 0, 0,      0, 0, 0, 0, 0,      0, 0, 0, 0, 0,      0, 0, 0, 0},    // Oviedo
        {0, 0, 0, 0, 0,     0, 0, 0, 1, 0,      0, 0, 0, 0, 1,      0, 0, 0, 0, 0,      0, 0, 0, 0, 0,      0, 0, 0, 0},    // Vitoria
        {1, 0, 0, 0, 0,     0, 0, 0, 0, 0,      0, 0, 0, 1, 0,      0, 0, 0, 0, 0,      0, 0, 0, 0, 0,      0, 0, 0, 0},    // Calatayud
        {0, 0, 0, 0, 0,     0, 0, 0, 0, 0,      0, 0, 1, 0, 1,      1, 0, 0, 0, 0,      0, 0, 0, 0, 0,      0, 0, 0, 0},    // Zagagoza
        {0, 0, 0, 0, 0,     0, 0, 0, 0, 0,      0, 1, 0, 1, 0,      0, 0, 0, 0, 0,      0, 0, 0, 0, 0,      0, 0, 0, 0},    // Huesca

        {0, 0, 0, 0, 0,     0, 0, 0, 0, 0,      0, 0, 0, 1, 0,      0, 0, 0, 0, 0,      0, 0, 0, 0, 0,      0, 0, 0, 0},    // Tarragona
        {1, 0, 0, 0, 0,     0, 0, 0, 0, 0,      0, 0, 0, 0, 0,      0, 0, 1, 0, 0,      1, 0, 0, 0, 0,      0, 0, 0, 0},    // Cuenca
        {0, 0, 0, 0, 0,     0, 0, 0, 0, 0,      0, 0, 0, 0, 0,      0, 1, 0, 1, 0,      0, 1, 0, 0, 0,      0, 0, 0, 0},    // Requena
        {0, 0, 0, 0, 0,     0, 0, 0, 0, 0,      0, 0, 0, 0, 0,      0, 0, 1, 0, 1,      1, 1, 0, 0, 0,      0, 0, 0, 0},    // Valencia
        {0, 0, 0, 0, 0,     0, 0, 0, 0, 0,      0, 0, 0, 0, 0,      0, 0, 0, 1, 0,      0, 0, 0, 0, 0,      0, 0, 0, 0},    // Castellon

        {0, 0, 0, 0, 0,     0, 0, 0, 0, 0,      0, 0, 0, 0, 0,      0, 1, 0, 1, 0,      0, 1, 0, 0, 0,      0, 0, 0, 0},    // Albacete
        {0, 0, 0, 0, 0,     0, 0, 0, 0, 0,      0, 0, 0, 0, 0,      0, 0, 1, 1, 0,      1, 0, 0, 0, 0,      0, 0, 0, 1},    // Alicante
        {1, 0, 0, 0, 0,     0, 0, 0, 0, 0,      0, 0, 0, 0, 0,      0, 0, 0, 0, 0,      0, 0, 0, 1, 0,      0, 0, 0, 0},    // Puertollano
        {0, 0, 0, 0, 0,     0, 0, 0, 0, 0,      0, 0, 0, 0, 0,      0, 0, 0, 0, 0,      0, 0, 1, 0, 1,      0, 1, 1, 0},    // Cordoba
        {0, 0, 0, 0, 0,     0, 0, 0, 0, 0,      0, 0, 0, 0, 0,      0, 0, 0, 0, 0,      0, 0, 0, 1, 0,      1, 1, 0, 0},    // Sevilla

        {0, 0, 0, 0, 0,     0, 0, 0, 0, 0,      0, 0, 0, 0, 0,      0, 0, 0, 0, 0,      0, 0, 0, 0, 1,      0, 0, 0, 0},    // Cadiz
        {0, 0, 0, 0, 0,     0, 0, 0, 0, 0,      0, 0, 0, 0, 0,      0, 0, 0, 0, 0,      0, 0, 0, 1, 1,      0, 0, 1, 0},    // Malaga
        {0, 0, 0, 0, 0,     0, 0, 0, 0, 0,      0, 0, 0, 0, 0,      0, 0, 0, 0, 0,      0, 0, 0, 1, 0,      0, 1, 0, 1},    // Granada
        {0, 0, 0, 0, 0,     0, 0, 0, 0, 0,      0, 0, 0, 0, 0,      0, 0, 0, 0, 0,      0, 1, 0, 0, 0,      0, 0, 1, 0}     // Almeria
    };

    isAdjacencyMatrixCorrect(adjacencyMatrixGraph,
                             sizeof(adjacencyMatrixGraph) / sizeof (adjacencyMatrixGraph[0]),
                             sizeof(adjacencyMatrixGraph[0]) / sizeof(int));



    printDFS(unweightedGraph, "Madrid");
    //printDFS(unweightedGraph, "Requena");
    //printDFS(unweightedGraph, "Sevilla");

    printBFS(unweightedGraph, "Madrid");
    //printBFS(unweightedGraph, "Requena");
    //printBFS(unweightedGraph, "Sevilla");

    printShortestRoute(unweightedGraph, "Cadiz", "Oviedo");
    //printShortestRoute(unweightedGraph, "Almeria", "Vitoria");

    printf("The graph is %s\n\n", hasCycle(unweightedGraph) ? "Cyclic" : "Acyclic");

    unordered_map<string, vector<string>> prim = primMST(unweightedGraph);
    printGraph(prim);
}