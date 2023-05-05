#include "./debruijn.h"

void DeBruijnGraph::chopString(int kmer_length, string fname) {
    ReadFile reads;
    reads.readsfiles(fname); 

    // ; 
    for(size_t i = 0; i <= reads.extracted_sequence.length() - kmer_length; i++) {
        kmers.push_back(reads.extracted_sequence.substr(i, kmer_length));

       // std::cout << i << "  N   \n";
    }

    std::cout << " kMers formatted succesfully   \n";
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

        // std::cout << i << "         B \n";      
    }

    // gra

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

     std::cout << " Graph Created Succesfully    \n";

    

    //Printing Graph



    // for(auto& keyval: graph) {
    //     std::cout << "Node: " << keyval.first << " \t";

    //     std::cout << "Edges: \n";

    //     for(Edge& E: keyval.second.outgoingEdges) {
    //         std::cout << " Outgoing Edge: " << E.outgoing.data << " Weight: " << E.occurrences << "\n";
    //     }
    // }

}

void DeBruijnGraph::formatGraph() {

    std::map<std::string, Node>::iterator it;
    for(auto& keyval: graph) {
        // std::cout << "Node: " << keyval.first << " \n";
        // for(Edge& E: keyval.second.outgoingEdges) {
        //         // std::cout << " Outgoing Edge: " << E.outgoing.data << " Weight: " << E.occurrences << "\n";
        // }

        std::vector<Edge> new_;

        for(size_t i = 0; i < keyval.second.outgoingEdges.size(); i++) {
            if(keyval.second.outgoingEdges.at(i).occurrences > 1) new_.push_back(keyval.second.outgoingEdges.at(i));
        }

        keyval.second.outgoingEdges.clear();

        for(Edge e: new_) keyval.second.outgoingEdges.push_back(e);

        // if(keyval.second.outgoingEdges.empty()) {
        //     rase(it);it = graph.find(keyval.first);
        //     graph.e
        // }




        
        // for(auto it = keyval.second.outgoingEdges.begin(); it != std::vector<Edge>::iterator();) {
        //     std::cout << 0 << "\n";
        //     if((it)->occurrences == 0) break;

        //     if((it)->occurrences == 1) {
        //         std::cout << 1 << "\n";
        //         auto copy = it + 1;
        //         std::cout << 3 << "\n";
        //         keyval.second.outgoingEdges.erase(it);
        //         it = copy;
        //         std::cout << 2 << "\n";
        //         continue;
        //     }

        //     // if()
        //     it++;
        // }
    }

    std::map<string, Node>::iterator itr = graph.begin();
    while (itr != graph.end()) {
        if ((*itr).second.outgoingEdges.empty()) {
        itr = graph.erase(itr);
        } else {
        ++itr;
        }
    }

    
}

void DeBruijnGraph::outputGraph() {
    // std::string message = "Hello, world!";
    std::ofstream outputFile("data/outputGraph.txt");

    if (outputFile.is_open()) {

        for(auto& keyval: graph) {
            outputFile << "Node: " << keyval.first << " \t";

            

            outputFile << "Edges: \n";

            for(Edge& E: keyval.second.outgoingEdges) {
                outputFile << " Outgoing Edge: " << E.outgoing.data << " Weight: " << E.occurrences << "\n";
            }
        }

        
        outputFile.close();
        std::cout << "Message saved to data/output.txt." << std::endl;
    }
    else {
        std::cout << "Unable to open output file." << std::endl;
    }
}

