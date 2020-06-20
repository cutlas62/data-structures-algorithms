#include <cstdio>
#include <vector>
#include <unordered_map>
#include <stack>
#include <set>
#include <deque>

using namespace std;

// Compiled using 'g++ graph.cpp -o graph' and executed using './graph' on Ubuntu 20.04
// SpanishCitiesGraph.png was used as the test graph


void printDFS (unordered_map<string, vector<string>> graph, string startNode)
{
    printf("\nDFS\n");
    if (graph.count(startNode) == 0)
    {
        throw invalid_argument("startNode is not in the graph");
    }

    stack<string> nodesToVisit;
    nodesToVisit.push(startNode);
    set<string> visitedNodes;

    while (!nodesToVisit.empty())
    {
        string curNode = nodesToVisit.top();
        nodesToVisit.pop();
        visitedNodes.insert(curNode);
        printf("%s ", curNode.c_str());

        for (string neighbor : graph.find(curNode)->second)
        {
            if (!visitedNodes.count(neighbor))
            {
                nodesToVisit.push(neighbor);
            }
        }
    }
    printf("\n");
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
        {"Alicante", {"Valencia", "Requena", "Albacete"}},
        {"Puertollano", {"Madrid", "Cordoba"}},
        {"Cordoba", {"Puertollano", "Sevilla", "Malaga", "Granada"}},
        {"Sevilla", {"Cordoba", "Cadiz", "Malaga"}},
        {"Cadiz", {"Sevilla"}},
        {"Malaga", {"Granada", "Cordoba", "Sevilla"}},
        {"Granada", {"Cordoba", "Malaga", "Almeria"}},
        {"Almeria", {"Granada", "Alicante"}}
    };


    printDFS(unweightedGraph, "Madrid");

}