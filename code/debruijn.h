#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <unordered_map>

#include "./readFile.h"

using namespace std;

struct Edge;

struct Node {
    std::string data;
    std::vector<Edge> outgoingEdges;
};

struct Edge {
    Node incoming;
    Node outgoing;
    int occurrences;
};








class DeBruijnGraph {
    public :
    std::vector<string> kmers;
    // std::
    // std::vector<Node> graph;
    std::unordered_map<std::string, Node> graph;
    void chopString(int kmer_length, string fname);
    void createGraph();
    // void 
    // void 
};