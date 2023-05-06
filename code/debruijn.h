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
    Node max_edge;
    std::map<std::string, Node> graph;
    void chopString(int kmer_length, string fname);
    void createGraph();
    void formatGraph(); // Only to be used on the big file.
    void outputGraph();
    void traversal(); 
    void connectedComponents();
    void longestConnectedSequence();
    std::string longestSequence();


    private:
    void DFS(Node n, std::map<string, bool>& visited);
    void DFS(Node n, std::map<string, bool>& visited, std::string& long_sequence, std::string& current_sequence);
    
    

};