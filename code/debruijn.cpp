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

    int max_edges = 0;

    for(auto& keyval: graph) {
        // std::cout << "Node: " << keyval.first << " \n";
        // for(Edge& E: keyval.second.outgoingEdges) {
        //         // std::cout << " Outgoing Edge: " << E.outgoing.data << " Weight: " << E.occurrences << "\n";
        // }

        std::vector<Edge> new_;

        int sum = 0;

        for(size_t i = 0; i < keyval.second.outgoingEdges.size(); i++) {
            if(keyval.second.outgoingEdges.at(i).occurrences > 1) {
                new_.push_back(keyval.second.outgoingEdges.at(i));
                sum += keyval.second.outgoingEdges.at(i).occurrences;
            }
        }



        keyval.second.outgoingEdges.clear();

        for(Edge e: new_) keyval.second.outgoingEdges.push_back(e);

        if(sum > max_edges) {
            max_edges = sum;
            max_edge = keyval.second;
        }

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


void DeBruijnGraph::traversal() {
    std::map<string, bool> visited;
    // std::map<string, Node>::iterator itr = graph.begin();

    Node iter = max_edge;
    visited.insert({iter.data, true});

    std::string formed_output = "";

    do {
        formed_output += iter.data;
        Node next_node;
        int max = 0;
        for(Edge& e: iter.outgoingEdges) {
            if(e.occurrences > max) {
                max = e.occurrences;
                next_node = e.outgoing;
            }
        }

        if(next_node.data != "") iter = next_node;
        else break;

    } while(visited.count(iter.data) == 0);


    std::cout << formed_output << "\n";
}


void DeBruijnGraph::DFS(Node n, std::map<string, bool>& visited) {
    std::cout << "DFS on Node : " << n.data << " \n";

    visited.insert({n.data, true});

    for(Edge& e: n.outgoingEdges) {
        string outgoing = e.outgoing.data;
        cout << "Outgoing Edges:" << e.outgoing.data<< "\n";
        if(visited.count(outgoing) == 0 ) {
            cout << "Calling for more DFS :" << e.outgoing.data<< "\n";
            if(graph.count(e.outgoing.data) > 0) DFS(graph.at(e.outgoing.data), visited);
        }
    }
}

void DeBruijnGraph::connectedComponents() {
    int connected = 0;
    std::map<string, bool> visited;
    std::map<string, Node>::iterator itr = graph.begin();

    while (itr != graph.end()) {

        std::cout << "Current Node : " << (*itr).first << "\n";

        if(visited.count((*itr).first) == 0) {
            connected++;
            DFS((*itr).second, visited);
        }
        itr++;
    }

    std::cout << "Connected Components : " << connected << "\n";
}




void DeBruijnGraph::DFS(Node n, std::map<string, bool>& visited, std::string& long_sequence, std::string& current_sequence) {
    visited.insert({n.data, true});
    current_sequence += n.data;

    if(long_sequence.size() < current_sequence.size()) long_sequence = current_sequence;

    for(Edge& e : n.outgoingEdges) {
        
        if(visited.count(e.outgoing.data) == 0) {
            std::cout << e.outgoing.data << "\n";
            if(graph.count(e.outgoing.data) > 0) DFS(graph.at(e.outgoing.data), visited, long_sequence, current_sequence);
            else break;
        }
    }

    // visited.erase(n.data);

}


std::string DeBruijnGraph::longestSequence() {
    // int n = graph.size();
    // vector<int> visited(n, 0), path, longestPath;

    // for()

    // for (int u = 0; u < n; u++) {
    //     if (!visited[u]) {
    //         dfs(graph, u, visited, path, longestPath);
    //     }
    // }

    // std:

    std::map<string, bool> visited;

    std::string current, longest;


    for(auto& keyval: graph) {
        std::cout << keyval.first << "\n";
            if(visited.count(keyval.first) == 0) {
                DFS(keyval.second, visited, longest, current);
            }
            
    }


    // return longestPath;
    return longest;
}



