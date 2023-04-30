#include "./debruijn.h"

void DeBruijnGraph::chopString(int kmer_length, string fname) {
    ReadFile reads;
    reads.readsfiles(fname); 

    // ; 
    for(size_t i = 0; i <= reads.extracted_sequence.length() - kmer_length; i++) {
        kmers.push_back(reads.extracted_sequence.substr(i, kmer_length));
    }
    // for(auto kmer: kmers) {
    //     std::cout << kmer << "\n";
    // }

}

void DeBruijnGraph::createGraph() {
    size_t size_of_graph = kmers.size();

    for(size_t i = 0; i < size_of_graph; i++) {
        Node to_add;
        to_add.data = kmers.at(i);
        to_add.outgoingEdges = {};

        if(! graph.count(kmers.at(i))) graph.insert({kmers.at(i), to_add});        
    }

    for(size_t i = 0; i < size_of_graph - 1; i++) {
        // Node* to_edit 
        string current_kmer = kmers.at(i);
        string next_kmer = kmers.at(i+1);

        Node& current_node = graph.at(current_kmer);
        Node& next_node = graph.at(next_kmer);

        bool itAlreadyExists = false;

        for(Edge& e: current_node.outgoingEdges) {
            if(e.outgoing.data == next_kmer) {
                itAlreadyExists = true;
                e.occurrences++;
                break;
            }
        }

        if(! itAlreadyExists) {
            Edge to_add;
            to_add.incoming = current_node;
            to_add.outgoing = next_node;
            to_add.occurrences = 1;

            current_node.outgoingEdges.push_back(to_add);
        }
        
    }

    

    //Printing Graph

    for(auto& keyval: graph) {
        std::cout << "Node: " << keyval.first << " \t";

        std::cout << "Edges: \n";

        for(Edge& E: keyval.second.outgoingEdges) {
            std::cout << " Outgoing Edge: " << E.outgoing.data << " Weight: " << E.occurrences << "\n";
        }
    }

}

