#include <iostream>
#include <fstream>
#include <string>

#include "code/readFile.h"
#include "code/debruijn.h"



using namespace std;

int main() {
    string filename;
    cout << "Enter the filename: ";
    getline(cin, filename);
    int kmer_length;
    cout << "Enter the length of the kmers: ";
    cin >> kmer_length;

    DeBruijnGraph dbg;
    dbg.chopString(kmer_length, filename);

    dbg.createGraph(); 

    std::cout << "GRAPH CREATED \n";

    dbg.formatGraph(); 

    dbg.outputGraph();

    // dbg.traversal();
    dbg.connectedComponents();

    std::cout << dbg.longestSequence();
    




    // ReadFile data;
    // data.readsfiles(filename);



    
    
    return 0;
}
